//
//  KeyFrameRegionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#include "LineaDeTiempo/Controller/KeyFrameRegionController.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"
namespace ofx {
namespace LineaDeTiempo {



KeyFrameRegionController::KeyFrameRegionController(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl)
: RegionController(name, timeRange, parentTrack, timeControl)
{
	
}



void KeyFrameRegionController::generateView()
{
	if(getView() == nullptr){
	auto p = dynamic_cast<TrackController*>(parent());
	if(p && p->getView())
	{
		
		setView(p->getView()->addRegion<KeyframesRegionView>(this));
			
	}

	generateChildrenViews(this);
	}
}
void KeyFrameRegionController::destroyView()
{
	if(getView()){
	destroyChildrenViews(this);
	
	auto p = dynamic_cast<TrackController*>(parent());
	if(p && p->getView())
	{
		
		if(p->getView()->removeRegion(this) == false)
		{
			ofLogError("KeyFrameRegionController::destroyView") << "Could not remove track correctly. " << getId();
		}
		
		setView(nullptr);
	}
	}
}




} } // ofx::LineaDeTiempo

