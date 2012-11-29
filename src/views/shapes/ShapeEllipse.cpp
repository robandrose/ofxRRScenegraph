#include "ShapeEllipse.h"



ShapeEllipse::ShapeEllipse() {
	resolution = 50;
	mode = OF_RECTMODE_CENTER;
}


void ShapeEllipse::_draw(){
	//path.setFillColor(ofColor(color.r,color.g,color.b,getCombinedAlpha()));
	ofPushStyle();
	if (_isFilled) {
		ofFill();
	} else {
		ofNoFill();
	}
	ofSetLineWidth(_strokeWidth);
	ofSetCircleResolution(resolution);
	if (mode==OF_RECTMODE_CENTER) {
		ofEllipse(0, 0, width, height);
	} else if (mode==OF_RECTMODE_CORNER) {
		ofEllipse(width/2.0, height/2.0, width, height);
	}
	
	ofPopStyle();
}