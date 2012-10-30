#include "ShapeEllipse.h"

ShapeEllipse::ShapeEllipse() {
	resolution = 50;
}
void ShapeEllipse::_draw(){
	ofSetCircleResolution(resolution);
	ofEllipse(0, 0, width, height);
}

void ShapeEllipse::setResolution(int _resolution) {
	resolution = _resolution;
}