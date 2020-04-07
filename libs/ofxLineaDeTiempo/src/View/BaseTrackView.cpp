//
//  BaseTrack.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include "MUI/Utils.h"
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {



BaseTrackView::BaseTrackView(const std::string& id, DOM::Element* parentGroupView, TimeRuler* timeRuler)
:DOM::Element(id, 0, 0, parentGroupView->getWidth(), 150)
, _parentGroupView(dynamic_cast<TrackGroupView*>(parentGroupView))
, _timeRuler(timeRuler)
{
	setParent(parentGroupView);

	_color = TrackBackgroundColor;
	_textColor = ofColor::white;
	
}


TracksPanel* BaseTrackView::getParentPanel()
{
	if(_parentGroupView){
		return _parentGroupView->getParentPanel();
	}
	return dynamic_cast<TracksPanel*>(this);
	
}

void BaseTrackView::setColor(const ofColor& color)
{
	_color = color;
	
	_textColor =  (color.getBrightness()>127)?ofColor::black:ofColor::white;
	
	
	auto c = color;
	ofNotifyEvent(colorChangeEvent, c, this);
}

const ofColor& BaseTrackView::getColor() const
{
	return _color;
}
const ofColor& BaseTrackView::getTextColor() const
{
	return _textColor;
}

void BaseTrackView::onDraw() const
{
	ofFill();
	ofSetColor(TrackBackgroundColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(TrackEdgeColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());
}



void BaseTrackView::updateLayout()
{
	for(auto r: children())
	{
		
		if(r)
		{
			r->updateLayout();
			
		}
	}
}


void BaseTrackView::setHeader(TrackHeader* header)
{
	_header = header;
}

TrackHeader* BaseTrackView::getHeader()
{
	return _header;
}

const TrackHeader* BaseTrackView::getHeader() const
{
	return _header;
}

TrackGroupView* BaseTrackView::getParentGroupView()
{
	return _parentGroupView;
}

TimeRuler * BaseTrackView::getTimeRuler()
{
	return _timeRuler;
}


const TimeRuler * BaseTrackView::getTimeRuler() const
{
	return _timeRuler;
}

}} //ofx::LineaDeTiempo
