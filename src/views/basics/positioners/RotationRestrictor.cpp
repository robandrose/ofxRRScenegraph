#include "IPositioner.h"
#include "RotationRestrictor.h"

RotationRestrictor::RotationRestrictor(float _minRotation, float _maxRotation) {
	minRotation = fmod(360 + fmod(_minRotation,360),  360);	// handle negative and positive wrap-around
	maxRotation = fmod(360 + fmod(_maxRotation,360), 360);
}

RotationRestrictor::RotationRestrictor() {
	minRotation = 0;
	maxRotation = 360;
}

void RotationRestrictor::setRestrictionValue(float _minRotation, float _maxRotation) {
	minRotation = fmod(360 + fmod(_minRotation,360),  360);	// handle negative and positive wrap-around
	maxRotation = fmod(360 + fmod(_maxRotation,360), 360);
};


void RotationRestrictor::restrict(BasicScreenObject* _object) {
	ofQuaternion orientation = _object->getOrientationQuat();
	ofVec3f norm(1,0,0);
	norm = norm * orientation;
	norm.z = 0;
	ofVec2f norm2d;
	norm2d.set(norm);
	float angle=norm2d.angle(ofVec2f(1,0));
	if (angle>0) { angle = 360-angle;}
	if (angle<0) { angle = angle*-1;}
	
	//cout << angle <<endl;
	
	
	if (! MathHelper::isAnlgeBetween(angle, minRotation, maxRotation)) {
		// angle is not within range, so find which is closer, min or max
		float minDiff = fabs(ofAngleDifferenceDegrees(minRotation, angle));
		float maxDiff = fabs(ofAngleDifferenceDegrees(maxRotation, angle));
		if (minDiff<maxDiff) { 
			angle = minRotation;
		} else {
			angle = maxRotation;
		}
		_object->setOrientation(ofVec3f(norm.x, norm.y, angle));
	}
	

};
