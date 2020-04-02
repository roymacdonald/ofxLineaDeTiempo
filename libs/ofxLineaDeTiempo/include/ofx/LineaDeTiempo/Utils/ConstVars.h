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

//BaseTrackView
static const ofColor TrackBackgroundColor = ofColor(80);
static const ofColor TrackEdgeColor = ofColor(120);
static const float TrackInitialHeight = 150.0;

//ofColor BaseTrackView::backgroundColor = ofColor(80);
//ofColor BaseTrackView::edgeColor = ofColor(120);
//const float BaseTrackView::initialHeight = 150;


//KeyframeView
static const float DefaultKeyframeSize = 15.0;
//float KeyframeView::defaultKeyframeSize = 15;

//RegionView
static float RegionViewHeaderHeight = 18.f;
//float RegionView::headerHeight = 18.f;

static const std::string DimensionNames [4] = { "x", "y", "z", "w" };


static std::string GetNameForDimension(const size_t & dim, const size_t & totalDims)
{
	if(totalDims <= 4){
		return DimensionNames[dim];
	}
	
	return ofToString(dim);
	
}

}} //ofx::LineaDeTiempo
//#include "LineaDeTiempo/Utils/ConstVars.h"

