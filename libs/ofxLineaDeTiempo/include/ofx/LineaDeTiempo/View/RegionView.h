//
//  TrackRegionView.h
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"
#include "ofRange.h"
#include "LineaDeTiempo/BaseTypes/BaseHasController.h"
#include "MUI/Widget.h"
#include "MUI/Handles/EdgeHandle.h"
#include "LineaDeTiempo/View/RegionHeaderView.h"
#include "LineaDeTiempo/BaseTypes/BaseHasHeader.h"
namespace ofx {
namespace LineaDeTiempo {

class TrackView;

class RegionController;


class RegionView
: public MUI::Widget
, public BaseHasController<RegionController>
, public BaseHasHeader<RegionHeaderView>

{
public:
	
	
	RegionView (TrackView* parentTrack, RegionController *controller);
	
	virtual ~RegionView() = default;
	
		
	virtual void updateRectFromTimeRange(const ofRange64u& timeRange);
	virtual void updateTimeRangeFromRect();
	virtual void updateLayout() override;

	const TrackView* parentTrack() const;
	TrackView* parentTrack();
	
	static float headerHeight;
	
	using BaseHasController<RegionController>::getController;
	using BaseHasController<RegionController>::setController;
	
	
	
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
	

	MUI::EdgeHandle* _leftHandle = nullptr;
	MUI::EdgeHandle* _rightHandle = nullptr;
	TrackView* _parentTrack = nullptr;
	
	
};


} } // ofx::LineaDeTiempo
