//
//  TrackController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/TracksController.h"

namespace ofx {
namespace LineaDeTiempo {


BaseTrackController::BaseTrackController(const std::string& name, const std::string& trackViewTypeName, TracksController* parent)
:BaseHasParent<TracksController>(parent)
,BaseViewController<BaseTrack>()
,BaseHasName(name)
{
	
}


//template<typename RegionViewType, typename RegionControllerType>
TrackController::TrackController(const std::string& name, const std::string& trackViewTypeName, TracksController* parent)
:BaseTrackController(name, trackViewTypeName, parent)
,AbstractHasRegions<TrackRegionController, std::true_type>()
{
	
}

//template<typename RegionViewType, typename RegionControllerType>
//TrackController_<RegionViewType, RegionControllerType>::~TrackController_()
//{
//	
//}



} } // ofx::LineaDeTiempo
