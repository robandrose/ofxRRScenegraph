#include "InteractiveContainer.h"


InteractiveContainer::InteractiveContainer() {
	_isFilled = true;
}


void InteractiveContainer::_draw(){
	if (_isFilled==true) { ofRect(0,0,width,height); } 
}


void InteractiveContainer::_drawForPicking(){
	ofRect(0,0,width,height);
}
