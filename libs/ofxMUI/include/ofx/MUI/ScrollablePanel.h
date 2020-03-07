//
//  ScrollablePanel.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/5/20.
//

#pragma once

//#include "ofxMUI.h"
#include "Scrollbar.h"
#include "ClippedView.h"
#include "ScaledView.h"
#include "Tracks.h"
#include "Constants.h"
#include "Margins.h"
namespace ofx {
namespace MUI {



template<typename HandleType, typename ScrollerData,  template <typename, typename> class ScrollBarType, typename ClippedViewType, typename ClippedContainerType>
class ScrollablePanel_: public Widget
{
public:

	ScrollablePanel_(const std::string& id, const ofRectangle& rect);
	
	virtual ~ScrollablePanel_(){}

	bool isScrollbarActive(DOM::Orientation scrollbarOrientation);
	float getScrollbarSize(DOM::Orientation scrollbarOrientation);
	
	ClippedViewType* getClippingView();
	
	ClippedContainerType*  getContainer();
	void updateLayout();
	
	
	
	void setForceShowScrollbars(bool show);
	bool isForceShowScrollbars();
	
	void setScrollH(ScrollerData d);
	void setScrollV(ScrollerData d);
	
	void setVScrollMargin(float top, float bottom);
	void setHScrollMargin(float left, float right);
	
	const Margins& getScrollMargins();
	
	
	///\brief sets the margins back to zero
	void resetScrollbarMargins();

	void updateContainerLayout();
	
protected:
	
	ClippedViewType* _clippingPanel = nullptr;
	
	Margins _scrollMargins;
	
	
	bool _forceShowScrollbars = false;
	
	void _updateScrollbar(ScrollBarType<HandleType, ScrollerData> * scrollbar);
	
	void _scrollVChanged(ScrollerData& s);
	void _scrollHChanged(ScrollerData& s);
		
	
	
public:
	std::vector<ScrollerData> _scrollData;
	
	ScrollBarType<HandleType, ScrollerData> * _scrollbarH = nullptr;
	ScrollBarType<HandleType, ScrollerData> * _scrollbarV = nullptr;
protected:
	
	ofEventListeners _scrollListeners;
	
	bool _onMouseScrollEvent(ofMouseEventArgs & e);

private:

};
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
template<typename PanelType>
class ScrollablePanelLayout: public DOM::Layout
{
public:
    ScrollablePanelLayout(PanelType* parent);

	virtual ~ScrollablePanelLayout(){}

    virtual void doLayout() override;
	
protected:
	PanelType* parentPanel;
};

typedef ScrollablePanel_<ScrollHandle, float, Scrollbar_, ClippedView, DOM::Element> ScrollablePanel;
typedef ScrollablePanel_<ZoomHandle, ofRange, Scrollbar_, ScaledView, ScaledContainer> ScalablePanel;
typedef ScrollablePanel_<ZoomHandle, ofRange, Scrollbar_, LineaDeTiempo::TracksClippedView, DOM::Element> TracksScrollPanel;
//typedef ScrollablePanel_<ZoomHandle, ofRange, Scrollbar_, TracksClippedView, ZoomableContainer> ZoomablePanel;

} } // ofx::MUI



