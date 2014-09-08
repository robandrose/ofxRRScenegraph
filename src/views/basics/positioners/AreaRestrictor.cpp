#include "AreaRestrictor.h"

AreaRestrictor::AreaRestrictor(ofRectangle _restarea, ofRectangle _srcarea) {
	restarea.set(_restarea);
	srcarea.set(_srcarea);
}

AreaRestrictor::AreaRestrictor() {
	restarea.set(0, 0, 100, 100);
	srcarea.set(0,0,0,0);
	
}

void AreaRestrictor::setRestrictionValue(ofRectangle _restarea, ofRectangle _srcarea) {
	restarea.set(_restarea);
	srcarea.set(_srcarea);
	
};


void AreaRestrictor::restrict(BasicScreenObject* _object) {
	
	ofVec3f newpos=_object->getPosition();
	
	if(newpos.x<restarea.x-srcarea.x){
		newpos.x=restarea.x-srcarea.x;
	}
	if(newpos.y<restarea.y-srcarea.y){
		newpos.y=restarea.y-srcarea.y;
	}
	
	if(newpos.x>(restarea.x+restarea.width)-(srcarea.x+srcarea.width)){
		newpos.x=(restarea.x+restarea.width)-(srcarea.x+srcarea.width);
	}
	
	if(newpos.y>(restarea.y+restarea.height)-(srcarea.y+srcarea.height)){
		newpos.y=(restarea.y+restarea.height)-(srcarea.y+srcarea.height);
	}
	
	
	_object->setPosition(newpos);
	
};
