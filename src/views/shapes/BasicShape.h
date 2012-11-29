/*
 *  BasicShape.h
 *  Picking_in_3d
 *
 *  Created by Matthias Rohrbach on 02.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#pragma once
#include "BasicScreenObject.h"


class BasicShape:public BasicScreenObject{
	
public:
	BasicShape();
	virtual void _draw(){};
	virtual void isFilled(bool filled)			{ _isFilled = filled; };
	virtual bool isFilled()						{ return _isFilled; };
	virtual void setStrokeWidth(float _sWidth)	{ _strokeWidth = _sWidth; };
	virtual float getStrokeWidth()				{ return _strokeWidth; };
	
	ofPath path;

protected:
	bool _isFilled;
	float _strokeWidth;
};