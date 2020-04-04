//
//  TimeRuler.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 4/2/20.
//

#include "TimeRuler.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include <chrono>

namespace ofx {
namespace LineaDeTiempo {

//==========================================================================================================
TimeRuler::TimeRuler(TracksPanel* panel, TimeControl* timeControl)
: DOM::Element("timeRuler", 0, 0, panel->getWidth(), TimeRulerInitialHeight)
, _panel(panel)
{
	
	_header = addChild<TimeRulerHeader>(timeControl);
	_bar = addChild<TimeRulerBar>( panel, timeControl);
	
	updateLayout();
	
	
	_panelListeners.push(panel->resize.newListener(this, &TimeRuler::_panelResized));
	_panelListeners.push(panel->getContainer()->move.newListener(this, &TimeRuler::  _tracksContainerMoved));
	_panelListeners.push(panel->getContainer()->resize.newListener(this, &TimeRuler::_tracksContainerResized));
	
	
	setDrawChildrenOnly(true);
	
	
	
}


void TimeRuler::_tracksContainerMoved(DOM::MoveEventArgs& e)
{
	updateLayout();
}

void TimeRuler::_tracksContainerResized(DOM::ResizeEventArgs& e)
{
	updateLayout();
}

void TimeRuler::_panelResized(DOM::ResizeEventArgs& e)
{
	setShape({0.f, 0.f, _panel->getWidth(), getHeight()});
	updateLayout();
}

void TimeRuler::updateLayout()
{
	if(_panel && _header && _bar && _panel->getClippingView())
	{
		auto cv = _panel->getClippingView();
		
		auto w = _panel->getTracksHeaderWidth();
		_header->setShape({0, 0, w, TimeRulerInitialHeight});
		
		auto x = screenToLocal(cv->localToScreen({0,0})).x;
		
		auto x2 = screenToLocal(cv->localToScreen({cv->getWidth(),0})).x;
		
		_bar->setShape({x, 0, x2 -x, TimeRulerInitialHeight});
		
		_header->updateLayout();
		_bar->updateLayout();
	}
}

//==========================================================================================================

ofBitmapFont TimeRulerHeader::bf = ofBitmapFont();


TimeRulerHeader::TimeRulerHeader( TimeControl* timeControl)
:  DOM::Element("TimeRulerHeader", 0,0,100,100)
, _timeControl(timeControl)
{
	
	
	
	
}


void TimeRulerHeader::updateLayout()
{
	
	
}

void TimeRulerHeader::onDraw() const
{
	DOM::Element::onDraw();
	stringstream ss;
	
	auto t =_timeControl->getCurrentTime();
	
	ss        << (t/(1000*60*60))%60;
	
	ss << ":" << (t/(1000*60))%60;
	
	ss << ":" << (t/1000)%60;
	
	ss << ":" << t%1000;
	
	
	
	auto bb = bf.getBoundingBox(ss.str(), 0, 0);
	
	auto y = bb.y;
	
	bb.alignTo(getShape());
	
	ofPushStyle();
	
	ofSetColor(DefaultTextColor);
	ofDrawBitmapString( ss.str(), bb.x, bb.y - y);
	
	ofNoFill();
	ofSetColor(TrackEdgeColor);
	ofDrawRectangle(getShape());
	
	ofPopStyle();
	
}

//==========================================================================================================

TimeRulerBar::TimeRulerBar( TracksPanel* panel, TimeControl* timeControl)
: MUI::Widget("TimeRulerBar", 0,0,100,100)
, _timeControl(timeControl)
, _panel(panel)
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
	
	
	_makeRulerLines();
	
	setDraggable(true);
	setHighlightOnOver(false);
	
	

	
}

void TimeRulerBar::_onDragging(const DOM::CapturedPointer& pointer)
{

	
	_timeControl->setCurrentTime(_panel->screenPositionToTime(pointer.position().x));
	
	
}

void TimeRulerBar::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	Widget::_onPointerEvent(e);
	
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
		_timeControl->setCurrentTime(_panel->screenPositionToTime(e.screenPosition().x));
    }
}


void TimeRulerBar::_makeRulerLines()
{
	if(_panel){
		
//		float distances [4];
//		bool bDraw [4];
//
//		_MILLIS =0,
//		_SECONDS,
//		_MUNUTES,
//		_HOURS
		

		_rulerLines.clear();
		
		_rulerLines.setMode(OF_PRIMITIVE_LINES);
		
		auto d = std::abs( _panel->timeToScreenPosition(0) - _panel->timeToScreenPosition(1));
		
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
		
		
		for(int i = startIndex; i < endIndex + 1; ++i)
		{
//			 if(distances[i] > _minLineDist && distances[i] < getWidth())
//			 {
				 uint64_t startTime = (uint64_t) floor(_currentRange.min/multipliers[i]) * multipliers[i] ;
//				 std::cout << i << "   startTime: " << startTime << " rangeMIn: " << _currentRange.min << "\n";
				 if(_currentRange.max > (startTime))
				 {
					 float h = ofMap(i, startIndex, endIndex, getHeight()*0.3, getHeight(), true);
					 float x = screenToLocal({_panel->timeToScreenPosition(startTime),0}).x;
					 for(size_t j = 0; x < w; ++j ){
						 
						 x += distances[i];
						
						 if(x < getWidth())
						 {
							 _rulerLines.addVertex({x, 0, 0});
							 _rulerLines.addVertex({x, h, 0});
						 }
					 }
					 
//				 }
			 }
		}
////		std::cout << "TimeRulerBar::_makeRulerLines  " << d << " - " << _rulerLines.getNumVertices()
//
//		<< " MILLIS  " << distances[_MILLIS]
//		<< " SECONDS " << distances[_SECONDS]
//		<< " MINUTES " << distances[_MINUTES]
//		<< " HOURS   " << distances[_HOURS]
//		<< "\n";
//
		
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
	if(_panel)
	{
		_currentRange.min = _panel->screenPositionToTime(localToScreen({0,0}).x);
		_currentRange.max = _panel->screenPositionToTime(localToScreen({getWidth(),0}).x);
		
		_makeRulerLines();
	}
}



} } // ofx::LineaDeTiempo


