//
//  KeyframeTrackView.hpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/13/20.
//

#pragma once

#include "LineaDeTiempo/View/TrackView.h"


namespace ofx {
namespace LineaDeTiempo {


template<typename DataType>
class KeyframeTrackController_;

template<typename DataType>
class KeyframeTrackView
: public TrackView
{
public:

	KeyframeTrackView(TrackGroupView* parentGroup, TrackController* controller, TimeRuler * timeRuler , TrackHeader* _headerContainer, bool belongsToPanel );
	virtual ~KeyframeTrackView() = default;
	

	ofParameter<DataType>& getParameter();
	const ofParameter<DataType>& getParameter() const;
	
	
	typedef DataType dataType;
protected:

	
	KeyframeTrackController_<DataType> * _keyframeTrackController = nullptr;
	
	
	
};




} } // ofx::LineaDeTiempo

