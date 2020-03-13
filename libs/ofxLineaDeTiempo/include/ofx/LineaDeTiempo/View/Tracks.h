//
//  Tracks.h
//
//  Created by Roy Macdonald on 2/18/20.
//

#pragma once
//#include "ofxMUI.h"

#include "DOM/Layout.h"
#include "MUI/BaseClasses.h"
#include "MUI/ClippedView.h"

namespace ofx {
namespace LineaDeTiempo {

class TracksClippedView: public MUI::ClippedView{
public:
	TracksClippedView(const std::string& id, const ofRectangle& rect);
	virtual ~TracksClippedView(){}
	

	virtual void updateLayout() override;
	
	void setZoom(const std::vector<ofRange>& zooms);
	
	void setZoom(int index, const ofRange& zoom);
	
	ofRange getZoom(int index) const;
		
	
	float getTracksWidth() const;
	
protected:

		
	glm::vec2 _minZoom = {
		0.0001, //std::numeric_limits<float>::epsilon(),
		0.0001 //std::numeric_limits<float>::epsilon()
	};

	ofRange _zoom [2];
	
	float _tracksWidth = 0;
	void _updateTracksWidth();
};



class TracksClippedViewLayout: public DOM::Layout
{
public:
    /// If the Orientation::DEFAULT is chosen, the default will be set to
    /// Orientation::HORIZONTAL.
    TracksClippedViewLayout(TracksClippedView* parent);

	virtual ~TracksClippedViewLayout(){}

    virtual void doLayout() override;

protected:

	TracksClippedView* _tracks = nullptr;
};




} } // ofx::LineaDeTiempo
