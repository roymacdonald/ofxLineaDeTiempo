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
: DOM::Node(name, parent)
//, _parentGroup(parent)
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
	return CollectionHelper::_remove<RegionController, TrackController>( region, this,  _regionsCollection);
}

void TrackController::generateView()
{
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		setView(p->getView()->template addChild<TrackView>(p->getView(), this));
	}
	for(auto child : children())
	{
		auto c = dynamic_cast<BaseHasViews*>(child);
		if(c) c->generateView();
	}
}
void TrackController::destroyView()
{
	for(auto child : children())
	{
		auto c = dynamic_cast<BaseHasViews*>(child);
		if(c) c->destroyView();
	}
	
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		p->getView()->removeChild(getView());
		setView(nullptr);
	}
}



//TrackGroupController * TrackController::parentGroup()
//{
//	return _parentGroup;
//}
//
//const TrackGroupController * TrackController::parentGroup() const
//{
//	return _parentGroup;
//}



} } // ofx::LineaDeTiempo
