/*
 *  BasicScreenObject.cpp
 *  BasicScreenObject_Test
 *
 *  Created by Matthias Rohrbach 2 on 10.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "BasicScreenObject.h"
#include "Renderer.h"

BasicScreenObject::BasicScreenObject(){
	
	ofAddListener(ofEvents().setup, this, &BasicScreenObject::_setup);
	ofAddListener(ofEvents().update, this, &BasicScreenObject::_update);
	ofAddListener(ofEvents().exit, this, &BasicScreenObject::_exit);
	ofAddListener(killEvent,this , &BasicScreenObject::onKill);
	ofAddListener(hideEvent, this, &BasicScreenObject::onHide);
	ofAddListener(showEvent, this, &BasicScreenObject::onShow);
	
	
	masktype=MASK_TYPE_CLIPPLANES;
	ismask = false;
	hasmask = false;
	
	
	setPosition(0,0,0);
	speed.set(0,0,0);
	accel.set(0,0,0);
	moveattractionforce=0;
	movedrag=1;
	
	
	setScale(1, 1, 1);
	width = height = 10;
	setAnchorPoint(0, 0, 0);
	
	
	alpha = 255;
	setColor(255,255,255);
	tweenr=255;
	tweeng=255;
	tweenb=255;
	
	
	// Rotation
	rotationdrag=0.99;
	rotationspeed.set(0,0,0);
	
	
	setRotationSpeed(0, 0, 0);
	setRotationDrag(0.99);
	rotationattractionforce=0;
	rotationattractionquat.set(0,0,0,1);
	rotationattractionangles.set(0,0,0);
	
	
	lightingbefore=false;
	lightingenabled=false;
	depthtestbefore=false;
	depthtestenabled=false;
	
	
	age=0;
	isadded=false;
	issetup=false;
	bool issetup; // TODO: issetup needed??

	
	parent_so=NULL;
	root = NULL;
	
	tweener.addListener(this);
	myEventArgs.target=this;
	
	sfactor=GL_SRC_ALPHA;
	dfactor=GL_ONE_MINUS_SRC_ALPHA;
		
	tweenx=0;
	tweeny=0;
	tweenz=0;
	tweenscalex=0;
	tweenscaley=0;
	tweenscalez=0;
	tweenrotslerp = 0.0;
	
	
	isvisible = true;
	isinteractive = false;
	isorderbyz=false;
	isupdating=true;
}


BasicScreenObject::~BasicScreenObject() {
	childlist.clear();
	ofRemoveListener(ofEvents().setup, this, &BasicScreenObject::_setup);
	ofRemoveListener(ofEvents().update, this, &BasicScreenObject::_update);
	ofRemoveListener(ofEvents().exit, this, &BasicScreenObject::_exit);
	ofRemoveListener(killEvent,this , &BasicScreenObject::onKill);
	ofRemoveListener(showEvent, this, &BasicScreenObject::onShow);
	ofRemoveListener(hideEvent, this, &BasicScreenObject::onHide);
}



/********************************************************
 *
 *	RENDERING
 *
 ********************************************************/


void BasicScreenObject::enableDepthTest(){ depthtestenabled=true;}
void BasicScreenObject::disableDepthTest(){ depthtestenabled=false; }


void BasicScreenObject::enableLighting(){ lightingenabled=true; }
void BasicScreenObject::disableLighting(){ lightingenabled=false; }


void BasicScreenObject::setBlendFactors(float _sfactor, float _dfactor){
	sfactor=_sfactor;
	dfactor=_dfactor;	
}


bool BasicScreenObject::isUpdating() { return isupdating;}
void BasicScreenObject::isUpdating(bool _isupdating) { isupdating = _isupdating; }


void BasicScreenObject::killMeSoftly(float _time){
	killingtimer.setup(_time/1000, false);
	killingtimer.stopTimer();
	ofAddListener(killingtimer.TIMER_REACHED, this, &BasicScreenObject::killingAfterTimer);
	killingtimer.startTimer();
}


void BasicScreenObject::killingAfterTimer(ofEventArgs &event){
	ofNotifyEvent(killEvent, myEventArgs, this);
	_onKill();
}


void BasicScreenObject::onKill(BasicScreenObjectEvent &event){ _onKill(); }
void BasicScreenObject::_onKill(){ }



/********************************************************
 *
 *	EVENTS TRIGGERED BY OF
 *
 ********************************************************/


void BasicScreenObject::_setup(ofEventArgs &e){
	issetup=true;
	setup();
}


void BasicScreenObject::_update(ofEventArgs &e){
	if(!isupdating)return;
	if(age==1){
		firstUpdate();
	}
	
	// Update Animations based on Tweening
    tweener.step(ofGetElapsedTimeMillis());
	
	if (moveParam.started) {
		
	}
	
	// Animations based on Forces and Attractionpoints
	doRotate();
	doMove();
	
	if(isorderbyz){
		doOrderChildrenByZ();
	}
	
	
	update();
	
	if(positioners.size()>0){
		
		for(positioner = positioners.begin(); positioner != positioners.end(); positioner++) {
			IPositioner* p = positioner->second;
			p->restrict(this);
		}
	}	
	
	age++;	
}


void BasicScreenObject::_exit(ofEventArgs &e){
	exit();
}



/********************************************************
 *
 *	SCENEGRAPH
 *
 ********************************************************/


BasicScreenObject* BasicScreenObject::getParent() { 
	if(parent_so)
		return parent_so; 
	return this;
}


void BasicScreenObject::setParent(BasicScreenObject* _parent){
	isadded=true;
	parent_so=_parent;
	setParent(* dynamic_cast<ofNode*> (_parent));
}


BasicScreenObject* BasicScreenObject::getRoot(){
	if(parent_so==NULL){
		root=this;
		return root;
	}
	return parent_so->getRoot();
}


void BasicScreenObject::setRoot(BasicScreenObject* _root){
	root=_root;
	
	if (root->getName() == "Renderer") {
		Renderer* renderer = (Renderer*)root;
		pickingName = renderer->getNextPickingName(this);
	}
	
	for (int i = 0; i < childlist.size(); i++) {
		BasicScreenObject* elm = childlist.at(i);
		elm->setRoot(_root);
	}
}


void BasicScreenObject::addChild(BasicScreenObject* _child){
	childlist.push_back(_child);
	_child->setParent(this);
	_child->setRoot(getRoot());
}


// TODO: implement BasicScreenObject::addChildAt
void BasicScreenObject::addChildAt(BasicScreenObject* _child, int _index){ }


void BasicScreenObject::removeChild(BasicScreenObject* _child){
	for(int i=0;i<childlist.size();i++){
		if(childlist[i]==_child){
			_child->clearParent();
			childlist.erase(childlist.begin()+i);
			break;
		}
	}
}


void BasicScreenObject::removeChildren(){ childlist.resize(0); }


// TODO: implement BasicScreenObject::removeChildAt
void BasicScreenObject::removeChildAt(BasicScreenObject* _child, int _index){ }


void BasicScreenObject::moveMeToTop(){
	if(parent_so!=NULL){
		parent_so->moveChildToTop(this);
	}
}


void BasicScreenObject::moveChildToTop(BasicScreenObject* _child){
	removeChild(_child);
	addChild(_child);
}


vector<BasicScreenObject*>* BasicScreenObject::getChildren(){ return &childlist; }


bool BasicScreenObject::isAdded(){ return isadded; }


void BasicScreenObject::isOrderChildrenByZ(bool _isorderbyz){ isorderbyz=_isorderbyz; }
bool BasicScreenObject::isOrderChildrenByZ(){ return isorderbyz; }


// TODO: Cameraabhängig machen
void BasicScreenObject::doOrderChildrenByZ(){
	//std::sort(childlist.begin(), childlist.end(), compareZ());
}



/********************************************************
 *
 *	DRAWING FUNCTIONS
 *
 *	invoked by the parent or the root/renderer
 *
 ********************************************************/


void BasicScreenObject::draw(){
	if (getCombinedVisible()) {
		
		glPushMatrix();
		glMultMatrixf(getLocalTransformMatrix().getPtr());		
		
		setupMask();
        
		glBlendFunc(sfactor, dfactor);
				
		lightingbefore=glIsEnabled(GL_LIGHTING);
		depthtestbefore=glIsEnabled(GL_DEPTH_TEST);
		
		if(depthtestenabled && !depthtestbefore)glEnable(GL_DEPTH_TEST);
		if(!depthtestenabled && depthtestbefore)glDisable(GL_DEPTH_TEST);
		
		if(lightingenabled && !lightingbefore)glEnable(GL_LIGHTING);
		if(!lightingenabled && lightingbefore)glDisable(GL_LIGHTING);
		
		
		ofPushMatrix();
		ofPushStyle();
		ofSetColor(color.r,color.g,color.b,getCombinedAlpha());
		_draw();
		ofPopStyle();
		ofPopMatrix();
		
		ofPushMatrix();
		drawChildren();
		ofPopMatrix();
		
		ofPushMatrix();
		_drawAfterChildren();
		ofPopMatrix();
		
		// lighting out
		if(lightingenabled && !lightingbefore)glDisable(GL_LIGHTING);
		if(!lightingenabled && lightingbefore)glEnable(GL_LIGHTING);
		
		// Depthtest out
		if(depthtestenabled && !depthtestbefore)glDisable(GL_DEPTH_TEST);
		if(!depthtestenabled && depthtestbefore)glEnable(GL_DEPTH_TEST);
				
		restoreMask();
		
		glPopMatrix();
	}
}

void BasicScreenObject::_draw(ofEventArgs &e){ _draw(); }


void BasicScreenObject::drawChildren(){
	for (int i = 0; i < childlist.size(); i++)
	{
		BasicScreenObject* elm = childlist.at(i);
		elm->draw();
	}
}


void BasicScreenObject::drawForPicking(){
	if (getCombinedVisible()) {
		
		glPushMatrix();
		glMultMatrixf(getLocalTransformMatrix().getPtr());
		
		setupMask();
		
		depthtestbefore=glIsEnabled(GL_DEPTH_TEST);
		if(depthtestenabled && !depthtestbefore)glEnable(GL_DEPTH_TEST);
		if(!depthtestenabled && depthtestbefore)glDisable(GL_DEPTH_TEST);
		
		if(isinteractive){
			ofPushStyle();
			ofColor pickingColor = pickingNameToColor(pickingName);
			ofSetColor(pickingColor.r, pickingColor.g, pickingColor.b);
			_drawForPicking();
			ofPopStyle();			
		}
		
		drawChildrenForPicking();
		
		if(depthtestenabled && !depthtestbefore){
			glDisable(GL_DEPTH_TEST);
		}
		if(!depthtestenabled && depthtestbefore){
			glEnable(GL_DEPTH_TEST);
		}
		restoreMask();		
		glPopMatrix();
	}
}


void BasicScreenObject::drawChildrenForPicking(){
	for (int i = 0; i < childlist.size(); i++)
	{
		BasicScreenObject* elm = childlist.at(i);
		elm->drawForPicking();
	}
}


/********************************************************
 *
 *	COORDINATE SYSTEM HELPERS
 *
 ********************************************************/


ofVec3f BasicScreenObject::localToGlobal(ofVec3f _local){
	ofVec3f origpoint(_local);
	ofMatrix4x4 global=getGlobalTransformMatrix();	
	origpoint=origpoint*global;	
	return origpoint;
}

ofVec3f BasicScreenObject::localToGlobal(float _x, float _y, float _z){
	ofVec3f local(_x, _y, _z);
	return localToGlobal(local);	
}

ofVec3f BasicScreenObject::globalToLocal(ofVec3f _global){
	ofVec3f origpoint(_global);
	ofMatrix4x4 local=getParent()->getGlobalTransformMatrix().getInverse();
	origpoint=origpoint*local;
	return origpoint;
}

ofVec3f BasicScreenObject::globalToLocal(float _x, float _y, float _z){
	ofVec3f globalpoint(_x, _y, _z);
	return globalToLocal(globalpoint);
}

ofVec3f BasicScreenObject::globalToLocalDir(ofVec3f _globaldir){
	ofMatrix4x4 local=getParent()->getGlobalTransformMatrix().getInverse();
	local.setTranslation(0, 0, 0);
	return _globaldir*local;	
}

ofVec3f BasicScreenObject::foreignToLocal(BasicScreenObject* _foreign, ofVec3f _foreignpos){
	ofMatrix4x4 inv=getGlobalTransformMatrix().getInverse();
	ofMatrix4x4 trans=_foreign->getGlobalTransformMatrix();
	trans.postMult(inv);
	return _foreignpos*trans;
}

ofVec3f BasicScreenObject::foreignToLocal(BasicScreenObject* _foreign, float _x, float _y, float _z){
	return foreignToLocal(_foreign, ofVec3f(_x, _y, _z));
}

ofVec3f BasicScreenObject::localToForeign(BasicScreenObject* _foreign, ofVec3f _local){
	ofMatrix4x4 inv=_foreign->getGlobalTransformMatrix().getInverse();
	ofMatrix4x4 trans=getGlobalTransformMatrix();
	trans.postMult(inv);
	return _local*trans;
}

ofVec3f BasicScreenObject::localToForeign(BasicScreenObject* _foreign, float _x, float _y, float _z){
	return localToForeign(_foreign, ofVec3f(_x, _y, _z));
}



ofRectangle BasicScreenObject::getBoundingBox(BasicScreenObject* ref){
	
	ofVec2f screenpos[4];
 	
	screenpos[0]=localToForeign(ref, 0, 0, 0);
	screenpos[1]=localToForeign(ref,width, 0, 0);
	screenpos[2]=localToForeign(ref,width, height, 0);
	screenpos[3]=localToForeign(ref,0, height, 0);
	
	float smallestx=100000;
	float smallesty=100000;
	float biggestx=-100000;
	float biggesty=-100000;
	
	for(int i=0;i<4;i++){
		ofVec2f spos=screenpos[i];
		
		if(spos.x>biggestx){
			biggestx=spos.x;
		}
		if(spos.x<smallestx){
			smallestx=spos.x;
		}
		if(spos.y>biggesty){
			biggesty=spos.y;
		}
		if(spos.y<smallesty){
			smallesty=spos.y;
		}
	}
	
	ofRectangle boundingbox;
	boundingbox.x=smallestx;
	boundingbox.y=smallesty;
	
	boundingbox.width=biggestx-smallestx;
	boundingbox.height=biggesty-smallesty;
	
	return boundingbox;
	
}

ofVec3f BasicScreenObject::getScreenPosition(){
	Renderer* r=(Renderer*)getRoot();	
	ofVec3f screenpos=r->getCamera()->worldToScreen(getGlobalPosition());
	return screenpos;
}

ofRectangle BasicScreenObject::getScreenBoundingBox(){
	Renderer* r=(Renderer*)getRoot();
	ofVec2f screenpos[4];
 	
	screenpos[0]=r->getCamera()->worldToScreen(localToGlobal(0, 0, 0));
	screenpos[1]=r->getCamera()->worldToScreen(localToGlobal(width, 0, 0));
	screenpos[2]=r->getCamera()->worldToScreen(localToGlobal(width, height, 0));
	screenpos[3]=r->getCamera()->worldToScreen(localToGlobal(0, height, 0));
	
	float smallestx=100000;
	float smallesty=100000;
	float biggestx=-100000;
	float biggesty=-100000;
	
	for(int i=0;i<4;i++){
		ofVec2f spos=screenpos[i];
		
		if(spos.x>biggestx){
			biggestx=spos.x;
		}
		if(spos.x<smallestx){
			smallestx=spos.x;
		}
		if(spos.y>biggesty){
			biggesty=spos.y;
		}
		if(spos.y<smallesty){
			smallesty=spos.y;
		}
	}
	
	ofRectangle boundingbox;
	boundingbox.x=smallestx;
	boundingbox.y=smallesty;
	
	boundingbox.width=biggestx-smallestx;
	boundingbox.height=biggesty-smallesty;
	
	return boundingbox;
	
}

/********************************************************
 *
 *	VISIBILITY
 *
 ********************************************************/


bool BasicScreenObject::isVisible() { return isvisible; }
void BasicScreenObject::isVisible(bool _visible) { isvisible = _visible; }


void BasicScreenObject::hide(){
	isVisible(false);
	setAlpha(0);
	ofNotifyEvent(hideEvent, myEventArgs, this);
}

void BasicScreenObject::hide(float _time){
	fadeTo(0, _time);
	visibletimer.setup(_time/1000, false);
	visibletimer.stopTimer();
	ofAddListener(visibletimer.TIMER_REACHED, this, &BasicScreenObject::hideAfterTimer);
	visibletimer.startTimer();
}

void BasicScreenObject::hideAfterTimer(ofEventArgs &event){
	ofRemoveListener(visibletimer.TIMER_REACHED, this, &BasicScreenObject::hideAfterTimer);
	hide();
}

void BasicScreenObject::show(){
	ofNotifyEvent(showEvent, myEventArgs, this);	
	ofRemoveListener(visibletimer.TIMER_REACHED, this, &BasicScreenObject::hideAfterTimer);
	isVisible(true);
	setAlpha(255);
}

void BasicScreenObject::show(float _time){
	ofNotifyEvent(showEvent, myEventArgs, this);
	ofRemoveListener(visibletimer.TIMER_REACHED, this, &BasicScreenObject::hideAfterTimer);
	isVisible(true);
	fadeTo(255, _time);
}

bool BasicScreenObject::getCombinedVisible(){
	bool parentvisible=true;
	if(parent_so!=NULL){
		parentvisible=parent_so->getCombinedVisible();
	}
	if(isvisible){
		return parentvisible;
	}else{
		return isvisible;
	}
}


/********************************************************
 *
 *	COLOR
 *
 ********************************************************/

void BasicScreenObject::setColor(float _r , float _g, float _b ){ color.set(_r, _g, _b); }
void BasicScreenObject::setColor(ofColor _c){ setColor(_c.r, _c.g, _c.b); }
ofColor BasicScreenObject::getColor() { return color; }

void BasicScreenObject::setNormalizedColor(ofColor _c){ setColor(_c.r*255.0, _c.g*255.0, _c.b*255.0); }

void BasicScreenObject::setRandomColor(){ setColor(ofRandom(0,255), ofRandom(0, 255), ofRandom(0, 255)); }

void BasicScreenObject::setAlpha(float _a){ alpha=_a; }
float BasicScreenObject::getAlpha() { return alpha; }

float BasicScreenObject::getCombinedAlpha(){
	float combinedbalpha;
	if(parent!=NULL){
		combinedbalpha=(alpha/255.0)*parent_so->getCombinedAlpha();
	}else{
		combinedbalpha=alpha;
	}
	return combinedbalpha;
}



/********************************************************
 *
 *	MASK
 *
 ********************************************************/

// TODO: using STENCIL_MASK, drawForPicking() is not masked

void BasicScreenObject::isMask(bool _ismask){ ismask = _ismask; }
bool BasicScreenObject::isMask() { return ismask; }


void BasicScreenObject::hasMask(bool _hasmask){ hasmask = _hasmask; }
bool BasicScreenObject::hasMask() { return hasmask; }


void BasicScreenObject::setMaskObject(BasicScreenObject* _maskobject){
	maskobject=_maskobject;
	maskobject->isMask(true);
	maskobject->disableDepthTest();
	hasMask(true);
}


BasicScreenObject* BasicScreenObject::getMaskObject() { return maskobject; }


void BasicScreenObject::setupMask(){
	if(hasMask()){
		if(masktype==MASK_TYPE_STENCIL){
			glClear(GL_STENCIL_BUFFER_BIT );
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_ALWAYS, 0x1, 0x1);
			glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
			glColorMask(0,0,0,0);
			glDisable(GL_DEPTH_TEST);
			maskobject->disableDepthTest();
			maskobject->draw();
			glColorMask(1,1,1,1);
			glStencilFunc(GL_EQUAL, 0x1, 0x1);
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		}else if(masktype==MASK_TYPE_SCISSOR){
			glEnable(GL_SCISSOR_TEST);
			ofVec3f maskpos=maskobject->localToGlobal(0,0,0);
			maskpos.y=ofGetHeight()-maskpos.y-maskobject->getHeight();
			
			glScissor(maskpos.x, maskpos.y,maskobject->getWidth(), maskobject->getHeight());
		}else if(masktype==MASK_TYPE_CLIPPLANES){
			GLdouble eq0[]={1,0,0,-maskobject->getPosition().x};
			GLdouble eq1[]={0,1,0,-maskobject->getPosition().y};
			GLdouble eq2[]={-1,0,0,maskobject->getWidth()-maskobject->getPosition().x};
			GLdouble eq3[]={0,-1,0,maskobject->getHeight()-maskobject->getPosition().y};				
			glClipPlane(GL_CLIP_PLANE0,eq0);
			glClipPlane(GL_CLIP_PLANE1,eq1);
			glClipPlane(GL_CLIP_PLANE2,eq2);
			glClipPlane(GL_CLIP_PLANE3,eq3);
			glEnable(GL_CLIP_PLANE0);
			glEnable(GL_CLIP_PLANE1);
			glEnable(GL_CLIP_PLANE2);
			glEnable(GL_CLIP_PLANE3);
		}
	}
}


void BasicScreenObject::restoreMask(){
	if(hasMask()){
		if(masktype==MASK_TYPE_STENCIL){
			glDisable(GL_STENCIL_TEST);
		}else if(masktype==MASK_TYPE_SCISSOR){
			glDisable(GL_SCISSOR_TEST);
		}else if(masktype==MASK_TYPE_CLIPPLANES){
			glDisable(GL_CLIP_PLANE0);
			glDisable(GL_CLIP_PLANE1);
			glDisable(GL_CLIP_PLANE2);
			glDisable(GL_CLIP_PLANE3);
		}
	}	
}



/********************************************************
 *
 *	OFFSET
 * 
 *  TODO: Offsets, what is this used for, how to use it?
 *
 ********************************************************/


void BasicScreenObject::setOffset(float _x, float _y, float _z){ offset.set(_x, _y, _z); }
void BasicScreenObject::setOffset(ofVec3f _offset){ setOffset(_offset.x, _offset.y, _offset.z); }



/********************************************************
 *
 *	ANCHOR POINT
 * 
 *  TODO: Think and wait.
 *
 ********************************************************/


void BasicScreenObject::setAnchorPoint(float _x, float _y, float _z){ anchorpoint.set(_x, _y, _z); }
void BasicScreenObject::setAnchorPoint(ofVec3f _anchor){ setAnchorPoint(_anchor.x, _anchor.y, _anchor.z); }



/********************************************************
 *
 *	POSITION
 *
 ********************************************************/

void BasicScreenObject::setPosition(float _x, float _y){ setPosition(_x,_y,getZ()); }
void BasicScreenObject::setX(float _x){ setPosition(_x,getY(),getZ()); }
void BasicScreenObject::setY(float _y){ setPosition(getX(),_y,getZ()); }
void BasicScreenObject::setZ(float _z){ setPosition(getX(),getY(),_z); }

ofVec3f BasicScreenObject::getOffset() { return offset; }
ofVec3f BasicScreenObject::getAnchorPoint() { return anchorpoint; }



/********************************************************
 *
 *	SIZE
 *
 ********************************************************/


float BasicScreenObject::getWidth() { return width; }
float BasicScreenObject::getHeight() { return height; }


void BasicScreenObject::setSize(float _width, float _height){
	width=_width;
	height=_height;
}



/********************************************************
 *
 *	SCALE
 *
 ********************************************************/



/********************************************************
 *
 *	ROTATION
 *
 ********************************************************/


ofVec3f BasicScreenObject :: getOrientationAxisAngles()
{
	
	ofVec3f result;
	ofQuaternion q = getOrientationQuat();
	
	double x=q.x();
	double y=q.y();
	double z=q.z();
	double w=q.w();
	
	double sqw = w * w;
    double sqx = x * x;
    double sqy = y * y;
    double sqz = z * z;
	double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	double test = x * y + z * w;
	if( test > 0.499 * unit )    // singularity at north pole
	{
		
		result.y = 2 * atan2( x, w );
		result.z = PI / 2;
		result.x = 0;

	}
	else if( test < -0.499 * unit )    // singularity at south pole
	{
		result.y = -2 * atan2( x, w );
		result.z = -PI  /2;
		result.x = 0;

	} else {
	
		result.y = atan2( 2 * y * w - 2 * x * z, sqx - sqy - sqz + sqw );
		result.z = asin( 2 * test / unit );
		result.x = atan2( 2 * x * w - 2 * y * z , -sqx + sqy - sqz + sqw );
	}
	return result;
}

void BasicScreenObject::setOrientation(const ofQuaternion&	q, bool _inverse){
	ofNode::setOrientation(q);
}


void BasicScreenObject::setOrientation(float _xangle, float _yangle, float _zangle){
	qx.makeRotate(_xangle, ofVec3f(1,0,0));
	qy.makeRotate(_yangle, ofVec3f(0,1,0));
	qz.makeRotate(_zangle, ofVec3f(0,0,1));
	
	ofQuaternion nowquat;
	nowquat=qx*qy*qz;
	nowquat.normalize();
	setOrientation(nowquat);
}


ofVec3f BasicScreenObject::getOrientationAngles() const{
	ofVec3f euler=getOrientationEuler();
	return euler;	
}


void BasicScreenObject::addRotation(float _xangle, float _yangle, float _zangle){
	
	qx.makeRotate(_xangle, ofVec3f(1,0,0));
	qy.makeRotate(_yangle, ofVec3f(0,1,0));
	qz.makeRotate(_zangle, ofVec3f(0,0,1));
	
	ofQuaternion nowquat=getOrientationQuat();
	nowquat*=qx*qy*qz;
	nowquat.normalize();
	setOrientation(nowquat);
}


void BasicScreenObject::setRotationSpeed(float _xrot, float _yrot, float _zrot, float _drag){
	if(_drag>=0){
		setRotationDrag(_drag);
	}
	rotationspeed.set(_xrot, _yrot, _zrot);
}


void BasicScreenObject::addRotationSpeed(float _xrot, float _yrot, float _zrot, float _drag){
	if(_drag>=0){
		setRotationDrag(_drag);
	}
	rotationaccel.set(_xrot, _yrot, _zrot);
	rotationspeed=rotationspeed+rotationaccel;
}


void BasicScreenObject::setRotationAttractionAngles(float _x, float _y, float _z, float _force, bool _inverse){
	
	rotationattractionangles.set(_x, _y, _z);
	rotationattractionforce=_force;
	
	qx.makeRotate(_x, ofVec3f(1,0,0));
	qy.makeRotate(_y, ofVec3f(0,1,0));
	qz.makeRotate(_z, ofVec3f(0,0,1));
	rotationattractionquat=qx*qy*qz;
	rotationattractionquat.normalize();
	
	if(_inverse){
		rotationattractionquat=rotationattractionquat.inverse();
	}
}


void BasicScreenObject::stopRotationAttraction(){ rotationattractionforce=0; }


void BasicScreenObject::setRotationDrag(float _drag){ rotationdrag=_drag; }


void BasicScreenObject::setSpeed(float _x, float _y, float _z, float _drag){
	speed.set(_x, _y, _z);
	if(_drag>=0){
		movedrag=_drag;
	}
}


void BasicScreenObject::addSpeed(float _x, float _y, float _z, float _drag){
	setSpeed(speed.x+_x, speed.y+_y, speed.z+_z, _drag);
}



/********************************************************
 *
 *	TRANSITIONING
 *
 ********************************************************/


void BasicScreenObject::moveTo(float  _endx, float _endy, float _endz, float _movetime){
	//ofLog(OF_LOG_NOTICE, "move");
    setSpeed(0,0,0);
	endposition.set(_endx, _endy, _endz);
	tweener.removeTween(&moveParam);
	moveParam=tween::TweenerParam(_movetime,tween::CUBIC, tween::EASE_IN_OUT);
	moveParam.useMilliSeconds = true;
	tweenx=getX();
	tweeny=getY();
	tweenz=getZ();
	
	moveParam.addProperty(&tweenx, _endx);
	moveParam.addProperty(&tweeny, _endy);
	moveParam.addProperty(&tweenz, _endz);
	
	tweener.addTween(moveParam);
}


void BasicScreenObject::setMoveAttractionPoint(float _endx, float _endy, float _endz, float _force, float _drag){
	endposition.set(_endx, _endy, _endz);
	moveattractionforce=_force;
	movedrag=_drag;
}


void BasicScreenObject::stopMoveAttraction(){
	moveattractionforce=0;
}


void BasicScreenObject::fadeTo(float _endalpha , float _fadetime){
	tweener.removeTween(&fadeParam);
	visibletimer.stopTimer();
	fadeParam=tween::TweenerParam(_fadetime,tween::LINEAR, tween::EASE_IN_OUT);
	fadeParam.addProperty(&alpha, _endalpha);
	tweener.addTween(fadeParam);
}


void BasicScreenObject::growTo(float _endwidth, float _endheight, float _growtime){
	tweener.removeTween(&growParam);
	growParam=tween::TweenerParam(_growtime,tween::CUBIC, tween::EASE_IN_OUT);
	growParam.addProperty(&width, _endwidth);
	growParam.addProperty(&height, _endheight);
	tweener.addTween(growParam);
}


void BasicScreenObject::scaleTo(float _endxscale, float _endyscale, float _endzscale, float _scaletime){
	tweener.removeTween(&scaleParam);
	scaleParam=tween::TweenerParam(_scaletime,tween::CUBIC, tween::EASE_IN_OUT);
	tweenscalex=getScale().x;
	tweenscaley=getScale().y;
	tweenscalez=getScale().z;
	
	scaleParam.addProperty(&tweenscalex, _endxscale);
	scaleParam.addProperty(&tweenscaley, _endyscale);
	scaleParam.addProperty(&tweenscalez, _endzscale);
	tweener.addTween(scaleParam);
}


void BasicScreenObject::uniformScaleTo(float _endscale, float _scaletime){
    scaleTo(_endscale, _endscale, _endscale, _scaletime);
}


void BasicScreenObject::colorTo(float _endr, float _endg, float _endb, float _colortime){
	tweener.removeTween(&colorParam);
	colorParam=tween::TweenerParam(_colortime,tween::CUBIC, tween::EASE_IN_OUT);
	tweenr=color.r;
	tweeng=color.g;
	tweenb=color.b;
	
	colorParam.addProperty(&tweenr, _endr);
	colorParam.addProperty(&tweeng, _endg);
	colorParam.addProperty(&tweenb, _endb);
	
	tweener.addTween(colorParam);
}


void BasicScreenObject::colorTo(ofColor _endc, float _colortime){
	colorTo(_endc.r,_endc.g,_endc.b,_colortime);
}


void BasicScreenObject::rotateTo(float _x, float _y, float _z,float _rotatetime ){
	
	qx.makeRotate(_x, ofVec3f(1,0,0));
	qy.makeRotate(_y, ofVec3f(0,1,0));
	qz.makeRotate(_z, ofVec3f(0,0,1));
	
	endquat=qx*qy*qz;
	endquat.normalize();
	
	rotateTo(endquat,_rotatetime );
}


void BasicScreenObject::rotateTo(ofQuaternion _quat,float _rotatetime ){
	
	rotationspeed.set(0,0,0);
	stopRotationAttraction();
	
	tweener.removeTween(&rotateParam);
	tweenrotslerp=0.0;
	
	endquat=_quat;
	startquat=getOrientationQuat();
	
	rotateParam=tween::TweenerParam(_rotatetime,tween::SINE, tween::EASE_IN_OUT);
	rotateParam.addProperty(&tweenrotslerp, 1.0);
	tweener.addTween(rotateParam);
}


void BasicScreenObject::doRotate(){
	
	rotationspeed*=rotationdrag;
	addRotation(rotationspeed.x, rotationspeed.y, rotationspeed.z);
	
	if(rotationattractionforce>0){
		ofQuaternion betweenquat=rotationattractionquat-getOrientationQuat();
		float betweenangle;
		ofVec3f dirvec(1,0,0);
		betweenquat.getRotate(betweenangle, dirvec);
		ofQuaternion nowquat=getOrientationQuat();
		nowquat.slerp(rotationattractionforce, nowquat, rotationattractionquat);
		setOrientation(nowquat);
	}
}


void BasicScreenObject::doMove(){
	speed*=movedrag;
	move(speed.x, speed.y, speed.z);
	
	if(moveattractionforce>0){
		ofVec3f dist;
		dist.set(endposition);
		dist-=getPosition();
		dist*=moveattractionforce;
		addSpeed(dist.x, dist.y, dist.z,movedrag);
	}
	
}



/********************************************************
 *
 *	POSITIONER SYSTEM
 *
 ********************************************************/

// ofNode callbacks
void BasicScreenObject::onPositionChanged() {};
void BasicScreenObject::onOrientationChanged() {};
void BasicScreenObject::onScaleChanged() {};



void BasicScreenObject::addPositioner(string _name, IPositioner* _positioner ) {
	positioners[_name] = _positioner;
}


bool BasicScreenObject::removePositioner(string _name) {
	return true;
}

IPositioner* BasicScreenObject::getPositioner(string _name) {
	map<string,IPositioner*>::iterator iter = positioners.find(_name);
	if( iter != positioners.end() ) return iter->second;
	return NULL;
}


bool BasicScreenObject::hasPositioner(string _name) {
	map<string,IPositioner*>::iterator iter = positioners.find(_name);
	if( iter != positioners.end() ) return true;
	return false;
}



 



/********************************************************
 *
 *	TWEENER EVENTS
 *
 ********************************************************/


void BasicScreenObject::onStart(tween::TweenerParam& param){
	if(param==moveParam){
		ofNotifyEvent(moveToStartEvent, myEventArgs, this);
	}
	if(param==scaleParam){
		ofNotifyEvent(scaleToStartEvent, myEventArgs, this);
	}
	if(param==rotateParam){
		ofNotifyEvent(rotateToStartEvent, myEventArgs, this);
	}
	if(param==fadeParam){
		ofNotifyEvent(fadeToStartEvent, myEventArgs, this);
	}
	if(param==colorParam){
		setColor(tweenr,tweeng,tweenb);
	}
}


void BasicScreenObject::onStep(tween::TweenerParam& param){
	if(param==moveParam){
		//moveParam.
		setPosition(tweenx, tweeny, tweenz);
		//ofLog(OF_LOG_NOTICE, ofToString(tweenx));
		ofNotifyEvent(moveToStepEvent, myEventArgs, this);
	}
	if(param==scaleParam){
		setScale(tweenscalex, tweenscaley, tweenscalez);
		ofNotifyEvent(scaleToStepEvent, myEventArgs, this);
	}
	if(param==rotateParam){
		ofQuaternion nowquat=getOrientationQuat();
		nowquat.slerp(tweenrotslerp, startquat, endquat);
		setOrientation(nowquat);
		ofNotifyEvent(rotateToStepEvent, myEventArgs, this);
	}
	if(param==fadeParam){
		ofNotifyEvent(fadeToStepEvent, myEventArgs, this);
	}
	if(param==colorParam){
		setColor(tweenr,tweeng,tweenb);
	}
}


void BasicScreenObject::onComplete(tween::TweenerParam& param){
	if(param==moveParam){
		setPosition(tweenx, tweeny, tweenz);
		ofNotifyEvent(moveToCompleteEvent, myEventArgs, this);
	}
	if(param==scaleParam){
		setScale(tweenscalex, tweenscaley, tweenscalez);
		ofNotifyEvent(scaleToCompleteEvent, myEventArgs, this);
	}
	if(param==rotateParam){
		ofNotifyEvent(rotateToCompleteEvent, myEventArgs, this);
	}
	if(param==fadeParam){
		ofNotifyEvent(fadeToCompleteEvent, myEventArgs, this);
	}
	if(param==colorParam){
		setColor(tweenr,tweeng,tweenb);
	}
}



/********************************************************
 *
 *	Stuff for Interactive Objects: Maybe move it there?
 *	maybe move all picking-stuff to interactive-object? does a non-interactive object ever need picking?
 *
 ********************************************************/


bool BasicScreenObject::isInteractive() {
	return isinteractive;
}


ofColor BasicScreenObject::pickingNameToColor(GLint _pickingName) {
	GLint c = _pickingName;
	int r = c >> 16 & 0xFF;
	int g = c >> 8 & 0xFF;
	int b = c & 0xFF;
	return ofColor(r,g,b);
}


GLint BasicScreenObject::colorToPickingName(ofColor& _color) {
	int r = _color.r;
	int g = _color.g;
	int b = _color.b;
	int c = (r << 16) + (g << 8) + b;
	return c;
}
