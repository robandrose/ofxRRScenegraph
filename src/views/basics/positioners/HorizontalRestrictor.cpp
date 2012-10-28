/*
 *  HorizontalRestrictor.cpp
 *  BasicScreenObject_Test
 *
 *  Created by Patrick Meister on 26.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "IPositioner.h"
#include "HorizontalRestrictor.h"

HorizontalRestrictor::HorizontalRestrictor(float _hPos) {
	hPos=_hPos;
}

HorizontalRestrictor::HorizontalRestrictor() {
	hPos = 0;
}

void HorizontalRestrictor::setRestrictionValue(float _hPos) {
	hPos=_hPos;
};


void HorizontalRestrictor::restrict(BasicScreenObject* _object) {
	_object->setY(hPos);
};