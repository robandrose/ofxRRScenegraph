/*
 *  BasicInteractiveObject.cpp
 *  BasicScreenObject_Test
 *
 *  Created by Matthias Rohrbach 2 on 12.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "BasicInteractiveObject.h"
#include "ofMain.h"
#include "Renderer.h"


BasicInteractiveObject::BasicInteractiveObject(){
	
	dragtarget		= this;
	
	mtscale = 1.0;
	mtrotate.set(0, 0, 0, 1);
	
	isstdraggable	= true;
	isdraggable		= true;
	isscaleable		= true;
	isrotateable	= true;
	isrotating		= false;
	isscaling		= false;
	isdragging		= false;
	
	isdragauto		= true;
	isscaleauto		= true;
	isrotateauto	= true;
	
	dragdamp		= .3;
	rotatedamp		= .3;
	scaledamp		= .3;
	
	dragthreshold	= 20;
	rotatethreshold	= 4;
	scalethreshold	= .1;
	tapThreshold	= 1000.0;
	
	mttoucha		= NULL;
	mttouchb		= NULL;
	mtcounter		= 0;
	mtscopeduration = 0;
	mttranslatedist = 0;
	mtrotatedist	= 0;
	
	mtscale			= 0;
	mtscalestart	= 0;
	mtscalespeed	= 0;
	mtscaledist		= 0;
	
	mtscoperunning	= false;
	
	ofAddListener(firstTouchDownEvent,	this, &BasicInteractiveObject::onFirstTouchDown);	
	ofAddListener(lastTouchUpEvent,		this, &BasicInteractiveObject::onLastTouchUp);	
	
	ofAddListener(tapEvent,				this, &BasicInteractiveObject::onTap);	
	ofAddListener(doubleTapEvent,		this, &BasicInteractiveObject::onDoubleTap);
	
	ofAddListener(swipeUpEvent,			this, &BasicInteractiveObject::onSwipeUp);
	ofAddListener(swipeDownEvent,		this, &BasicInteractiveObject::onSwipeDown);
	ofAddListener(swipeLeftEvent,		this, &BasicInteractiveObject::onSwipeLeft);
	ofAddListener(swipeRightEvent,		this, &BasicInteractiveObject::onSwipeRight);
	ofAddListener(scaleStartEvent,		this, &BasicInteractiveObject::onScaleStart);
	ofAddListener(scaleStopEvent,		this, &BasicInteractiveObject::onScaleStop);
	ofAddListener(dragStartEvent,		this, &BasicInteractiveObject::onDragStart);
	ofAddListener(dragStopEvent,		this, &BasicInteractiveObject::onDragStop);
	ofAddListener(rotateStartEvent,		this, &BasicInteractiveObject::onRotateStart);
	ofAddListener(rotateStopEvent,		this, &BasicInteractiveObject::onRotateStop);
	
	ofAddListener(startMultiTouchScopeEvent,	this, &BasicInteractiveObject::onStartMultiTouchScope);
	ofAddListener(updateMultiTouchScopeEvent,	this, &BasicInteractiveObject::onUpdateMultiTouchScope);
	ofAddListener(endMultiTouchScopeEvent,		this, &BasicInteractiveObject::onEndMultiTouchScope);
}


BasicInteractiveObject::~BasicInteractiveObject(){
	
	ofRemoveListener(firstTouchDownEvent,	this, &BasicInteractiveObject::onFirstTouchDown);	
	ofRemoveListener(lastTouchUpEvent,		this, &BasicInteractiveObject::onLastTouchUp);	
	
	ofRemoveListener(tapEvent,				this, &BasicInteractiveObject::onTap);	
	ofRemoveListener(doubleTapEvent,		this, &BasicInteractiveObject::onDoubleTap);
	ofRemoveListener(swipeUpEvent,			this, &BasicInteractiveObject::onSwipeUp);
	ofRemoveListener(swipeDownEvent,		this, &BasicInteractiveObject::onSwipeDown);
	ofRemoveListener(swipeLeftEvent,		this, &BasicInteractiveObject::onSwipeLeft);
	ofRemoveListener(swipeRightEvent,		this, &BasicInteractiveObject::onSwipeRight);
	ofRemoveListener(scaleStartEvent,		this, &BasicInteractiveObject::onScaleStart);
	ofRemoveListener(scaleStopEvent,		this, &BasicInteractiveObject::onScaleStop);
	ofRemoveListener(dragStartEvent,		this, &BasicInteractiveObject::onDragStart);
	ofRemoveListener(dragStopEvent,			this, &BasicInteractiveObject::onDragStop);
	ofRemoveListener(rotateStartEvent,		this, &BasicInteractiveObject::onRotateStart);
	ofRemoveListener(rotateStopEvent,		this, &BasicInteractiveObject::onRotateStop);
	
	ofRemoveListener(startMultiTouchScopeEvent,	this, &BasicInteractiveObject::onStartMultiTouchScope);
	ofRemoveListener(updateMultiTouchScopeEvent,this, &BasicInteractiveObject::onUpdateMultiTouchScope);
	ofRemoveListener(endMultiTouchScopeEvent,	this, &BasicInteractiveObject::onEndMultiTouchScope);	
}


void BasicInteractiveObject::update(){
	updateMtTransform();
}


void BasicInteractiveObject::drawForPicking(){
	if (isVisible() && isParentTreeVisible()) {
		
		glPushMatrix();
		glMultMatrixf(getLocalTransformMatrix().getPtr());
		
		if (hasmask) setupMask();
		
		depthtestbefore = glIsEnabled(GL_DEPTH_TEST);
		if (depthtestenabled && !depthtestbefore)glEnable(GL_DEPTH_TEST);
		if (!depthtestenabled && depthtestbefore)glDisable(GL_DEPTH_TEST);
		
		ofPushStyle();
		ofColor pickingColor = pickingNameToColor(pickingName);
		ofSetColor(pickingColor.r, pickingColor.g, pickingColor.b);
		_drawForPicking();
		ofPopStyle();			
		
		drawChildrenForPicking();
		
		if(depthtestenabled && !depthtestbefore){
			glDisable(GL_DEPTH_TEST);
		}
		if(!depthtestenabled && depthtestbefore){
			glEnable(GL_DEPTH_TEST);
		}
		if(hasmask) restoreMask();		
		glPopMatrix();
	}
}

void BasicInteractiveObject::setRoot(BasicScreenObject* _root){
	root = _root;
	
	if (root->getName() == "Renderer") {
		Renderer* renderer = (Renderer*)root;
		pickingName = renderer->getNextPickingName(this);
	}
	
	for (int i = 0; i < childlist.size(); i++) {
		BasicScreenObject* elm = childlist.at(i);
		elm->setRoot(_root);
	}
}


void BasicInteractiveObject::setDragThreshold(		float _dragthreshold)		{ dragthreshold		= _dragthreshold; }
void BasicInteractiveObject::setScaleThreshold(		float _scalethreshold)		{ scalethreshold	= _scalethreshold; }
void BasicInteractiveObject::setRotationThreshold(	float _rotatethreshold)		{ rotatethreshold	= _rotatethreshold; }
void BasicInteractiveObject::setTapThreshold(		float _tapThreshold)		{ tapThreshold		= _tapThreshold; }

void BasicInteractiveObject::setDragDamping(		float _dragDamping)			{ dragdamp		= _dragDamping; };
void BasicInteractiveObject::setScaleDamping(		float _scaleDamping)		{ scaledamp		= _scaleDamping; };
void BasicInteractiveObject::setRotationDamping(	float _rotationDamping)		{ rotatedamp	= _rotationDamping; };


//Aktionen, werden direkt vom Renderer aufgerufen.

void BasicInteractiveObject::touchDownOnMe(mtRay ray, int touchId){
	addMultiTouch( ray, touchId);
}

void BasicInteractiveObject::touchMovedOnMe(mtRay ray, int touchId){
	updateMultiTouch( ray, touchId);
}

void BasicInteractiveObject::touchUpOnMe(mtRay ray, int touchId){
	removeMultiTouch( ray, touchId);
}

void BasicInteractiveObject::touchDownOutside(mtRay ray, int touchId){	

}

void BasicInteractiveObject::touchMovedOutside(mtRay ray, int touchId){
	updateMultiTouch(ray, touchId);
}

void BasicInteractiveObject::touchUpOutside(mtRay ray, int touchId){
	removeMultiTouch(ray, touchId);
}


// Multitouch internal handling:
// TODO: if internal, these should be private or protected!
void BasicInteractiveObject::addMultiTouch(mtRay ray, int touchId){
	MultiTouchPoint* mtp = new MultiTouchPoint();
	
	plane.pos	= getGlobalPosition();
	plane.norm	= ofVec3f(0,0,1)*getGlobalOrientation();
	
	float u		= plane.norm.dot(plane.pos-ray.pos)/plane.norm.dot(ray.dir);
	ofVec3f gintersection = ray.pos+ray.dir*u;
	
	mtp->screenpos.set(ray.screenpos);
	mtp->globalstartpos.set(gintersection);	
	mtp->localstartpos	= globalToLocal(mtp->globalstartpos);
	mtp->localpos		= mtp->localstartpos;
	mtp->localoffset	= mtp->localstartpos-getPosition();
	mtp->globalpos		= mtp->globalstartpos;
	mtp->globalmovedist	= 0;
	mtp->starttime		= ofGetElapsedTimeMillis();	
	
	activeMultiTouches[touchId] = mtp;
	mtcounter++;
	
	if(activeMultiTouches.size() == 1){
		// Start of Scope
		mtstarttime		= ofGetElapsedTimeMillis();
		mtscoperunning	= true;

		MultiTouchEvent params(this, mtp);
		ofNotifyEvent(firstTouchDownEvent,params,this);
	}
	
	if(activeMultiTouches.size()>=2){		
		MultiTouchEvent params(this);
		ofNotifyEvent(startMultiTouchScopeEvent,params,this);
	}
	
	mttranslatedist	= 0;
	mtrotatedist	= 0;
	mtscaledist		= 0;
	
	mttranslatespeed.set(0,0,0);
	mtrotatespeed.set(0,0,0,1);
	mtscalespeed=0;
	
	resetMTStartValues();
}

void BasicInteractiveObject::updateMultiTouch(mtRay ray, int touchId){
	if(isMultiTouchActive(touchId)){
	
		plane.pos	= getGlobalPosition();
		plane.norm	= ofVec3f(0,0,1)*getGlobalOrientation();
		
		float u		= plane.norm.dot(plane.pos-ray.pos)/plane.norm.dot(ray.dir);
		ofVec3f gintersection = ray.pos+ray.dir*u;
		
		MultiTouchPoint* mtp = activeMultiTouches[touchId];

		mtp->screenpos.set(ray.screenpos);
		mtp->globalposbef.set(mtp->globalpos);
		mtp->globalpos.set(gintersection);
		mtp->globalspeed.set(mtp->globalpos-mtp->globalposbef);
		mtp->localposbef.set(mtp->localpos);
		mtp->localpos.set(globalToLocal(mtp->globalpos));
		mtp->localspeeddamped.set((mtp->localspeed + (mtp->localpos-mtp->localposbef))/2);
		mtp->localspeed.set(mtp->localpos-mtp->localposbef);		
		mtp->globalmovedist += mtp->globalspeed.length();
	}
}

void BasicInteractiveObject::removeMultiTouch(mtRay ray, int touchId){

	if(isMultiTouchActive(touchId)){
		
		// copy that touch in case we need to dispatch it with an event
		MultiTouchPoint* oldMtp = activeMultiTouches[touchId];
		MultiTouchPoint* mtp	= new MultiTouchPoint();
		mtp->starttime			= oldMtp->starttime;
		mtp->globalmovedist		= oldMtp->globalmovedist;
		mtp->screenpos			= oldMtp->screenpos;
		mtp->localoffset		= oldMtp->localoffset;
		mtp->localstartpos		= oldMtp->localstartpos;
		mtp->localpos			= oldMtp->localpos;
		mtp->localposbef		= oldMtp->localposbef;
		mtp->localspeed			= oldMtp->localspeed;
		mtp->localspeeddamped	= oldMtp->localspeeddamped;
		mtp->globalstartpos		= oldMtp->globalstartpos;
		mtp->globalpos			= oldMtp->globalpos;
		mtp->globalposbef		= oldMtp->globalposbef;
		mtp->globalspeed		= oldMtp->globalspeed;
		
		activeMultiTouches.erase(activeMultiTouches.find(touchId));
		
		if(getNumActiveTouches() == 0 && mtcounter > 0){
			// End of Scope
			mtscoperunning	= false;
			mtscopeduration	= ofGetElapsedTimeMillis()-mtstarttime;
			
			if(!isrotating && !isscaling){
				// check for taps
				if (!isdragging && mtscopeduration < tapThreshold) {
					if ( mtcounter == 1 ){
						MultiTouchEvent params(this, mtp);
						ofNotifyEvent(tapEvent,params,this);
						
					} else if ( mtcounter == 2 ){
						MultiTouchEvent params(this, mtp);
						ofNotifyEvent(doubleTapEvent,params,this);
					}
					
					// check for swipe
				} else if (mtscopeduration < 1000 && mttranslatespeed.length() > 0.0){
					
					MultiTouchEvent params(this, mtp);
					
					if (abs(mttranslatespeed.x) > abs(mttranslatespeed.y)) {
						if (mttranslatespeed.x < 0) {
							ofNotifyEvent(swipeLeftEvent,params,this);
						} else {
							ofNotifyEvent(swipeRightEvent,params,this);
						}
					} else {
						if (mttranslatespeed.y < 0) {
							ofNotifyEvent(swipeUpEvent,params,this);
						} else {
							ofNotifyEvent(swipeDownEvent,params,this);
						}
					}
				}
				
			}
			
			if (isdragging==true) {
				isdragging = false;
				MultiTouchEvent params(this);
				ofNotifyEvent(dragStopEvent,params,this);
			}
			
			MultiTouchEvent params(this, mtp);
			ofNotifyEvent(lastTouchUpEvent,params,this);
			
			mtcounter=0;
		}
		
		if(getNumActiveTouches()<2 && mtcounter>=2){
			if (isrotating==true) {
				isrotating = false;
				MultiTouchEvent params(this);
				ofNotifyEvent(rotateStopEvent,params,this);
			}
			if (isscaling==true) {
				isscaling = false;
				MultiTouchEvent params(this);
				ofNotifyEvent(scaleStopEvent,params,this);
			}
			
			MultiTouchEvent params(this);
			ofNotifyEvent(endMultiTouchScopeEvent,params,this);
		}
		
		resetMTStartValues();
		
	}
}


void BasicInteractiveObject::resetMTStartValues(){
	
	if(getNumActiveTouches() == 0)return;

	if(getNumActiveTouches() == 1){
		mttoucha	= activeMultiTouches.begin()->second;
		mttouchb	= mttoucha;
	}else{		
		
		// Find relevant touchpoints:
		ofVec3f dist;
		float biggestdist = 0;	
		
		for(amt = activeMultiTouches.begin(); amt != activeMultiTouches.end(); amt++) {
			MultiTouchPoint* p = amt->second;
			for(amtinner=activeMultiTouches.begin(); amtinner != activeMultiTouches.end(); amtinner++){
				
				MultiTouchPoint* p2 = amtinner->second;
				dist.set(p->globalpos);
				dist -= p2->globalpos;			
				
				if(dist.length() > biggestdist){
					mttoucha = p;
					mttouchb = p2;
					biggestdist=dist.length();
				}
			}
		}
	}
	
	mttransformstart		= getCurrentMtTransform();
	mttransformmatrixstart	= getLocalTransformMatrix();
	mtscalestart			= getScale().x;
	mtrotatestart			= getOrientationQuat();
	
	mtpivot.set(getCurrentMtTranslate()-getPosition());
	mtpivot	= mtpivot*mtrotatestart.inverse();
	mtpivot/= mtscalestart;
	
	mttranslatestart = getCurrentMtTranslate()-mtpivot;
	
	mttranslate.set(0,0,0);
	mtrotate.set(0,0,0,1);
	mtscale = 1;
	
}

void BasicInteractiveObject::updateMtTransform(){
	if(!mtscoperunning) return;
	mttransform = getCurrentMtTransform();
	
	mttransformmatrix.makeIdentityMatrix();
	
	if(getNumActiveTouches() > 1){
		
		mttransformmatrix.translate(-(mttranslatestart+mtpivot));
		
		if(isScaleable()){
			
			mtscalespeed	= mtscale;
			
			float endscale	= (float)mttransform.length() / mttransformstart.length();
			mtscale			+= (endscale-mtscale)*scaledamp;
			
			mtscalespeed	= mtscale-mtscalespeed;
			mtscaledist		+= fabs(mtscalespeed);
			
			if (isscaling == false) {
				if(mtscaledist > scalethreshold){
					isscaling = true;
					MultiTouchEvent params(this);
					ofNotifyEvent(scaleStartEvent,params,this);
				}
			}
			
			if(isScaleAuto() && isscaling){
				mttransformmatrix.scale(mtscale, mtscale, mtscale);
			}
		}
		
		if(isRotateable()){
			mtrotatespeed = mtrotate;
			
			ofQuaternion newrotate;
			newrotate.makeRotate(mttransformstart, mttransform);
			mtrotate.slerp(rotatedamp, mtrotate, newrotate);
			mtrotatespeed	=  mtrotate*mtrotatespeed.inverse();
			mtrotatedist	+= fabs(mtrotatespeed.getEuler().x);
			
			if (isrotating == false) {
				if(mtrotatedist > rotatethreshold){
					isrotating = true;
					MultiTouchEvent params(this);
					ofNotifyEvent(rotateStartEvent, params, this);
				}
			}
			
			if(isRotateAuto() && isrotating){
				mttransformmatrix.rotate(mtrotate);
			}
		}
		
		mttransformmatrix.translate(mttranslatestart + mtpivot);
	}
	
	bool stAlsoOk=true;
	
	if(getNumActiveTouches() == 1 ){
		if(!isStDraggable()){
			stAlsoOk = false;
		}
	}
	
	if(isDraggable() && stAlsoOk){
		
		mttranslatespeed.set(mttranslate);
		mttranslate.interpolate(getCurrentMtTranslate() - mtpivot - mttranslatestart, dragdamp);
		mttranslatespeed	=	mttranslate-mttranslatespeed;
		mttranslatedist		+=	mttranslatespeed.length();
		
		if (isdragging == false) {
			if(mttranslatedist > dragthreshold){
				isdragging = true;
				MultiTouchEvent params(this);
				ofNotifyEvent(dragStartEvent,params,this);
			}
		}
		
		if(isDragAuto() && isdragging){
			mttransformmatrix.translate(mttranslate);
		}
	}
	
	ofMatrix4x4 currentmatrix;
	
	currentmatrix.set(mttransformmatrixstart);
	currentmatrix.postMult(mttransformmatrix);
	
	setTransformMatrix(currentmatrix);
	
	MultiTouchEvent params(this);
	ofNotifyEvent(updateMultiTouchScopeEvent, params, this);
	
}

ofVec3f BasicInteractiveObject::getCurrentMtTransform(){
	ofVec3f mtvec;
	mtvec.set(mttouchb->localpos);
	mtvec -= mttoucha->localpos;
	return mtvec;
}

ofVec3f BasicInteractiveObject::getCurrentMtTranslate(){
	ofVec3f mtvec;
	mtvec.set(mttoucha->localpos);
	mtvec += mttouchb->localpos;
	mtvec /= 2;	
	return mtvec;
}


int BasicInteractiveObject::getNumActiveTouches(){
	return activeMultiTouches.size();
}

bool BasicInteractiveObject::isMultiTouchActive(int touchId) {
	return activeMultiTouches.find(touchId) != activeMultiTouches.end();
}

ofColor BasicInteractiveObject::pickingNameToColor(GLint _pickingName) {
	GLint c = _pickingName;
	int r = c >> 16 & 0xFF;
	int g = c >> 8 & 0xFF;
	int b = c & 0xFF;
	return ofColor(r,g,b);
}


GLint BasicInteractiveObject::colorToPickingName(ofColor& _color) {
	int r = _color.r;
	int g = _color.g;
	int b = _color.b;
	int c = (r << 16) + (g << 8) + b;
	return c;
}
