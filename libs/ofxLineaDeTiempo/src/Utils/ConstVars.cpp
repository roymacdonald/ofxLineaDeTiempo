//
//  ConstVars.cpp
//  example
//
//  Created by Roy Macdonald on 4/9/20.
//

#include "LineaDeTiempo/Utils/ConstVars.h"

namespace ofx {
namespace LineaDeTiempo {



ofParameter<ofColor> ConstVars::TrackBackgroundColor = ofParameter<ofColor>("TrackBackgroundColor", ofColor(30), ofColor(0,0,0,0), ofColor(255,255,255,255));
ofParameter<ofColor> ConstVars::TrackEdgeColor = ofParameter<ofColor>("TrackEdgeColor", ofColor(120), ofColor(0,0,0,0), ofColor(255,255,255,255));
ofParameter<ofColor> ConstVars::PanelBackgroundColor = ofParameter<ofColor>("PanelBackgroundColor", ofColor(40), ofColor(0,0,0,0), ofColor(255,255,255,255));


 ofColor ConstVars::SelectedColor = ofColor::yellow;


ofParameter<float> ConstVars::TrackInitialHeight = ofParameter<float>("TrackInitialHeight", 150.0, 0.f, 400.f);
ofParameter<float> ConstVars::DefaultKeyframeSize = ofParameter<float>("DefaultKeyframeSize", 5.0, 0.f, 20.f);
ofParameter<float> ConstVars::ViewTopHeaderHeight = ofParameter<float>("ViewTopHeaderHeight", 18.f, 0.f, 50.f);
ofParameter<float> ConstVars::HeaderViewIndent = ofParameter<float>("HeaderViewIndent", 4.f, 0.f, 10.f);
ofParameter<float> ConstVars::TimeRulerInitialHeight = ofParameter<float>("TimeRulerInitialHeight", 40.f, 0.f, 100.f);
ofParameter<float> ConstVars::PlayheadTriangleSize = ofParameter<float>("PlayheadTriangleSize", 15.f, 0.f, 150.f);
ofParameter<float> ConstVars::PlayheadWidth = ofParameter<float>("PlayheadWidth", 3.f, 0.f, 10.f);


uint64_t ConstVars::tooltipDelay = 800;




}} //ofx::LineaDeTiempo

