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