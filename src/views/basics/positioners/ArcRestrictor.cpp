/*
 *  HorizontalRestrictor.cpp
 *  BasicScreenObject_Test
 *
 *  Created by Patrick Meister on 26.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "IPositioner.h"
#include "ArcRestrictor.h"

ArcRestrictor::ArcRestrictor(ofVec2f _pivotPoint, float _radius, float _minAngle, float _maxAngle) {
	pivotPoint = _pivotPoint;
	radius = _radius;
	minAngle = _minAngle;
	maxAngle = _maxAngle;
}

ArcRestrictor::ArcRestrictor() {
	pivotPoint = ofVec2f(0,0);
	radius = 100;
	minAngle = 0;
	maxAngle = 360;
}

void ArcRestrictor::setRestrictionValue(ofVec2f _pivotPoint, float _radius, float _minAngle, float _maxAngle) {
	pivotPoint = _pivotPoint;
	radius = _radius;
	minAngle = _minAngle;
	maxAngle = _maxAngle;
};


void ArcRestrictor::restrict(BasicScreenObject* _object) {
	// get angle to pivot point, find allowed angle
	ofVec2f vec = _object->getPosition()-pivotPoint;
	float angle = atan2(vec.y, vec.x);
	
	if (angle<0) { angle = TWO_PI+angle; }
	
	angle = ofRadToDeg(angle);
		
	if (! MathHelper::isAnlgeBetween(angle, minAngle, maxAngle)) {
		// angle is not within range, so find which is closer, min or max
		float minDiff = fabs(ofAngleDifferenceDegrees(minAngle, angle));
		float maxDiff = fabs(ofAngleDifferenceDegrees(maxAngle, angle));
		if (minDiff<maxDiff) { 
			angle = minAngle;
		} else {
			angle = maxAngle;
		}

	}
	
	// find final position taking radius into account
	_object->setX(pivotPoint.x + cos(ofDegToRad(angle))*radius);
	_object->setY(pivotPoint.y + sin(ofDegToRad(angle))*radius);
};