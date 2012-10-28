/*
 *  SettingsManager.cpp
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach on 16.11.09.
 *  Copyright 2009 rob & rose grafik. All rights reserved.
 *
 */

#include "SettingsManager.h"

SettingsManager::SettingsManager(){
	settings=new ofxXmlSettings();
	loadXMLFile();
}

SettingsManager::~SettingsManager(){
	settingsmap.clear();
}

void SettingsManager::loadXMLFile(){
	ofLog(OF_LOG_NOTICE, "loading settings.xml");
	settings->loadFile("config/settings.xml");
	settings->pushTag("settings", 0);
	
	int numsettings=settings->getNumTags("setting");	
	for(int i=0;i<numsettings;i++){
		string key = settings->getValue("setting:key","", i);
		string value= settings->getValue("setting:value", "", i);
		settingsmap[key]=value;
	}
}

string SettingsManager::get(string _key){
	return settingsmap[_key];
}