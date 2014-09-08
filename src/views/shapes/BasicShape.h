/*
 BasicShape
 
 Baseclass for a Shape, contains a ofPath for drawing more complex stuff
 
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


class BasicShape:public BasicScreenObject{
	
public:
	BasicShape();
	virtual void _draw(){};
	virtual void isFilled(bool filled)			{ _isFilled = filled; };
	virtual bool isFilled()						{ return _isFilled; };
	virtual void setStrokeWidth(float _sWidth)	{ _strokeWidth = _sWidth; };
	virtual float getStrokeWidth()				{ return _strokeWidth; };
    virtual void setStrokeColor(ofColor _color) { _strokeColor=_color;};
	
	ofPath path;

protected:
	bool _isFilled;
	float _strokeWidth;
        ofColor _strokeColor;
};