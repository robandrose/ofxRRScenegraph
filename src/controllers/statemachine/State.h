#pragma once
#include "StateController.h"

class StateController;
class State {
	
public:
	State()	{};
	virtual ~State(){};
	virtual void setController(StateController* _controller)	{ controller = _controller; };
	virtual void enter(int _lastState)	{};
	virtual void leave(int _newState)	{};

protected:
	StateController* controller;
};