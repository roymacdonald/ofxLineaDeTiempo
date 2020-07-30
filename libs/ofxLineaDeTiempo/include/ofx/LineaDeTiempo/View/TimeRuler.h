//
//  TimeRuler.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 4/2/20.
//

#pragma once


#include "ofx/DOM/Element.h"
#include "LineaDeTiempo/Controller/TimeControl.h"
#include "ofRange.h"
#include "LineaDeTiempo/View/TimeRulerHeader.h"
#include "LineaDeTiempo/View/TimeRulerBar.h"
#include "MUI/ZoomScrollbar.h"


namespace ofx {
namespace LineaDeTiempo {

class TracksPanel;

class TimeRuler
: public DOM::Element
{
public:
	TimeRuler( TracksPanel* panel, TimeControl* timeControl, const ofRectangle& rect, MUI::ZoomScrollbar * scrollbar);
	
	virtual ~TimeRuler() = default;
	
	virtual void updateLayout() override;
	
	
	float timeToScreenPosition(uint64_t time) const;
	
	uint64_t  screenPositionToTime(float x) const;
	

	void setPlayheadHeight(float height);

	
	const ofRange64u & getVisibleTimeRange() const;
	
	void printStatus();
	
protected:
	friend class TimeRulerBar;
	TimeRulerHeader* _header = nullptr;

	TimeRulerBar* _bar = nullptr;
	
	TimeControlView* _totalTimeLoopButtons = nullptr;

	TracksPanel* _panel = nullptr;
	
	
	void _setBarShape(bool dontCheck = false);
	
	
	TimeControl * _timeControl = nullptr;
	
//	virtual void _onShapeChange(const ShapeChangeEventArgs& ) override;
	
//	ofRange _trackScreenHorizontal;
	
	ofRange64u _visibleTimeRange;
	
	
//	ofEventListener _trackContainerListener;
//	void _tracksContainerShapeChanged(DOM::ShapeChangeEventArgs& e);
	
	Playhead * _playhead = nullptr;
	
//	void _setTrackScreenHorizontalRange();
	
	ofEventListener _totalTimeListener;
	void _totalTimeChanged();
	
	ofEventListener _horizontalZoomScrollbarListener;
	void _horizontalZoomChanged(ofRange&);

	void _updateVisibleTimeRange();
	
	MUI::ZoomScrollbar * _scrollbar = nullptr;

	
	
	
};


} } // ofx::LineaDeTiempo
