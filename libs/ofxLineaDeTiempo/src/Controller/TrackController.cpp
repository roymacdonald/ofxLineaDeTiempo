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
//, BaseHasRegions<RegionController>()
, BaseViewController<TrackView>()
{
	
}

//
//
//template<typename NewRegionControllerType>
//NewRegionControllerType * TrackController::_addRegion( const std::string& regionName, const ofRange64u& timeRange)
//{
//
//	auto uniqueName = _regionsCollection.makeUniqueName(regionName, "Region");
//
//	return BaseController::
//
//	_add < NewRegionControllerType, RegionController >
//
//	( _regionsCollection, uniqueName, timeRange, this);
//
//}

bool TrackController::_removeRegion(RegionController* region)
{
	return BaseController::_remove<RegionController>( region,   _regionsCollection);
}



void TrackController::generateView()
{
	if(_parentGroup && _parentGroup->getView())
	{
		setView(_parentGroup->getView()->addChild<TrackView>(_parentGroup->getView(), this));
	}
}
void TrackController::destroyView()
{
	if(_parentGroup && _parentGroup->getView())
	{
		_parentGroup->getView()->removeChild(_parentGroup->getView());
		setView(nullptr);
	}
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
