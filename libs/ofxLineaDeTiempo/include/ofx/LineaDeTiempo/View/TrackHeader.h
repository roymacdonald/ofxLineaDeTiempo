//
//  TrackHeader.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once

//#include "BaseClasses.h"
#include "ofx/MUI/Widget.h"

namespace ofx {
namespace LineaDeTiempo {

class BaseTrack;
class TracksPanel;
class TrackHeader: public MUI::Widget{//}, public BaseHasLayout{
public:
	TrackHeader(BaseTrack* track, float width, TracksPanel* panel);
	
	virtual ~TrackHeader(){}
	
	BaseTrack* getTrack();
	const BaseTrack* getTrack() const;
	
protected:
	BaseTrack* _track = nullptr;
	TracksPanel* _panel = nullptr;
	
	
	ofEventListeners _trackListeners;
	
	void _trackMoved(DOM::MoveEventArgs& e);
	void _trackResized(DOM::ResizeEventArgs& e);
	
	void _updateFromTrack();
	
	
};
} } // ofx::LineaDeTiempo
