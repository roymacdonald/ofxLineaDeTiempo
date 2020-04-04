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
	
//	setStyles(regionStyles);
	
//	setFocusable(false);
	updateLayout();
	
	_leftHandle = addChild<MUI::EdgeHandle>("leftHandle", DOM::RECT_LEFT, this);
	_rightHandle = addChild<MUI::EdgeHandle>("rightHandle", DOM::RECT_RIGHT, this);
	
	_header = addChild<RegionHeaderView>(this);
	_header->setStyles(headerStyles);
	
	setShapeDrawMode(MUI::ShapeDrawMode::ROUNDED_RECTANGLE);


	_shapeListeners.push(move.newListener(this, &RegionView::moved));

	_shapeListeners.push(resize.newListener(this, &RegionView::resized));
	
	if(controller)
		_timeRangeChangeListener = controller->timeRangeChangedEvent.newListener(this, &RegionView::_timeRangeChanged);
	setDraggable(true);
}

void RegionView::_timeRangeChanged(ofRange64u& timeRange)
{
	if(!bIgnoreTimeRangeChange)
	{
		updateRectFromTimeRange(timeRange);
	}
	_onTimeRangeChange();
}
void RegionView::moved(DOM::MoveEventArgs&)
{
	
	bIgnoreTimeRangeChange = true;
	updateTimeRangeFromRect();
	bIgnoreTimeRangeChange = false;
}

void RegionView::resized (DOM::ResizeEventArgs&)
{
	if(_leftHandle && _leftHandle->isDragging()) return;
	
	bIgnoreTimeRangeChange = true;
	updateTimeRangeFromRect();
	bIgnoreTimeRangeChange = false;
}


void RegionView::updateLayout() {
	if(_controller && !bIgnoreTimeRangeChange)
	updateRectFromTimeRange(_controller->getTimeRange());
}

void RegionView::updateTimeRangeFromRect()
{
	if(_parentTrack && _controller){
//		std::cout << "RegionView::updateTimeRangeFromRect " << getId() << "  -  " << getShape();
		_controller->setTimeRange(_parentTrack->rectToTimeRange(getShape()), false);
		
//		std::cout << "  " << _controller->getTimeRange() << "\n";
	}
}

void RegionView::updateRectFromTimeRange(const ofRange64u& timeRange){
	if(_parentTrack){
//		std::cout << "RegionView::updateRectFromTimeRange " << getId() << "  -  " <<  timeRange;
		setShape(_parentTrack->timeRangeToRect(timeRange));
//		std::cout << "  " << getShape() << "\n";
	}
}

const TrackView* RegionView::parentTrack() const
{
	return _parentTrack;
}

TrackView* RegionView::parentTrack()
{
	return _parentTrack;
}

//const RegionController * RegionView::getController() const
//{
//	return _controller;
//}
//RegionController * RegionView::getController()
//{
//	return _controller;
//}
//void RegionView::setController(RegionController * controller)
//{
//	_controller = controller;
//}


//void RegionView::setHeader(RegionHeaderView* header)
//{
//	_header = header;
//}
//RegionHeaderView* RegionView::getHeader()
//{
//	return _header;
//}
//const RegionHeaderView* RegionView::getHeader() const
//{
//	return _header;
//}



} } // ofx::LineaDeTiempo
