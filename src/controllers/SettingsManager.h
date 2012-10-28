/*
 *  SettingsManager.h
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach on 16.11.09.
 *  Copyright 2009 rob & rose grafik. All rights reserved.
 *
 */



#pragma once
#include "ofxXmlSettings.h"


class SettingsManager{
	
public:
	SettingsManager();
	virtual ~SettingsManager();
	string get(string _key);
	
private:
	void loadXMLFile();
	map<string,string>settingsmap;	
	ofxXmlSettings* settings;	
};
