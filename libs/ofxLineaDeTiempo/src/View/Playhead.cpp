//
//  Playhead.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/3/20.
//

#include "LineaDeTiempo/View/Playhead.h"
#include "LineaDeTiempo/Controller/TimeControl.h"
#include "TracksPanel.h"
namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------
Playhead::Playhead(TracksPanel* tracksPanel):
ConstrainedGrabHandle("Playhead",DOM::HORIZONTAL, {0,0, 3, 100}),
_tracksPanel(tracksPanel)
{
	
	_currentTimeListener = getTimeControl().currentTimeUpdateEvent.newListener(this, &Playhead::_currentTimeChanged);
	
	
	_draggingStateListener = isDraggingEvent.newListener(this, &Playhead::_draggingStateChanged);
	
	if(_tracksPanel)
	{
		this->constrainTo(_tracksPanel->getClippingView());
	}
	moveToFront();
}
//---------------------------------------------------------------------
void Playhead::onDraw() const
{
	ofPushStyle();
	ofFill();
	
	
	//		auto styles = getStyles();
	
	//		if (isPointerDown())
	//		{
	if(isDragging()){
		ofSetColor(255, 200);
	}
	else
	{
		ofSetColor(ofColor::red);
	}
	//		}
	//		else if (isPointerOver() && _highlightOnOver)
	//		{
	//			ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_OVER));
	//		}
	//		else
	//		{
	//			ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
	//		}
	
	ofDrawRectangle(0, 0, getWidth(), getHeight());
	
	ofNoFill();
	
	if (isPointerDown())
	{
		ofSetColor(255, 120);
		ofDrawRectangle(0, 0, getWidth(), getHeight());
	}
	else if (isPointerOver() && _highlightOnOver)
	{
		ofSetColor(30, 120);
		ofDrawRectangle(0, 0, getWidth(), getHeight());
		//			ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_OVER));
	}
	else
	{
		//			ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
	}
	
	
	ofPopStyle();
	
}
//---------------------------------------------------------------------
void Playhead::_draggingStateChanged(bool & bDragging)
{
	auto & _timeControl = getTimeControl();
	if(bDragging){
		_wasPlaying = _timeControl.isPlaying();
		_timeControl.pause();
	}
	else
	{
		if(_wasPlaying)
		{
			_wasPlaying = false;
			_timeControl.play();
		}
	}
}
//---------------------------------------------------------------------
void Playhead::_currentTimeChanged(uint64_t& t)
{
	if(!isDragging())
	{
		updatePosition();
		//	   if(_tracksPanel)
		//	   {
		//		setPosition(screenToParent({_tracksPanel->timeToScreenPosition(t),0}).x - (getWidth() / 2), getY());
		//	   }
	}
}
//---------------------------------------------------------------------
void Playhead::updatePosition()
{
	if(_tracksPanel)
	{
		setPosition(screenToParent({_tracksPanel->timeToScreenPosition(getTimeControl().getCurrentTime()),0}).x - (getWidth() / 2), getY());
	}
}
//---------------------------------------------------------------------
void Playhead::_onDragging(const DOM::CapturedPointer& pointer)
{
	ConstrainedGrabHandle::_onDragging(pointer);
	
	getTimeControl().setCurrentTime(_tracksPanel->screenPositionToTime(parentToScreen({getX() + (getWidth() / 2), 0 }).x));
	
}

} } // ofx::LineaDeTiempo
