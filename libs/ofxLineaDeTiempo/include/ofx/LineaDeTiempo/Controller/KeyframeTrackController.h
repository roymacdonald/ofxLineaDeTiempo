//
//  KeyFrameTrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once

#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/KeyFrameRegionController.h"


namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TrackGroupController;


class KeyFrameTrackController
: public TrackController
{
public:
		
	KeyFrameTrackController(const std::string& name, TrackGroupController* parent, TimeControl* timeControl);
	
	virtual ~KeyFrameTrackController() = default;
	
	KeyFrameRegionController * addRegion( const std::string& regionName, const ofRange64u& timeRange);
	
	bool removeRegion(KeyFrameRegionController* track);
	
	
protected:
	
	
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
