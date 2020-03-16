//
//  BaseTrack.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#include "LineaDeTiempo/View/TrackView.h"
#include "MUI/Utils.h"
#include "LineaDeTiempo/Controller/TrackController.h"
namespace ofx {
namespace LineaDeTiempo {


const float TrackView::initialHeight = 150;
ofColor TrackView::backgroundColor = ofColor(80);
ofColor TrackView::edgeColor = ofColor(120);

TrackView::TrackView(TrackGroupView* parentGroupView, TrackController* controller)
:DOM::Element(controller->getId(), 0, 0, initialHeight, initialHeight)
,BaseHasLayout()
,BaseHasHeader<TrackHeader>()
,BaseHasRegions<RegionView>()
,BaseHasController<TrackController>(controller)
,_parentGroupView(parentGroupView)
{
	_regionsStyle = make_shared<MUI::Styles>();
}

ofRectangle TrackView::timeRangeToRect(const ofRange64u& t) const
{
	ofRectangle r (timeToLocalPosition(t.min), 0,timeToLocalPosition(t.max), getHeight());
	r.width -= r.x;
	return r;
}

float TrackView::timeToLocalPosition(const uint64_t& t) const
{
	return MUI::Math::lerp(t, 0, getTimeControl().getTotalTime(), 0, getWidth());
}

uint64_t TrackView::localPositionToTime(float x) const
{
	return MUI::Math::lerp(x, 0, getWidth(), 0, getTimeControl().getTotalTime());
}

float TrackView::timeToScreenPosition(uint64_t time) const
{
	return DOM::Element::localToScreen({timeToLocalPosition(time),0}).x;
}

uint64_t  TrackView::screenPositionToTime(float x) const
{
	return localPositionToTime(DOM::Element::screenToLocal({x,0}).x);
}

void TrackView::setColor(const ofColor& color)
{
	_color = color;
	
	_regionsStyle->setColor(_color, MUI::Styles::ROLE_BACKGROUND);
	
}

const ofColor& TrackView::getColor()
{
	return _color;
}

shared_ptr<MUI::Styles> TrackView::getRegionsStyle()
{
	return _regionsStyle;
}

void TrackView::onDraw() const
{
	ofFill();
	ofSetColor(backgroundColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(edgeColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());
}

//---------------------------------------------------------------------------------------------------------------------
float TrackView::getHeightFactor()
{
	return _heightFactor;
}

void TrackView::setHeightFactor(float factor)
{
	_heightFactor = factor;
}

void TrackView::updateLayout()
{
	
	for(auto r: children())
	{
		
		if(r)
		{
			r->updateLayout();
			
		}
	}
}
TrackGroupView* TrackView::parentGroup()
{
	return _parentGroupView;
}

const TrackGroupView* TrackView::parentGroup() const
{
	return _parentGroupView;
}




}} //ofx::LineaDeTiempo
