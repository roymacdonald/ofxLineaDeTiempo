//
//  RegionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

namespace ofx {
namespace LineaDeTiempo {


RegionController::RegionController(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack)
: BaseController(name, parentTrack)
, _parentTrack(parentTrack)
, _timeRange(timeRange)
{
	
}
		

const ofRange64u& RegionController::getTimeRange()
 {
 	return _timeRange;
 }


void RegionController::setTimeRange(const ofRange64u& t){
 	if(_timeRange != t){
 		_timeRange = t;
//		if(getView())
//		{
//			getView()->updateRectFromTimeRange(_timeRange);
//		}
 		ofNotifyEvent(timeRangeChangedEvent, _timeRange, this);
 	}
 }

TrackController * RegionController::getParentTrack()
{
	return _parentTrack;
}

const TrackController * RegionController::getParentTrack() const
{
	return _parentTrack;
}


} } // ofx::LineaDeTiempo
