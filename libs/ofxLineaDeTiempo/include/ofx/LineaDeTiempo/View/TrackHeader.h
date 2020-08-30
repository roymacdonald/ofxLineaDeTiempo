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
#include "ofx/MUI/Follower.h"

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
	
	TrackGroupView* getTrackGroup();
	const TrackGroupView* getTrackGroup() const;
	
	virtual void onDraw() const override;
	
	bool isGroupHeader() const;
	
	MUI::Follower* getFollower();
protected:
	BaseTrackView* _track = nullptr;
	TrackGroupView* _group = nullptr;
	
	
	ofEventListener _edgeHandleListener;
	
	bool _bGroupHeader = false;
	
	bool _belongsToPanel = false;
	
	
	MUI::EdgeHandle* _edgeHandle = nullptr;
	
	virtual float _getMinHeight();

	std::unique_ptr<MUI::Follower> _follower = nullptr;
	
};
} } // ofx::LineaDeTiempo
