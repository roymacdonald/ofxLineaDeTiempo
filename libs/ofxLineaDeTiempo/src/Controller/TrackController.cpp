//
//  TrackController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Data/KeyframedData.h"
namespace ofx {
namespace LineaDeTiempo {



TrackController::TrackController(const std::string& name, TrackGroupController* parent, TimeControl* timeControl)
: BaseController<TrackView>(name, parent, timeControl)
{
	_timeControlListeners.push(timeControl->playEvent.newListener(this, &TrackController::_findCurrentRegion));
	_timeControlListeners.push(timeControl->stopEvent.newListener(this, &TrackController::_resetCurrentRegion));
		

}


TrackController::~TrackController()
{
	destroyView();
}


void TrackController::_resetCurrentRegion()
{
 _currentRegion = 0;
}


void TrackController::_findRegionAtCurrentTime(const size_t& startIndex)
{
	auto t = getTimeControl()->getCurrentTime();
	auto& regions = _regionsCollection.getCollection();
	for(size_t i =startIndex; i < regions.size(); ++i)
	{
		if(regions[i]->getTimeRange().max > t)
		{
			_currentRegion =i;
			return;
		}
	}
	_currentRegion = regions.size();
}


void TrackController::_findCurrentRegion()
{
	_findRegionAtCurrentTime(0);

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

bool TrackController::removeRegion(RegionController* region)
{
	return CollectionHelper::_remove<RegionController, TrackController>( region, this,  _regionsCollection);
}

TrackGroupView* TrackController::_getTrackGroupView()
{
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p) return p->getView();
	return nullptr;
	
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
	if(_currentRegion < _regionsCollection.size() && _regionsCollection.at(_currentRegion))
	{
		auto r = _regionsCollection.at(_currentRegion);
		if( r->getTimeRange().contains(time) )
		{
			r->update(time);
		}
		else if(r->getTimeRange().max < time)
		{
			_findRegionAtCurrentTime(_currentRegion+1);
			if(_currentRegion < _regionsCollection.size()) update(time);
		}
	}
	else
	{

		_findCurrentRegion();
		if(_currentRegion < _regionsCollection.size()) update(time);
		
	}
}


bool TrackController::removeRegion(const std::string& name)
{
	 return removeRegion(_regionsCollection.at(name));
}

bool TrackController::removeRegion(const size_t& index)
{
	 return removeRegion(_regionsCollection.at(index));
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
const size_t& TrackController::getCurrentRegionIndex()const
{
	return _currentRegion;
}

void TrackController::fromJson(const ofJson& j)
{
	
	_currentRegion = j.value("_currentRegion", 0);

	setId(j["name"]);
	
	
	if(j.count("_regionsCollection")){
		auto r = j["_regionsCollection"];
		if(_regionsCollection.checkJson(r))
		{
			_makeFromJson(r);
		}
	}
}

void TrackController::_makeFromJson(const ofJson& json)
{
	for(auto j: json["elements"])
	{
		if(	j.count("class") > 0 && j.count("name") > 0){
			
			auto clss = j["class"].get<std::string>();
			auto name = j["name"].get<std::string>();
			
			if(clss == "KeyframeRegionController_")
			{
				if(j.count("_dataTypeName")){
					auto dataTypeName = j["_dataTypeName"].get<std::string>();
					RegionController* r = getRegion(name);
					if(r)
					{
						if(dataTypeName == r->getDataTypeName())
						{
							r->fromJson(j);
						}
						else
						{
							ofLogWarning("TrackRegionController::_makeFromJson") << "dataTypeNames differ " << dataTypeName << " != " <<  r->getDataTypeName();
						}
					}
					else
					{
						_addRegionFromJson(name, j);
					}
				}
			}
			else
			{
				ofLogWarning("TrackGroupController::_makeFromJson") << "unknown class:  " << clss;
			}
		}
		else
		{
			ofLogWarning("TrackGroupController::_makeFromJson") << " malformed json. does not have name or class objects";
		}
	}
}




ofJson TrackController::toJson()
{
	ofJson j;
	j["class"] = "TrackController";
	j["name"] = getId();
	j["_currentRegion"] = _currentRegion;
	
	j["_regionsCollection"] =_regionsCollection.toJson();

	j["_dataTypeName"] = _dataTypeName;
	
	return j;
}

} } // ofx::LineaDeTiempo
