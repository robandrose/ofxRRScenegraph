#pragma once
#include "BasicController.h"
#include "State.h"
class State;
class StateController: public BasicController {
	
public:
	StateController() {};
	virtual ~StateController(){};
	
	int		getState()	{ return currentState; };
	void	setState( int newState );

protected:
	int				currentState;
	map<int,State*>	states;
};