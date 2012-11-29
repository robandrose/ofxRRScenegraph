/*
 *  ShapeRoundedRect.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
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


