//
//  Schnipsel.cpp
//  RRScenegraph_example
//
//  Created by Matthias Rohrbach on 22.08.14.
//
//

#include "Schnipsel.h"

Schnipsel::Schnipsel() {
    
}


void Schnipsel::_draw(){
	ofRect(0,0,width,height);
}


void Schnipsel::onTap(MultiTouchEvent&e){
    cout << "onTap";
    moveMeToTop();
    
}

void Schnipsel::onDoubleTap(MultiTouchEvent& e){
    moveMeToBottom();
}