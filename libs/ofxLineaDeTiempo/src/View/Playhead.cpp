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
Playhead::Playhead(TimeRuler* timeRuler, TimeControl* timeControl, DOM::Element * constraint)
: ConstrainedGrabHandle("Playhead",DOM::HORIZONTAL, {0,0, ConstVars::PlayheadWidth, 100})
, _timeRuler(timeRuler)
, _timeControl(timeControl)
, _constraint(constraint)
{
	
	_currentTimeListener = timeControl->currentTimeUpdateEvent.newListener(this, &Playhead::_currentTimeChanged);

	stopEventListener = timeControl->stopEvent.newListener(this, &Playhead::_onStopEvent);
	
	
	_constraintShapeListener = _constraint->shapeChanged.newListener(this, &Playhead::_constraintShapeChanged);
	
	
	_draggingStateListener = isDraggingEvent.newListener(this, &Playhead::_draggingStateChanged);
	

	this->constrainTo(constraint);
	
	
	_playheadTriangle.setMode(OF_PRIMITIVE_TRIANGLES);
	
	
	
	_playheadTriangle.addVertex({ (ConstVars::PlayheadWidth - ConstVars::PlayheadTriangleSize) *0.5 , 0, 0});
	_playheadTriangle.addVertex({ (ConstVars::PlayheadWidth + ConstVars::PlayheadTriangleSize) *0.5 , 0, 0});
	_playheadTriangle.addVertex({ ConstVars::PlayheadWidth*0.5 , ConstVars::PlayheadTriangleSize * sin(ofDegToRad(60)), 0});
	
	
	
	
	moveToFront();
	
	fix: la posicion deja de calcularse correctamente cuando se mueve el panel completo
	
	
}

void Playhead::_onStopEvent()
{
	updatePosition();
}

void Playhead::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	if(e.changedVertically())
	{
		_constraintRect.y = getY();
		_constraintRect.height = getHeight();
	}
	if(e.xChanged())
	{
		bIgnorePointer = !_constraintRect.intersects(getShape());
	}
}

void Playhead::_constraintShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(_constraint && e.changedHorizontally()){
		_constraintRect = _constraint->getScreenShape();
		auto x = screenToParentX(_constraintRect.x);
		_constraintRect.setPosition( x, 0);
		_constraintRect.height = getHeight();
	}
}
//---------------------------------------------------------------------
void Playhead::onDraw() const
{
	
	ofRectangle r = _constraintRect.getIntersection(getShape());

	r.x = 0;
	r.y = 0;
	
	
	
		if(r.width > 0.0f ){
			
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
	if(!bIgnorePointer)
	{
		ConstrainedGrabHandle::_onDragging(pointer);
		
		if(_timeRuler && _timeControl)
		{
			
			_timeControl->setCurrentTime(_timeRuler->screenPositionToTime(parentToScreenX(getX() + getWidth() / 2)));
		}
	}
}


void Playhead::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	if(!bIgnorePointer)	
	{
		MUI::ConstrainedGrabHandle::_onPointerEvent(e);
	}
}


void Playhead::_onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
	if(!bIgnorePointer || isDragging())
	{
		MUI::ConstrainedGrabHandle::_onPointerCaptureEvent(e);
	}
}
} } // ofx::LineaDeTiempo
