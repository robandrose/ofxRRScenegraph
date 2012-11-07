/*
 *  BasicShape.cpp
 *  Picking_in_3d
 *
 *  Created by Matthias Rohrbach on 02.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "BasicShape.h"

BasicShape::BasicShape() {
	_isFilled		= true;
	_strokeWidth	= 1.0;
}

bool BasicShape::isFilled() {
	return _isFilled;
}

void BasicShape::isFilled(bool filled) {
	_isFilled = filled;
}

float BasicShape::getStrokeWidth() {
	return _strokeWidth;
}

void BasicShape::setStrokeWidth(float _sWidth) {
	_strokeWidth = _sWidth;
}




