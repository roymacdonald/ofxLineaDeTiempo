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



TrackController::TrackController(const std::string& name, TrackGroupController* parent, TimeControl* timeControl)
: DOM::Node(name, parent)
//, _parentGroup(parent)
, BaseHasTimeControl(timeControl, "TrackController")
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
//ofEventListener _timeChangedListener;
//bool _bListeningTimeChange = false;

void TrackController::enableTimeUpdate()
{
	if(!_bListeningTimeChange)
	{
		_timeChangedListener = getTimeControl()->currentTimeUpdateEvent.newListener(this, &TrackController::update);
		_bListeningTimeChange = true;
	}
}

void TrackController::disableTimeUpdate()
{
	if(_bListeningTimeChange)
	{
		_bListeningTimeChange = false;
		_timeChangedListener.unsubscribe();
	}
}

bool TrackController::isUpdatingTime()
{
	return _bListeningTimeChange;
}

bool TrackController::_removeRegion(RegionController* region)
{
	return CollectionHelper::_remove<RegionController, TrackController>( region, this,  _regionsCollection);
}

TrackGroupView* TrackController::_getTrackGroupView()
{
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p) return p->getView();
	return nullptr;
	
}

void TrackController::generateView()
{
	_generateView<TrackView>();
//	if(getView()) return;
//	auto p = dynamic_cast<TrackGroupController*>(parent());
//	if(p && p->getView())
//	{
//
//		setView(p->getView()->addTrack<TrackView>(this));
//
//	}
//
//	generateChildrenViews(this);
}
void TrackController::destroyView()
{
	if(getView() == nullptr) return;
	destroyChildrenViews(this);
	
//	auto p = dynamic_cast<TrackGroupController*>(parent());
	auto view = _getTrackGroupView();
	if(view)
//	if(p && p->getView())
	{
		
		if(view->removeTrack(this) == false)
		{
			ofLogError("TrackController::destroyView") << "Could not remove track correctly. " << getId();
		}
		
		setView(nullptr);
	}
	
}



} } // ofx::LineaDeTiempo
