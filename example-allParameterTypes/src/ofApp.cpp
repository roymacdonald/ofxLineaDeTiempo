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
	gui.add(numbersGroup);
	
	gui.add(_param_void);
	gui.add(_param_bool);
	gui.add(glmGroup);
	
	gui.add(colorGroup);
	
	
	
	/// then simply add your ofxPanel to the timeline.
	timeline.add(gui);
	
	/// The timeline also works without its view, so you need to generate it.
	/// This can be done and undone on runtime, in order to show or hide the timeline.
	/// look further down in the keyReleased function to see how to create or destroy the view.
	timeline.generateView();

	
	
	
	/// 
	
	
	setHelpString();
	
	

	/// set the timelines shape.
	setTimelineShape();
	
}

//--------------------------------------------------------------
void ofApp::setTimelineShape(){

	float x = 0;
	if(bDrawGui){
	/// In this case we set it to be  draw side by side with the GUI
		x = gui.getShape().getMaxX() + 5;
	}

	ofRectangle shape( x, 0, ofGetWidth() - x - 5 , ofGetHeight() - helpStringHeight);

	timeline.setShape(shape);
}

//--------------------------------------------------------------
void ofApp::setHelpString()
{
	
	helpString =  "[ Key ] : action\n";
	helpString += "[ v ] : Show/Hide Timeline\n";
	helpString += "[ space bar ] : Toggle Play\n";
	helpString += "[ return/enter ] : Stop\n";
	helpString += "[ s ] : Save\n";
	helpString += "[ l ] : Load\n";
	helpString += "[ g ] : Toggle Draw Gui\n";
	helpString += "[ p ] : Print current timeline structure\n";
	helpString += "[ h ] : Show/Hide this help\n";
	
	ofBitmapFont bf;
	helpStringHeight = bf.getBoundingBox(helpString, 0, 0).height;
	
}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	timeline.draw();

	
	if(bDrawGui) gui.draw();
	
	if(bDrawHelp) ofDrawBitmapString(helpString, 20, ofGetHeight() - helpStringHeight);
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
	else if (key == ' ')
	{
		timeline.getTimeControl()->tooglePlay();
	
	}
	else if (key == OF_KEY_RETURN)
	{
		timeline.getTimeControl()->stop();
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
		setTimelineShape();
	}
	else if (key == 'p') {
		timeline.printStructure();
		if(timeline.getView()) timeline.getView()->printStructure();
	}
	else if (key == 'h') {
		bDrawHelp ^= true;
	}
	else if (key == 't')
	{
		timeline.setTotalTime(60000	);
	}
}
