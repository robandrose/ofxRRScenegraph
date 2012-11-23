/*
 *  MultiTouchEvent.h
 *  openFrameworks
 *
 *  Created by Matthias Rohrbach 2 on 10.06.12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
class BasicInteractiveObject;
class MultiTouchPoint;
class MultiTouchEvent {
	public:
		BasicInteractiveObject* target;
		MultiTouchPoint* touchPoint;
		MultiTouchEvent(BasicInteractiveObject* _target) {
			target = _target;
			touchPoint = NULL;
		}
		MultiTouchEvent(BasicInteractiveObject* _target, MultiTouchPoint* _mtp) {
			target = _target;
			touchPoint = _mtp;
		}
};
