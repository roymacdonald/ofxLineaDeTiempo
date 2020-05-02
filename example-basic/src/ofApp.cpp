#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){
		
	
	gui.setup();
	
	
	gui.add(_param_float);
	gui.add(_param_bool);
	gui.add(_param_void);
	gui.add(_param_ofColor);
	gui.add(_param_Vec3);
	
	
	/// then simply add your ofxPanel to the timeline.
	timeline.add(gui);
	
	/// The timeline also works without its view, so you need to generate it.
	/// This can be done and undone on runtime, in order to show or hide the timeline.
	/// look further down in the keyReleased function to see how to create or destroy the view.
	timeline.generateView();
	
	/// By default ofxLineaDeTiempo will auto adjust itself to fill the whole window in which it is being drawn.
	/// if you uncomment the following line, the timeline's shape will be set and the autofill property will get disabled.
	/// When you do so, the ofxLineaDeTiempo instance will now be drawn with a header bar, which you can clic and drag to drag the whole timeline around. Aswell it will have a handle in its lowerright corner which you can use for resizing the timeline.
	timeline.setShape(ofRectangle(100,100,ofGetWidth() - 200, ofGetHeight()-200));
	
	setHelpString();
	
}
void ofApp::setHelpString()
{
	
	helpString =  "[ Key ] : action\n";
	helpString += "[ v ] : Show/Hide Timeline\n";
	helpString += "[ space bar ] : Toggle Play\n";
	helpString += "[ return/enter ] : Stop\n";
	helpString += "[ s ] : Save\n";
	helpString += "[ l ] : Load\n";
	helpString += "[ g ] : Toggle Draw Gui\n";
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
	
	if(bDrawHelp) ofDrawBitmapStringHighlight(helpString, 20, ofGetHeight() - helpStringHeight, ofColor(0, 100));
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
	else if (key == 'h') {
		bDrawHelp ^= true;
	}
	else if (key == OF_KEY_RETURN){
		timeline.getTimeControl()->stop();
	}
	
}
