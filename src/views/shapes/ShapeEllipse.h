#pragma once
#include "BasicShape.h"


class ShapeEllipse:public BasicShape{
public:
	ShapeEllipse();
	void _draw();
	void setResolution(int resolution);

protected:
	int resolution;
};