//
//  TrackHeaderView.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once


//#include "ofx/MUI/Widget.h"
#include "ofx/DOM/Element.h"
#include "ofx/MUI/Handles/EdgeHandle.h"

namespace ofx {
namespace LineaDeTiempo {

class BaseTrackView;
class TrackGroupView;


class TrackHeader
: public DOM::Element

{
public:

	TrackHeader(const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group, bool belongsToPanel);
	
	virtual ~TrackHeader(){}
	
	BaseTrackView* getTrack();
	const BaseTrackView* getTrack() const;
	
	virtual void onDraw() const override;
	
	bool isGroupHeader() const;
protected:
	BaseTrackView* _track = nullptr;
	TrackGroupView* _group = nullptr;
	
	
	ofEventListener _trackListener;
	ofEventListener _edgeHandleListener;
	
	
	void _updateShape();
	
	void _onEdgeHandleChange(DOM::ShapeChangeEventArgs& );
	
	void _trackShapeChanged(DOM::ShapeChangeEventArgs& e);
//	void _trackMoved(DOM::MoveEventArgs& e);
//	void _trackResized(DOM::ResizeEventArgs& e);
	
//	void _updateFromTrack();
	
	bool _bGroupHeader = false;
	
	bool _belongsToPanel = false;
	
	
	MUI::EdgeHandle* _edgeHandle = nullptr;
	
};
} } // ofx::LineaDeTiempo
