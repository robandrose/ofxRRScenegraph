#include "TextManager.h"

TextManager::TextManager(){
	settings=new ofxXmlSettings();
	loadSettings();
}

TextManager::~TextManager(){
	strings.clear();
}

void TextManager::loadSettings(){
	ofLog(OF_LOG_NOTICE, "loading texts.xml");
	settings->loadFile("config/texts.xml");
	settings->pushTag("texts", 0);
	int numtexts=settings->getNumTags("text");
	
	for(int i=0;i<numtexts;i++){
		string name = settings->getValue("text:name","", i);
		string textstring= settings->getValue("text:string", "", i);
		strings[name]=textstring;
	}
}

string TextManager::get(string _textkey){
	
	return strings[_textkey];
}