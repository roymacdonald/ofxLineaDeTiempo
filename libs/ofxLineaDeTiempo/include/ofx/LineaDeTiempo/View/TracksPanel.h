//
//  TracksPanel.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once


#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/TimeRuler.h"
#include "MUI/Label.h"
#include "MUI/ZoomablePanel.h"
#include "LineaDeTiempo/View/TracksClippedView.h"
#include "LineaDeTiempo/View/TrackHeaderGroup.h"

namespace ofx {
namespace LineaDeTiempo {


class TracksPanelController;
class TrackController;

class TracksPanel
: public TrackGroupView
{
public:
	TracksPanel(const std::string& id, const ofRectangle& rect, DOM::Element* parentView, TracksPanelController* controller);
	
	virtual ~TracksPanel() = default;

	virtual void updateLayout() override;
	
	virtual void onDraw() const override;
	
	virtual void onUpdate() override;
		
	typedef ofx::MUI::ClippedView_<TrackHeaderGroup> HeadersView;
	typedef ofx::MUI::ZoomablePanel<TracksClippedView, MUI::AutoReziseContainer>  TracksView;
	
	void setTracksHeaderWidth(float w);
	
	TracksPanelController* getController();
	const TracksPanelController* getController() const;

	TracksView* getTracksView();
	const TracksView* getTracksView() const;
	
	HeadersView * getHeadersView();
	const HeadersView * getHeadersView() const;
	
    
    
    ///\brief sets the vertical or horizontal scroll and zoom values. Think of it as setting the scroll handles.
    ///Their position is a normalized value between 0 and 1.
    ///when calling setVerticalScrollZoom({0,1}) it will zoom all the way out showing everything.
    /// when both values are equal zoom will be at its maximum.
    /// If the view is not active it will do nothing
    ///\param val. it is made by two float values between 0 and 1. Tip: You can call like setVerticalScrollZoom({0,1});
    ///\returns true if it was able to set the scroll/zoom. Otherwise false
    bool setVerticalScrollZoom(const ofRange& val );
    bool setHorizontalScrollZoom(const ofRange& val );
    
    ///\brief sets the vertical or horizontal scroll and zoom values. Think of it as setting the scroll handles.
    ///Their position is a normalized value between 0 and 1.
    ///when calling setVerticalScrollZoom({0,1}) it will zoom all the way out showing everything.
    /// when both values are equal zoom will be at its maximum.
    /// If the view is not active it will do nothing
    ///\param val. it is made by two float values between 0 and 1. Tip: You can call like setVerticalScrollZoom({0,1});
    ///\param orientation the zoom/scroll value you want. Either ofx::DOM::HORIZONTAL or ofx::DOM::VERTICAL.
    ///\returns true if it was able to set the scroll/zoom. Otherwise false
    bool setScrollZoom(const ofRange& val, DOM::Orientation orientation );
    
    ///\brief gets the vertical or horizontal scroll and zoom values. Think of this values as the position of the scroll handles, in normalized values between 0 and 1.
    ///If there is no view it will return an empty ofRange.
    ///\returns an ofRange with the zoom/scroll values. an ofRange with values min == 0 and max == 1 means that it is zoomed all the way out.
    ofRange  getVerticalScrollZoom();
    ofRange  getHorizontalScrollZoom();
    
    
    ///\brief gets the vertical or horizontal scroll and zoom values. Think of this values as the position of the scroll handles, in normalized values between 0 and 1.
    ///If there is no view it will return an empty ofRange.
    ///\param orientation the zoom/scroll value you want. Either ofx::DOM::HORIZONTAL or ofx::DOM::VERTICAL.
    ///\returns an ofRange with the zoom/scroll values. an ofRange with values min == 0 and max == 1 means that it is zoomed all the way out.
    ofRange  getScrollZoom(DOM::Orientation orientation);
    
    
    
protected:
	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;
	
	
	friend class TracksPanelController;
	
	
	ofRectangle _makeHeadersViewRect();
	ofRectangle _makeTracksViewRect();
	ofRectangle _makeTimeRulerViewRect();
	
	ofEventListener _viewListener;
	void _viewShapeChanged(DOM::ShapeChangeEventArgs&);
	
	virtual void onChildrensChange() override;
	
private:

	
	ofEventListener _tracksViewListener;
	ofEventListener _totalTimeChangedListener;
	
	void _totalTimeChanged();
	
	void _tracksViewShapeChanged(DOM::ShapeChangeEventArgs&);
	
	TracksPanelController* _controller = nullptr;

	
	TracksView * _tracksView = nullptr;
	
	HeadersView * _headersView = nullptr;

	bool _bLayoutNeedsUpdate = true;
	
};
} } // ofx::LineaDeTiempo
