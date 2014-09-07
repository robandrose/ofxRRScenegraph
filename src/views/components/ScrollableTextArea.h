/*
 *  ScrollableTextArea.h
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 05.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */


#pragma once

#include "BasicScreenObject.h"
#include "HegiTextField.h"
#include "Shapes.h"
#include "AreaRestrictor.h"
#include "MultiTouchEvent.h"
#include "InteractiveContainer.h"

class ScrollableTextArea:public BasicScreenObject{
public:
	
	ScrollableTextArea();
	virtual ~ScrollableTextArea() {};

	void update();
	
	void setSize(float _width, float _height);
	void setText(string _text);
	void scrollTo(float _y);
	
	HegiTextField tf;
	
protected:
	void onScrollStop(MultiTouchEvent &event);
	void onScrollStart(MultiTouchEvent &event);	
	
	InteractiveContainer scrollContainer;
		
	ShapeRect _mask;
	ShapeRect scrollBar;
	
	AreaRestrictor scrollRestrictor;
	
	bool	needsScrolling;
	float	scrollHeight;
	float	scrollBarHeight;
	
	void	_updateScrollSize();
};
