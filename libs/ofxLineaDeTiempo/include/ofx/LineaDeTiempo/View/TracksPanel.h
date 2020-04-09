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
#include "MUI/MUI.h"

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
		
	typedef ofx::MUI::ClippedView_<TrackHeader> HeadersView;
	typedef ofx::MUI::TracksScrollPanel TracksView;
	
//	virtual void _updateContainers() override;
	
	void setTracksHeaderWidth(float w);
	
	
	shared_ptr<ofx::MUI::Styles> getRegionsStyle();
	const shared_ptr<ofx::MUI::Styles> getRegionsStyle() const;
	
	TracksPanelController* getController();
	const TracksPanelController* getController() const;

	TracksView* getTracksView();
	const TracksView* getTracksView() const;
	
	HeadersView * getHeadersView();
	const HeadersView * getHeadersView() const;

	
	
protected:
	
	friend class TracksPanelController;
	
	void _setup();
	
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();
	ofRectangle _makeTimeRulerViewRect();
	
	ofEventListener _viewListener;
	void _viewShapeChanged(DOM::ShapeChangeEventArgs&);
	
private:

	
	ofEventListener _tracksViewListener;
	void _tracksViewShapeChanged(DOM::ShapeChangeEventArgs&);
	
	TracksPanelController* _controller = nullptr;

//	TimeRuler * _timeRuler = nullptr;
	
	TracksView * _tracksView = nullptr;
	
	HeadersView * _headersView = nullptr;

	shared_ptr<ofx::MUI::Styles> _regionsStyle = nullptr;
	
	
};
} } // ofx::LineaDeTiempo
