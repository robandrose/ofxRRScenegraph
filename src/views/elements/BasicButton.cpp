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
	isenabled=true;
	isselected=false;
	hasactiveimage=false;	
	isselected=false;
	
	temp=NULL;
	normal=NULL;
	selected=NULL;
	disabled=NULL;
	active=NULL;
	currentImage=NULL;
}

BasicButton::~BasicButton(){
}


void BasicButton::onFirstTouchDown(MultiTouchEvent& _event){
	if(hasactiveimage){
		currentImage = active;
	}
}

void BasicButton::onLastTouchUp(MultiTouchEvent& _event){
	currentImage = temp;
}


void BasicButton::_draw(){
	if(normal==NULL){
		ofRect(0,0,width,height);
	}
	if (currentImage != NULL) currentImage->draw(0,0,width, height);
}


void BasicButton::setImage(ofImage* _normal, ofImage* _selected, ofImage* _active, ofImage* _disabled){
	
	normal=_normal;
	selected=_selected;

	if(selected==NULL){
		selected=normal;
	}
	
	active=_active;
	
	hasactiveimage=true;
	if(active==NULL){
		active=normal;
		hasactiveimage=false;
	}

	disabled=_disabled;
	if(disabled==NULL){
		disabled=normal;
	}
	temp=normal;
    currentImage = normal;
}

void BasicButton::toggle(){
	if(isselected){
		deselect();
	}else{
		select();
	}
}

bool BasicButton::isSelected(){
	return isselected;
}

void BasicButton::select(){
	if(isselected)return;
	isselected=true;
	temp=selected;
	currentImage = selected;
}

void BasicButton::deselect(){
	if(!isselected)return;
	isselected=false;
	temp=normal;
	currentImage = normal;
}

void BasicButton::disable(){
	isenabled=false;
	temp=disabled;
	currentImage = disabled;
}

void BasicButton::enable(){
	isenabled=false;
	temp=normal;
	currentImage = normal;
}
