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


class BasicButton : public BasicInteractiveObject {
	
public:
	BasicButton();
	virtual ~BasicButton();	// destructor
	
	ofEvent<BasicScreenObjectEvent> pressEvent;
	ofEvent<BasicScreenObjectEvent> releaseEvent;

	virtual void onTap(MultiTouchEvent& _event){};
	virtual void onDoubleTap(MultiTouchEvent& _event){};
	virtual void onFirstTouchDown(MultiTouchEvent& _event);
	virtual void onLastTouchUp(MultiTouchEvent& _event);	
	virtual void onStartMultiTouchScope(MultiTouchEvent& _event) {};
	
	virtual void setImage(ofImage* _normal, ofImage* _selected=NULL, ofImage* _active=NULL, ofImage* _disabled=NULL);
	virtual void toggle();
	virtual void select();
	virtual void deselect();
	virtual void enable();
	virtual void disable();
	virtual void isScalingImage(bool _scale);
	virtual bool isScalingImage();
	
	bool isSelected();
	
	
protected:
	virtual void _draw();
	
	string mytxt;
	ofImage* currentImage;
	ofImage* active;
	ofImage* normal;
	ofImage* selected;
	ofImage* disabled;
    ofImage* temp;

	bool isEnabled;
	bool _isSelected;
	bool hasActiveimage;
	bool _isScalingImage;
};