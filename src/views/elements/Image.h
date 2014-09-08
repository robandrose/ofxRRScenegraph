/*
 Image
 Basic Image with some nice resizeing functions.
 
 Copyright (C) 2014 Rob&Rose
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 IN THE SOFTWARE.
 */



#pragma once
#include "BasicScreenObject.h"
#include "ofxThreadedImageLoader.h"


class Image:public BasicScreenObject{
public:
	Image();
	virtual ~Image();
	
	void setup() {};
	void update();
	
	void load(string _filename);
	void loadAsyncFromDisk(string _filename, ofxThreadedImageLoader* loader);
	void loadAsyncFromURL(string _url, ofxThreadedImageLoader* loader);
	
	void setLoadingPlaceholder(BasicScreenObject* _loadingPlaceholder);
	
	void		setImagePointer(ofImage* _img);
	ofImage*	getImagePointer();
	
	void setSize(float _width, float _height);
	void updateRealImageSize();
	void isUpdateRealImageSize(bool _isupdatereal){isUpdateReal=_isupdatereal;};
	
	void setMaxSize(float _width, float _height);
	void updateSize();
	void crop(int x, int y, int w, int h);
	void cropFitScale(int _width, int _height);
	void scaleFitPad(int _width, int _height, ofColor _color, bool _vcenter, bool _hcenter);
	void clone(Image* _srcImage);
	void clone(ofImage* _srcImage);
	
	void setRectMode(ofRectMode _mode);
	
    bool isLoaded();
    void clear();
	
	ofEvent<BasicScreenObjectEvent> imageLoadedEvent;
	
protected:
	void _draw();
	
private:
	ofImage*	img;
	BasicScreenObject* loadingPlaceholder;

	float		maxWidth;
	float		maxHeight;
	bool		hasMaxSize;
	bool		changed;
	
	bool		isUpdateReal;
    bool		loaded;
	bool		loadingAsync;
	
	ofRectMode	mode;
	
	
	int tmpResizeCounter; //TODO: remove
	string tmpFilepath;
};