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
class MultiTouchEvent {
	public:
		BasicInteractiveObject* target;
		MultiTouchEvent(BasicInteractiveObject* _target) {
			target = _target;
		}
};
