/*
 *  Renderer.h
 *  BasicScreenObject_Test
 *
 *  Created by Matthias Rohrbach 2 on 12.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */


#pragma once

#include "BasicScreenObject.h"
#include "BasicInteractiveObject.h"
#include "ofxTuioClient.h"
#include "GuiSettingsController.h"


#define MT_ADD 0
#define MT_UPDATE 1
#define MT_REMOVE 2

class Renderer : public BasicInteractiveObject {
public:
	Renderer();
	virtual ~Renderer();
	
	void startTuio(int _port);
	void setupColorPicker(float _width, float _height, float _sampling, float _increment);
	
	void draw();
	void drawMap();	
	void drawCursors();
	
	void setCursorSize(float _cursorsize);
    void isDrawCursors(bool _dracursors);
	
	BasicScreenObject* getObjectAt(float _screenx, float _screeny);
	GLuint getNextPickingName(BasicScreenObject* _object);
	
	ofCamera* getCamera(){return &camera;};
	
	long lastInteractionMillis();
	
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
	
	
protected:
	
	void setup();
	void _draw();
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
	bool touchtomouse;
	bool mousetotouch;
	
	// the finger/session id of the touch that is emulating the mouse
	int mousetouchid;
	
	// the event object of the last emulated mouse event (used to ignore the mouse event if it was created using the emulator)
	ofMouseEventArgs* lastfakemouseevent;
	
	void notifyObjects(float _screenx, float _screeny,int _fingerid, int _action);
	
	GLuint nextPickingName;
	map<GLuint, BasicScreenObject*> pickingObjects;
	
	int port;
	int maxcursors;
	bool drawcursors;
	float cursorsize;
	long lastinteraction;
	
	
	// Pixel picking:
	
	ofFbo pickingmap;
	ofPixels mapPixels ;
	
	int captureincrement ;
	float mapsampling;
	float mapscale ;            //amount the screen is scaled
	float mapscaleinv ;           //returns fbo to screen size
	ofRectangle maxbounds;
	
	// Camera
	
	ofCamera camera;
	
	// Save currentviewport, to enable raygeneration in update loop
	ofRectangle currentviewport;
		
};
