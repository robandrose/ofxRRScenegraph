/*
 *  HorizontalRestrictor.h
 *  BasicScreenObject_Test
 *
 *  Created by Patrick Meister on 26.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "IPositioner.h"
#include "BasicScreenObject.h"


//class IPositioner;
class ArcRestrictor: public IPositioner {
public:
	ArcRestrictor();
	ArcRestrictor(ofVec2f _pivotPoint, float _radius, float _minAngle, float _maxAngle);
	void setRestrictionValue(ofVec2f _pivotPoint, float _radius, float _minAngle, float _maxAngle);
	
	void restrict(BasicScreenObject* _object);
	
private:
	ofVec2f pivotPoint;
	float radius;
	float minAngle;
	float maxAngle;
	//float currentAngle;
	bool isSetup;
};