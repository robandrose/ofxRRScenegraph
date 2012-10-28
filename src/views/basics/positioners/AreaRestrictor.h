/*
 *  AreaRestrictor.h
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 05.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "IPositioner.h"
#include "BasicScreenObject.h"

//class IPositioner;
class AreaRestrictor: public IPositioner {
public:
	AreaRestrictor();
	AreaRestrictor(ofRectangle _restarea, ofRectangle _srcarea);
	void setRestrictionValue(ofRectangle _area, ofRectangle _srcarea);
	
	void restrict(BasicScreenObject* _object);
	
private:

	ofRectangle srcarea;
	ofRectangle restarea;
	
	bool isSetup;
};