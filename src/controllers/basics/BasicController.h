/*
 BasicController
 Basic Controller Class to be inherited by all Controllers
 
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
#include "ofMain.h"
#include "BasicControllerEvent.h"


class BasicController {
	
public:
	BasicController();
	virtual ~BasicController();
	
	BasicControllerEvent myEventArgs;

	
protected:
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
	void _draw(ofEventArgs &e);
	void _exit(ofEventArgs &e);
	void _keyPressed(ofKeyEventArgs &e);
	void _keyReleased(ofKeyEventArgs &e);
	
		
	
	virtual void setup(){};
	virtual void update(){};
	virtual void draw(){};
	virtual void exit(){};
	virtual void keyPressed(ofKeyEventArgs &e){};
	virtual void keyReleased(ofKeyEventArgs &e){};
};