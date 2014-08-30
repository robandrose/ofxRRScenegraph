/*
 *  ShapeRect.h
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */


#pragma once
#include "BasicShape.h"


class ShapeRect:public BasicShape{

public:
	
	ShapeRect();
	void _draw();
	void setRectMode(ofRectMode _mode)	{ mode = _mode; };
    
	
protected:
	ofRectMode mode;
};