/***********************************************************************

 Copyright (c) 2009, Todd Vanderlin, www.vanderlin.cc

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***********************************************************************/

#include "ofxTimer.h"

ofxTimer::ofxTimer() {

}

ofxTimer::~ofxTimer() {

}

// ---------------------------------------

void ofxTimer::setup(float seconds, bool loopTimer) {

	bLoop		= loopTimer;
	bPauseTimer = false;

	//timer
	bStartTimer = true;
	delay		= seconds;	// seconds
	timer		= 0;
	timerStart	= 0;

	//events
	
	ofAddListener(ofEvents().update, this, &ofxTimer::update);

}

// ---------------------------------------
void ofxTimer::loop(bool b) {
	bLoop = b;
}

// ---------------------------------------

void ofxTimer::update(ofEventArgs &e) {
	if(!bPauseTimer) {
		if(bStartTimer) {
			bStartTimer = false;
			timerStart  = ofGetElapsedTimef();
		}

		float time = ofGetElapsedTimef() - timerStart;
		if(time >= delay) {
			if(!bLoop) bPauseTimer = true;
			bStartTimer = true;
			static ofEventArgs timerEventArgs;
			ofNotifyEvent(TIMER_REACHED, timerEventArgs, this);
		}
	}
}

// ---------------------------------------

void ofxTimer::setTimer(float seconds) {
	delay = seconds;
}

void ofxTimer::startTimer() {
	bPauseTimer = false;
}

void ofxTimer::stopTimer() {
	bPauseTimer = true;
}

void ofxTimer::restartTimer(){
	bStartTimer=true;
	bPauseTimer = false;
}
