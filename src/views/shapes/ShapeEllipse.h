#pragma once
#include "BasicShape.h"


class ShapeEllipse:public BasicShape{

public:
	ShapeEllipse();
	void _draw();
	void setResolution(int _resolution)	{ resolution = _resolution; };
	void setEllipseMode(int _mode)		{ mode = _mode; };

	
protected:
	int resolution;
	int mode; // like ofRectMode
};