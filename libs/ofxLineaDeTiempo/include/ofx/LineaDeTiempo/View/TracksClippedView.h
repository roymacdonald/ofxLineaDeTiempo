//
//  TracksClippedView.h
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"


#include "MUI/ClippedView.h"
#include "MUI/ZoomScrollbar.h"
#include "ofRange.h"

namespace ofx {

namespace LineaDeTiempo {



class TracksClippedView
: public MUI::ClippedView

{
public:
	
	TracksClippedView(const std::string& id, const ofRectangle& rect);
	virtual ~TracksClippedView(){}
	

	float getTracksWidth() const;
	
	
	virtual void updateLayout() override;
	
	void setScrollbars(MUI::ZoomScrollbar* zoomScrollbarH, MUI::ZoomScrollbar* zoomScrollbarV);
	
	
protected:
	
	void updateTracksWidth();
	
	void updateVerticalLayout();
		

	MUI::ZoomScrollbar* _zoomScrollbarH = nullptr;
	MUI::ZoomScrollbar* _zoomScrollbarV = nullptr;
	
	
	void zoomChangedH(ofRange&);
	void zoomChangedV(ofRange&);
	

	void _containerHeightToZoom();
	void _containerWidthToZoom();


	

	float _unscaledHeight = 0;
	
	void _updateTracksUnscaledHeight();
	
	float _getZoomableHeight();
//
//	size_t _numGroups = 0;


	ofEventListener _containerShapeListener;
	
	void _onContainerShapeChange(DOM::ShapeChangeEventArgs& e);
	
	enum UpdateState
	{
		UPDATE_STATE_NONE = 0,
		CONTAINER_SHAPE_CHANGE,
		SCROLLBAR_CHANGED
	}
	updateState = UPDATE_STATE_NONE;
	
	
	ofEventListeners zoomListeners;
	
};




} } // ofx::LineaDeTiempo
