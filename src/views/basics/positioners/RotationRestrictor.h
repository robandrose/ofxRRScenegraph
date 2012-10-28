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
class RotationRestrictor: public IPositioner {
public:
	RotationRestrictor();
	RotationRestrictor(float _minRotation, float _maxRotation);
	void setRestrictionValue(float _minRotation, float _maxRotation);
	
	void restrict(BasicScreenObject* _object);
	
private:
	float minRotation;
	float maxRotation;
	bool isSetup;
};