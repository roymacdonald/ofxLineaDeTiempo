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
	static ofParameter<ofColor> TrackBackgroundColor  ;
	static ofParameter<ofColor> TrackEdgeColor        ;
	static ofParameter<ofColor> TooltipTextColor;
	static ofParameter<ofColor> TooltipBackgroundColor;
	static ofParameter<ofColor> TooltipBorderColor;

	static ofColor SelectedColor;
	
	static ofParameter<float> TrackInitialHeight      ;
	static ofParameter<float> DefaultKeyframeSize     ;
	static ofParameter<float> ViewTopHeaderHeight     ;
	static ofParameter<float> HeaderViewIndent        ;
	static ofParameter<float> TimeRulerInitialHeight  ;
	static ofParameter<float> PlayheadTriangleSize    ;
	static ofParameter<float> PlayheadWidth           ;
	
	///\brief How much time the pointer needs to be without moving over an element with tooltips in order to show thet tooltip
	/// units: milliseconds
	static uint64_t tooltipDelay;
	///\brief Maximum amount of time a tooltip can be shown.
	/// units: milliseconds
	static uint64_t tooltipTimeout;
	
	///\ Show tooltips on elements that have this feature implemented
	static bool showTooltips;
	
	
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


