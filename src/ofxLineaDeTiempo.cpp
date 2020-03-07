
#include "ofxLineaDeTiempo.h"
#include "KeyFrames.h"
#include "Utils.h"
//-------------------------------------------------------------
ofxLineaDeTiempo::ofxLineaDeTiempo()
{
	timeControl = std::make_shared<ofx::LineaDeTiempo::TimeControl>();
//	keyListener = ofEvents().keyReleased.newListener(this, &ofxLineaDeTiempo::keyReleased);
	
	tr = this->addChild<ofx::LineaDeTiempo::TracksPanel>("Tracks", ofRectangle( 0, 0, ofGetWidth(), ofGetHeight()), timeControl);

	t1 = tr->addKeyframesTrack("k");
//	auto t2 = tr->addTrack();
	
//	t1->track->addRegion(ofRange_<uint64_t>(1000, 4000));
//	t1->track->addRegion(ofRange_<uint64_t>(5000, 7000));
//
//	t2->track->addRegion(ofRange_<uint64_t>(2000, 5000));
//	t2->track->addRegion(ofRange_<uint64_t>(7000, 10000));

}
//-------------------------------------------------------------
void ofxLineaDeTiempo::setup()
{
	tr->tracksView->setScrollV({0,1});
	tr->tracksView->setScrollH({0,1});
}
//-------------------------------------------------------------
void ofxLineaDeTiempo::onDraw() const
//void ofxLineaDeTiempo::draw()
{
	
	auto x = t1->track->timeToScreenPosition(timeControl->getCurrentTime());
	
	
	
	ofPushStyle();
	ofSetColor(ofColor::yellow);
	ofSetLineWidth(3);
	ofDrawLine(x, 0, x, ofGetHeight());
	ofPopStyle();
	
	
	timeControl->drawDebug(20,  ofGetHeight()-280);
	
	
	auto x2 = tr->timeToScreenPosition(timeControl->getCurrentTime());
	
	
	auto  t0 = t1->track->screenPositionToTime(ofGetMouseX());
	auto  t1 = tr->screenPositionToTime(ofGetMouseX());
	
	{
		std::stringstream ss;
	
		ss << "timeToScreen:\n    track: " << x << "\n    panel: " << x2;
		ofDrawBitmapStringHighlight(ss.str(), 300, ofGetHeight()-280, ofIsFloatEqual(x, x2)?ofColor::black:ofColor::red);
	}
	{
		std::stringstream ss;
		ss << "screenToTime:\n    track: " << t0 << "\n    panel: " << t1;
		ofDrawBitmapStringHighlight(ss.str(), 300, ofGetHeight()-200, (t0 == t1)?ofColor::black:ofColor::red);
	}
	
}
//-------------------------------------------------------------
void ofxLineaDeTiempo::update()
{
	
}
//-------------------------------------------------------------
void ofxLineaDeTiempo::keyReleased(ofKeyEventArgs& args)
{

//	if(args.key == ' ')
//	{
//		if(timeControl->isPaused() || timeControl->isStopped()){
//			timeControl->play();
//		}
//		else
//		{
//			timeControl->pause();
//		}
//	}
//	else if(args.key == 'q')
//	{
//		tr->updateLayout();
//	}
//	else if(args.key == 'w')
//	{
//		tr->tracksView->updateContainerLayout();
//	}
//	else if(args.key == 's')
//	{
//		timeControl->stop();
//	}
//	else if(args.key == 'p')
//	{
////		printStructure(&mui);
//
//	}
	
}
