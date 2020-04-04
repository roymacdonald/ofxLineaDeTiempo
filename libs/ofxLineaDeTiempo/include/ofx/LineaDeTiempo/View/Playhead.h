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


class TracksPanel;


class Playhead
: public MUI::ConstrainedGrabHandle
{
public:
	
	Playhead(TracksPanel* tracksPanel, TimeControl* timeControl);
	virtual ~Playhead(){}
	
	virtual void onDraw() const override;
	
	void updatePosition();
	
protected:
	
	ofEventListener _currentTimeListener;
	void _currentTimeChanged(uint64_t& t);

	ofEventListener _draggingStateListener;
	void _draggingStateChanged(bool & bDragging);
		
	void _tracksViewShapeChanged(DOM::ResizeEventArgs &);
	
	ofEventListeners _tracksListeners;
	
	void _trackNumChanged(DOM::ElementEventArgs& );
	void _tracksOrderChanged(DOM::ElementOrderEventArgs& );

	virtual void _onDragging(const DOM::CapturedPointer& pointer)override;
	
	TimeControl* _timeControl = nullptr;

	TracksPanel* _tracksPanel = nullptr;
	
private:
	
	
	
	ofMesh _playheadTriangle;
	
	bool _wasPlaying = false;
	
};

} } // ofx::LineaDeTiempo
