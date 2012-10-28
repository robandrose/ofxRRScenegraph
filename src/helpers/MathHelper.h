/*
 *  MathHelper.h
 *  Picking_in_3d
 *
 *  Created by Patrick Meister on 03.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

class MathHelper  {
public:
	static bool isAnlgeBetween(float _angle, float _startAngle, float _endAngle);
	static float cleanAngle(float _dirtyAngle);
};
