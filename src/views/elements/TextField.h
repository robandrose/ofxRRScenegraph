/*
 TextField
 
 Textfield Element based on ofxPango Text.
 
 Copyright (C) 2014 Rob&Rose
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 IN THE SOFTWARE.
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
	void	setLetterSpacing(int _letterspacing); // 1024=1 geviert (?)
	void	setLineSpacing(int _linespacing);
	float	getLineSpacing(){return lineSpacing;};
	void	setAntialiasType(cairo_antialias_t _type); 
	cairo_antialias_t getAntialiasType() {return antialiasType;};
	int		getLineCount();
	
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
	
	void renderText();	
	
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
	int		letterSpacing;
	float		indent;
	vector<int>	tabs;
	ofPoint		bounds;
	
	bool		changed;
	
	float umlautoffset;
	float umlautoffsetfactor;
	
	void updateFontDescription();
	
};
