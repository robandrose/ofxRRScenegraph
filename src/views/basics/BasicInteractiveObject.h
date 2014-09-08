/*
 BasicInteractiveObject.h
 
 Basic Element for all interactive Elements, registers in Renderer to receive the picking color and draws 
 itself in the picking loop. Multitouch-Transitions can be applied to the element itself or any other BasicScreenObject
 this is convenient if only used as a sliding area, and you need to retrieve the speed of the sliding operation.
 
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
#include "MultitouchEvent.h"

#include <set>


class mtRay{
public:
	ofVec2f screenpos;
	ofVec3f pos;
	ofVec3f dir;
};

class mtPlane{
public:
	ofVec3f pos;
	ofVec3f norm;
};

class MultiTouchPoint{
public:
	long	starttime;
	float	globalmovedist;
	
	ofPoint	screenpos;
	
	ofPoint localoffset;
	ofPoint localstartpos;
	ofPoint localpos;
	ofPoint localposbef;
	ofPoint localspeed;
	ofPoint localspeeddamped;
	
	ofPoint globalstartpos;
	ofPoint globalpos;
	ofPoint globalposbef;
	ofPoint globalspeed;
};



class BasicInteractiveObject: public BasicScreenObject {
public:
	
	BasicInteractiveObject();
	virtual ~BasicInteractiveObject();
	
	// Functions to be overloaded:
	
	// Attention on overload, don't forget to call BasicInteractiveObject::update() in update()
	virtual void update();
	virtual void _drawForPicking(){ofRect(0,0,width,height);};
	virtual void drawForPicking();
	
	virtual void onFirstTouchDown(MultiTouchEvent& _event){};
	virtual void onLastTouchUp(MultiTouchEvent& _event){};
	
	virtual void onTap(MultiTouchEvent& _event){};
	virtual void onDoubleTap(MultiTouchEvent& _event){};
	virtual void onSwipeUp(MultiTouchEvent& _event){};
	virtual void onSwipeDown(MultiTouchEvent& _event){};
	virtual void onSwipeLeft(MultiTouchEvent& _event){};
	virtual void onSwipeRight(MultiTouchEvent& _event){};
	virtual void onScaleStart(MultiTouchEvent& _event){};
	virtual void onScaleStop(MultiTouchEvent& _event){};
	virtual void onDragStart(MultiTouchEvent& _event){};
	virtual void onDragStop(MultiTouchEvent& _event){};
	virtual void onRotateStart(MultiTouchEvent& _event){};
	virtual void onRotateStop(MultiTouchEvent& _event){};
	
	virtual void onStartMultiTouchScope(MultiTouchEvent& _event){};
	virtual void onUpdateMultiTouchScope(MultiTouchEvent& _event){};
	virtual void onEndMultiTouchScope(MultiTouchEvent& _event){};
	
	// Settings:
	void setDragTarget(BasicInteractiveObject* _dragtarget);
	void setMtTarget(BasicScreenObject* _mttarget);
    
	void setDragThreshold(float _dragthreshold);
	void setScaleThreshold(float _scalethreshold);
	void setRotationThreshold(float _rotationthreshold);
	void setTapThreshold(float _tapThreshold);
	
	void setDragDamping(float _dragDamping);
	void setScaleDamping(float _scaleDamping);
	void setRotationDamping(float _rotationDamping);

	void isDraggable(bool _isdraggable){isdraggable=_isdraggable;};
	bool isDraggable(){return isdraggable;};
	
	void isStDraggable(bool _isstdraggable){isstdraggable=_isstdraggable;};
	bool isStDraggable(){return isstdraggable;};
	
	void isScaleable(bool _isscaleable){isscaleable=_isscaleable;};
	bool isScaleable(){return isscaleable;};
	
	void isRotateable(bool _isrotateable){isrotateable=_isrotateable;};
	bool isRotateable(){return isrotateable;};
		
	void isDragAuto(bool _isdragauto){isdragauto=_isdragauto;};
	bool isDragAuto(){return isdragauto;};
	
	void isScaleAuto(bool _isscaleauto){isscaleauto=_isscaleauto;};
	bool isScaleAuto(){return isscaleauto;};
	
	void isRotateAuto(bool _isrotateauto){isrotateauto=_isrotateauto;};
	bool isRotateAuto(){return isrotateauto;};
	
	bool isDragging(){return isdragging;};
	bool isRotating(){return isrotating;};
	bool isScaleing(){return isscaling;};
	
	ofVec3f getDragSpeed(){return mttranslatespeed;};
	
	
	
	//events
	
	ofEvent<MultiTouchEvent> firstTouchDownEvent;
	ofEvent<MultiTouchEvent> lastTouchUpEvent;
	
	ofEvent<MultiTouchEvent> tapEvent;
	ofEvent<MultiTouchEvent> doubleTapEvent;
	ofEvent<MultiTouchEvent> swipeUpEvent;
	ofEvent<MultiTouchEvent> swipeDownEvent;
	ofEvent<MultiTouchEvent> swipeLeftEvent;
	ofEvent<MultiTouchEvent> swipeRightEvent;
	ofEvent<MultiTouchEvent> scaleStartEvent;
	ofEvent<MultiTouchEvent> scaleStopEvent;
	ofEvent<MultiTouchEvent> dragStartEvent;
	ofEvent<MultiTouchEvent> dragStopEvent;
	ofEvent<MultiTouchEvent> rotateStartEvent;
	ofEvent<MultiTouchEvent> rotateStopEvent;
	
	ofEvent<MultiTouchEvent> startMultiTouchScopeEvent;
	ofEvent<MultiTouchEvent> updateMultiTouchScopeEvent;
	ofEvent<MultiTouchEvent> endMultiTouchScopeEvent;
	
	// Functions called by Renderer:
	void touchDownOnMe(mtRay ray, int touchId);
	void touchMovedOnMe(mtRay ray, int touchId);
	void touchUpOnMe(mtRay ray, int touchId);
	
	void touchDownOutside(mtRay ray, int touchId);
	void touchMovedOutside(mtRay ray, int touchId);
	void touchUpOutside(mtRay ray, int touchId);
	
	// Internal handling of Multitouches
	void addMultiTouch(mtRay ray, int touchId);
	void updateMultiTouch(mtRay ray, int touchId);
	void removeMultiTouch(mtRay ray, int touchId);
	
	ofVec3f	mttranslate;
	ofVec3f mttranslatestart;
	ofVec3f mttranslatespeed;
	float	mttranslatedist;
	
	ofQuaternion	mtrotate;
	ofQuaternion	mtrotatestart;	
	ofQuaternion	mtrotatespeed;
	float			mtrotatedist;
	
	float mtscale;
	float mtscalestart;
	float mtscalespeed;
	float mtscaledist;
	
	ofVec3f mtpivot;
	
	virtual void setRoot(BasicScreenObject* _root);
	ofColor	pickingNameToColor(GLint _pickingName);
	GLint	colorToPickingName(ofColor& _color);
	
	map<int, MultiTouchPoint*>* getActiveMultiTouches() { return &activeMultiTouches; };
	
    
    ofMatrix4x4 mttransformmatrixstart; // Transformmatrix upon start of interactionScope
	ofMatrix4x4 mttransformmatrix; // Additional Transformmatrix during scope (start->now)
	
    
    
protected:
	
	ofVec3f camerapoint;	
		
	map<int, MultiTouchPoint*> activeMultiTouches;
	map<int, MultiTouchPoint*>::iterator amt;
	map<int, MultiTouchPoint*>::iterator amtinner;
	
	// Settings	
	
	bool isstdraggable;
	bool isdraggable;
	bool isscaleable;
	bool isrotateable;
	
	bool isdragauto;
	bool isscaleauto;
	bool isrotateauto;
	
	float dragthreshold;
	float scalethreshold;
	float rotatethreshold;
	float tapThreshold;
	
	float dragdamp;
	float scaledamp;
	float rotatedamp;
	
	// Scope
	int		mtcounter;
	long	mtstarttime;;
	bool	mtscoperunning;
	int		mtscopeduration;
	
	bool isdragging;
	bool isscaling;
	bool isrotating;
	
	// The relevant touchpoints for the interaction, the furthest apart
	MultiTouchPoint* mttoucha;
	MultiTouchPoint* mttouchb;
	
	
	// Vector made of relevant Touchpoint to create Rotation and Scale Transformations
	ofVec3f mttransform;
	ofVec3f mttransformstart;
	
	
	void	resetMTStartValues();
	ofVec3f getCurrentMtTransform();
	ofVec3f getCurrentMtTranslate();
	void	updateMtTransform();
	
	BasicInteractiveObject* dragtarget;
    BasicScreenObject* mttarget;
    
	int		getNumActiveTouches();
	bool	isMultiTouchActive(int touchId);

	mtPlane	plane;
};
