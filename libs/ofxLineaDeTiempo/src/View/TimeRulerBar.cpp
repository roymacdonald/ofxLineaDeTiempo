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
	
//	moveToFront();
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
		_rulerLines.addVertex({0, _timecodeTextRect.height, 0});
		_rulerLines.addVertex({getWidth(), _timecodeTextRect.height, 0});
		
		
		auto screenX = getScreenX();
		float currentLabelPos = 0;
		_labels.clear();
		for(int i = startIndex; i < endIndex + 1; ++i)
		{
			uint64_t startTime = (uint64_t) floor(_currentRange.min/multipliers[i]) * multipliers[i] ;
			if(_currentRange.max > (startTime))
			{
				
				float h = ofMap(i, startIndex, endIndex, (getHeight() - _timecodeTextRect.height)*0.5, getHeight() - _timecodeTextRect.height, true);
				float y = _timecodeTextRect.height;
				
				
				float x = _timeRuler->timeToScreenPosition(startTime) - screenX;
				
				float mn_widht = _timecodeTextRect.width;
				
				float t_h, t_y;
				
				for(size_t j = 0; x < w; ++j ){
					

//
//					if(x < getWidth())
					
//					{
					
					t_h = h;
					t_y = y;
					
						if(i == endIndex && (j == 0 || (x - currentLabelPos) >  mn_widht))
						{
							
							_labels[x + _textMargin] = ofxTimecode::timecodeForMillis(startTime + j*multipliers[i]);
							currentLabelPos = x;
							t_h = getHeight();
							t_y = 0;
						}
						
						
						_rulerLines.addVertex({x, t_y, 0});
						_rulerLines.addVertex({x, t_h + t_y, 0});
					x += distances[i];
//					}
				}
			}
		}
	}
}


void TimeRulerBar::onDraw() const
{
	ofSetColor(ConstVars::TrackBackgroundColor);
	ofFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofSetColor(ConstVars::TrackEdgeColor);
	ofNoFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
	
	for(auto& l : _labels)
	{
		ofDrawBitmapString(l.second, l.first, _timecodeTextRect.y);
		
	}

	ofSetColor(200);
	_rulerLines.draw();
		
	
	auto str = ofxTimecode::timecodeForMillis( _timeRuler->screenPositionToTime(ofGetMouseX()));
	
	ofDrawBitmapStringHighlight(str, ofGetMouseX()-getScreenX()+6, ofGetMouseY()-getScreenY() + 14);
	
	
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


