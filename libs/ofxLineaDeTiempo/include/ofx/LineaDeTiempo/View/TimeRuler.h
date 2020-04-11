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

namespace ofx {
namespace LineaDeTiempo {

class TracksPanel;

class TimeRuler
: public DOM::Element
{
public:
	TimeRuler( TracksPanel* panel, TimeControl* timeControl, const ofRectangle& rect);
	
	virtual ~TimeRuler() = default;
	
	virtual void updateLayout() override;
	
	
	float timeToScreenPosition(uint64_t time) const;
	
	uint64_t  screenPositionToTime(float x) const;
	

protected:
	friend class TimeRulerBar;
	TimeRulerHeader* _header = nullptr;

	TimeRulerBar* _bar = nullptr;
	

	TracksPanel* _panel = nullptr;
	
	
	void _setBarShape(bool dontCheck = false);
	
	
	TimeControl * _timeControl = nullptr;
	
	ofRange _trackScreenHorizontal;
	
	
	ofEventListener _trackContainerListener;
	void _tracksContainerShapeChanged(DOM::ShapeChangeEventArgs& e);
	
};


} } // ofx::LineaDeTiempo
