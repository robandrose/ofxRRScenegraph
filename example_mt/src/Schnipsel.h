//
//  Schnipsel.h
//  RRScenegraph_example
//
//  Created by Matthias Rohrbach on 22.08.14.
//
//

#pragma once
#include "BasicInteractiveObject.h"

class Schnipsel : public BasicInteractiveObject {
public:
	Schnipsel();
	virtual ~Schnipsel() {};	// destructor
	
    
protected:
	void _draw();
    
    void onTap(MultiTouchEvent &e);
    void onDoubleTap(MultiTouchEvent &e);
    
};