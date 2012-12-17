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
	virtual ~TextField() {};
	
	void	setup();
	void	update();
	virtual void	_draw();
	
	void	setText(string _text);
	string	getText();
	
	void	setFontName(string _fontname);
	void	setFontSize(float _fontsize);	
	void	setFontDescription(string _fontdescription);
	
	void	setSize(float _width, float _height);
	void	setTextAlign(int _textalign);
	void	setLineSpacing(int _linespacing);
	float	getLineSpacing(){return lineSpacing;};
	void	setAntialiasType(cairo_antialias_t _type); 
	cairo_antialias_t getAntialiasType() {return antialiasType;};
	
	void setIndent(float _indent);
	void setTabs(vector<int> _tabs);
	
	virtual void setColor(float _r, float _g, float _b);
	virtual void setColor(ofColor _c);
	
	ofPoint				getTextBounds();	
	ofxPCPangoLayout*	getLayout();
	
	static const int ALIGN_CENTER;
	static const int ALIGN_LEFT;
	static const int ALIGN_RIGHT;
	
	ofEvent<BasicScreenObjectEvent> textRenderedEvent;
	
protected:
	
	ofxPango*					pango;
	ofxPCContext*				context;
	ofxPCPangoLayout*			layout;
	ofxPCPangoFontDescription*	fd;
	
	ofImage		textImage;	
	
	string		textContent;	
	string		fontName;
	float		fontSize;
	string		fontDescription;
	int			textAlign;
	bool		justify;
	cairo_antialias_t	antialiasType;
	
	int			lineSpacing;
	float		indent;
	vector<int>	tabs;
	ofPoint		bounds;
	
	bool		changed;
	
	void updateFontDescription();
	void renderText();	
};
