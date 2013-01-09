/*
 *  BasicButton.cpp
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach on 26.10.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "BasicButton.h"



BasicButton::BasicButton() {
	isEnabled		= true;
	_isSelected		= false;
	hasActiveimage	= false;	
	_isScalingImage = false;
	
	temp			= NULL;
	normal			= NULL;
	selected		= NULL;
	disabled		= NULL;
	active			= NULL;
	currentImage	= NULL;
}


void BasicButton::onFirstTouchDown(MultiTouchEvent& _event){
	if (isEnabled) {
		if(hasActiveimage){
			currentImage = active;
		}
		ofNotifyEvent(pressEvent, myEventArgs, this);
	}
}

void BasicButton::onLastTouchUp(MultiTouchEvent& _event){
	if (isEnabled) {
		currentImage = temp;
		ofNotifyEvent(releaseEvent, myEventArgs, this);
	}
}


void BasicButton::_draw(){
	if(normal == NULL){
		ofRect(0,0,width,height);
	}
	
	if (currentImage != NULL) {
		//ofSetColor(color.r, color.g, color.b, 0);	// TODO: strange stuff with alpha
		if (_isScalingImage) {
			currentImage->draw(0,0,width, height);
		} else {
			currentImage->draw((width  - currentImage->getWidth()) *.5,
							   (height - currentImage->getHeight())*.5);
		}
	}
}


void BasicButton::setImage(ofImage* _normal, ofImage* _selected, ofImage* _active, ofImage* _disabled){
	
	normal		= _normal;
	selected	= _selected;

	if(selected == NULL){
		selected	= normal;
	}
	
	active	= _active;
	
	hasActiveimage	= true;
	if(active == NULL){
		active			= normal;
		hasActiveimage	= false;
	}

	disabled=_disabled;
	if(disabled==NULL){
		disabled	= normal;
	}
	temp			= normal;
    currentImage	= normal;
}

void BasicButton::toggle(){
	if(_isSelected){
		deselect();
	}else{
		select();
	}
}

bool BasicButton::isSelected(){
	return _isSelected;
}

void BasicButton::select(){
	if(_isSelected || !isEnabled)return;
	_isSelected		= true;
	temp			= selected;
	currentImage	= selected;
}

void BasicButton::deselect(){
	if(!_isSelected || !isEnabled)return;
	_isSelected		= false;
	temp			= normal;
	currentImage	= normal;
}

void BasicButton::disable(){
	if (!isEnabled) return;
	isEnabled		= false;
	_isSelected		= false;
	temp			= disabled;
	currentImage	= disabled;
}

void BasicButton::enable(){
	if (isEnabled) return;
	isEnabled		= true;
	temp			= normal;
	currentImage	= normal;
}