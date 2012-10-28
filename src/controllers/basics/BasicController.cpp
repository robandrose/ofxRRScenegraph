/*
 *  BasicController.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "BasicController.h"

BasicController::BasicController() {
	
	
	myEventArgs.target=this;
	
	
	ofAddListener(ofEvents().setup, this, &BasicController::_setup);
    ofAddListener(ofEvents().update, this, &BasicController::_update);
	ofAddListener(ofEvents().exit, this, &BasicController::_exit);
	
	
}

BasicController::~BasicController() {
	ofRemoveListener(ofEvents().setup, this, &BasicController::_setup);
    ofRemoveListener(ofEvents().update, this, &BasicController::_update);
	ofRemoveListener(ofEvents().exit, this, &BasicController::_exit);
}

void BasicController::_setup(ofEventArgs &e){setup();}
void BasicController::_update(ofEventArgs &e){update();}
void BasicController::_exit(ofEventArgs &e){exit();}
