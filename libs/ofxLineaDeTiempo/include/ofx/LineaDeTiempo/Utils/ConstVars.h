//
//  Constants.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/31/20.
//

#pragma once
#include "ofColor.h"
#include <vector>
namespace ofx {
namespace LineaDeTiempo {

static const ofColor DefaultTextColor = ofColor(220);

//BaseTrackView
static const ofColor TrackBackgroundColor = ofColor(40);
static const ofColor TrackEdgeColor = ofColor(120);
static const float   TrackInitialHeight = 150.0;

//KeyframeView
static const float DefaultKeyframeSize = 5.0;

//RegionView
static float ViewTopHeaderHeight = 18.f;
static const ofColor RegionBackgroundColor = ofColor(80);

//HeaderView

static float HeaderViewIndent = 25.f;


//TimeRuler

static float TimeRulerInitialHeight = 30.f;

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

