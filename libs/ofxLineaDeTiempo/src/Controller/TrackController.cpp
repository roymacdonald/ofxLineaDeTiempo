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
	_timeControlListeners.push(timeControl->playEvent.newListener(this, &TrackController::_findCurrentRegion));
	_timeControlListeners.push(timeControl->stopEvent.newListener(this, &TrackController::_resetCurrentRegion));
		

}




void TrackController::_resetCurrentRegion()
{
 _currentRegion = 0;
}


void TrackController::_findNextRegion(const size_t& startIndex)
{
//	std::cout << "TrackController::_findNextRegion " << startIndex <<"\n";
	auto t = getTimeControl()->getCurrentTime();
	auto regions = _regionsCollection.getCollection();
	for(size_t i =startIndex; i < regions.size(); i++)
	{
		if(regions[i]->getTimeRange().min >= t)
		{
			_currentRegion =i;
			return;
		}
	}
	_currentRegion = regions.size();
}


void TrackController::_findCurrentRegion()
{
	_findNextRegion(0);

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

void TrackController::update(uint64_t& time)
{
//	std::cout << _regionsCollection.size() << " , " << std::boolalpha << (bool)(_regionsCollection.at(_currentRegion)) << "\n" ;
	if(_currentRegion < _regionsCollection.size() && _regionsCollection.at(_currentRegion))
	{
//		std::cout << "1";
		auto r = _regionsCollection.at(_currentRegion);
		if( r->getTimeRange().contains(time) )
		{
			r->update(time);
		}
		else if(r->getTimeRange().max < time)
		{
			_findNextRegion(_currentRegion+1);
			update(time);
		}
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
const size_t& TrackController::getCurrentRegion()const
{
	return _currentRegion;
}


} } // ofx::LineaDeTiempo
