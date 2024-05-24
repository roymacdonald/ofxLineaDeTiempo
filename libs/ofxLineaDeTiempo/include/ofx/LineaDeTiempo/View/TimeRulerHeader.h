//
//  TimeRulerHeader.hpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//



#pragma once


#include "ofx/DOM/Element.h"
#include "LineaDeTiempo/Controller/TimeControl.h"
#include "LineaDeTiempo/View/TimeControlView.h"


namespace ofx {
namespace LineaDeTiempo {


class TimeRulerHeader
: public DOM::Element
{
public:
	TimeRulerHeader( const ofRectangle& shape, TracksPanel* panel, TimeControl* timeControl);
	
	virtual ~TimeRulerHeader() = default;
	
	virtual void updateLayout() override;
protected:
	TimeControlView* _timeControlView  = nullptr;
	TimeDisplay* _timeDisplay = nullptr;
};



} } // ofx::LineaDeTiempo
