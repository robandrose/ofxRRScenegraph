/*
 *  Image.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 04.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "Image.h"

Image::Image(){
	hasmaxsize=false;
	changed=false;
    isupdatereal=false;
    img = new ofImage();
    loaded = false;
}

Image::~Image(){
	img->clear();
}

void Image::setup(){
	
}

void Image::update(){
	if(changed && img){
		updateSize();
	}
}

void Image::load(string _filename){
	filename=_filename;
	img->loadImage(filename);
	setSize(img->getWidth(), img->getHeight());
	changed=true;
	loaded = true;
}

ofImage* Image::getImagePointer(){
	return img;
}

void Image::setSize(float _width, float _height){
	BasicScreenObject::setSize(_width, _height);
	if(isupdatereal){
        updateRealImageSize();
	}
}

void Image::updateRealImageSize(){
    if(img) img->resize(width, height);
}

void Image::crop(int x, int y, int w, int h) {
	if (img==NULL) return;
	img->crop(x, y, w, h);
	BasicScreenObject::setSize(w,h);
}

void Image::setMaxSize(float _maxwidth, float _maxheight){
	hasmaxsize=true;
	maxwidth=_maxwidth;
	maxheight=_maxheight;
	
	updateSize();
}

void Image::updateSize(){
    if(img==NULL)return;
    if(!hasmaxsize)return;
	float fact=(maxwidth/maxheight)/(img->getWidth()/img->getHeight());
	float newwidth=maxwidth;
	float newheight=maxheight;
	if(fact>=1){
		newwidth=maxheight/img->getHeight()*img->getWidth();
	}else{
		newheight=maxwidth/img->getWidth()*img->getHeight();
	}
	setSize(newwidth, newheight);
	changed=false;
}

void Image::_draw(){
	if (img==NULL)return;
	
	if(img->getWidth()>0){
        img->draw(0,0,width,height);
	}
}

bool Image::isLoaded() {
    return loaded;
}

void Image::clear() {
    if (loaded && img != NULL) {
        img->clear();
    }
}


void Image::setImagePointer(ofImage* _img) {
	
    img = _img;
    changed = true;
    loaded = true;
}
