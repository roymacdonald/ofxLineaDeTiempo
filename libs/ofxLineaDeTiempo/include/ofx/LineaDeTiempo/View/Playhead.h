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
	
	ofEventListener _currentTimeListener;
	void _currentTimeChanged(uint64_t& t);

	ofEventListener _draggingStateListener;
	void _draggingStateChanged(bool & bDragging);
		
	
	
	ofEventListeners _tracksListeners;
	
	void _trackNumChanged(DOM::ElementEventArgs& );
	void _tracksOrderChanged(DOM::ElementOrderEventArgs& );

	virtual void _onDragging(const DOM::CapturedPointer& pointer)override;
	
	TimeControl* _timeControl = nullptr;

	TimeRuler* _timeRuler = nullptr;
	
private:
	
	DOM::Element * _constraint = nullptr;
	
	
	ofMesh _playheadTriangle;
	
	bool _wasPlaying = false;
	
};

} } // ofx::LineaDeTiempo
