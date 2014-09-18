#include "StateController.h"


void StateController::setState(int newState) {
	ofLog(OF_LOG_NOTICE, "state changing from %i to %i", currentState, newState);
	int oldState = currentState;
	currentState = newState;		// changing it here already, in case state is changed again in leave/enter methods
	states[oldState]->leave(newState);
	states[newState]->enter(oldState);
}
