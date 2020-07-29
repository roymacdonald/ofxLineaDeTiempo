//
//  TrackRegion.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
namespace ofx {
namespace LineaDeTiempo {





RegionView::RegionView (TrackView* parentTrack, RegionController *controller, std::shared_ptr<MUI::Styles> headerStyles)
: Widget(controller->getId(), 0,0, ConstVars::TrackInitialHeight, ConstVars::TrackInitialHeight)
, _parentTrack(parentTrack)
, _controller(controller)
{
	


	
	_leftHandle = addChild<MUI::EdgeHandle>("leftHandle", DOM::RECT_LEFT, this, MUI::ALIGN_INSIDE);
	_rightHandle = addChild<MUI::EdgeHandle>("rightHandle", DOM::RECT_RIGHT, this, MUI::ALIGN_INSIDE);
	
	_leftHandle->setTargetConstraint(_parentTrack);
	_rightHandle->setTargetConstraint(_parentTrack);
	
	_header = addChild<RegionHeaderView>(this);
	_header->setStyles(headerStyles);
	
	setShapeDrawMode(MUI::ShapeDrawMode::ROUNDED_RECTANGLE);


	setDraggable(true);
	updateLayout();
	
}


void RegionView::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	if(!bIgnoreShapeChange && e.changedHorizontally())
	{
//		bIgnoreTimeRangeChange = true;
		updateTimeRangeFromRect();
		
//		bIgnoreTimeRangeChange = false;
	}
}


void RegionView::updateTimeRangeFromRect()
{
	bIgnoreTimeRangeChange = true;
	if(_parentTrack && _controller){
//		_controller->setTimeRange(_parentTrack->rectToTimeRange(getShape()), false);
		// communicate from view to controller via ofEvent to make sure there are no threading data races
		updateLayout();
		auto t = _parentTrack->rectToTimeRange(getShape());
		ofNotifyEvent(timeRangeChangedEvent, t, this);
	}
	bIgnoreTimeRangeChange = false;
}


void RegionView::updateRectFromTimeRange()
{
	updateRectFromTimeRange(_controller->getTimeRange());
}

void RegionView::updateRectFromTimeRange(const ofRange64u& timeRange)
{
	bIgnoreShapeChange = true;
	if(_parentTrack){
		setShape(_parentTrack->timeRangeToRect(timeRange));
		updateLayout();
	}
	bIgnoreShapeChange = false;
}

const TrackView* RegionView::parentTrack() const
{
	return _parentTrack;
}

TrackView* RegionView::parentTrack()
{
	return _parentTrack;
}



} } // ofx::LineaDeTiempo
