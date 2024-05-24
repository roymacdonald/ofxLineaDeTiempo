//
//  Playhead.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/3/20.
//

#pragma once
#include "MUI/Handles/ConstrainedGrabHandle.h"
#include "MUI/ofRectangleHelper.h"

#include "LineaDeTiempo/Controller/TimeControl.h"

namespace ofx {
namespace LineaDeTiempo {


class TimeRuler;


class Playhead
: public MUI::ConstrainedGrabHandle
{
public:
	
	Playhead(TimeRuler* timeRuler, TimeControl* timeControl, DOM::Element * constraint);
	virtual ~Playhead(){}
	
	virtual void onDraw() const override;
	
	void updatePosition();
	
protected:
	
	bool bIgnorePointer = false;
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

    virtual void _onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e) override;
	
	ofEventListener _currentTimeListener;
	void _currentTimeChanged(uint64_t& t);

	ofEventListener stopEventListener;
	void _onStopEvent();
	
	
	
	ofEventListener _draggingStateListener;
	void _draggingStateChanged(bool & bDragging);
		

	TimeControl* _timeControl = nullptr;

	TimeRuler* _timeRuler = nullptr;
	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;
	
private:
	
	DOM::Element * _constraint = nullptr;
	
	
	ofMesh _playheadTriangle;
	
	bool _wasPlaying = false;
	
	ofEventListener _constraintShapeListener;
	void _constraintShapeChanged(DOM::ShapeChangeEventArgs&);
	ofRectangle _constraintRect;
	
	
	
};

} } // ofx::LineaDeTiempo
