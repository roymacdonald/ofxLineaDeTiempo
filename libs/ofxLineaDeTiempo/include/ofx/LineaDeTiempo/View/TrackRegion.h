//
//  TrackRegion.h
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"
#include "ofRange.h"
#include "ResizableHandle.h"
#include "BaseClasses.h"

namespace ofx {
namespace LineaDeTiempo {

class BaseTrack;

class TrackRegion: public MUI::Widget, public BaseHasLayout{
public:
	
	TrackRegion(const std::string& id, BaseTrack* parentTrack, const ofRange64u & timeRange);
	
	virtual ~TrackRegion(){}
	
	
	const ofRange64u& getTimeRange();
	
	void setTimeRange(const ofRange64u& t);
	
	ofEvent<ofRange64u> timeRangeChangedEvent;
	
	virtual void updateRectFromTimeRange();
	virtual void updateLayout() override;

	const BaseTrack* parentTrack();
	
	static float headerHeight;
	
protected:
	
	ofRange64u _timeRange;
	BaseTrack* _parentTrack = nullptr;
	
	
};


} } // ofx::LineaDeTiempo
