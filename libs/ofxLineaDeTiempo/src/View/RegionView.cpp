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
: Widget(controller->getId(), 0,0, TrackInitialHeight, TrackInitialHeight)
, _parentTrack(parentTrack)
, _controller(controller)
{
	


	
	_leftHandle = addChild<MUI::EdgeHandle>("leftHandle", DOM::RECT_LEFT, this);
	_rightHandle = addChild<MUI::EdgeHandle>("rightHandle", DOM::RECT_RIGHT, this);
	
	_header = addChild<RegionHeaderView>(this);
	_header->setStyles(headerStyles);
	
	setShapeDrawMode(MUI::ShapeDrawMode::ROUNDED_RECTANGLE);


	_shapeListener = shapeChanged.newListener(this, &RegionView::_shapeChanged);

//	_shapeListeners.push(resize.newListener(this, &RegionView::resized));
	
	if(controller)
		_timeRangeChangeListener = controller->timeRangeChangedEvent.newListener(this, &RegionView::_timeRangeChanged);
	setDraggable(true);
	updateLayout();
	
}

void RegionView::_timeRangeChanged(ofRange64u& timeRange)
{
	if(!bIgnoreTimeRangeChange)
	{
		
		updateRectFromTimeRange(timeRange);
		
	}
	_onTimeRangeChange();
}
void RegionView::_shapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!bIgnoreShapeChange && e.changedHorizontally())
	{
//		bIgnoreTimeRangeChange = true;
		updateTimeRangeFromRect();
		
//		bIgnoreTimeRangeChange = false;
	}
}

//void RegionView::updateLayout()
//{
//	if(_controller && !bIgnoreTimeRangeChange)
//	updateRectFromTimeRange();
//}

void RegionView::updateTimeRangeFromRect()
{
	bIgnoreTimeRangeChange = true;
	if(_parentTrack && _controller){
//		std::cout << "RegionView::updateTimeRangeFromRect " << getId() << "  -  " << getShape();
		_controller->setTimeRange(_parentTrack->rectToTimeRange(getShape()), false);
		updateLayout();
//		std::cout << "  " << _controller->getTimeRange() << "\n";
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
