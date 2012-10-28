/*
 *  BasicController.h
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "BasicControllerEvent.h"


class BasicController {
	
public:
	BasicController();
	virtual ~BasicController();
	
protected:
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
	void _exit(ofEventArgs &e);
	
	virtual void setup(){};
	virtual void update(){};
	virtual void exit(){};
	
	BasicControllerEvent myEventArgs;
	
	
};