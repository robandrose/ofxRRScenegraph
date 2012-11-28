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


TextField::TextField(){
	
	pango = new ofxPango();
	context=NULL;
	layout=NULL;
	fd=NULL;
	
	changed=false;
		
	setFontSize(15);
	setFontName("Graphik");
	setSize(200, 50);
	setLineSpacing(3);
	setTextAlign(ALIGN_LEFT);
	setIndent(0.0);
	setAntialiasType(CAIRO_ANTIALIAS_DEFAULT);
}

TextField::~TextField(){
	
}

void TextField::setup(){
	
}

void TextField::update(){	
	if(changed){
		// TODO: fix this bug. if rendered only once, text is scrambled sometimes.
		renderText();
		renderText();
	}
}

void TextField::setText(string _text){
	if(_text==mytext)return;
	mytext=_text;

	changed=true;
}

string TextField::getText(){
	return mytext;	
}

void TextField::setFontName(string _fontname) {
	fontname=_fontname;
	updateFontDescription();
}

void TextField::setFontSize(float _fontsize){
	fontsize=_fontsize;
	updateFontDescription();
}

void TextField::updateFontDescription(){
	setFontDescription(fontname+" "+ofToString(fontsize));	
}

void TextField::setFontDescription(string _fontdescription){
	if(fd!=NULL){
		delete fd;
	}	
	fontdescription=_fontdescription;	
	fd = new ofxPCPangoFontDescription();
	fd->createFromString(fontdescription);
	changed=true;
}



void TextField::setSize(float _width, float _height){
	BasicScreenObject::setSize(_width, _height);
	if (layout != NULL) delete layout;
	layout = pango->createLayout(width, height);
	layout->setWidth(width); 
	layout->fill(0, 0, 0, 0);
	text_image.clear();
	text_image.allocate(layout->getWidth(), layout->getHeight(), OF_IMAGE_COLOR_ALPHA);	
	changed=true;
}

void TextField::setTextAlign(int _textalign){
	align=_textalign;
	changed=true;
}

void TextField::setLineSpacing(int _linespacing){
	linespacing=_linespacing;
	changed=true;
}

void TextField::setIndent(float _indent){
	indent=_indent;
	changed=true;
}

void TextField::setTabs(vector<int> _tabs){
	tabs=_tabs;
	changed=true;
}

void TextField::setColor(float _r, float _g, float _b){
	BasicScreenObject::setColor(_r,_g,_b);
	changed=true;
}


void TextField::setColor(ofColor _c){
	BasicScreenObject::setColor(_c.r,_c.g,_c.b);
	changed=true;
}

void TextField::setAntialiasType(cairo_antialias_t _type) {
	antialias_type = _type;
	changed = true;
}

ofPoint TextField::getTextBounds(){
	if (changed) {
		renderText();
		renderText();
	}
	return bounds;
}

void TextField::renderText(){

	layout->context->clear();
	layout->setWidth(width);
	layout->setFontDescription(*fd, antialias_type);
	layout->setTextColor(color.r/255.0f,color.g/255.0f,color.b/255.0f,1);
	layout->setSpacing(linespacing);	
	layout->setIndent(indent);
	layout->setMarkup(mytext);
	layout->setTabs(tabs);
	layout->setPangoAlign(align);
	layout->show();

	text_image.setFromPixels(layout->context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);
	bounds=layout->getPixelSize();	
	
	changed=false;
	
	if(bounds.y!=height){
		setSize(width, bounds.y);
	}
	
}

void TextField::_draw(){
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); // To avoid ugly dark eges in alpha blending
	text_image.draw(0, 0);
}

ofxPCPangoLayout* TextField::getLayout(){
	return layout;
}
