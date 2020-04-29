//
//  TracksClippedView.h
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"


#include "MUI/ClippedView.h"

namespace ofx {

namespace LineaDeTiempo {



class TracksClippedView
: public MUI::ClippedView

{
public:

	
	
	TracksClippedView(const std::string& id, const ofRectangle& rect);
	virtual ~TracksClippedView(){}
	
	virtual void setZoom(DOM::Orientation orientation, const ofRange& zoom) override;

	float getTracksWidth() const;
	
	ofRange containerHeightToZoom();
	ofRange containerWidthToZoom();

protected:
	
	void updateTracksWidth();
	
	void updateVerticalLayout();
		


//	float _zoomToScale(const ofRange& zoom);
	
	
	
//	float _tracksWidth = 0;
	float _unscaledHeight = 0;
	
	void _updateTracksUnscaledHeight();
	
	float _getZoomableHeight();

	
//	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& e) override;
//	void _onTrackAdded(DOM::ElementEventArgs&);
//	void _onTrackRemoved(DOM::ElementEventArgs&);

	
//	void _updateVZoombar();
//	void _updateHZoombar();

	size_t _numGroups = 0;

//	bool _bIgnoreScrollbar = false;
	
};




} } // ofx::LineaDeTiempo
