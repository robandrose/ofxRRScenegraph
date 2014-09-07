/*
 *  ScrollableTextArea.cpp
 *  UI_Components_Dev
 *
 *  Created by Matthias Rohrbach on 05.07.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#include "ScrollableTextArea.h"
#include "InteractionConst.h"
#include "ColorConst.h"
#include "ofxTransitions.h"


ScrollableTextArea::ScrollableTextArea(){
	
	scrollContainer.isScaleable(false);
	scrollContainer.isRotateable(false);
	scrollContainer.setDragDamping(0.1);
	scrollContainer.setDragThreshold(0.0);
	addChild(&scrollContainer);
	
	scrollBar.setColor(ColorConst::MIDDLE_GREY);
	scrollBar.setSize(2, 10);
	addChild(&scrollBar);
	
	setMaskType(MASK_TYPE_CLIPPLANES);
	setMaskObject(&_mask);
	
	tf.setColor(ofColor::black);

	scrollContainer.addChild(&tf);
	scrollContainer.addPositioner("scrollStop", &scrollRestrictor);
	
	scrollBar.isVisible(false);
	needsScrolling = false;
	
	ofAddListener(scrollContainer.lastTouchUpEvent, this, &ScrollableTextArea::onScrollStop);
	ofAddListener(scrollContainer.dragStartEvent,	this, &ScrollableTextArea::onScrollStart);
}


void ScrollableTextArea::update(){
	if (needsScrolling) {
		if (scrollHeight>FLT_EPSILON) {	// prevent division by zero warning in ofMap
			float scrollypos=ofMap(scrollContainer.getY(), 0, scrollHeight, 0,_mask.getHeight()-scrollBarHeight, false);
			scrollBar.setY(-scrollypos);
		}
		
		if (!scrollContainer.isDragging()) {
			if (scrollBar.getAlpha() != 0.0) { 
				if (scrollContainer.getSpeed().length() <= .1) {
					if ( !scrollBar.isFadeTweenActive()) scrollBar.fadeToInvisible(InteractionConst::SCROLLBAR_DISAPPEAR_TIME, &ofxTransitions::linear, InteractionConst::SCROLLBAR_DISAPPEAR_TIME);	
				}
			}
		}
		
	}else{
		scrollBar.isVisible(false);
	}
}


void ScrollableTextArea::setSize(float _width, float _height){
	BasicScreenObject::setSize(_width, _height);
	_updateScrollSize();
}


void ScrollableTextArea::setText(string _text){
	tf.setText(_text);
	scrollTo(0.0);
	_updateScrollSize();
}


void ScrollableTextArea::scrollTo(float _y) {
	scrollContainer.setPosition(scrollContainer.getX(), _y);
}


void ScrollableTextArea::_updateScrollSize() {
	scrollContainer.setSize(width, tf.getTextBounds().y);
	tf.setSize(width, height);
	_mask.setSize(width, height);
	
	scrollBarHeight = (_mask.getHeight()/tf.getTextBounds().y)*_mask.getHeight();
	scrollBar.setSize(2, scrollBarHeight);
	scrollBar.setPosition(width-scrollBar.getWidth(), 0);
	
	scrollHeight = tf.getTextBounds().y-_mask.getHeight();
	scrollRestrictor.setRestrictionValue(ofRectangle(0,-scrollHeight,0,scrollHeight), ofRectangle(0,0,0,0));
	
	needsScrolling = (tf.getTextBounds().y > _mask.getHeight());
}


void ScrollableTextArea::onScrollStart(MultiTouchEvent& _event){
	if ( needsScrolling ) {
		scrollBar.isVisible(true);
		scrollBar.fadeTo(255.0, InteractionConst::SCROLLBAR_APPEAR_TIME);
	}
}


void ScrollableTextArea::onScrollStop(MultiTouchEvent& _event){
	if ( needsScrolling ) {
		scrollContainer.setSpeed(scrollContainer.getDragSpeed(),0.9);
	}
	
}