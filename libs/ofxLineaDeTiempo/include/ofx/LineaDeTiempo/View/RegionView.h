//
//  TrackRegionView.h
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"
#include "ofRange.h"
#include "MUI/Widget.h"
#include "MUI/Handles/EdgeHandle.h"
#include "LineaDeTiempo/View/RegionHeaderView.h"
#include <memory>

namespace ofx {
namespace LineaDeTiempo {

class TrackView;

class RegionController;


class RegionView
: public MUI::Widget
{
public:
	
	
	RegionView (TrackView* parentTrack, RegionController *controller, std::shared_ptr<MUI::Styles> headerStyles);
	
	virtual ~RegionView() = default;
	
	void updateRectFromTimeRange();
	void updateRectFromTimeRange(const ofRange64u& timeRange);
	void updateTimeRangeFromRect();


	const TrackView* parentTrack() const;
	TrackView* parentTrack();
	
	
	ofEvent<ofRange64u> timeRangeChangedEvent;
	
	
	void moveRegionX(float x);
	
	bool isBeingMoved() const;
	
protected:
	
	


	bool bIgnoreTimeRangeChange = false;
	bool bIgnoreShapeChange = false;

	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs&) override;

	
	RegionController * _controller = nullptr;
	

	MUI::EdgeHandle* _leftHandle = nullptr;
	MUI::EdgeHandle* _rightHandle = nullptr;
	
	TrackView* _parentTrack = nullptr;
	
	RegionHeaderView* _header = nullptr;
	
private:
	bool bIsMoving = false;
};


} } // ofx::LineaDeTiempo
