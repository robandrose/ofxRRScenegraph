/*
 ShapeRoundedRect
 
 The oh so beloved rounded rectangle
 
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
#include "ShapeRoundedRect.h"

ShapeRoundedRect::ShapeRoundedRect() {
	cornerRadius = 10.0;
}


void ShapeRoundedRect::_draw(){
	
	path.setStrokeWidth(_strokeWidth);
	path.setFillColor(ofColor(color.r,color.g,color.b,getCombinedAlpha()));
	path.setStrokeColor(ofColor(color.r,color.g,color.b,getCombinedAlpha()));
	path.setFilled(_isFilled);
	path.draw();
}


void ShapeRoundedRect::setRadius(float r){
	
	// way faster than ofRectRounded()!!!
	
	cornerRadius = r;
	
	float x=0;
	float y=0;
	float z=0;
	float w=getWidth();
	float h=getHeight();
	
	float x2 = x + w;
	float y2 = y + h;
	
	if (r > w || r > h){
		ofRect(x, y, z, w, h);
		return;
	}
	path.setCurveResolution(5);
	path.clear();
	path.lineTo(x+r, y);
	path.bezierTo(x,y, x,y+r, x,y+r);
	path.lineTo(x, y2-r);
	path.bezierTo(x,y2, x+r,y2, x+r,y2);
	path.lineTo(x2-r, y2);
	path.bezierTo(x2,y2, x2,y2-r, x2,y2-r);
	path.lineTo(x2, y+r);
	path.bezierTo(x2,y, x2-r,y, x2-r,y);
	path.lineTo(x+r, y);
	path.close();
}


