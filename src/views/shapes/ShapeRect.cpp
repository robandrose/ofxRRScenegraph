#include "ShapeRect.h"

ShapeRect::ShapeRect() {
	mode = OF_RECTMODE_CORNER;
}


void ShapeRect::_draw(){
	ofPushStyle();
	if (_isFilled) {
		ofFill();
	} else {
		ofNoFill();
	}
	ofSetRectMode(mode);
	ofFill();
	
    ofRect(0, 0, width, height);
	
    ofSetLineWidth(_strokeWidth);
    ofNoFill();
    ofSetColor(_strokeColor, getCombinedAlpha());
    
    ofRect(0, 0, width, height);
	
    
    ofPopStyle();
}