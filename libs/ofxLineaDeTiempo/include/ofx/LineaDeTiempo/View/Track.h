//
//  Track.h
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"

#include "TrackRegion.h"
#include "BaseClasses.h"

#include "TrackHeader.h"
#include "TimeControl.h"
#include <map>

namespace ofx {
namespace LineaDeTiempo {

//class Tracks;

class BaseTrack: public DOM::Element, public BaseHasLayout{
public:
	BaseTrack(const std::string& id, std::shared_ptr<LineaDeTiempo::TimeControl> timeControl );
	virtual ~BaseTrack(){}
	
	static const float initialHeight;
	
	float getHeightFactor();
	void setHeightFactor(float factor);
	
	
	ofRectangle timeRangeToRect(const ofRange64u& t) const;
	float timeToLocalPosition(const uint64_t& t) const;
	
	uint64_t localPositionToTime(float x) const;
	
	float timeToScreenPosition(uint64_t time) const;
	uint64_t  screenPositionToTime(float x) const;
	
	
	void setHeader(TrackHeader* header);
	
	void setColor(const ofColor& color);
	const ofColor& getColor();
	
	static ofColor backgroundColor;
	static ofColor edgeColor;
	
	virtual void onDraw() const override;
	
	std::string getName(){return _trackName;}
	
protected:
	
	TrackHeader* _header;
	
	float _heightFactor = 1;
		
	std::shared_ptr<LineaDeTiempo::TimeControl> _timeControl;
	
	ofColor _color;
	
	shared_ptr<MUI::Styles> _regionsStyle = nullptr;

	std::string _trackName;
	
private:
	
	
};

template<typename RegionType>
class Track_: public BaseTrack{
public:
	static_assert(std::is_base_of<TrackRegion, RegionType>(), "RegionType must be a TrackRegion or derived from TrackRegion.");
	Track_(const std::string& id, std::shared_ptr<LineaDeTiempo::TimeControl> timeControl );
	virtual ~Track_(){}
	
	RegionType* addRegion( const ofRange64u & timeRange);
	RegionType* addRegion(std::string name, const ofRange64u & timeRange);
	
	RegionType* getRegionByIndex(size_t index);
	RegionType* getRegionByName(const std::string& name);
	
	bool removeRegion(RegionType* track);
	bool removeRegionByIndex(size_t index);
	bool removeRegionByName(const std::string& name);
	
	size_t getNumRegions();
	
	const std::vector<RegionType*>& getRegions() const;
	std::vector<RegionType*>& getRegions();
	
	virtual void updateLayout() override;
	
	ofEvent<RegionType*> regionAddedEvent;
	ofEvent<RegionType*> regionRemovedEvent;
	
protected:
	std::vector<RegionType* > _regions;
	std::map<std::string, RegionType* > _regionsNameMap;
	
};



} } // ofx::LineaDeTiempo
