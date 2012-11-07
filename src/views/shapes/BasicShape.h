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
	virtual void isFilled(bool filled);
	virtual bool isFilled();
	virtual void setStrokeWidth(float _sWidth);
	virtual float getStrokeWidth();
	ofPath path;

protected:
	bool _isFilled;
	float _strokeWidth;
};