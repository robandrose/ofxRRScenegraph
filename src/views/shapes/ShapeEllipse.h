#pragma once
#include "BasicShape.h"


class ShapeEllipse:public BasicShape{
public:
	ShapeEllipse();
	void _draw();
	void setResolution(int resolution);
	void setEllipseMode(int _mode);

protected:
	int resolution;
	int mode; // like ofRectMode
};