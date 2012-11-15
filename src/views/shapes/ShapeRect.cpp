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
	ofSetLineWidth(_strokeWidth);
	ofRect(0, 0, width, height);
	ofPopStyle();
}

void ShapeRect::setRectMode(ofRectMode _mode) {
	mode = _mode;
}