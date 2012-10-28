/*
 *  BasicButton.h
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach on 26.10.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "BasicInteractiveObject.h"
#include "Image.h"

#define BUTTON_STATE_NORMAL 0
#define BUTTON_STATE_ACTIVE 1
#define BUTTON_STATE_SELECTED 2
#define BUTTON_STATE_DISABLED 3
#define BUTTON_STATE_SELECTED_ACTIVE 4



	


class BasicButton : public BasicInteractiveObject {
public:
	BasicButton();
	virtual ~BasicButton();	// destructor

	void onTap(MultiTouchEvent& _event);
	void onDoubleTap(MultiTouchEvent& _event);
	void onFirstTouchDown(MultiTouchEvent& _event);
	void onLastTouchUp(MultiTouchEvent& _event);	
	void onStartMultiTouchScope(MultiTouchEvent& _event);
	
	
	//virtual void setSize(float _width, float _height);
	
	virtual void setImage(ofImage* _normal, ofImage* _selected=NULL, ofImage* _active=NULL, ofImage* _disabled=NULL);
	virtual void toggle();
	virtual void select();
	virtual void deselect();
	virtual void enable();
	virtual void disable();
	
	bool isSelected();
	
	
	
protected:
	void _draw();
	void _drawForPicking();
	
	string mytxt;
	ofImage* currentImage;
	ofImage* active;
	ofImage* normal;
	ofImage* selected;
	ofImage* disabled;
    ofImage* temp;

	bool isenabled;
	bool isselected;
	
	bool hasactiveimage;
	

};