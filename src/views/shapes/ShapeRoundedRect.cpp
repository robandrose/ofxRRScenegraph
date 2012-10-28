/*
 *  ShapeRoundedRect.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "ShapeRoundedRect.h"

void ShapeRoundedRect::_draw(){
	/*if(mesh!=NULL){
		mesh->draw();
		
	}*/

	path.draw();
	
}

//----------------------------------------------------------
void ShapeRoundedRect::setupShape(float r){
	
	
	float x=0;
	float y=0;
	float z=0;
	float w=getWidth();
	float h=getHeight();
	
	float x2 = x + w;
	float y2 = y + h;
	
	if (r > w || r > h){
		ofRect(x, y, z, w, h);
		return;
	}
	path.setCurveResolution(5);
	path.clear();
	path.lineTo(x+r, y);
	path.bezierTo(x,y, x,y+r, x,y+r);
	path.lineTo(x, y2-r);
	path.bezierTo(x,y2, x+r,y2, x+r,y2);
	path.lineTo(x2-r, y2);
	path.bezierTo(x2,y2, x2,y2-r, x2,y2-r);
	path.lineTo(x2, y+r);
	path.bezierTo(x2,y, x2-r,y, x2-r,y);
	path.lineTo(x+r, y);
	path.close();
	
		
	//mesh=new ofVboMesh(path.getTessellation());
	
	//mesh->setUsage(GL_STATIC_DRAW);
	//mesh->setMode(OF_PRIMITIVE_LINE_STRIP);
	
}


