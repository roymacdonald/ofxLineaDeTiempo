//
//  TrackRegion.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#include "TrackRegionView.h"
#include "Track.h"
#include "LineaDeTiempo/Controller/TrackRegionController.h"

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
float TrackRegion::headerHeight = 30.f;

//---------------------------------------------------------------------------------------------------------------------
TrackRegion::TrackRegion(const std::string& id, BaseTrack* parentTrack, const ofRange64u & timeRange, TrackRegionController *controller)
: Widget(id, 0,0, BaseTrack::initialHeight, BaseTrack::initialHeight)
, _timeRange(timeRange)
, _parentTrack(parentTrack)
, BaseHasController<TrackRegionController>(controller)
{
	setFocusable(true);
	updateRectFromTimeRange();
}

//---------------------------------------------------------------------------------------------------------------------
const ofRange64u& TrackRegion::getTimeRange()
{
	return _timeRange;
}
//---------------------------------------------------------------------------------------------------------------------
void TrackRegion::updateLayout() {
	updateRectFromTimeRange();
}
//---------------------------------------------------------------------------------------------------------------------
void TrackRegion::setTimeRange(const ofRange64u& t){
	if(_timeRange != t){
		_timeRange = t;
		updateRectFromTimeRange();
		ofNotifyEvent(timeRangeChangedEvent, _timeRange, this);
	}
}
//---------------------------------------------------------------------------------------------------------------------
void TrackRegion::updateRectFromTimeRange(){
	if(_parentTrack){
		setShape(_parentTrack->timeRangeToRect(_timeRange));
	}
}
//---------------------------------------------------------------------------------------------------------------------
const BaseTrack* TrackRegion::parentTrack()
{
	return _parentTrack;
}
} } // ofx::LineaDeTiempo
