//
//  BaseTrack.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "MUI/Utils.h"


namespace ofx {
namespace LineaDeTiempo {



ofColor BaseTrackView::backgroundColor = ofColor(80);
ofColor BaseTrackView::edgeColor = ofColor(120);
const float BaseTrackView::initialHeight = 150;

BaseTrackView::BaseTrackView(const std::string& id, DOM::Element* parentView)
:DOM::Element(id, 0, 0, 150, 150)
,BaseHasHeader<TrackHeader>()
//,_parentGroupView(parentGroupView)
{
	setParent(parentView);
}


void BaseTrackView::setColor(const ofColor& color)
{
	_color = color;
}

const ofColor& BaseTrackView::getColor() const
{
	return _color;
}

void BaseTrackView::onDraw() const
{
	ofFill();
	ofSetColor(backgroundColor);
	ofDrawRectangle(0, 0, getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(edgeColor);
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
//TrackGroupView* BaseTrackView::parentGroup()
//{
//	return _parentGroupView;
//}
//
//const TrackGroupView* BaseTrackView::parentGroup() const
//{
//	return _parentGroupView;
//}
//



}} //ofx::LineaDeTiempo
