/*
 *  ShapeRect.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "ShapeRect.h"



ShapeRect::ShapeRect() {
	mode = OF_RECTMODE_CORNER;
}


void ShapeRect::_draw(){
	ofPushStyle();
	if (_isFilled) {
		ofFill();
	} else {
		ofNoFill();
	}
	ofSetRectMode(mode);
	ofRect(0, 0, width, height);
	
    ofSetLineWidth(_strokeWidth);
	ofSetColor(_strokeColor, getCombinedAlpha());
    ofNoFill();
    ofRect(0, 0, width, height);
	
    ofPopStyle();
}