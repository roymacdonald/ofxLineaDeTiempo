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

class ConstVars
{
public:
	
	/** @name Colors
	 *	Most of the colors are defined through the document styles, yet there are a few things that looked better if their color was set individually.
	 */
	///@{
	
	///\brief The background color of the main view (panel). This color will be mostly shown when there is nothing in that area, as most of the UI elements have solid colors
	static ofParameter<ofColor> PanelBackgroundColor;
	
	///\brief The background color of each track.
	/// The idea is that it is slightly different from the panel background color so it is easily perceived what is a track and what is not.
	static ofParameter<ofColor> TrackBackgroundColor;
	
	///\brief The edge color of each track
	static ofParameter<ofColor> TrackEdgeColor      ;
	static ofColor SelectedColor;
	
	
	
	///@}
	/** @name ToolTip Options
	 *  The Tooltip is a small text box that shows up as an aid for the user when it hovers the mouse over elements that have it enabled.
	 *  The tooltip shows at the mouse position, thus its name.
	 */
	///@{
	
	///\brief The Tooltip's text color
	static ofParameter<ofColor> TooltipTextColor;
	
	///\brief The Tooltip's bounding box background color
	static ofParameter<ofColor> TooltipBackgroundColor;
	
	///\brief The Tooltip's bounding box border color
	static ofParameter<ofColor> TooltipBorderColor;
	

	///\brief How much time the pointer needs to be without moving over an element with tooltips in order to show thet tooltip
	/// units: milliseconds
	static ofParameter<uint64_t> tooltipDelay;
	///\brief Maximum amount of time a tooltip can be shown.
	/// units: milliseconds
	static ofParameter<uint64_t> tooltipTimeout;
	
	///\brief Show tooltips on elements that have this feature implemented
	static ofParameter<bool> showTooltips;

	///@}
	
	
	/** @name Sizes
	 *	Default or initial sizes of some of the UI elements.
	 */
	///@{
	
	///\brief This is the initial track height. Even when this is used for the initial height it is used as the tracks height changes as a point of reference for some calculations
	static ofParameter<float> TrackInitialHeight      ;
	
	///\brief The width and height of the drawn keyframes; circles
	static ofParameter<float> DefaultKeyframeSize     ;
	
	///\brief The height of the top header that some elements have.
	static ofParameter<float> ViewTopHeaderHeight     ;
	
	///\brief The left indent added to the tracks headers when these belong to a group
	static ofParameter<float> HeaderViewIndent        ;
	
	///\brief The initial height of the time ruler. so far this does not change dynamically
	static ofParameter<float> TimeRulerInitialHeight  ;
	
	///\brief The width of the line drawn at the playhead position.
	static ofParameter<float> PlayheadWidth           ;
	
	///\brief The size of the triangle drawn at the top of the playhead line.
	static ofParameter<float> PlayheadTriangleSize    ;
	
	
	///@}
	
	
	///\brief get an ofParameterGroup containing all the ConstVars parameters
	static ofParameterGroup& getParameters();
	
    
    ///\brief enable support for HiDpi displays
    static void enableHiDpi();
    ///\brief disable support for HiDpi displays
    static void disableHiDpi();
    
private:
    static bool isHiDpiEnabled;
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


