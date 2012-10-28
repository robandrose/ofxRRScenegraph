/*
 *  TextField.cpp
 *
 *  Created by Matthias Rohrbach on 14.07.11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextField.h"

const int TextField::ALIGN_LEFT=0;
const int TextField::ALIGN_RIGHT=1;
const int TextField::ALIGN_CENTER=2;


TextField::TextField(){
	
	pango = new ofxPango();
	context=NULL;
	layout=NULL;
	fd=NULL;
	
	
	setFontDescription("Graphik 12");
	setSize(100, 50);
	
	setLineSpacing(3);
	setTextAlign(ALIGN_LEFT);
	setIndent(0.0);
	

	
}

TextField::~TextField(){
	
}

void TextField::setup(){
	
}

void TextField::firstUpdate(){
	
}

void TextField::update(){	

}

void TextField::setText(string _text){
	if(_text==mytext)return;
	mytext=_text;
	renderText();
}

string TextField::getText(){
	return mytext;	
}

void TextField::setFontDescription(string _fontdescription){
	if(fd!=NULL){
		delete fd;
	}
	
	fontdescription=_fontdescription;	
	fd = new ofxPCPangoFontDescription();
	fd->createFromString(fontdescription);
	
}

void TextField::setFontName(string _fontname) {
	setFontDescription(_fontname);
	renderText();
}

void TextField::setFontSize(float _fontsize){
	
}

void TextField::setSize(float _width, float _height){
	BasicScreenObject::setSize(_width, _height);
	layout = pango->createLayout(width, height);
	layout->setWidth(width); 
	layout->fill(0, 0, 0, 0);
	text_image.clear();
	text_image.allocate(layout->getWidth(), layout->getHeight(), OF_IMAGE_COLOR_ALPHA);	
	renderText();
}

void TextField::setTextAlign(int _textalign){
	align=_textalign;
	renderText();
}

void TextField::setLineSpacing(int _linespacing){
	linespacing=_linespacing;
	renderText();
}

void TextField::setIndent(float _indent){
	indent=_indent;
	renderText();	
}

void TextField::setTabs(vector<int> _tabs){
	tabs=_tabs;
	renderText();	
}

void TextField::setColor(float _r, float _g, float _b){
	BasicScreenObject::setColor(_r,_g,_b);
	renderText();
}

ofPoint TextField::getTextBounds(){
	return bounds;
}

void TextField::renderText(){
	
	layout->context->clear();
	layout->setWidth(width); 	
	layout->setFontDescription(*fd);
	layout->setTextColor(color.r/255.0f,color.g/255.0f,color.b/255.0f,1);
	layout->setSpacing(linespacing);	
	layout->setIndent(indent);
	layout->setMarkup(mytext);
	layout->setTabs(tabs);
	
	switch(align){
			case ALIGN_LEFT:
			layout->setAlignLeft();
			break;
		case ALIGN_RIGHT:
			layout->setAlignRight();
			break;
		case ALIGN_CENTER:
			layout->setAlignCenter();
			break;			
	}
	
	layout->show();	
	
	text_image.setFromPixels(layout->context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);
	
	bounds=layout->getPixelSize();
	
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
