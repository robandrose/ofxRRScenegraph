/*
 ScaleRestrictor
 
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
#include "BasicInteractiveObject.h"
#include "TextField.h"
#include "ShapeRect.h"

class TextButton : public BasicInteractiveObject {
	
public:
	TextButton();
	virtual ~TextButton() {};	// destructor
	
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

	bool isSelected()	{ return _isSelected; };
	TextField	text;
	ShapeRect	bg;
  	
protected:
	virtual void _draw();
	virtual void layout();
	
	ofColor		currentColor;
	ofColor		activeColor;
	ofColor		normalColor;
	ofColor		selectedColor;
	ofColor		disabledColor;
	ofColor		tempColor;
	
	bool	needsRelayout;
	bool	isEnabled;
	bool	_isSelected;
	bool	hasActiveColor;
};