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
class ScaleRestrictor: public IPositioner {
public:
	ScaleRestrictor();
	ScaleRestrictor(float _minScale, float _maxScale);
	void setRestrictionValue(float _minScale, float _maxScale);
	
	void restrict(BasicScreenObject* _object);
	
private:
	float minScale;
	float maxScale;
	bool isSetup;
};