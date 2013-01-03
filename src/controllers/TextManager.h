#pragma once
#include "ofxXmlSettings.h"



class TextManager{
	
public:
	TextManager();
	virtual ~TextManager();
	
	void	loadSettings();
	string	get(string _textkey);
	
private:
	map<string,string>strings;	
	ofxXmlSettings* settings;	
};
