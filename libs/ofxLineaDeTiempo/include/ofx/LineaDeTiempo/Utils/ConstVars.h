//
//  Constants.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/31/20.
//

#pragma once
#include "ofColor.h"
#include "ofParameter.h"
#include "MUI/Styles.h"
namespace ofx {
namespace LineaDeTiempo {

struct ConstVars
{
	
	
	static ofParameter<ofColor> PanelBackgroundColor;
	static ofParameter<ofColor> DefaultTextColor      ;//= {"DefaultTextColor", ofColor(220), ofColor::black, ofColor::white};
	static ofParameter<ofColor> TrackBackgroundColor  ;//= {"TrackBackgroundColor", ofColor(40), ofColor::black, ofColor::white};
	static ofParameter<ofColor> TrackEdgeColor        ;//= {"TrackEdgeColor", ofColor(120), ofColor::black, ofColor::white};
	static ofParameter<ofColor> RegionBackgroundColor ;//= {"RegionBackgroundColor", ofColor(80), ofColor::black, ofColor::white};

	static ofColor SelectedColor;
	
	static ofParameter<float> TrackInitialHeight      ;//= {"TrackInitialHeight", 150.0, 0.f, 400.f};
	static ofParameter<float> DefaultKeyframeSize     ;//= {"DefaultKeyframeSize", 5.0, 0.f, 20.f};
	static ofParameter<float> ViewTopHeaderHeight     ;//= {"ViewTopHeaderHeight", 18.f, 0.f, 50.f};
	static ofParameter<float> HeaderViewIndent        ;//= {"HeaderViewIndent", 4.f, 0.f, 10.f};
	static ofParameter<float> TimeRulerInitialHeight  ;//= {"TimeRulerInitialHeight", 30.f, 0.f, 100.f};
	static ofParameter<float> PlayheadTriangleSize    ;//= {"PlayheadTriangleSize", 15.f, 0.f, 150.f};
	static ofParameter<float> PlayheadWidth           ;//= {"PlayheadWidth", 3.f, 0.f, 10.f};
	
	
	
	
};


//Names

static const std::string DimensionNames [4] = { "x", "y", "z", "w" };

static const std::string ColorChannelNames [4] = { "r", "g", "b", "a" };

static std::string GetNameForDimension(const size_t & dim, const size_t & totalDims)
{
	if(totalDims <= 4){
		return DimensionNames[dim];
	}
	
	return ofToString(dim);
	
}

}} //ofx::LineaDeTiempo


