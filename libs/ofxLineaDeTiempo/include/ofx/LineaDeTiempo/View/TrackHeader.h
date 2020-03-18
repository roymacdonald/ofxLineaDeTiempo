//
//  TrackHeaderView.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once


#include "ofx/MUI/Widget.h"

namespace ofx {
namespace LineaDeTiempo {

class BaseTrackView;
class TrackGroupView;


class TrackHeader
: public MUI::Widget

{
public:
	TrackHeader(BaseTrackView* track, float width, TrackGroupView* group);
	
	virtual ~TrackHeader(){}
	
	BaseTrackView* getTrack();
	const BaseTrackView* getTrack() const;
	
protected:
	BaseTrackView* _track = nullptr;
	TrackGroupView* _group = nullptr;
	
	
	ofEventListeners _trackListeners;
	
	void _trackMoved(DOM::MoveEventArgs& e);
	void _trackResized(DOM::ResizeEventArgs& e);
	
	void _updateFromTrack();
	
	
};
} } // ofx::LineaDeTiempo
