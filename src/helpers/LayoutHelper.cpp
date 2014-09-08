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
