//
//  Playhead.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/3/20.
//

#include "Playhead.h"

#include "TracksPanel.h"
namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------
Playhead::Playhead(TracksPanel* tracksPanel, std::shared_ptr<LineaDeTiempo::TimeControl> timeControl):
ConstrainedGrabHandle("Playhead",DOM::HORIZONTAL, {0,0, 3, 100}),
_timeControl(timeControl),
_tracksPanel(tracksPanel)
{
	if(_timeControl)
	{
		_currentTimeListener = _timeControl->currentTimeUpdateEvent.newListener(this, &Playhead::_currentTimeChanged);
	}
	
	_draggingStateListener = isDraggingEvent.newListener(this, &Playhead::_draggingStateChanged);
	
	if(_tracksPanel)
	{
		this->constrainTo(_tracksPanel->tracksView->getClippingView());
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
	if(_timeControl){
		if(bDragging){
			_wasPlaying = _timeControl->isPlaying();
			_timeControl->pause();
		}
		else
		{
			if(_wasPlaying)
			{
				_wasPlaying = false;
				_timeControl->play();
			}
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
	if(_tracksPanel && _timeControl)
	{
		setPosition(screenToParent({_tracksPanel->timeToScreenPosition(_timeControl->getCurrentTime()),0}).x - (getWidth() / 2), getY());
	}
}
//---------------------------------------------------------------------
void Playhead::_onDragging(const DOM::CapturedPointer& pointer)
{
	ConstrainedGrabHandle::_onDragging(pointer);
	
	_timeControl->setCurrentTime(_tracksPanel->screenPositionToTime(parentToScreen({getX() + (getWidth() / 2), 0 }).x));
	
}

} } // ofx::LineaDeTiempo
