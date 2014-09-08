#pragma once
#include "BasicShape.h"

class ShapeRoundedRect:public BasicShape{

public:	
	ShapeRoundedRect();
	void _draw();
	void setRadius(float r);

protected:
	float cornerRadius;
	
};