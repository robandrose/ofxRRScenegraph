/*
 *  MathHelper.cpp
 *  Picking_in_3d
 *
 *  Created by Patrick Meister on 03.07.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "LayoutHelper.h"

/*
 * turns a position in a list (index) into coloumn/row coordinates
 * maxColoumns: the number of coloumns of the grid
 * returns: a 2d vector containing the grid position (coloumn, row numbers. not pixels!)
 */
ofVec2f LayoutHelper::getGridPosition(int maxColoumns, int index) {
	int c = index%maxColoumns;
	int r = index/maxColoumns;
	return ofVec2f(c,r);
}
