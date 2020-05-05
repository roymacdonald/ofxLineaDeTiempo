//
//  TimeRulerHeader.cpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//

#include "LineaDeTiempo/View/TimeRulerHeader.h"


namespace ofx {
namespace LineaDeTiempo {




TimeRulerHeader::TimeRulerHeader( const ofRectangle& shape, TracksPanel* panel, TimeControl* timeControl)
:  DOM::Element("TimeRulerHeader",shape)
{
	ofRectangle s (0,0,shape.width, shape.height/2);
	
	_timeControlView  =  addChild<TimeControlView>(s, panel,  timeControl, DOM::HORIZONTAL);
	
	_timeControlView->add(SET_IN_BUTTON);
	_timeControlView->add(GOTO_IN_BUTTON);
	_timeControlView->add(SPACER);
	_timeControlView->add(JUMP_BACKWARDS_BUTTON);
	_timeControlView->add(TRIGGER_BUTTON);
	_timeControlView->add(PLAY_PAUSE_TOGGLE);
	_timeControlView->add(STOP_BUTTON);
	_timeControlView->add(JUMP_FORWARDS_BUTTON);
	_timeControlView->add(SPACER);
	_timeControlView->add(GOTO_OUT_BUTTON);
	_timeControlView->add(SET_OUT_BUTTON);
	
	
	s.y += s.getHeight();
	
	_timeDisplay = addChild<TimeDisplay>(s, timeControl);
	
	updateLayout();

}
void TimeRulerHeader::updateLayout()
{
	ofRectangle shape(0,0,getWidth(), getHeight()/2);
	if(_timeControlView)
	{
		_timeControlView->setShape(shape);
		_timeControlView->updateLayout();
	}
	if(_timeDisplay)
	{
		shape.y += shape.getHeight();
		_timeDisplay->setShape(shape);
		_timeDisplay->updateLayout();
	}
}

} } // ofx::LineaDeTiempo

