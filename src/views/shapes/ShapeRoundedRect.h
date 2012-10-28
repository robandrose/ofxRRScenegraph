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
	void _draw();
	void setupShape(float r=10);
	
	ofVboMesh* mesh;
	
	
};