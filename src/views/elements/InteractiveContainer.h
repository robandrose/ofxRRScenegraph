#pragma once
#include "BasicInteractiveObject.h"

class InteractiveContainer : public BasicInteractiveObject {
public:
	InteractiveContainer();
	virtual ~InteractiveContainer() {};	// destructor
	
	bool isFilled()				{ return _isFilled; };
	void isFilled(bool _filled) { _isFilled = _filled; };

protected:
	void _draw();
	void _drawForPicking();
	bool _isFilled;
};