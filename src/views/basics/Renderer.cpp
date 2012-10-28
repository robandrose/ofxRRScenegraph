/*
 *  Renderer.cpp
 *  BasicScreenObject_Test
 *
 *  Created by Matthias Rohrbach 2 on 12.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "Renderer.h"

Renderer::Renderer(){
	myname="Renderer";
	nextPickingName = 100;
	cursorsize=10;
	maxcursors=20;
	captureincrement=2;
	mapsampling=2;
	
	touchtomouse = true;
	mousetotouch = true;
	mousetouchid = -1;
	
	currentviewport=ofRectangle(0,0,0,0);
	
	bTuioSetup=false;
	bColorPickerSetup=false;
}

Renderer::~Renderer(){

}

void Renderer::setup(){
	
	ofAddListener(ofEvents().mousePressed, this, &Renderer::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &Renderer::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &Renderer::mouseReleased);
	
	ofAddListener(ofEvents().touchDown,this,&Renderer::tuioAdded);
	ofAddListener(ofEvents().touchUp,this,&Renderer::tuioRemoved);
	ofAddListener(ofEvents().touchMoved,this,&Renderer::tuioUpdated);
}

void Renderer::setupColorPicker(float _width, float _height, float _sampling, float _increment){	
	BasicScreenObject::setSize(_width,_height);
	mapsampling=_sampling;
	captureincrement=_increment;
	mapscale=1.0f/(float)mapsampling;
	
	ofFbo::Settings s;
	
	s.width=getWidth()/mapsampling;
	s.height=getHeight()/mapsampling;
	s.internalformat=GL_RGB;
	s.useDepth=true;
	
	pickingmap.allocate(s );
	maxbounds = ofRectangle ( 0 , 0 , pickingmap.getWidth()-1 , pickingmap.getHeight()-1 ) ;
	camera.setupPerspective();
	
	bColorPickerSetup=true;
	
}


void Renderer::update(){
	if(bColorPickerSetup){
		
		bool waslighting=glIsEnabled(GL_LIGHTING);
		if(waslighting){
			glDisable(GL_LIGHTING);
		}
		
		if(ofGetFrameNum() % captureincrement==0){
			pickingmap.begin();
			
			ofClear(0);
			ofPushMatrix() ;
			ofScale( mapscale , mapscale , mapscale) ;		
			BasicScreenObject::drawForPicking();	
			ofPopMatrix();
			
			pickingmap.end();		
			pickingmap.readToPixels(mapPixels);
		}
		if(waslighting){
			glEnable(GL_LIGHTING);
		}
	}
}

void Renderer::draw(){
	currentviewport=ofGetCurrentViewport();
	camera.begin();
	BasicScreenObject::draw();
	camera.end();
	drawCursors();
}


void Renderer::_draw(){		
	
}

void Renderer::startTuio(int _port) {
	port = _port;
	tuio.connect(_port);
	bTuioSetup=true;
}


void Renderer::tuioAdded(ofTouchEventArgs & _cursor) {	
	
	if (touchtomouse && mousetouchid==-1) {
		mousetouchid = _cursor.id;

		static ofMouseEventArgs mouseEventArgs;
		mouseEventArgs.x = _cursor.x*ofGetWidth();
		mouseEventArgs.y = _cursor.y*ofGetHeight();
		mouseEventArgs.button = 1;
		lastfakemouseevent = &mouseEventArgs;
		ofNotifyEvent( ofEvents().mousePressed, mouseEventArgs );
		
	}
	
	notifyObjects(_cursor.x*ofGetWidth(), _cursor.y*ofGetHeight(), _cursor.id, MT_ADD);
}

void Renderer::tuioRemoved(ofTouchEventArgs & _cursor){
	
	if (touchtomouse && mousetouchid==_cursor.id) {
		mousetouchid = -1;
		
		static ofMouseEventArgs mouseEventArgs;
		mouseEventArgs.x = _cursor.x*ofGetWidth();
		mouseEventArgs.y = _cursor.y*ofGetHeight();
		mouseEventArgs.button = 1;
		lastfakemouseevent = &mouseEventArgs;
		ofNotifyEvent( ofEvents().mouseReleased , mouseEventArgs );
	}
	
	notifyObjects(_cursor.x*ofGetWidth(), _cursor.y*ofGetHeight(), _cursor.id, MT_REMOVE);
}

void Renderer::tuioUpdated(ofTouchEventArgs & _cursor){
	
	if (touchtomouse && mousetouchid==_cursor.id) {
		static ofMouseEventArgs mouseEventArgs;
		mouseEventArgs.x = _cursor.x*ofGetWidth();
		mouseEventArgs.y = _cursor.y*ofGetHeight();
		mouseEventArgs.button = 1;
		lastfakemouseevent = &mouseEventArgs;
		ofNotifyEvent( ofEvents().mouseDragged, mouseEventArgs );
	}
	
	notifyObjects(_cursor.x*ofGetWidth(), _cursor.y*ofGetHeight(), _cursor.id, MT_UPDATE);
}

void Renderer::mousePressed(ofMouseEventArgs& _cursor){
	if (mousetotouch) {
		// ignore this mouse-event, if it was created by emulating a mouse-event from a touch
		if (lastfakemouseevent != &_cursor) {
			notifyObjects(_cursor.x, _cursor.y, -1, MT_ADD);
		}
	}
}

void Renderer::mouseReleased(ofMouseEventArgs& _cursor){
	if (mousetotouch) {
		// ignore this mouse-event, if it was created by emulating a mouse-event from a touch
		if (lastfakemouseevent != &_cursor) {
			notifyObjects(_cursor.x, _cursor.y, -1, MT_REMOVE);
		}
	}
}

void Renderer::mouseDragged(ofMouseEventArgs& _cursor){
	if (mousetotouch) {
		// ignore this mouse-event, if it was created by emulating a mouse-event from a touch
		if (lastfakemouseevent != &_cursor) {
			notifyObjects(_cursor.x, _cursor.y, -1, MT_UPDATE);
		}
	}
}


void Renderer::notifyObjects(float _screenx, float _screeny,int _fingerid, int _action){
	
	mtRay ray;
	ray.pos=camera.screenToWorld(ofVec3f(_screenx,_screeny,-1),currentviewport);
	ray.dir=camera.screenToWorld(ofVec3f(_screenx,_screeny,1), currentviewport)-ray.pos;
	ray.screenpos.set(_screenx, _screeny);
	
	
	BasicInteractiveObject* overobj=(BasicInteractiveObject*)getObjectAt(_screenx, _screeny);
	
	for(int i=0;i<pickingObjects.size();i++){
		BasicInteractiveObject* obj =(BasicInteractiveObject*) pickingObjects[i];
		if (obj != NULL && obj->isInteractive() && obj!=overobj) {
			switch (_action) {
				case (MT_ADD) : {
					obj->touchDownOutside(ray,_fingerid);
					break;
				}
				case (MT_UPDATE) : {
					obj->touchMovedOutside(ray,_fingerid);
					break;
				}
				case (MT_REMOVE) : {
					obj->touchUpOutside(ray,_fingerid);
					break;
				}
			}
		}
	}
	
	if(overobj!=NULL){
		switch (_action) {
			case (MT_ADD) : {
				overobj->touchDownOnMe(ray,_fingerid);
				break;
			}
			case (MT_UPDATE) : {
				overobj->touchMovedOnMe(ray,_fingerid);
				break;
			}
			case (MT_REMOVE) : {
				overobj->touchUpOnMe(ray,_fingerid);
				break;
			}
		}		
	}
	
	lastinteraction=ofGetElapsedTimeMillis();
}


 
void Renderer::drawMap() {
	ofSetColor(255, 255, 255);
	pickingmap.draw(0, 0,pickingmap.getWidth(),pickingmap.getHeight());
}

void Renderer::drawCursors(){

	
	
	ofEnableAlphaBlending();
	glBlendFunc(GL_ONE, GL_ONE);
	
	if(bTuioSetup){
		std::list<TuioCursor*> cursorList =  tuio.client->getTuioCursors();
		std::list<TuioCursor*>::iterator tit;
		tuio.client->lockCursorList();
		for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
			TuioCursor * cur = (*tit);
			glColor3f(0.1,0.1, 0.1);
			for(int i=0;i<5;i++){
				ofEllipse(cur->getX()*ofGetWidth(), cur->getY()*ofGetHeight(), 20.0+i*i, 20.0+i*i);
			}
		}
		tuio.client->unlockCursorList();
	}
	
	if (mousetotouch) {
		if (ofGetMousePressed()) {
			glColor3f(0.1,0.1, 0.1);
			for(int i=0;i<5;i++){
				ofEllipse(ofGetMouseX(), ofGetMouseY(), 20.0+i*i, 20.0+i*i);
			}
		}
	}
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

BasicScreenObject* Renderer::getObjectAt(float _screenx, float _screeny){
	int fbox=_screenx/mapsampling;
	int fboy=_screeny/mapsampling;
	fbox=ofClamp(fbox, 0, maxbounds.width);
	fboy=ofClamp(fboy, 0, maxbounds.height);
	int index = (fbox + fboy * pickingmap.getWidth()) * 3 ;
	ofColor	fboc=ofColor( mapPixels[index] , mapPixels[index + 1] , mapPixels[index + 2] );
	GLint pickingName=colorToPickingName(fboc);
	BasicScreenObject* obj = NULL;
	if (pickingObjects.find(pickingName) != pickingObjects.end()) {
		obj = pickingObjects[pickingName];
	}	
	return obj;	
}

GLuint Renderer::getNextPickingName(BasicScreenObject* _object) {
	GLuint np = ++nextPickingName;
	pickingObjects[np] = _object;
	return np;
}

long Renderer::lastInteractionMillis(){
	return lastinteraction;
}
