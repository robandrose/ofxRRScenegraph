//
//  InteractiveElement.h
//  RRScenegraph_example
//
//  Created by Matthias Rohrbach on 07.09.14.
//
//

#include "BasicInteractiveObject.h"

class InteractiveElement : public BasicInteractiveObject {
public:
	InteractiveElement();
	virtual ~InteractiveElement() {};	// destructor
  
    
protected:
    
    void _draw();
	void _drawForPicking();
    void onTap(MultiTouchEvent& e);
    
    ofBoxPrimitive mybox;
};