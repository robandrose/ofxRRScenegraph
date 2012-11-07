/*
 *  ShapeRect.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "ShapeRect.h"

void ShapeRect::_draw(){
	ofPushStyle();
	if (_isFilled) {
		ofFill();
	} else {
		ofNoFill();
	}
	ofSetLineWidth(_strokeWidth);
	ofRect(0, 0, width, height);
	ofPopStyle();
}