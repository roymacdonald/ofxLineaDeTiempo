//
//  TracksClippedView.h
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"

#include "DOM/Layout.h"
#include "MUI/ClippedView.h"

namespace ofx {
namespace LineaDeTiempo {

class TracksClippedView
: public MUI::ClippedView

{
public:

	TracksClippedView(const std::string& id, const ofRectangle& rect);
	virtual ~TracksClippedView(){}
	

	
	
//	void setZoom(const std::vector<ofRange>& zooms);
	
	void setZoom(DOM::Orientation orientation, const ofRange& zoom);
	
	void setZoomV(ofRange& v);
	void setZoomH(ofRange& v);
	
	
	ofRange getZoom(DOM::Orientation orientation) const;
		
	
	float getTracksWidth() const;
	
	
	ofRange getVerticalZoomFromContainerHeight();
	
	
protected:


	
		
	glm::vec2 _minZoom = {
		0.0001, //std::numeric_limits<float>::epsilon(),
		0.0001 //std::numeric_limits<float>::epsilon()
	};

	ofRange _zoom [2];
	
	float _tracksWidth = 0;
	void _updateTracksWidth();
	
	void _updateVerticalLayout();
	
	float _unscaledHeight = 0;
	void _updateTracksUnscaledHeight();
	
	
	ofEventListeners _listeners;
	
	void _onResize(DOM::ShapeChangeEventArgs& e);
	void _onTrackAdded(DOM::ElementEventArgs&);
	void _onTrackRemoved(DOM::ElementEventArgs&);
	

	size_t _numGroups = 0;
	
};




} } // ofx::LineaDeTiempo
