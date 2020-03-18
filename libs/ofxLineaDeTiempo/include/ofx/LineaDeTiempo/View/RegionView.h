//
//  TrackRegionView.h
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"
#include "ofRange.h"
#include "ResizableHandle.h"
#include "LineaDeTiempo/BaseTypes/BaseHasController.h"
#include "MUI/Widget.h"

namespace ofx {
namespace LineaDeTiempo {

class TrackView;

class RegionController;


class RegionView
: public MUI::Widget
, public BaseHasController<RegionController>

{
public:
	
	
	RegionView (TrackView* parentTrack, RegionController *controller);
	
	virtual ~RegionView() = default;
	
		
	virtual void updateRectFromTimeRange(const ofRange64u& timeRange);
	virtual void updateLayout() override;

	const TrackView* parentTrack() const;
	TrackView* parentTrack();
	
	static float headerHeight;
	
	using BaseHasController<RegionController>::getController;
	using BaseHasController<RegionController>::setController;
	
	
	
protected:
	
	
	TrackView* _parentTrack = nullptr;
	
	
};


} } // ofx::LineaDeTiempo
