/*
 ScrollableContainer
 
 Add BasicScreenObjects to the container and have them scrolled. Does not work with interactiveObjects
 beacause selection and dragging is all handled from container.
 
 
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

#include "BasicScreenObject.h"
#include "TextField.h"
#include "Elements.h"
#include "Shapes.h"
#include "AreaRestrictor.h"
#include "MultiTouchEvent.h"

class ScrollableContainer:public BasicScreenObject{
public:
	
	ScrollableContainer();
	virtual ~ScrollableContainer() {};

	virtual void	update();
	virtual void	setSize(float _width, float _height);
	
    // Settings
	virtual bool	isScrollBarEnabled()				{ return enableScrollBar; };
	virtual void	isScrollBarEnabled(bool _visible)	{ enableScrollBar = _visible; };
	
	virtual bool	isScrollHorizontal()				{ return horizontalMode; };
	virtual void	isScrollHorizontal(bool _scrollH)	{ horizontalMode = _scrollH; };
	
	virtual bool	isSnapToElements()					{ return snapToElements; };
	virtual void	isSnapToElements(bool _snap)		{ snapToElements = _snap; };
	
	virtual float	getElementPadding()					{ return ePadding; };
	virtual void	setElementPadding(float _padding)	{ ePadding = _padding; _updateLayout(); };
	
    // Timings
    virtual void    setDefaultTiming(float _atime, float _dtime){ defaultAppearTime=_atime;defaultDisappearTime=_dtime;};
    virtual void    setDefaultScrollbarTiming(float _atime, float _dtime){scrollBarAppearTime=_atime;scrollBarDisappearTime=_dtime;}
    virtual void    setSnapToElementsTiming(float _time){snapToElementsTime=_time;};

    
	virtual void	forceLayoutUpdate()					{ _updateLayout(); };
	
	virtual vector<BasicScreenObject*>* getElements()	{ return &elements; };
	virtual void	addElement(BasicScreenObject* _element);
	virtual void	removeElement(BasicScreenObject* _element);
	virtual void	clearElements();
	
	virtual void	scrollToElement(int _elementNr, int _speed=1000);
	virtual void	flashScrollbar();
	
	virtual int		getActiveElement()	{ return _activeElementNr; };
	virtual int		getElementCount()	{ return elements.size(); };
	
	ofEvent<BasicScreenObjectEvent>	activeElementChangedEvent;
	ofEvent<BasicScreenObjectEvent>	elementTapEvent;
	ofEvent<BasicScreenObjectEvent> elementFirstTouchDownEvent;
	ofEvent<BasicScreenObjectEvent> elementLastTouchUpEvent;
	
protected:
	void onManualScrollStart(MultiTouchEvent &event);
	void onManualScrollStop(MultiTouchEvent &event);
	void onSwipeUp(MultiTouchEvent &event);
	void onSwipeDown(MultiTouchEvent &event);
	void onSwipeRight(MultiTouchEvent &event);
	void onSwipeLeft(MultiTouchEvent &event);
	void onContentsMoved(BasicScreenObjectEvent &event);
	void onContentTap(MultiTouchEvent &event);
	void onContentTouchDown(MultiTouchEvent &event);
	void onContentTouchUp(MultiTouchEvent &event);
	
	void onSnapFinished(BasicScreenObjectEvent & event);
	void onElementChangedSize(BasicScreenObjectEvent & event);
	void onElementRemoved(BasicScreenObjectEvent & event);
	
	InteractiveContainer scrollContainer;
		
	ShapeRect mask;
	ShapeRect scrollBar;
	
	AreaRestrictor scrollRestrictor;
	
	float	contentSize;
	float	scrollBarSize;
	
	float	ePadding;
	bool	snapToElements;
	bool	horizontalMode;		// scrollbar mode. true= horizontal scroller, false = vertial scroller
	bool	enableScrollBar;	// user setting
	bool	_showScrollBar;		// calculated setting (false if content is smaller than container estate)
	int		_activeElementNr;
	bool	elementChangedWhileDragging; // true if container was manually dragged to a different element (ignore swipe in this case) 
	
	bool	_swiped;
	
	vector<BasicScreenObject*> elements;
	
	virtual void	_updateLayout(bool tweened = false);
	virtual void	_updateActiveElement();
	virtual int		_findActiveElement();
	virtual void	_handleActiveElementChange();
	virtual void	_handleRelease();
	
	virtual BasicScreenObject*	_elementByPosition(ofPoint _position);
    
    float   scrollBarAppearTime;
    float   scrollBarDisappearTime;
    float   defaultAppearTime;
    float   defaultDisappearTime;    
    float   snapToElementsTime;


};
