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
class HorizontalRestrictor: public IPositioner {
public:
	HorizontalRestrictor();
	HorizontalRestrictor(float _hPos);
	void setRestrictionValue(float _hPos);
	
	void restrict(BasicScreenObject* _object);
	
private:
	float hPos;
	bool isSetup;
};