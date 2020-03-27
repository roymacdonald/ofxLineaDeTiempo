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
, BaseHasTimeControl(timeControl, "TrackController")
, BaseViewController<TrackView>()
{
	
}

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
}

void TrackController::destroyView()
{
	if(getView() == nullptr) return;
	destroyChildrenViews(this);
	
	auto view = _getTrackGroupView();
	if(view)
	{
		if(view->removeTrack(this) == false)
		{
			ofLogError("TrackController::destroyView") << "Could not remove track correctly. " << getId();
		}
		
		setView(nullptr);
	}
}



bool TrackController::removeRegion(const std::string& name)
{
	 return _removeRegion(_regionsCollection.at(name));
}

bool TrackController::removeRegion(const size_t& index)
{
	 return _removeRegion(_regionsCollection.at(index));
 }

 RegionController* TrackController::getRegion(const std::string& name)
 {
	 return _regionsCollection.at(name);
 }

 const RegionController* TrackController::getRegion(const std::string& name) const
 {
	 return _regionsCollection.at(name);
 }

 RegionController* TrackController::getRegion(const size_t& index)
 {
	 return _regionsCollection.at(index);
 }

 const RegionController* TrackController::getRegion(const size_t& index)const
 {
	 return _regionsCollection.at(index);
 }

 const std::vector<RegionController*>& TrackController::getRegions()
 {
	return _regionsCollection.getCollection();
 }

 const std::vector<const RegionController*>& TrackController::getRegions() const
 {
	 return _regionsCollection.getCollection();
 }

 size_t TrackController::getNumRegions() const
 {
	 return _regionsCollection.size();
 }



} } // ofx::LineaDeTiempo
