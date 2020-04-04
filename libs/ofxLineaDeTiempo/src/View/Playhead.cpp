//
//  Playhead.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/3/20.
//

#include "LineaDeTiempo/View/Playhead.h"
#include "LineaDeTiempo/Controller/TimeControl.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include "LineaDeTiempo/Utils/ConstVars.h"

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------
Playhead::Playhead(TracksPanel* tracksPanel, TimeControl* timeControl)
: ConstrainedGrabHandle("Playhead",DOM::HORIZONTAL, {0,0, PlayheadWidth, 100})
, _tracksPanel(tracksPanel)
, _timeControl(timeControl)
{
	
	_currentTimeListener = timeControl->currentTimeUpdateEvent.newListener(this, &Playhead::_currentTimeChanged);
	
	
	_draggingStateListener = isDraggingEvent.newListener(this, &Playhead::_draggingStateChanged);
	
	if(_tracksPanel)
	{
		this->constrainTo(_tracksPanel->getClippingView());
		
//		auto v = tracksPanel->getClippingView();
//		_tracksListeners.push( v->resize.newListener(this, &Playhead::_tracksViewShapeChanged));
//		_tracksListeners.push( v->childAdded.newListener(this, &Playhead::_trackNumChanged));
//		_tracksListeners.push( v->childRemoved.newListener(this, &Playhead::_trackNumChanged));
//		_tracksListeners.push( v->childReordered.newListener(this, &Playhead::_tracksOrderChanged));
	}
	
	
	_playheadTriangle.setMode(OF_PRIMITIVE_TRIANGLES);
	
	
	
	_playheadTriangle.addVertex({ (PlayheadWidth - PlayheadTriangleSize) *0.5 , 0, 0});
	_playheadTriangle.addVertex({ (PlayheadWidth + PlayheadTriangleSize) *0.5 , 0, 0});
	_playheadTriangle.addVertex({ PlayheadWidth*0.5 , PlayheadTriangleSize * sin(ofDegToRad(60)), 0});
	
	
	
	moveToFront();
}

void Playhead::_trackNumChanged(DOM::ElementEventArgs& e)
{
	if(e.element() != this)
	{
		moveToFront();
	}
}
void Playhead::_tracksOrderChanged(DOM::ElementOrderEventArgs& e)
{
	if(e.element() != this)
	{
		moveToFront();
	}
}


////---------------------------------------------------------------------
//void Playhead::_tracksViewShapeChanged(DOM::ResizeEventArgs &)
//{
//	if(_tracksPanel)
//	{
//		setSize(getSize().x, _tracksPanel->getClippingView()->getHeight());
//	}
//}
//---------------------------------------------------------------------
void Playhead::onDraw() const
{
	ofPushStyle();
	ofFill();
	
	
	if(isDragging()){
		ofSetColor(255, 200);
	}
	else
	{
		ofSetColor(ofColor::red);
	}
	
	
	ofSetColor(200);
	
	_playheadTriangle.draw();

	
	
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
	}
	_playheadTriangle.drawWireframe();
	
	ofPopStyle();
	
}
//---------------------------------------------------------------------
void Playhead::_draggingStateChanged(bool & bDragging)
{
	if(!_timeControl) return;
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
//---------------------------------------------------------------------
void Playhead::_currentTimeChanged(uint64_t& t)
{
	if(!isDragging())
	{
		updatePosition();
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
	
	if(_tracksPanel && _timeControl)
	{
		
		_timeControl->setCurrentTime(_tracksPanel->screenPositionToTime(parentToScreen({getX() + (getWidth() / 2), 0 }).x));
	}
	
}

} } // ofx::LineaDeTiempo
