#pragma once
#include "BasicInteractiveObject.h"
#include "TextField.h"
#include "ShapeRect.h"


class TextButton : public BasicInteractiveObject {
	
public:
	TextButton();
	virtual ~TextButton();	// destructor
	
	void update();
	
	ofEvent<BasicScreenObjectEvent> pressEvent;
	ofEvent<BasicScreenObjectEvent> releaseEvent;

	virtual void onTap(MultiTouchEvent& _event){};
	virtual void onDoubleTap(MultiTouchEvent& _event){};
	virtual void onFirstTouchDown(MultiTouchEvent& _event);
	virtual void onLastTouchUp(MultiTouchEvent& _event);	
	virtual void onStartMultiTouchScope(MultiTouchEvent& _event) {};

	virtual void setText(string _txt);
	virtual void setColors(ofColor _normal, ofColor _selected = NULL, ofColor _active=NULL, ofColor _disabled=NULL);
	virtual void toggle();
	virtual void select();
	virtual void deselect();
	virtual void enable();
	virtual void disable();
	
	virtual void setSize(float _width, float _height);

	
	bool isSelected();
	
	
protected:
	virtual void _draw();
	
	virtual void layout();
	
	TextField	text;
	ofColor		currentColor;
	ofColor		activeColor;
	ofColor		normalColor;
	ofColor		selectedColor;
	ofColor		disabledColor;
	ofColor		tempColor;
	
	ShapeRect	bg;
	
	bool	needsRelayout;
	
	bool	isEnabled;
	bool	_isSelected;
	bool	hasActiveimage;
	bool	_isScalingImage;
};