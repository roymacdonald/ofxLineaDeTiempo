//
//  RegionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

namespace ofx {
namespace LineaDeTiempo {

RegionController::RegionController(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl)
:BaseController<RegionView>(name, parentTrack, timeControl)
{
	setTimeRange(timeRange);
}
		


const ofRange64u& RegionController::getTimeRange() const
 {
 	return _timeRange;
 }



void RegionController::_registerViewTimeRangeEvent()
{
	if(getView())
	{
		_keyframesViewTimeRangeChangeListener = getView()->timeRangeChangedEvent.newListener(this, &RegionController::_onViewTimeRangeChange);
	}
}


void RegionController::_unregisterViewTimeRangeEvent()
{
	_keyframesViewTimeRangeChangeListener.unsubscribe();
}


void RegionController::_onViewTimeRangeChange(ofRange64u& t)
{
	this->setTimeRange(t, false);
}



void RegionController::setTimeRange(const ofRange64u& t, bool updateView )
{
 	if(_timeRange != t){
 		_timeRange = t;
		if(updateView && getView())
		{
			getView()->updateRectFromTimeRange(_timeRange);
		}
 		ofNotifyEvent(timeRangeChangedEvent, _timeRange, this);
 	}
 }

TrackController * RegionController::getParentTrack()
{
	return _parentTrack;
}

const TrackController * RegionController::getParentTrack() const
{
	return _parentTrack;
}
				
	
	

void RegionController::fromJson(const ofJson& j)
{
	
	setId(j["name"]);
	
	try{
		ofRange64u t;
		j["_timeRange"]["min"].get_to(t.min);
		j["_timeRange"]["max"].get_to(t.max);
		setTimeRange(t, true);
	}
	catch (ofJson::out_of_range& e)
	{
			// output exception information
		std::cout << "message: " << e.what() << '\n'
					  << "exception id: " << e.id << std::endl;
	}
}

ofJson RegionController::toJson()
{
	ofJson j;
	j["class"] = "RegionController";
	j["name"] = getId();
	j["_dataTypeName"] = _dataTypeName;
//	j["view"] = bool(getView());
	j["_timeRange"]["min"] = _timeRange.min;
	j["_timeRange"]["max"] = _timeRange.max;


	return j;
}





} } // ofx::LineaDeTiempo
