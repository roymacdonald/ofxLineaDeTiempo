//
//  Playhead.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/3/20.
//

#pragma once
#include "ConstrainedGrabHandle.h"
#include "ofRectangleHelper.h"
//#include "TimeControl.h"
//#include "TracksPanel.h"
//#include "Constants.h"



namespace ofx {
namespace LineaDeTiempo {


class TracksPanel;




class Playhead: public MUI::ConstrainedGrabHandle{
public:
	
	Playhead(TracksPanel* tracksPanel);
	virtual ~Playhead(){}
	
	virtual void onDraw() const override;
	
	void updatePosition();
	
protected:
	
	ofEventListener _currentTimeListener;
	void _currentTimeChanged(uint64_t& t);

	ofEventListener _draggingStateListener;
	void _draggingStateChanged(bool & bDragging);
	
	TracksPanel* _tracksPanel = nullptr;
	
	void _tracksViewShapeChanged(DOM::ResizeEventArgs &);
	
	ofEventListeners _tracksListeners;
	
	void _trackNumChanged(DOM::ElementEventArgs& );// childAdded; childRemoved;
	void _tracksOrderChanged(DOM::ElementOrderEventArgs& );// childReordered;

	
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer)override;
	
private:
	
	bool _wasPlaying = false;
	
};

} } // ofx::LineaDeTiempo
