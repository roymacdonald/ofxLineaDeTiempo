//
//  TrackController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/TrackGroupController.h"

namespace ofx {
namespace LineaDeTiempo {



TrackController::TrackController(const std::string& name, TrackGroupController* parent)
	: BaseController(name, parent)
	, _parentGroup(parent)
	, BaseHasRegions<RegionController>()
	, BaseViewController<TrackView>()
{
	
}
	
	
	
	template<typename NewRegionControllerType>
	NewRegionControllerType * TrackController::addRegion( const std::string& regionName, const ofRange64u& timeRange)
	{
		
		auto uniqueName = _regionsCollection.makeUniqueName(regionName, "Region");
		
		return BaseController::_add
		<
		NewRegionControllerType
//		,NewRegionViewType
		,RegionController
		>
		( _regionsCollection, uniqueName, timeRange, this);
		
		
	}
	
	bool TrackController::removeRegion(RegionController* region)
	{
		
		
		return BaseController::_remove<RegionController>( region,   _regionsCollection);
		
	}
	
	
	
	TrackGroupController * TrackController::parentGroup()
	{
		return _parentGroup;
	}
	
	const TrackGroupController * TrackController::parentGroup() const
	{
		return _parentGroup;
	}
	


} } // ofx::LineaDeTiempo
