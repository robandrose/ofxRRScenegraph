#include "Renderer.h"

Renderer::Renderer(){
	myname			= "Renderer";
	nextPickingName	= 100;
	cursorsize		= 10;
	maxcursors		= 20;
	captureincrement= 2;
	mapsampling		= 2;
	
	touchtomouse = true;
	mousetotouch = true;
	mousetouchid = -1;
	
	currentviewport	= ofRectangle(0,0,0,0);
	
	bTuioSetup			= false;
	bColorPickerSetup	= false;
	isRenderer			= true;
	_isAddedToRenderer	= true;
	drawcursors			= true;
	
	idleEventFired		= false;
	idleTimeout			= 30000;	// 30 seconds
}


Renderer::~Renderer(){
 
}

void Renderer::resize(){
    BasicScreenObject::setSize(ofGetWidth(),ofGetHeight());
    camera.setupPerspective();
	
	
}

void Renderer::setup(){
	
	camera.setupPerspective();
	BasicScreenObject::setSize(ofGetWidth(),ofGetHeight());
	
	ofAddListener(ofEvents().mousePressed, this, &Renderer::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &Renderer::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &Renderer::mouseReleased);
	
	ofAddListener(ofEvents().touchDown,this,&Renderer::tuioAdded);
	ofAddListener(ofEvents().touchUp,this,&Renderer::tuioRemoved);
	ofAddListener(ofEvents().touchMoved,this,&Renderer::tuioUpdated);
}


void Renderer::setupColorPicker(float _width, float _height, float _sampling, float _increment){	
	
	BasicScreenObject::setSize(_width,_height);
	mapsampling			= _sampling;
	captureincrement	= _increment;
	mapscale			= 1.0f/(float)mapsampling;
	
	ofFbo::Settings s;
	
	s.width				= getWidth()  / mapsampling;
	s.height			= getHeight() / mapsampling;
	s.internalformat	= GL_RGB; // would be much faster using GL_LUMINANCE or GL_LUMINANCE32F_ARB (32bit resolution should be enough);
	s.useDepth			= true;
	
	pickingmap.allocate(s );

	maxbounds = ofRectangle ( 0 , 0 , pickingmap.getWidth()-1 , pickingmap.getHeight()-1 ) ;
	camera.setupPerspective();
	
	bColorPickerSetup=true;
}


void Renderer::update(){

	Tweener.update();

	if(bColorPickerSetup){
		
		bool waslighting = glIsEnabled(GL_LIGHTING);
		if(waslighting){
			glDisable(GL_LIGHTING);
		}
		
		if(ofGetFrameNum() % captureincrement==0){
			pickingmap.begin();
			ofClear(0);
			ofScale( mapscale , mapscale , mapscale) ;		
			camera.begin();
			BasicScreenObject::drawForPicking();
			camera.end();
			pickingmap.end();						
		}
		
		if(waslighting){
			glEnable(GL_LIGHTING);
		}
		
		if (!touchActions.empty()) {
			pickingmap.readToPixels(mapPixels);	// < takes 20ms for rgb fbo. 1ms for GL_LUMINANCE
		}
		
		while (!touchActions.empty() ) {
			notifyObjects(touchActions.front());
			touchActions.pop();
		}
	}
	
	if (!idleEventFired) {
		if (ofGetElapsedTimeMillis() > lastinteraction + idleTimeout) {
			idleEventFired = true;
			ofNotifyEvent(idleEvent, myEventArgs, this);
		}
	}
	
}


void Renderer::forceUpdate() { update(); }


void Renderer::draw(){
	currentviewport = ofGetCurrentViewport();
	camera.begin();
	BasicScreenObject::draw();
	camera.end();
    if (drawcursors) drawCursors();
}


void Renderer::startTuio(int _port) {
	port = _port;
	tuio.connect(_port);
	bTuioSetup = true;
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
	
	queueTouchAction(_cursor.x*ofGetWidth(), _cursor.y*ofGetHeight(), _cursor.id, MT_ADD);
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
	
	queueTouchAction(_cursor.x*ofGetWidth(), _cursor.y*ofGetHeight(), _cursor.id, MT_REMOVE);
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
	
	queueTouchAction(_cursor.x*ofGetWidth(), _cursor.y*ofGetHeight(), _cursor.id, MT_UPDATE);
}


void Renderer::mousePressed(ofMouseEventArgs& _cursor){
	if (mousetotouch) {
		// ignore this mouse-event, if it was created by emulating a mouse-event from a touch
		if (lastfakemouseevent != &_cursor) {
			queueTouchAction(_cursor.x, _cursor.y, -1, MT_ADD);
		}
	}
}


void Renderer::mouseReleased(ofMouseEventArgs& _cursor){
	if (mousetotouch) {
		// ignore this mouse-event, if it was created by emulating a mouse-event from a touch
		if (lastfakemouseevent != &_cursor) {
			queueTouchAction(_cursor.x, _cursor.y, -1, MT_REMOVE);
		}
	}
}


void Renderer::mouseDragged(ofMouseEventArgs& _cursor){
	if (mousetotouch) {
		// ignore this mouse-event, if it was created by emulating a mouse-event from a touch
		if (lastfakemouseevent != &_cursor) {
			queueTouchAction(_cursor.x, _cursor.y, -1, MT_UPDATE);
		}
	}
}


void Renderer::queueTouchAction(float _screenx, float _screeny, int _fingerid, int _action) {
	TouchAction touch = {_screenx, _screeny, _fingerid, _action};
	touchActions.push(touch);
}


void Renderer::notifyObjects(TouchAction _touchAction) {
	
	mtRay ray;
    // y-Axis needs to be flipped from openframeworks 0.8.0 on because of the flipped camera (somehow)
    
	ray.pos = camera.screenToWorld( ofVec3f( _touchAction.screenX, ofGetHeight()-_touchAction.screenY,-1),	currentviewport);
	ray.dir = camera.screenToWorld( ofVec3f( _touchAction.screenX,ofGetHeight()-_touchAction.screenY, 1),	currentviewport) - ray.pos;
	ray.screenpos.set(_touchAction.screenX, _touchAction.screenY);
	
	
	BasicInteractiveObject* overobj = (BasicInteractiveObject*)getObjectAt(_touchAction.screenX, _touchAction.screenY);
	
	for(int i=0;i<pickingObjects.size();i++){
		BasicInteractiveObject* obj =(BasicInteractiveObject*) pickingObjects[i];
		if (obj != NULL && obj!=overobj) {
			switch (_touchAction.action) {
				case (MT_ADD) : {
					obj->touchDownOutside(	ray,_touchAction.fingerId );
					break;
				}
				case (MT_UPDATE) : {
					obj->touchMovedOutside(	ray,_touchAction.fingerId );
					break;
				}
				case (MT_REMOVE) : {
					obj->touchUpOutside(	ray,_touchAction.fingerId );
					break;
				}
			}
		}
	}
	
	if(overobj!=NULL){
		switch (_touchAction.action) {
			case (MT_ADD) : {
				overobj->touchDownOnMe(	ray,_touchAction.fingerId );
				break;
			}
			case (MT_UPDATE) : {
				overobj->touchMovedOnMe(ray,_touchAction.fingerId );
				break;
			}
			case (MT_REMOVE) : {
				overobj->touchUpOnMe(	ray,_touchAction.fingerId );
				break;
			}
		}		
	}
	
	lastinteraction	= ofGetElapsedTimeMillis();
	
	if (idleEventFired) {
		idleEventFired = false;
		ofNotifyEvent(idleFinishEvent, myEventArgs, this);
	}
}


void Renderer::drawMap() {
	//ofSetColor(255, 255, 255);
	pickingmap.draw(0, 0);
}


void Renderer::drawCursors(){

	ofEnableAlphaBlending();
	glBlendFunc(GL_ONE, GL_ONE);
	
	if(bTuioSetup){
		std::list<TuioCursor*> cursorList =  tuio.client->getTuioCursors();
		std::list<TuioCursor*>::iterator tit;
		tuio.client->lockCursorList();
		
		for (tit = cursorList.begin(); tit != cursorList.end(); tit++) {
			TuioCursor * cur = (*tit);
			glColor3f(0.1,0.1, 0.1);
			for(int i = 0; i < 5; i++){
				ofEllipse(cur->getX()*ofGetWidth(),
						  cur->getY()*ofGetHeight(),
						  20.0+i*i,
						  20.0+i*i);
			}
		}
		tuio.client->unlockCursorList();
	}
	
	if (mousetotouch) {
		if (ofGetMousePressed()) {
			glColor3f(0.1,0.1, 0.1);
			for(int i = 0; i < 5; i++){
				ofEllipse(ofGetMouseX(),
						  ofGetMouseY(),
						  20.0+i*i,
						  20.0+i*i);
			}
		}
	}
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}


BasicScreenObject* Renderer::getObjectAt(float _screenx, float _screeny){
	int fbox	=_screenx/mapsampling;
	int fboy	=_screeny/mapsampling;
	fbox		= ofClamp(fbox, 0, maxbounds.width);
	fboy		= ofClamp(fboy, 0, maxbounds.height);
	
	int index	= (fbox + fboy * pickingmap.getWidth()) * 3 ;
	//int index	= (fbox + fboy * pickingmap.getWidth());
	
	//if (bColorPickerSetup)	pickingmap.readToPixels(mapPixels);
	
	ofColor	fboc			= ofColor( mapPixels[index] , mapPixels[index + 1] , mapPixels[index + 2] );
	//ofColor	fboc			= ofColor( mapPixels[index] , mapPixels[index] , mapPixels[index] );
	GLint pickingName		= colorToPickingName(fboc);
	BasicScreenObject* obj	= NULL;
	
	if (pickingObjects.find(pickingName) != pickingObjects.end()) {
		obj = pickingObjects[pickingName];
	}	
	return obj;	
}


GLuint Renderer::getNextPickingName(BasicInteractiveObject* _object) {
	GLuint np = ++nextPickingName;
	pickingObjects[np] = _object;
	return np;
}


long Renderer::getLastInteractionMillis
(){
	return lastinteraction;
}


void Renderer::isDrawCursors(bool _drawCursors) {
	drawcursors = _drawCursors;
}


void Renderer::forceInteraction() {
	lastinteraction	= ofGetElapsedTimeMillis();
	if (idleEventFired) {
		idleEventFired = false;
		ofNotifyEvent(idleFinishEvent, myEventArgs, this);
	}
}