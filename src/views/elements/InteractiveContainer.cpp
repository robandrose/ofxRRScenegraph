#include "InteractiveContainer.h"


InteractiveContainer::InteractiveContainer() {
	_isFilled = true;
}

InteractiveContainer::~InteractiveContainer(){
}

void InteractiveContainer::_draw(){
	if (_isFilled==true) { ofRect(0,0,width,height); } 
}


void InteractiveContainer::_drawForPicking(){
	ofRect(0,0,width,height);
}

bool InteractiveContainer::isFilled() { return _isFilled; }
void InteractiveContainer::isFilled(bool _filled) { _isFilled = _filled; }