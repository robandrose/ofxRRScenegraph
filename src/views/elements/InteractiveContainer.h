#pragma once
#include "BasicInteractiveObject.h"

class InteractiveContainer : public BasicInteractiveObject {
public:
	InteractiveContainer();
	virtual ~InteractiveContainer();	// destructor
	bool isFilled();
	void isFilled(bool _filled);

protected:
	void _draw();
	void _drawForPicking();
	bool _isFilled;
};