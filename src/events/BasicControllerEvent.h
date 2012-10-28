/*
 *  BasicScreenObjectEvent.h
 *  BasicScreenObject_Test
 *
 *  Created by Matthias Rohrbach 2 on 10.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#pragma once

class BasicController;
class BasicControllerEvent {	
public:
	BasicController* target;
	void* args;
	string message;
	
	
	BasicControllerEvent() {
		target = NULL;
		message="";
		
	}
	BasicControllerEvent(BasicController* _target) {
		target = _target;
		message="";
		
	}
};