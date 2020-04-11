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
//
//static ofParameter<ofColor> DefaultTextColor;// = ofColor(220);
//
////BaseTrackView
//static  ofParameter<ofColor> TrackBackgroundColor;// = ofColor(40);
//static  ofParameter<ofColor> TrackEdgeColor;// = ofColor(120);
//static  ofParameter<float>   TrackInitialHeight;// = 150.0;
//
////KeyframeView
//static ofParameter<float> DefaultKeyframeSize;// = 5.0;
//
////RegionView
//static ofParameter<float> ViewTopHeaderHeight;// = 18.f;
//static  ofParameter<ofColor> RegionBackgroundColor;// = ofColor(80);
//
////HeaderView
//
//static ofParameter<float> HeaderViewIndent;// = 4.f;
//
//
////TimeRuler
//
//static ofParameter<float> TimeRulerInitialHeight;// = 30.f;
//
//static ofParameter<float> PlayheadTriangleSize;// = 15.f;
//
//static ofParameter<float> PlayheadWidth;// = 3.f;


// [^:](DefaultTextColor|TrackBackgroundColor|TrackEdgeColor|RegionBackgroundColor|TrackInitialHeight|DefaultKeyframeSize|ViewTopHeaderHeight|HeaderViewIndent|TimeRulerInitialHeight|PlayheadTriangleSize|PlayheadWidth)


struct ConstVars
{
	
	static ofParameter<ofColor> DefaultTextColor      ;//= {"DefaultTextColor", ofColor(220), ofColor::black, ofColor::white};
	static ofParameter<ofColor> TrackBackgroundColor  ;//= {"TrackBackgroundColor", ofColor(40), ofColor::black, ofColor::white};
	static ofParameter<ofColor> TrackEdgeColor        ;//= {"TrackEdgeColor", ofColor(120), ofColor::black, ofColor::white};
	static ofParameter<ofColor> RegionBackgroundColor ;//= {"RegionBackgroundColor", ofColor(80), ofColor::black, ofColor::white};
	static ofParameter<ofColor> SelectedColor; //ofColor::yellow
	
	
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
//#include "LineaDeTiempo/Utils/ConstVars.h"

