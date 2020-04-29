#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){



	numbersGroup.add(_param_int32_t);
	numbersGroup.add(_param_uint32_t);
	numbersGroup.add(_param_int64_t);
	numbersGroup.add(_param_uint64_t);
	numbersGroup.add(_param_int8_t);
	numbersGroup.add(_param_uint8_t);
	numbersGroup.add(_param_int16_t);
	numbersGroup.add(_param_uint16_t);
	numbersGroup.add(_param_size_t);
	numbersGroup.add(_param_float);
	numbersGroup.add(_param_double);

	colorGroup.add(_param_ofColor);
	colorGroup.add(_param_ofShortColor);
	colorGroup.add(_param_ofFloatColor);
	glmGroup.add(_param_Vec2);
	glmGroup.add(_param_Vec3);
	glmGroup.add(_param_Vec4);
		
	
	/// start by setting up the ofxGui as you'd regularly do.
	gui.setup();
//	gui.add(numbersGroup);
	
	gui.add(_param_void);
	gui.add(glmGroup);
	
	gui.add(colorGroup);
	
	
	
	/// then simply add your ofxPanel to the timeline.
	timeline.add(gui);
	
	/// The timeline also works without its view, so you need to generate it.
	/// This can be done and undone on runtime, in order to show or hide the timeline.
	/// look further down in the keyReleased function to see how to create or destroy the view.
	timeline.generateView();
//	timeline.enableAutoFillScreen();

	timeline.setShape({100, 100, 405, 300});
	
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	timeline.draw();

	
	if(bDrawGui) gui.draw();
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'v') {
		if(timeline.hasView())
		{
			timeline.destroyView();
		}
		else
		{
			timeline.generateView();
		}
	}
	else if (key == 'z')
	{

		auto p = timeline.getPanel();
		if(p)
		{
			p->getTracksView()->_scrollbarH->setValue({0,1});
			p->getTracksView()->_scrollbarV->setValue({0,1});
		}
	}
	else if (key == ' ')
	{
		timeline.getTimeControl()->tooglePlay();
	
	}
	else if (key == 's')
	{
		timeline.save( ofToDataPath("testSave.json"));
	
	}
	else if (key == 'l')
	{
		timeline.load( ofToDataPath("testSave.json"));
	
	}
	else if (key == 'g')
	{
		bDrawGui ^= true;
	}
	else if (key == 'p') {
		timeline.printStructure();
		if(timeline.getView()) timeline.getView()->printStructure();
	}
	else if (key == 't') {
		auto p = timeline.getPanel();
		if(p)
		{
			p->updateLayout();
		}
//		timeline.getGroup(0)->getGroup(0)->getTrack(0)->getView()->setScaledHeight(300);
	}
	
}
