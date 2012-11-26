#include "TextButton.h"



TextButton::TextButton() {
	isEnabled=true;
	_isSelected=false;
	hasActiveimage=false;	
	_isScalingImage = true;
	
	tempColor=NULL;
	normalColor=NULL;
	selectedColor=NULL;
	disabledColor=NULL;
	activeColor=NULL;
	currentColor=NULL;
	
	addChild(&bg);
	
	needsRelayout = false;
	
	text.setColor(0,0,0);
	addChild(&text);
}

TextButton::~TextButton(){
}


void TextButton::update() {
	BasicScreenObject::update();
	if (needsRelayout) {
		layout();
	}
}


void TextButton::onFirstTouchDown(MultiTouchEvent& _event){
	if (isEnabled) {
		if(hasActiveimage){
			currentColor = activeColor;
		}
		ofNotifyEvent(pressEvent, myEventArgs, this);
	}
}

void TextButton::onLastTouchUp(MultiTouchEvent& _event){
	if (isEnabled) {
		currentColor = tempColor;
		ofNotifyEvent(releaseEvent, myEventArgs, this);
	}
}


void TextButton::_draw(){

	if(normalColor==NULL){
		bg.setColor(255, 255,255);
	}
	if (currentColor != NULL) {
		ofSetColor(currentColor);
		bg.setColor(currentColor);
	}
}


void TextButton::setText(string _txt) {
	text.setText(_txt);
	needsRelayout = true;
}


void TextButton::setSize(float _width, float _height) {
	BasicScreenObject::setSize(_width, _height);
	text.setSize(_width, _height);
	needsRelayout = true;
}


void TextButton::layout() {
	bg.setSize(getWidth(), getHeight());
	text.setPosition((getWidth() - text.getTextBounds().x)/2.0,
					 (getHeight()- text.getTextBounds().y)/2.0);
}


void TextButton::setColors(ofColor _normalColor, ofColor _selectedColor, ofColor _activeColor, ofColor _disabledColor) {
	
	normalColor=_normalColor;
	selectedColor=_selectedColor;

	if(selectedColor==NULL){
		selectedColor=normalColor;
	}
	
	activeColor=_activeColor;
	
	hasActiveimage=true;
	if(activeColor==NULL){
		activeColor=normalColor;
		hasActiveimage=false;
	}

	disabledColor=_disabledColor;
	if(disabledColor==NULL){
		disabledColor=normalColor;
	}
	tempColor=normalColor;
    currentColor = normalColor;
}

void TextButton::toggle(){
	if(_isSelected){
		deselect();
	}else{
		select();
	}
}

bool TextButton::isSelected(){
	return _isSelected;
}

void TextButton::select(){
	if(_isSelected || !isEnabled)return;
	_isSelected=true;
	tempColor=selectedColor;
	currentColor = selectedColor;
}

void TextButton::deselect(){
	if(!_isSelected || !isEnabled)return;
	_isSelected=false;
	tempColor=normalColor;
	currentColor = normalColor;
}

void TextButton::disable(){
	if (!isEnabled) return;
	isEnabled=false;
	_isSelected=false;
	tempColor=disabledColor;
	currentColor = disabledColor;
}

void TextButton::enable(){
	if (isEnabled) return;
	isEnabled=true;
	tempColor=normalColor;
	currentColor = normalColor;
}