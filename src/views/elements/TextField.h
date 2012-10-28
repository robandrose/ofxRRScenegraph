/*
 *  TextField.h
 *
 *  Created by Matthias Rohrbach on 14.07.11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "BasicScreenObject.h"
#include "ofxPango.h"



class TextField : public BasicScreenObject{
public:
	TextField();
	virtual ~TextField();
	void setup();
	void firstUpdate();
	void update();
	void _draw();
	
	void setText(string _text);
	string getText();

	
	void setFontDescription(string _fontdescription);
	
	void setFontName(string _fongName);
	void setFontSize(float _fontsize);

	void setSize(float _width, float _height);
	void setTextAlign(int _textalign);
	void setLineSpacing(int _linespacing);
	float getLineSpacing(){return linespacing;};
	
	void setIndent(float _indent);
	void setTabs(vector<int> _tabs);
	
	
	virtual void setColor(float _r, float _g, float _b);
	virtual void setColor(ofColor _c){BasicScreenObject::setColor(_c);};
	
	ofPoint getTextBounds();
	
	ofxPCPangoLayout* getLayout();
	
	static const int ALIGN_CENTER;
	static const int ALIGN_LEFT;
	static const int ALIGN_RIGHT;
	
private:
	
	ofxPango* pango;
	ofxPCContext* context;
	ofxPCPangoLayout* layout;
	ofxPCPangoFontDescription* fd;
	
	ofImage text_image;
	
	string mytext;	
	string fontdescription;
	float fontsize;
	int align;
	bool justify;
	
	int linespacing;
	float indent;
	vector<int> tabs;
	
	ofPoint bounds;
	
	void renderText();	
};
