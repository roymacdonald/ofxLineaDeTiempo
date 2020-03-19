//
//#include "ofxLineaDeTiempo.h"
//#include "KeyFrames.h"
//#include "Utils.h"
////-------------------------------------------------------------
//ofxLineaDeTiempo::ofxLineaDeTiempo()
//{
//
////	keyListener = ofEvents().keyReleased.newListener(this, &ofxLineaDeTiempo::keyReleased);
//
//	tr = this->addChild<ofx::LineaDeTiempo::TracksPanel>("Tracks", ofRectangle( 0, 0, ofGetWidth(), ofGetHeight()));
//
////	t1 = tr->addKeyframesTrack("k");
////	auto t2 = tr->addTrack();
//
////	t1->track->addRegion(ofRange_<uint64_t>(1000, 4000));
////	t1->track->addRegion(ofRange_<uint64_t>(5000, 7000));
////
////	t2->track->addRegion(ofRange_<uint64_t>(2000, 5000));
////	t2->track->addRegion(ofRange_<uint64_t>(7000, 10000));
//
//}
////-------------------------------------------------------------
//void ofxLineaDeTiempo::setup()
//{
////	tr->tracksView->setScrollV({0,1});
////	tr->tracksView->setScrollH({0,1});
//}
////-------------------------------------------------------------
//void ofxLineaDeTiempo::onDraw() const
////void ofxLineaDeTiempo::draw()
//{
//
////	auto x = t1->timeToScreenPosition(ofx::LineaDeTiempo::getTimeControl().getCurrentTime());
//
//
////
////	ofPushStyle();
////	ofSetColor(ofColor::yellow);
////	ofSetLineWidth(3);
////	ofDrawLine(x, 0, x, ofGetHeight());
////	ofPopStyle();
////
////
////	ofx::LineaDeTiempo::getTimeControl().drawDebug(20,  ofGetHeight()-280);
////
////
////	auto x2 = tr->timeToScreenPosition(ofx::LineaDeTiempo::getTimeControl().getCurrentTime());
////
////
////	auto  t0 = t1->screenPositionToTime(ofGetMouseX());
////	auto  t1 = tr->screenPositionToTime(ofGetMouseX());
////
////	{
////		std::stringstream ss;
////
////		ss << "timeToScreen:\n    track: " << x << "\n    panel: " << x2;
////		ofDrawBitmapStringHighlight(ss.str(), 300, ofGetHeight()-280, ofIsFloatEqual(x, x2)?ofColor::black:ofColor::red);
////	}
////	{
////		std::stringstream ss;
////		ss << "screenToTime:\n    track: " << t0 << "\n    panel: " << t1;
////		ofDrawBitmapStringHighlight(ss.str(), 300, ofGetHeight()-200, (t0 == t1)?ofColor::black:ofColor::red);
////	}
////
//}
////-------------------------------------------------------------
//void ofxLineaDeTiempo::update()
//{
//
//}
////-------------------------------------------------------------
//void ofxLineaDeTiempo::keyReleased(ofKeyEventArgs& args)
//{
//
////	if(args.key == ' ')
////	{
////		if(ofx::LineaDeTiempo::getTimeControl().isPaused() || ofx::LineaDeTiempo::getTimeControl().isStopped()){
////			ofx::LineaDeTiempo::getTimeControl().play();
////		}
////		else
////		{
////			ofx::LineaDeTiempo::getTimeControl().pause();
////		}
////	}
////	else if(args.key == 'q')
////	{
////		tr->updateLayout();
////	}
////	else if(args.key == 'w')
////	{
////		tr->tracksView->updateContainerLayout();
////	}
////	else if(args.key == 's')
////	{
////		ofx::LineaDeTiempo::getTimeControl().stop();
////	}
////	else if(args.key == 'p')
////	{
//////		printStructure(&mui);
////
////	}
//
//}
