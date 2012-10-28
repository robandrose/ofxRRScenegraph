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
class VerticalRestrictor: public IPositioner {
public:
	VerticalRestrictor();
	VerticalRestrictor(float _vPos);
	void setRestrictionValue(float _vPos);
	
	void restrict(BasicScreenObject* _object);
	
private:
	float vPos;
	bool isSetup;
};