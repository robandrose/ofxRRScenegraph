#include "BasicController.h"

BasicController::BasicController() {
	myEventArgs.target=this;
	ofAddListener(ofEvents().setup, this, &BasicController::_setup);
    ofAddListener(ofEvents().update, this, &BasicController::_update);
	ofAddListener(ofEvents().draw, this, &BasicController::_draw);
	ofAddListener(ofEvents().exit, this, &BasicController::_exit);
	ofAddListener(ofEvents().keyPressed, this, &BasicController::_keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &BasicController::_keyReleased);
}

BasicController::~BasicController() {
	ofRemoveListener(ofEvents().setup, this, &BasicController::_setup);
    ofRemoveListener(ofEvents().update, this, &BasicController::_update);
	ofRemoveListener(ofEvents().draw, this, &BasicController::_draw);
	ofRemoveListener(ofEvents().exit, this, &BasicController::_exit);
	ofRemoveListener(ofEvents().keyPressed, this, &BasicController::_keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &BasicController::_keyReleased);
}

void BasicController::_setup(ofEventArgs &e){setup();}
void BasicController::_update(ofEventArgs &e){update();}
void BasicController::_draw(ofEventArgs &e){draw();}
void BasicController::_exit(ofEventArgs &e){exit();}
void BasicController::_keyPressed(ofKeyEventArgs &e){keyPressed(e);}
void BasicController::_keyReleased(ofKeyEventArgs &e){keyReleased(e);}

