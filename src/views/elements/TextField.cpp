/*
 *  TextField.cpp
 *
 *  Created by Matthias Rohrbach on 14.07.11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextField.h"

const int TextField::ALIGN_LEFT=PANGO_ALIGN_LEFT;
const int TextField::ALIGN_RIGHT=PANGO_ALIGN_RIGHT;
const int TextField::ALIGN_CENTER=PANGO_ALIGN_CENTER;


TextField::TextField() {
	pango	= new ofxPango();
	context	= NULL;
	layout	= NULL;
	fd		= NULL;
	changed	= false;
		
	setFontSize(15);
	setFontName("Graphik");
	setSize(200, 50);
	setLineSpacing(3);
	setTextAlign(ALIGN_LEFT);
	setIndent(0.0);
	setAntialiasType(CAIRO_ANTIALIAS_DEFAULT);
}


void TextField::setup() {
	layout = pango->createLayout(width, height);
	layout->setWidth(width);
	layout->fill(0, 0, 0, 0);
}


void TextField::update() {	
	if(changed){
		renderText();
	}
}


void TextField::_draw() {
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); // To avoid ugly dark eges in alpha blending
	textImage.draw(0, 0);
}


void TextField::updateFontDescription() {
	setFontDescription(fontName+" "+ofToString(fontSize));	
}


void TextField::setFontDescription(string _fontDescription) {
	if(fd!=NULL){
		delete fd;
	}	
	fontDescription=_fontDescription;	
	fd = new ofxPCPangoFontDescription();
	fd->createFromString(fontDescription);
	changed=true;
}


void TextField::setText(string _text) {
	if(_text == textContent) return;
	textContent = _text;
	changed=true;
}


void TextField::setFontName(string _fontName) {
	if(_fontName == fontName) return;
	fontName = _fontName;
	updateFontDescription();
}


void TextField::setFontSize(float _fontSize) {
	if(_fontSize == fontSize) return;
	fontSize = _fontSize;
	updateFontDescription();
}


void TextField::setSize(float _width, float _height) {
	BasicScreenObject::setSize(_width, _height);
	if (layout != NULL) delete layout;
	layout = pango->createLayout(width, height);	
	changed=true;
}


void TextField::setTextAlign(int _textAlign) {
	if(_textAlign == textAlign) return;
	textAlign	= _textAlign;
	changed		= true;
}


void TextField::setLineSpacing(int _lineSpacing) {
	if(_lineSpacing == lineSpacing) return;
	lineSpacing	= _lineSpacing;
	changed		= true;
}


void TextField::setIndent(float _indent) {
	if(_indent == indent) return;
	indent	= _indent;
	changed	= true;
}


void TextField::setTabs(vector<int> _tabs) {
	tabs	= _tabs;
	changed = true;
}


void TextField::setColor(float _r, float _g, float _b) {
	BasicScreenObject::setColor(_r,_g,_b);
	changed = true;
}


void TextField::setColor(ofColor _c) {
	BasicScreenObject::setColor(_c.r,_c.g,_c.b);
	changed = true;
}


void TextField::setAntialiasType(cairo_antialias_t _type) {
	if(_type == antialiasType) return;
	antialiasType	= _type;
	changed			= true;
}


ofPoint TextField::getTextBounds() {
	if (changed) {
		renderText();
	}
	return bounds;
}


ofxPCPangoLayout* TextField::getLayout() {
	return layout;
}


string TextField::getText() {
	return textContent;	
}


void TextField::renderText() {

	layout->context->clear();
	layout->setFontDescription(*fd, antialiasType);
	layout->setTextColor(color.r/255.0f, color.g/255.0f, color.b/255.0f, 1);
	layout->setSpacing(lineSpacing);	
	layout->setIndent(indent);
	layout->setMarkup(textContent);
	layout->setTabs(tabs);
	layout->setPangoAlign(textAlign);
	layout->show();

	bounds=layout->getPixelSize();	
	
	changed=false;
	
	if(bounds.y!=height){
		setSize(width, bounds.y);
	}
	
	textImage.setFromPixels(layout->context->getSurface()->getPixels(), width, height, OF_IMAGE_COLOR_ALPHA, true);
}