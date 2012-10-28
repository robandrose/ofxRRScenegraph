/*
 *  TextureManager.cpp
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach on 16.11.09.
 *  Copyright 2009 rob & rose grafik. All rights reserved.
 *
 */

#include "TextureManager.h"

TextureManager::TextureManager(){
	settings=new ofxXmlSettings();
	loadSettings();
}

TextureManager::~TextureManager(){
	imgmap.clear();
}

void TextureManager::loadSettings(){
	ofLog(OF_LOG_NOTICE, "loading textures.xml");
	settings->loadFile("config/textures.xml");
	settings->pushTag("textures", 0);
	int numtextures=settings->getNumTags("texture");
	
	for(int i=0;i<numtextures;i++){
		cout << settings->getValue("texture:source", "", i)<< "\n";
		string key = settings->getValue("texture:key","", i);
		string source= settings->getValue("texture:source", "", i);
		ofImage* img=new ofImage();
		
		img->loadImage(source);
		img->setImageType(OF_IMAGE_COLOR_ALPHA);
		imgmap[key]=img;
	}
}

ofImage* TextureManager::get(string _texkey){
	
	return imgmap[_texkey];
}