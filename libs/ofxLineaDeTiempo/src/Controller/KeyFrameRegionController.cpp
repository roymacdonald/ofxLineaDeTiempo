//
//  KeyFrameRegionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#include "LineaDeTiempo/Controller/KeyFrameRegionController.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/View/KeyFrames.h"
namespace ofx {
namespace LineaDeTiempo {



KeyFrameRegionController::KeyFrameRegionController(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack)
: RegionController(name, timeRange, parentTrack)
{
	
}
	
void KeyFrameRegionController::generateView()
{
	if(_parentTrack && _parentTrack->getView())
	{
		setView(_parentTrack->getView()->addChild<KeyFrames>(_parentTrack->getView(), this));
	}
}

void KeyFrameRegionController::destroyView()
{
	if(_parentTrack && _parentTrack->getView())
		{
			_parentTrack->getView()->removeChild(_parentTrack->getView());
			setView(nullptr);
		}
}

	


} } // ofx::LineaDeTiempo

