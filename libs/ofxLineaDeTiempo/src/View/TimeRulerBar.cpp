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
	
	ofBitmapFont bf;
	_timecodeTextRect = bf.getBoundingBox(ofxTimecode::timecodeForMillis(0), 0, 0);
	_timecodeTextRect.y *= -1;
	_timecodeTextRect.y += _textMargin;

	_timecodeTextRect.width += _textMargin*2;
	_timecodeTextRect.height += _textMargin *2;
	
	makeRulerLines();
	
	setDraggable(true);
	setHighlightOnOver(false);
	setMoveToFrontOnCapture(false);
	
	
	setDrawAsViewport(true);
	

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
				startIndex = std::min(i, startIndex);
				endIndex = std::max(i, endIndex);
			}
		}
		_rulerLines.addVertex({0, _timecodeTextRect.height, 0});
		_rulerLines.addVertex({getWidth(), _timecodeTextRect.height, 0});
		
		
		auto screenX = getScreenX();
		float currentLabelPos = 0;
		_labels.clear();

		float& mn_widht = _timecodeTextRect.width;
		
		int stride = ceil(_timecodeTextRect.width/distances[endIndex]);

		float h = 0;
		float y = 0;
		uint64_t startTime;
		for(int i = startIndex; i < endIndex + 1; ++i)
		{
			startTime = (uint64_t) floor(_currentRange.min/multipliers[i]) * multipliers[i] ;
			if(_currentRange.max > (startTime))
			{
				h = ofMap(i, startIndex, endIndex, (getHeight() - _timecodeTextRect.height)*0.5, getHeight() - _timecodeTextRect.height, true);
				y = _timecodeTextRect.height;

				
				float x = _timeRuler->timeToScreenPosition(startTime) - screenX;
				
				
				
				for(size_t j = 0; x < w; ++j ){
					
					_rulerLines.addVertex({x, y, 0});
					_rulerLines.addVertex({x, h + y, 0});
					x += distances[i];
					
				}
			}
		}
		startTime = (uint64_t) floor(_currentRange.min/(multipliers[endIndex]*stride)) * multipliers[endIndex]*stride ;
		float x = _timeRuler->timeToScreenPosition(startTime) - screenX;
		
		size_t n = ceil(_currentRange.max - startTime)/(multipliers[endIndex]*stride);
		n += 1;
		
		for(size_t j = 0; j < n && x < w; ++j )
		{
			_labels[x + _textMargin] = ofxTimecode::timecodeForMillis(startTime );

			startTime += multipliers[endIndex] * stride;
			x += distances[endIndex] * stride;
			_rulerLines.addVertex({x, 0, 0});
			_rulerLines.addVertex({x, _timecodeTextRect.height, 0});
		}
	}
}


void TimeRulerBar::onDraw() const
{
	ofSetColor(ConstVars::TrackBackgroundColor.get());
	ofFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofSetColor(ConstVars::TrackEdgeColor.get());
	ofNoFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
	
	for(auto& l : _labels)
	{
		ofDrawBitmapString(l.second, l.first, _timecodeTextRect.y);
		
	}

	ofSetColor(200);
	_rulerLines.draw();
		
	glm::vec2 m (ofGetMouseX(), ofGetMouseY());
	auto sp = getScreenPosition();
	if(m.x >= sp.x){
		auto str = ofxTimecode::timecodeForMillis( _timeRuler->screenPositionToTime(m.x));
	
		ofDrawBitmapStringHighlight(str, m.x - sp.x +6, m.y - sp.y + 14);
	}
	
}



} } // ofx::LineaDeTiempo


