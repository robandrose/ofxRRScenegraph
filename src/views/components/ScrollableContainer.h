/*
 *  ScrollableContainer.h
 *
 *  Created by Patrick Meister on 15.08.2012.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
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
	
	virtual bool	isScrollBarEnabled()				{ return enableScrollBar; };
	virtual void	isScrollBarEnabled(bool _visible)	{ enableScrollBar = _visible; };
	
	virtual bool	isScrollHorizontal()				{ return horizontalMode; };
	virtual void	isScrollHorizontal(bool _scrollH)	{ horizontalMode = _scrollH; };
	
	virtual bool	isSnapToElements()					{ return snapToElements; };
	virtual void	isSnapToElements(bool _snap)		{ snapToElements = _snap; };
	
	virtual float	getElementPadding()					{ return ePadding; };
	virtual void	setElementPadding(float _padding)	{ ePadding = _padding; _updateLayout(); };
	
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
};
