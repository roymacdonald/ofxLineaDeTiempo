////
////  RegionController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/6/20.
////
//
#pragma once

#include "LineaDeTiempo/Controller/BaseController.h"

#include "LineaDeTiempo/View/RegionView.h"
#include "ofRange.h"

#include <type_traits>
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"

namespace ofx {
namespace LineaDeTiempo {


class TrackController;


class RegionController
: public BaseController<RegionView>
, public AbstractSerializable
{
public:

	RegionController(const std::string& name, TrackController* parentTrack, TimeControl* timeControl);
	
	RegionController(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl);
	
	virtual ~RegionController() = default;
	
	const ofRange64u& getTimeRange() const;
	
	void setTimeRange(const ofRange64u& t, bool updateView = true);
	
	TrackController * getParentTrack();
	
	const TrackController * getParentTrack() const;
	
	ofEvent<ofRange64u> timeRangeChangedEvent;

	
	virtual void update(uint64_t& t) = 0;
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	const std::string&  getDataTypeName() const;
					
protected:
		
	

	TrackController * _parentTrack;

private:
	ofRange64u _timeRange;
	
};


} } // ofx::LineaDeTiempo
