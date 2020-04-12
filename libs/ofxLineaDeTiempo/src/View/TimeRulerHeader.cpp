//
//  TimeRulerHeader.cpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//

#include "LineaDeTiempo/View/TimeRulerHeader.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "LineaDeTiempo/Utils/FontUtils.h"
#include "ofxTimecode.h"

namespace ofx {
namespace LineaDeTiempo {


ofBitmapFont TimeRulerHeader::_bf = ofBitmapFont();


TimeRulerHeader::TimeRulerHeader( TimeControl* timeControl)
:  DOM::Element("TimeRulerHeader", 0,0,100,100)
, _timeControl(timeControl)
{

}

void TimeRulerHeader::updateLayout()
{

	_makeTimeText();
		
	ofBitmapFont _bf;
	
	auto bb = _bf.getBoundingBox(_timeText, 0, 0);

	auto y = bb.y;

	bb.alignTo(getShape());

	_textPos = {bb.x, bb.y - y};
	
}
void TimeRulerHeader::_makeTimeText() const
{
	auto t =_timeControl->getCurrentTime();
	
	_timeText = ofxTimecode::timecodeForMillis(t);
    
}

void TimeRulerHeader::onDraw() const
{
	DOM::Element::onDraw();
	
	_makeTimeText();
		
	ofPushStyle();
	
	ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
	ofDrawBitmapString( _timeText, _textPos);
	
	
	ofNoFill();
	ofSetColor(ConstVars::TrackEdgeColor);
	ofDrawRectangle(getShape());
	
	ofPopStyle();
	
}

} } // ofx::LineaDeTiempo

