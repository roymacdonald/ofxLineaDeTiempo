//
//  TimeRulerBar.cpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//

#include "LineaDeTiempo/View/TimeRulerBar.h"
#include "LineaDeTiempo/View/TimeRuler.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include <chrono>

namespace ofx {
namespace LineaDeTiempo {

TimeRulerBar::TimeRulerBar(  TimeRuler* timeRuler, TimeControl* timeControl)
: MUI::Widget("TimeRulerBar", 0,0,100,100)
, _timeControl(timeControl)
, _timeRuler(timeRuler)
{
	
	distances.resize(_NUM_SUBDIVISIONS);
	bDraw.resize(_NUM_SUBDIVISIONS);
	multipliers.resize(_NUM_SUBDIVISIONS);
	
	
	multipliers[_MILLIS] = 	1;//std::chrono::milliseconds(1).count();
	multipliers[_CENTS] = 10;
	multipliers[_TENS] = 100;
	multipliers[_SECONDS] = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::seconds(1)).count();
	multipliers[_MINUTES] = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::minutes(1)).count();
	multipliers[_HOURS]   = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::hours(1)).count();
	
	
	makeRulerLines();
	
	setDraggable(true);
	setHighlightOnOver(false);
	
	_playhead = addChild<Playhead>(timeRuler, timeControl);
	
	moveToFront();
//	_updatePlayheadSize();
}

void TimeRulerBar::_onDragging(const DOM::CapturedPointer& pointer)
{

	
	_timeControl->setCurrentTime(_timeRuler->screenPositionToTime(pointer.position().x));
	
	
}

void TimeRulerBar::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	Widget::_onPointerEvent(e);
	
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
		_timeControl->setCurrentTime(_timeRuler->screenPositionToTime(e.screenPosition().x));
    }
}


void TimeRulerBar::makeRulerLines()
{
	if(_timeRuler){
		auto scr_x  = getScreenX();
		_currentRange.min = _timeRuler->screenPositionToTime(scr_x);
		_currentRange.max = _timeRuler->screenPositionToTime(scr_x+ getWidth());
		
		
		_rulerLines.clear();
		
		_rulerLines.setMode(OF_PRIMITIVE_LINES);
		
		auto d = std::abs( _timeRuler->timeToScreenPosition(0) - _timeRuler->timeToScreenPosition(1));
		
		auto w = getWidth();
		
		int startIndex = distances.size();
		int endIndex = 0;
		for(int i = 0; i < distances.size(); ++i)
		{
			distances[i] = d* multipliers[i];
			
			
			if(distances[i] > _minLineDist && distances[i] < getWidth())
			{
				startIndex = min(i, startIndex);
				endIndex = max(i, endIndex);
			}
		}
		
		
		auto screenX = getScreenX();
		
		for(int i = startIndex; i < endIndex + 1; ++i)
		{
			uint64_t startTime = (uint64_t) floor(_currentRange.min/multipliers[i]) * multipliers[i] ;
			if(_currentRange.max > (startTime))
			{
				float h = ofMap(i, startIndex, endIndex, getHeight()*0.3, getHeight(), true);
				float x = _timeRuler->timeToScreenPosition(startTime) - screenX;
				for(size_t j = 0; x < w; ++j ){
					
					x += distances[i];
					
					if(x < getWidth())
					{
						_rulerLines.addVertex({x, 0, 0});
						_rulerLines.addVertex({x, h, 0});
					}
				}
			}
		}
	}
}

 void TimeRulerBar::setPlayheadHeight(float height)
{
	if(_playhead){
		_playhead->setHeight(height);
		_playhead->moveToFront();
	}
}

void TimeRulerBar::onDraw() const
{
	ofSetColor(TrackBackgroundColor);
	ofFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofSetColor(TrackEdgeColor);
	ofNoFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());


	ofSetColor(200);
	_rulerLines.draw();
		
	
}

void TimeRulerBar::updateLayout()
{

	std::cout << "void TimeRulerBar::updateLayout() being called. this does nothing and should not be called\n";
}
//	if(_timeRuler)
//	{
//
//		makeRulerLines();
//
//		_updatePlayheadSize();
//	}
//}



} } // ofx::LineaDeTiempo


