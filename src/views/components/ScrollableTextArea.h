
#pragma once

#include "BasicScreenObject.h"
#include "Shapes.h"
#include "TextField.h"
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
	
	TextField tf;
	
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
	float   scrollBarDisappearTime;
    
	void	_updateScrollSize();
};

