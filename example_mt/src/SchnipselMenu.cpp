//
//  SchnipselMenu.cpp
//  RRScenegraph_example
//
//  Created by Matthias Rohrbach on 22.08.14.
//
//

#include "SchnipselMenu.h"

SchnipselMenu::SchnipselMenu() {
    
}


void SchnipselMenu::_draw(){
	ofRect(0,0,width,height);
}


void SchnipselMenu::onTap(MultiTouchEvent&e){
    cout << "onTap";
    moveMeToTop();
    
}

void SchnipselMenu::onDoubleTap(MultiTouchEvent& e){
    moveMeToBottom();
}