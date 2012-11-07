#include "ShapeEllipse.h"

ShapeEllipse::ShapeEllipse() {
	resolution = 50;
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
	ofEllipse(0, 0, width, height);
	ofPopStyle();
}

void ShapeEllipse::setResolution(int _resolution) {
	resolution = _resolution;
}