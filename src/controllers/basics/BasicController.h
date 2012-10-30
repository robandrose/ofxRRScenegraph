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
	
	BasicControllerEvent myEventArgs;

	
protected:
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
	void _draw(ofEventArgs &e);
	void _exit(ofEventArgs &e);
	void _keyPressed(ofKeyEventArgs &e);
	void _keyReleased(ofKeyEventArgs &e);
	
		
	
	virtual void setup(){};
	virtual void update(){};
	virtual void draw(){};
	virtual void exit(){};
	virtual void keyPressed(ofKeyEventArgs &e){};
	virtual void keyReleased(ofKeyEventArgs &e){};
};