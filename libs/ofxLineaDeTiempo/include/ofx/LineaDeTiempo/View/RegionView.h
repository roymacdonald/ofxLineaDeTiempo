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
	
	
	RegionView (TrackView* parentTrack, RegionController *controller, std::shared_ptr<MUI::Styles> regionStyles);
	
	virtual ~RegionView() = default;
	
		
	void updateRectFromTimeRange(const ofRange64u& timeRange);
	void updateTimeRangeFromRect();
	virtual void updateLayout() override;

	const TrackView* parentTrack() const;
	TrackView* parentTrack();
	
//	static float headerHeight;
	
	
protected:
	
	ofEventListeners _shapeListeners;

	ofEventListener _timeRangeChangeListener;
	bool bIgnoreTimeRangeChange = false;
	void _timeRangeChanged(ofRange64u& );
	
	
	void moved (DOM::MoveEventArgs&);
	void resized (DOM::ResizeEventArgs&);

	virtual void _onTimeRangeChange()
	{
		
	}// = 0;
	
	RegionController * _controller = nullptr;
	

	MUI::EdgeHandle* _leftHandle = nullptr;
	MUI::EdgeHandle* _rightHandle = nullptr;
	TrackView* _parentTrack = nullptr;
	
	RegionHeaderView* _header = nullptr;
};


} } // ofx::LineaDeTiempo
