//
//  InteractiveElement.cpp
//  RRScenegraph_example
//
//  Created by Matthias Rohrbach on 07.09.14.
//
//

#include "InteractiveElement.h"

InteractiveElement::InteractiveElement(){
    
}

void InteractiveElement::_draw(){
    mybox.set(width, height, 100);
    mybox.drawFaces();    
    
}
void InteractiveElement::_drawForPicking(){
    mybox.drawFaces();    
}

void InteractiveElement::onTap(MultiTouchEvent& e){
    mybox.rotate(30,0,1,0);
}