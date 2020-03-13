//
//  Track.h
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"

#include "TrackRegion.h"
#include "BaseClasses.h"


#include "TimeControl.h"
#include <map>
#include "LineaDeTiempo/BaseTypes/AbstractHasRegions.h"
#include "LineaDeTiempo/BaseTypes/BaseHasController.h"

namespace ofx {
namespace LineaDeTiempo {

class TrackController;
class TrackHeader;



class BaseTrack
:public DOM::Element
,public BaseHasLayout
,public AbstractHasRegions<TrackRegion, false_type>
,public BaseHasController<TrackController>
{
public:
	BaseTrack(const std::string& id , const std::string& viewTypeName, TrackController* controller );
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
	
	TrackHeader* getHeader();
	const TrackHeader* getHeader() const;
	
	
	void setColor(const ofColor& color);
	const ofColor& getColor();
	
	static ofColor backgroundColor;
	static ofColor edgeColor;
	
	virtual void onDraw() const override;
	
	std::string getName(){return _trackName;}
	
	const std::string&  getViewTypeName() { return _viewTypeName;}
	
	
	
	template<typename RegionType>
	RegionType* addRegion( const ofRange64u & timeRange, TrackRegionController * controller);
	
	template<typename RegionType>
	RegionType* addRegion(std::string name, const ofRange64u & timeRange, TrackRegionController * controller);
		
	bool removeRegion(TrackRegion* track) override;

	
	
	
	
protected:
	
	std::string _viewTypeName = "";
	
	TrackHeader* _header;
	
	float _heightFactor = 1;
		
	
	ofColor _color;
	
	shared_ptr<MUI::Styles> _regionsStyle = nullptr;

	std::string _trackName;
	
private:
	
	
};

template<typename RegionType>
class Track_
: public BaseTrack

{
public:
	static_assert(std::is_base_of<TrackRegion, RegionType>(), "RegionType must be a TrackRegion or derived from TrackRegion.");
	Track_(const std::string& id , TrackController* controller);
	virtual ~Track_(){}
	
	
	virtual void updateLayout() override;
	

	
	
	
	
protected:
//	std::vector<RegionType* > _regions;
//	std::map<std::string, RegionType* > _regionsNameMap;
	
};


//struct TrackAndHeader{
//
//	TrackAndHeader(TrackHeader* _header, BaseTrack* _track):
//	header(_header),
//	track(_track)
//	{
//		
//	}
//				   
//	TrackHeader* header = nullptr;
//	BaseTrack* track = nullptr;
//	
//};



} } // ofx::LineaDeTiempo
