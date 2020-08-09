//
//  ConstVars.cpp
//  example
//
//  Created by Roy Macdonald on 4/9/20.
//

#include "LineaDeTiempo/Utils/ConstVars.h"

namespace ofx {
namespace LineaDeTiempo {



ofParameter<ofColor> ConstVars::TrackBackgroundColor = ofParameter<ofColor>("TrackBackgroundColor", ofColor(51), ofColor(0,0,0,0), ofColor(255,255,255,255));
ofParameter<ofColor> ConstVars::TrackEdgeColor = ofParameter<ofColor>("TrackEdgeColor", ofColor(80), ofColor(0,0,0,0), ofColor(255,255,255,255));
ofParameter<ofColor> ConstVars::PanelBackgroundColor = ofParameter<ofColor>("PanelBackgroundColor", ofColor(40), ofColor(0,0,0,0), ofColor(255,255,255,255));

ofParameter<ofColor> ConstVars::TooltipTextColor = ofParameter<ofColor>("Tooltip Text", ofColor(0), ofColor(0,0,0,0), ofColor(255,255,255,255));
ofParameter<ofColor> ConstVars::TooltipBackgroundColor = ofParameter<ofColor>("Tooltip Background", ofColor(255), ofColor(0,0,0,0), ofColor(255,255,255,255));
ofParameter<ofColor> ConstVars::TooltipBorderColor = ofParameter<ofColor>("Tooltip Border", ofColor(0), ofColor(0,0,0,0), ofColor(255,255,255,255));

 ofColor ConstVars::SelectedColor = ofColor::yellow;


ofParameter<float> ConstVars::TrackInitialHeight = ofParameter<float>("TrackInitialHeight", 150.0, 0.f, 400.f);
ofParameter<float> ConstVars::DefaultKeyframeSize = ofParameter<float>("DefaultKeyframeSize", 5.0, 0.f, 20.f);
ofParameter<float> ConstVars::ViewTopHeaderHeight = ofParameter<float>("ViewTopHeaderHeight", 18.f, 0.f, 50.f);
ofParameter<float> ConstVars::HeaderViewIndent = ofParameter<float>("HeaderViewIndent", 4.f, 0.f, 10.f);
ofParameter<float> ConstVars::TimeRulerInitialHeight = ofParameter<float>("TimeRulerInitialHeight", 40.f, 0.f, 100.f);
ofParameter<float> ConstVars::PlayheadTriangleSize = ofParameter<float>("PlayheadTriangleSize", 15.f, 0.f, 150.f);
ofParameter<float> ConstVars::PlayheadWidth = ofParameter<float>("PlayheadWidth", 3.f, 0.f, 10.f);


ofParameter<uint64_t> ConstVars::tooltipDelay = ofParameter<uint64_t> ("Tooltip Delay",800, 0, 3000);
ofParameter<uint64_t> ConstVars::tooltipTimeout = ofParameter<uint64_t> ("Tooltip Timeout",3000, 0, 5000);
ofParameter<bool> ConstVars::showTooltips = ofParameter<bool> ("Show Tooltips",true);




ofParameterGroup& ConstVars::getParameters(){
	static std::unique_ptr<ofParameterGroup> group;

	if(!group){
		
		group = std::make_unique<ofParameterGroup>("Const Vars");

		ofParameterGroup colorsGroup ("colors");
		colorsGroup.add(PanelBackgroundColor);
		colorsGroup.add(TrackBackgroundColor);
		colorsGroup.add(TrackEdgeColor);
		colorsGroup.add(TooltipTextColor);
		colorsGroup.add(TooltipBackgroundColor);
		colorsGroup.add(TooltipBorderColor);
		
		ofParameterGroup measuresGroup("Measures");

		measuresGroup.add(TrackInitialHeight);
		measuresGroup.add(DefaultKeyframeSize);
		measuresGroup.add(ViewTopHeaderHeight);
		measuresGroup.add(HeaderViewIndent);
		measuresGroup.add(TimeRulerInitialHeight);
		measuresGroup.add(PlayheadTriangleSize);
		measuresGroup.add(PlayheadWidth);

		ofParameterGroup tooltipGroup("Tooltip");		
		tooltipGroup.add(tooltipDelay);
		tooltipGroup.add(tooltipTimeout);
		tooltipGroup.add(showTooltips);
		
		group->add(colorsGroup);
		group->add(measuresGroup);
		group->add(tooltipGroup);

	}
	return *group;
}



}} //ofx::LineaDeTiempo

