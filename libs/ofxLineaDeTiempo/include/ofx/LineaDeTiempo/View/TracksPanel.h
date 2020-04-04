//
//  TracksPanel.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once
#include "MUI/ScrollablePanel.h"



#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/TimeRuler.h"

namespace ofx {
namespace LineaDeTiempo {



class TracksPanelController;
class TrackController;

class TracksPanel
: public TrackGroupView



{
public:
	TracksPanel(const std::string& id, DOM::Element* parentView, const ofRectangle& rect, TracksPanelController* controller);
	
	virtual ~TracksPanel() = default;


	virtual void updateLayout() override;
	
	virtual void onDraw() const override;
	
	float timeToScreenPosition(uint64_t time) const;
	uint64_t  screenPositionToTime(float x) const;
	
	
	TracksClippedView* getClippingView();
	const TracksClippedView* getClippingView()const;
	
	DOM::Element* getContainer();
	const DOM::Element* getContainer() const;
	
	
	virtual void _updateContainers() override;
	
	shared_ptr<MUI::Styles> getRegionsStyle();
	
	
	void setTracksHeaderWidth(float w);
	
	TimeRuler * _timeRuler = nullptr;
	
protected:
	friend class TracksPanelController;
	
	void _setup();
	
	MUI::TracksScrollPanel* tracksView;
	MUI::ClippedView_<TrackHeader> * headersView;

	ofEventListeners _tracksContainerListeners;
	
	
	void _updateHeadersFromTracks();

	
	void _tracksMoved(DOM::MoveEventArgs& e);
	void _tracksResized(DOM::ResizeEventArgs& e);
	
	
	shared_ptr<MUI::Styles> _regionsStyle = nullptr;
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();

	ofEventListener _parentListener;
	void _parentViewResized(DOM::ResizeEventArgs&);
	
private:
	
	
	
	
};
} } // ofx::LineaDeTiempo
