#pragma once
#include "BasicScreenObject.h"
#include "Shapes.h";

class FpsMeter:public BasicScreenObject{
public:
	FpsMeter();
	void update();
	void _draw();
	void setSize(float _width, float _height);
	
	static const int MAX_SIZE = 1920;
	
private:
	float fpsList[MAX_SIZE];
	int currentIndex;
	int currentSize;
	float currentFps;
	float largest;
};