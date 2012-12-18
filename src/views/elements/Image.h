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