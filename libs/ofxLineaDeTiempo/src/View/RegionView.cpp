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


float RegionView::headerHeight = 30.f;


RegionView::RegionView (TrackView* parentTrack, RegionController *controller)
: Widget(controller->getId(), 0,0, BaseTrackView::initialHeight, BaseTrackView::initialHeight)
, _parentTrack(parentTrack)
, BaseHasController<RegionController>(controller)
{
	setFocusable(true);
	updateLayout();
}

void RegionView::updateLayout() {
	if(getController())
	updateRectFromTimeRange(getController()->getTimeRange());
}


void RegionView::updateRectFromTimeRange(const ofRange64u& timeRange){
	if(_parentTrack){
		setShape(_parentTrack->timeRangeToRect(timeRange));
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
