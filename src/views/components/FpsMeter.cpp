#include "FpsMeter.h"

FpsMeter::FpsMeter(){
	setSize(100, 30);
	color = ofColor(255,255,255,255);
	warningThreshold = 120;
}


void FpsMeter::update() {
	BasicScreenObject::update();
	
	currentFps				= ofGetFrameRate();
	fpsList[currentIndex]	= currentFps;
	currentIndex			= (currentIndex + 1) % currentSize;
	
	largest = 0;
	for (int i=0; i < currentSize; i++) {
		if (fpsList[i]>largest) largest = fpsList[i];
	}
}

void FpsMeter::_draw() {
	ofPushStyle();
	ofSetColor(color);
	
	ofNoFill();
	ofSetLineWidth(1);
	ofRect(1, 1, width-1, height-1);
	
	int oldestIndex = (currentIndex+1)%currentSize;
	int currentPos = 0;
	for (int i=0; i < currentSize; i++) {
		currentPos = (oldestIndex + i) % currentSize;
		if (fpsList[currentPos] < warningThreshold) {
			ofSetColor(255, 0, 0);
		} else {
			ofSetColor(color);
		}
		ofLine(i, height, i, height-ofMap(fpsList[currentPos], 0.0, largest, 0.0, height, false) );
	}
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("fps: " + ofToString(int(currentFps)), 5,height/2+5 );
	ofPopStyle();
}

void FpsMeter::setSize(float _width, float _height){
	_width = ofClamp(_width, 0, MAX_SIZE);
	BasicScreenObject::setSize(_width, _height);
	currentSize = _width;
	currentIndex = 0;
	largest = 0;
}