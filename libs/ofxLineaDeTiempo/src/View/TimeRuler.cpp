//
//  TimeRuler.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 4/2/20.
//

#include "LineaDeTiempo/View/TimeRuler.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include <chrono>

namespace ofx {
namespace LineaDeTiempo {

//==========================================================================================================
TimeRuler::TimeRuler(TracksPanel* panel, TimeControl* timeControl, const ofRectangle& rect)
: DOM::Element("timeRuler", rect)
, _panel(panel)
, _timeControl(timeControl)
{
	
	_header = addChild<TimeRulerHeader>(timeControl);
	_bar = addChild<TimeRulerBar>( this, timeControl);
	
	updateLayout();
	
	
//	_panelListeners.push(panel->shapeChanged.newListener(this, &TimeRuler::_panelShapeChanged));
//	_panelListeners.push(panel->getContainer()->shapeChanged.newListener(this, &TimeRuler::_tracksContainerShapeChanged));
	
//	_panelListeners.push(panel->resize.newListener(this, &TimeRuler::_panelResized));
//	_panelListeners.push(panel->getContainer()->move.newListener(this, &TimeRuler::  _tracksContainerMoved));
//	_panelListeners.push(panel->getContainer()->resize.newListener(this, &TimeRuler::_tracksContainerResized));
	
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
	
	
}

void TimeRuler::_tracksContainerShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(e.changedHorizontally()){
		if(_bar && _panel->getTracksView() && _panel->getTracksView()->getContainer())
		{
			auto r = _panel->getTracksView()->getContainer()->getScreenShape();
			if(r.width < 0.0f) r.standardize();
			
			if(! ofIsFloatEqual(_trackScreenHorizontal.min, r.x) ||
			   ! ofIsFloatEqual(_trackScreenHorizontal.max, r.x + r.width))
			{
				_trackScreenHorizontal.min = r.x;
				_trackScreenHorizontal.max = r.x + r.width;
			}
			if(e.widthChanged())
			{
				_setBarShape(true);
			}
			else
			if(e.xChanged())
			{
				_bar->makeRulerLines();
			}
		}
	}
}

void TimeRuler::_setBarShape(bool dontCheck)
{
	if(_panel && _panel->getTracksView())
	{
		auto cv = _panel->getTracksView()->getClippingView();
		if(cv){
			float x = cv->getX() + _header->getWidth();
			if( dontCheck || !ofIsFloatEqual(x, _bar->getX()) || !ofIsFloatEqual(cv->getWidth(), _bar->getWidth()))
			{
				_bar->setShape({x, 0, cv->getWidth(), TimeRulerInitialHeight});
				_bar->makeRulerLines();
			}
		}
	}
}


void TimeRuler::updateLayout()
{
	if(_panel && _header && _bar)// && _panel->getClippingView())
	{
		
		auto w = _panel->getTracksHeaderWidth();
		if(! ofIsFloatEqual(w, _header->getWidth()) ||
		   ! ofIsFloatEqual(TimeRulerInitialHeight, _header->getHeight())
		   ){
			_header->setShape({0, 0, w, TimeRulerInitialHeight});
			_header->updateLayout();
		}
		
		_setBarShape();
		
		if(_panel->getTracksView() && _panel->getTracksView()->getClippingView())
		{
			float h = _panel->getTracksView()->getClippingView()->getScreenShape().getMaxY() - getScreenY();
			_bar->setPlayheadHeight(h);
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



} } // ofx::LineaDeTiempo


