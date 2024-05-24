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



BaseTrackView::BaseTrackView(const std::string& id, DOM::Element* parentGroupView, TimeRuler * timeRuler)
:DOM::Element(id, 0, 0, parentGroupView->getWidth(), 150)
, _parentGroupView(dynamic_cast<TrackGroupView*>(parentGroupView))
, _timeRuler(timeRuler)
{
	setParent(parentGroupView);
	
	
	_color = ConstVars::TrackBackgroundColor;
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
	ofSetColor(ConstVars::TrackBackgroundColor.get());
	ofDrawRectangle(0, 0, getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(ConstVars::TrackEdgeColor.get());
	ofDrawRectangle(0, 0, getWidth(), getHeight());
}


void BaseTrackView::updateWidth(const float& w)
{
	auto s = getShape();
	s.width = w;
	s.x = 0;
	setShape(s);
	for(auto& c: children<BaseTrackView>())
	{
		c->updateWidth(w);
	}
}

void BaseTrackView::setHeader(TrackHeader* header)
{
	_header = header;
	if(_header)
	{
		int followType = MUI::FOLLOW_Y | MUI::FOLLOW_HEIGHT;
		int followMode = MUI::FOLLOW_SCREEN;
	
		getFollower()->mutuallyFollow(_header->getFollower(), followType, followMode);

	}
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


MUI::Follower* BaseTrackView::getFollower()
{
	if(!_follower)
		_follower = std::make_unique<MUI::Follower>(this);
	return _follower.get();
}

}} //ofx::LineaDeTiempo
