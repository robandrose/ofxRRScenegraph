/*
 *  MathHelper.cpp
 *  Picking_in_3d
 *
 *  Created by Patrick Meister on 03.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MathHelper.h"

bool MathHelper::isAnlgeBetween(float _angle, float _startAngle, float _endAngle) {
	_angle = cleanAngle(_angle);
	
	if (_startAngle < _endAngle) return (_startAngle <= _angle && _angle <= _endAngle);
	return (_startAngle <= _angle || _angle <= _endAngle);
}

float MathHelper::cleanAngle(float _dirtyAngle) {
	return fmod(360 + fmod(_dirtyAngle,360),360);
}

int MathHelper::minInt(int a, int b) {
	if (b < a) return b;
	return a;
}

float MathHelper::minFloat(float a, float b) {
	if (b<a) return b;
	return a;
}

int MathHelper::maxInt(int a, int b) {
	if (b > a) return b;
	return a;
}

float MathHelper::maxFloat(float a, float b) {
	if (b > a) return b;
	return a;
}