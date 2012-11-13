/*
 *  Image.h
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */


#pragma once
#include "BasicScreenObject.h"


class Image:public BasicScreenObject{
public:
	Image();
	virtual ~Image();
	
	void setup();
	void update();
	
	void load(string _filename);
	void setImagePointer(ofImage* _img);
	ofImage* getImagePointer();
	
	void setSize(float _width, float _height);
	void updateRealImageSize();
	void isUpdateRealImageSize(bool _isupdatereal){isupdatereal=_isupdatereal;};
	
	void setMaxSize(float _width, float _height);
	void updateSize();
	void crop(int x, int y, int w, int h);
	void cropFitScale(int _width, int _height);
	
    bool isLoaded();
    void clear();
	
protected:
	void _draw();
	
private:
	ofImage* img;

	float maxwidth;
	float maxheight;
	bool hasmaxsize;
	bool changed;
	
	bool isupdatereal;
    bool loaded;	
};