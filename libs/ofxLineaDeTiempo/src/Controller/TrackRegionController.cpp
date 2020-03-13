//
//  TrackRegionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "TrackRegionController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

namespace ofx {
namespace LineaDeTiempo {



TrackRegionController::TrackRegionController(const std::string& name, TrackController * parent):
BaseViewController<TrackRegion>(),
BaseHasParent<TrackController>(parent),
BaseHasName(name)
{
	
}
		


} } // ofx::LineaDeTiempo
