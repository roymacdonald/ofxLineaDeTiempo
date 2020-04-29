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
#include "MUI/Label.h"
#include "MUI/ZoomablePanel.h"
#include "LineaDeTiempo/View/TracksClippedView.h"

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
	
	virtual void onUpdate() override;
		
	typedef ofx::MUI::ClippedView_<TrackHeader> HeadersView;
	typedef ofx::MUI::ZoomablePanel<TracksClippedView, MUI::AutoReziseContainer>  TracksView;
	
	void setTracksHeaderWidth(float w);
	
	TracksPanelController* getController();
	const TracksPanelController* getController() const;

	TracksView* getTracksView();
	const TracksView* getTracksView() const;
	
	HeadersView * getHeadersView();
	const HeadersView * getHeadersView() const;

	void useHandles(bool b);
	
//	virtual void onChildrensChange() override;
	
protected:
	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;
	
	
	friend class TracksPanelController;
	
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();
	ofRectangle _makeTimeRulerViewRect();
	
	ofEventListener _viewListener;
	void _viewShapeChanged(DOM::ShapeChangeEventArgs&);
	
	
	
	void _cornerHandleChanged(DOM::ShapeChangeEventArgs&);
	void _headerHandleChanged(DOM::ShapeChangeEventArgs&);

private:

	
	ofEventListener _tracksViewListener;
	void _tracksViewShapeChanged(DOM::ShapeChangeEventArgs&);
	
	TracksPanelController* _controller = nullptr;

	
	TracksView * _tracksView = nullptr;
	
	HeadersView * _headersView = nullptr;

	bool bUsingHandles = false;
	
	MUI::Widget * _cornerHandle = nullptr;
	MUI::Label *  _headerHandle = nullptr;

	ofEventListener _cornerHandleListener;
	ofEventListener _headerHandleListener;
	
	bool _ignoreCornerHandleChange = false;
	bool _ignoreHeaderHandleChange = false;
	
	void _setHeaderHandleShape();
	void _setCornerHandleViewRect();
	
	
	bool _bLayoutNeedsUpdate = true;
	
};
} } // ofx::LineaDeTiempo
