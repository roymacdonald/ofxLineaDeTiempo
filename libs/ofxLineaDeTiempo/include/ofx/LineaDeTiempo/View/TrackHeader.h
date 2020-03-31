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
//	TrackHeader(const std::string& id, const ofRectangle& rect);
	TrackHeader(const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group);
	
	virtual ~TrackHeader(){}
	
	BaseTrackView* getTrack();
	const BaseTrackView* getTrack() const;
	
	virtual void onDraw() const;
protected:
	BaseTrackView* _track = nullptr;
	TrackGroupView* _group = nullptr;
	
	
	ofEventListeners _trackListeners;
	
	void _trackMoved(DOM::MoveEventArgs& e);
	void _trackResized(DOM::ResizeEventArgs& e);
	
	void _updateFromTrack();
	
	
};
} } // ofx::LineaDeTiempo
