//
//  TimeRulerHeader.cpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//

#include "TimeRulerHeader.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
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
		
	
	auto bb = _bf.getBoundingBox(_timeText, 0, 0);
	
	auto y = bb.y;
	
	bb.alignTo(getShape());
	
	_textPos = {bb.x, bb.y - y};
	
}
void TimeRulerHeader::_makeTimeText() const
{
	auto t =_timeControl->getCurrentTime();
	
	_timeText = ofToString((t/(1000*60*60))%60, 3, '0')
	
    	+ ":" + ofToString ((t/(1000*60))%60, 2, '0')
    
    	+ ":" + ofToString ((t/1000)%60, 2, '0')
    
    	+ ":" + ofToString ((t%1000), 3, '0');
    
}

void TimeRulerHeader::onDraw() const
{
	DOM::Element::onDraw();
	
	_makeTimeText();
		
	ofPushStyle();
	
	ofSetColor(ConstVars::DefaultTextColor);
	ofDrawBitmapString( _timeText, _textPos);
	
	ofNoFill();
	ofSetColor(ConstVars::TrackEdgeColor);
	ofDrawRectangle(getShape());
	
	ofPopStyle();
	
}

} } // ofx::LineaDeTiempo

