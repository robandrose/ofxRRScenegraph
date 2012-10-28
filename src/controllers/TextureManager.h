/*
 *  TextureManager.h
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach on 16.11.09.
 *  Copyright 2009 rob & rose grafik. All rights reserved.
 *
 */


#pragma once
#include "ofxXmlSettings.h"



class TextureManager{
	
public:
	TextureManager();
	virtual ~TextureManager();
	
	void loadSettings();
	ofImage* get(string _texkey);
	
private:
	map<string,ofImage*>imgmap;	
	ofxXmlSettings* settings;	
};
