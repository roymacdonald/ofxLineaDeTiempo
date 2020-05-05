//
//  TimeRuler.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 4/2/20.
//

#include "LineaDeTiempo/View/TimeRuler.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "MUI/Constants.h"
#include <chrono>
#include "ofMath.h"

namespace ofx {
namespace LineaDeTiempo {

//==========================================================================================================
TimeRuler::TimeRuler(TracksPanel* panel, TimeControl* timeControl, const ofRectangle& rect)
: DOM::Element("timeRuler", rect)
, _panel(panel)
, _timeControl(timeControl)
{
	
	_header = addChild<TimeRulerHeader>(ofRectangle (0, 0, _panel->getTracksHeaderWidth(), ConstVars::TimeRulerInitialHeight), panel, timeControl);
	_header->updateLayout();
	
	_bar = addChild<TimeRulerBar>( this, timeControl);

	_playhead = addChild<Playhead>(this, timeControl, _bar);
	_playhead->updatePosition();

	
	_totalTimeLoopButtons = addChild<TimeControlView>(ofRectangle (rect.getMaxX()-SCROLL_BAR_SIZE, 0, SCROLL_BAR_SIZE + CONTAINER_MARGIN, ConstVars::TimeRulerInitialHeight), panel, timeControl, DOM::VERTICAL);
	_totalTimeLoopButtons->add(SET_TOTAL_TIME_BUTTON);
	_totalTimeLoopButtons->add(SPACER);
	_totalTimeLoopButtons->add(LOOP_TOGGLE);
	
	
	updateLayout();
	
	if(panel->getTracksView() && panel->getTracksView()->getContainer())
	{
	_trackContainerListener = panel->getTracksView()->getContainer()->shapeChanged.newListener(this, &TimeRuler::_tracksContainerShapeChanged);
	}
	else
	{
		ofLogError("TimeRuler::TimeRuler") << "Panel's track view or its container are null. Cant set listeners for those";
	}
	
	setDrawChildrenOnly(true);
	moveToFront();
	_playhead->moveToFront();
	
}
void TimeRuler::_setTrackScreenHorizontalRange()
{
	if(_panel->getTracksView() && _panel->getTracksView()->getContainer())
	{
		auto r = _panel->getTracksView()->getContainer()->getScreenShape();
		if(r.width < 0.0f) r.standardize();
		
//		if(! ofIsFloatEqual(_trackScreenHorizontal.min, r.x) ||
//		   ! ofIsFloatEqual(_trackScreenHorizontal.max, r.x + r.width))
//		{
			_trackScreenHorizontal.min = r.x;
			_trackScreenHorizontal.max = r.x + r.width;
		
		_visibleTimeRange.min = screenPositionToTime(_trackScreenHorizontal.min);
		_visibleTimeRange.max = screenPositionToTime(_trackScreenHorizontal.max);
		
//		}
	}
}


void TimeRuler::_tracksContainerShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(e.changedHorizontally()){
		if(_bar)
		{
			
			_setTrackScreenHorizontalRange();
			
			if(e.widthChanged())
			{
				_setBarShape(true);
			}
			else
			if(e.xChanged())
			{
				_bar->makeRulerLines();
				if(_playhead) _playhead->updatePosition();
			}
		}
	}
}

void TimeRuler::_setBarShape(bool dontCheck)
{
	if(_bar && _panel && _panel->getTracksView())
	{
		auto cv = _panel->getTracksView()->getClippingView();
		if(cv){
			float x = cv->getX() + _header->getWidth();
			if( dontCheck || !ofIsFloatEqual(x, _bar->getX()) || !ofIsFloatEqual(cv->getWidth(), _bar->getWidth()))
			{
				_bar->setShape({x, 0, cv->getWidth(), ConstVars::TimeRulerInitialHeight});
				_bar->makeRulerLines();
				if(_playhead) _playhead->updatePosition();
			}
		}
	}
}


void TimeRuler::updateLayout()
{
	_setTrackScreenHorizontalRange();
	if(_panel && _header && _bar)// && _panel->getClippingView())
	{
		
		auto w = _panel->getTracksHeaderWidth();
		if(! ofIsFloatEqual(w, _header->getWidth()) ||
		   ! ofIsFloatEqual(ConstVars::TimeRulerInitialHeight.get(), _header->getHeight())
		   ){
			_header->setShape({0, 0, w, ConstVars::TimeRulerInitialHeight});
			_header->updateLayout();
		}
		
		_setBarShape();
		
		if(_totalTimeLoopButtons)
		{
			_totalTimeLoopButtons->setShape(ofRectangle (_bar->getShape().getMaxX() , 0, SCROLL_BAR_SIZE + CONTAINER_MARGIN, ConstVars::TimeRulerInitialHeight));
		}
		
		if(_panel->getTracksView() && _panel->getTracksView()->getClippingView())
		{
			float h = _panel->getTracksView()->getClippingView()->getScreenShape().getMaxY() - getScreenY();
			setPlayheadHeight(h);
		}

	}
}

float TimeRuler::timeToScreenPosition(uint64_t time) const
{
		return MUI::Math::lerp(time, 0, _timeControl->getTotalTime(),  _trackScreenHorizontal.min, _trackScreenHorizontal.max);
}

uint64_t  TimeRuler::screenPositionToTime(float x) const
{
	return MUI::Math::lerp(x, _trackScreenHorizontal.min, _trackScreenHorizontal.max, 0, _timeControl->getTotalTime(), true);
}

void TimeRuler::setPlayheadHeight(float height)
{
	if(_playhead){
		_playhead->setHeight(height);
		_playhead->moveToFront();
	}
}

const ofRange64u & TimeRuler::getVisibleTimeRange() const
{
	return _visibleTimeRange;
}
} } // ofx::LineaDeTiempo


