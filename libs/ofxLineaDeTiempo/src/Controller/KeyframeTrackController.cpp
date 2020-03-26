//
//  KeyFrameTrackController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#include "KeyFrameTrackController.h"

#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Controller/KeyFrameRegionController.h"


namespace ofx {
namespace LineaDeTiempo {


KeyFrameTrackController::KeyFrameTrackController(const std::string& name, TrackGroupController* parent, TimeControl* timeControl)
:TrackController(name, parent, timeControl)
{
	
}

KeyFrameRegionController * KeyFrameTrackController::addRegion( const std::string& regionName, const ofRange64u& timeRange)
{
	return _addRegion<KeyFrameRegionController>(regionName, timeRange);
}

bool KeyFrameTrackController::removeRegion(KeyFrameRegionController* track)
{
	return _removeRegion(track);
}

} } // ofx::LineaDeTiempo

