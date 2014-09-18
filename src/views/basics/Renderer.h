/*
 Renderer.h
 
 Root Element of Scenegraph, handles Camera and Picking, 
 registers all BasicScreenObjects in a map, stores all the interaction events (mouse and tuio) 
 performs picking by initiating the drawForPicking scope to an FBO, and then notifies all the 
 Objects of what just happened. 
 
 Copyright (C) 2014 Rob&Rose
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial 
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 IN THE SOFTWARE.
 */


#pragma once

#include "BasicScreenObject.h"
#include "BasicInteractiveObject.h"
#include "ofxTuioClient.h"
#include "ofxTweener.h"
#include "ofxFastFboReader.h"

#define MT_ADD 0
#define MT_UPDATE 1
#define MT_REMOVE 2

struct TouchAction {
	float	screenX;
	float	screenY;
	int		fingerId;
	int		action;
};

class Renderer : public BasicInteractiveObject {
public:
	Renderer();
	virtual ~Renderer();
	
	void startTuio(int _port);
	void setupColorPicker(float _width, float _height, float _sampling, float _increment);
	
    void resize();
    
	void draw();
	void drawMap();	
	void drawCursors();
	
	void setCursorSize(float _cursorsize);
    void isDrawCursors(bool _dracursors);
	
	BasicScreenObject* getObjectAt(float _screenx, float _screeny);
	GLuint getNextPickingName(BasicInteractiveObject* _object);
	
	ofCamera* getCamera(){return &camera;};
	
	long getLastInteractionMillis();
	void setIdleTimeout(int _millis) { idleTimeout = _millis; };
	ofEvent<BasicScreenObjectEvent> idleEvent;
	ofEvent<BasicScreenObjectEvent> idleFinishEvent;
	
	/* Wether the mouse events should emulate touch-events.
	 * If both isMouseToTouch and isTouchToMouse are activated,
	 * the emulated mouse event is not converted to a touch.
	 */
	void isMouseToTouch(bool _mousetotouch){mousetotouch=_mousetotouch;};
	bool isMouseToTouch(){return mousetotouch;};
	
	/* Wether the touch events should emulate mouse-events.
	 * If both isMouseToTouch and isTouchToMouse are activated,
	 * the emulated mouse event is not converted to a touch.
	 * Only one (the first, if there are multiple current touches) 
	 * touch _is_ the mouse. Only mousePressed, mouseDragged and
	 * mouseReleased events are dispatched.
	 */
	void isTouchToMouse(bool _touchtomouse){touchtomouse=_touchtomouse;};
	bool isTouchToMouse(){return touchtomouse;};
	
	bool isVisible() { return true; };
	bool isParentTreeVisible() { return true; };
	
	void forceUpdate();
	void forceInteraction();
	
protected:
	
	bool bTuioSetup;
	bool bColorPickerSetup;
	
	void setup();
	void _draw() {};
	void update();
	
	//TUIO Controller functions
	ofxTuioClient tuio;
	void tuioAdded(ofTouchEventArgs & cursor);
	void tuioRemoved(ofTouchEventArgs & cursor);
	void tuioUpdated(ofTouchEventArgs & cursor);
	
	//called by frameworks mouse events
	void mouseDragged(ofMouseEventArgs& e);
	void mousePressed(ofMouseEventArgs& e);
	void mouseReleased(ofMouseEventArgs& e);
	
	virtual void _drawForPicking(){};
	
	// mouse-touch and touch-mouse emulator settings 
	bool	touchtomouse;
	bool	mousetotouch;
	
	// the finger/session id of the touch that is emulating the mouse
	int		mousetouchid;
	
	// the event object of the last emulated mouse event (used to ignore the mouse event if it was created using the emulator)
	ofMouseEventArgs* lastfakemouseevent;
	
	void notifyObjects(TouchAction _touchAction);
	void queueTouchAction(float _screenx, float _screeny,int _fingerid, int _action);
	
	GLuint nextPickingName;
	map<GLuint, BasicInteractiveObject*> pickingObjects;
	
	int		port;
	int		maxcursors;
	bool	drawcursors;
	float	cursorsize;
	long	lastinteraction;
	bool	idleEventFired;
	int		idleTimeout;
	
	queue<TouchAction>	touchActions;
	
	// Pixel picking:
	ofFbo				pickingmap;
	ofxFastFboReader	fboReader;
	ofPixels			mapPixels ;
	
	int			captureincrement ;
	float		mapsampling;
	float		mapscale ;            //amount the screen is scaled
	float		mapscaleinv ;           //returns fbo to screen size
	ofRectangle maxbounds;
	
	// Camera
	ofCamera camera;
	
	// Save currentviewport, to enable raygeneration in update loop
	ofRectangle currentviewport;
		
};
