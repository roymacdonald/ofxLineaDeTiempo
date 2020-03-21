//
//  KeyFrameRegionController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once
#include "LineaDeTiempo/Controller/RegionController.h"

namespace ofx {
namespace LineaDeTiempo {


class TrackController;


class KeyFrameRegionController
: public RegionController


{
public:

	KeyFrameRegionController(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl);
	
	virtual ~KeyFrameRegionController() = default;
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	
	
protected:

private:
	
	
};


} } // ofx::LineaDeTiempo
