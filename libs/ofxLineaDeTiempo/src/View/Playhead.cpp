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
Playhead::Playhead(TimeRuler* timeRuler, TimeControl* timeControl)
: ConstrainedGrabHandle("Playhead",DOM::HORIZONTAL, {0,0, PlayheadWidth, 100})
, _timeRuler(timeRuler)
, _timeControl(timeControl)
{
	
	_currentTimeListener = timeControl->currentTimeUpdateEvent.newListener(this, &Playhead::_currentTimeChanged);
	
	
	_draggingStateListener = isDraggingEvent.newListener(this, &Playhead::_draggingStateChanged);
	
//	if(timeRuler)
//	{
//		this->constrainTo(_tracksPanel->getClippingView());
//	}

	this->setConstrainedToParent(true);
	
	
	_playheadTriangle.setMode(OF_PRIMITIVE_TRIANGLES);
	
	
	
	_playheadTriangle.addVertex({ (PlayheadWidth - PlayheadTriangleSize) *0.5 , 0, 0});
	_playheadTriangle.addVertex({ (PlayheadWidth + PlayheadTriangleSize) *0.5 , 0, 0});
	_playheadTriangle.addVertex({ PlayheadWidth*0.5 , PlayheadTriangleSize * sin(ofDegToRad(60)), 0});
	
	
	
	moveToFront();
}

//---------------------------------------------------------------------
void Playhead::onDraw() const
{
	ofRectangle r (0,0,getWidth(), getHeight());
	
	auto x = getX();
	
	if(x < 0.0f)
	{
		r.x -= x;
		r.width += x;
		
	}
	else
		if (x + getWidth() > parent()->getWidth())
		{
			r.width = parent()->getWidth() - x;
		}
	
	if(r.width > 0.0f && r.getMaxX() > 0.f ){
		
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
		ofDrawRectangle(r);
		
		ofNoFill();
		
		if (isPointerDown())
		{
			ofSetColor(255, 120);
			ofDrawRectangle(r);
		}
		else if (isPointerOver() && _highlightOnOver)
		{
			ofSetColor(30, 120);
			ofDrawRectangle(r);
		}
		_playheadTriangle.drawWireframe();
		
		ofPopStyle();
	}
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
	if(_timeRuler && _timeControl)
	{
		setPosition(screenToParentX(_timeRuler->timeToScreenPosition(_timeControl->getCurrentTime())) - (getWidth() / 2), getY());
	}
}
//---------------------------------------------------------------------
void Playhead::_onDragging(const DOM::CapturedPointer& pointer)
{
	ConstrainedGrabHandle::_onDragging(pointer);
	
	if(_timeRuler && _timeControl)
	{
		
		_timeControl->setCurrentTime(_timeRuler->screenPositionToTime(parentToScreenX(getX() + getWidth() / 2)));
	}
	
}

} } // ofx::LineaDeTiempo
