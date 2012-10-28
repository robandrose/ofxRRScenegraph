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
	
	virtual void _draw();
	
	ofPath path;
	
};