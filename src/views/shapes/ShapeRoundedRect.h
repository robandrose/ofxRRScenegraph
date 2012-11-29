/*
 *  ShapeRoundedRect.h
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

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