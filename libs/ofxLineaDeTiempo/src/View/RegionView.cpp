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

namespace ofx {
namespace LineaDeTiempo {


float RegionView::headerHeight = 18.f;


RegionView::RegionView (TrackView* parentTrack, RegionController *controller)
: Widget(controller->getId(), 0,0, BaseTrackView::initialHeight, BaseTrackView::initialHeight)
, _parentTrack(parentTrack)
, BaseHasController<RegionController>(controller)
, BaseHasHeader<RegionHeaderView>()
{
//	setFocusable(false);
	updateLayout();
	
	_leftHandle = addChild<MUI::EdgeHandle>("leftHandle", DOM::RECT_LEFT, this);
	_rightHandle = addChild<MUI::EdgeHandle>("rightHandle", DOM::RECT_RIGHT, this);
	
	setHeader(addChild<RegionHeaderView>(this));
	
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
	if(getController() && !bIgnoreTimeRangeChange)
	updateRectFromTimeRange(getController()->getTimeRange());
}

void RegionView::updateTimeRangeFromRect()
{
	if(_parentTrack && getController()){
//		std::cout << "RegionView::updateTimeRangeFromRect " << getId() << "  -  " << getShape();
		getController()->setTimeRange(_parentTrack->rectToTimeRange(getShape()), false);
		
//		std::cout << "  " << getController()->getTimeRange() << "\n";
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


} } // ofx::LineaDeTiempo
