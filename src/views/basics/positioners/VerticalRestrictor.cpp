/*
 *  HorizontalRestrictor.cpp
 *  BasicScreenObject_Test
 *
 *  Created by Patrick Meister on 26.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "IPositioner.h"
#include "VerticalRestrictor.h"

VerticalRestrictor::VerticalRestrictor(float _vPos) {
	vPos=_vPos;
}

VerticalRestrictor::VerticalRestrictor() {
	vPos=0;
}

void VerticalRestrictor::setRestrictionValue(float _vPos) {
	vPos=_vPos;
};


void VerticalRestrictor::restrict(BasicScreenObject* _object) {
	_object->setX(vPos);
};