#include "IPositioner.h"
#include "ScaleRestrictor.h"
#include "BasicInteractiveObject.h"

ScaleRestrictor::ScaleRestrictor(float _minScale, float _maxScale) {
	minScale = _minScale;
	maxScale = _maxScale;
}

ScaleRestrictor::ScaleRestrictor() {
	minScale = 0;
	maxScale = 360;
}

void ScaleRestrictor::setRestrictionValue(float _minScale, float _maxScale) {
	minScale = _minScale;
	maxScale = _maxScale;
};


void ScaleRestrictor::restrict(BasicScreenObject* _object) {
	
	
	float scale = _object->getScale().x;
	//cout << "z-orientation: " << orientation.z << endl;
	if (scale < minScale){
		_object->setScale(minScale);
	}
	if (scale > maxScale){
		_object->setScale(maxScale);
	}
	
	/*
	BasicInteractiveObject* io=(BasicInteractiveObject*)_object;
	
	float mtscale=io->mtscalestart*io->mtscale;
	
	if (mtscale < minScale){
		io->mtscale=(float)minScale/io->mtscalestart;
	}
	if (mtscale > maxScale){
		io->mtscale=(float)maxScale/io->mtscalestart;
	}
	*/
	
};
