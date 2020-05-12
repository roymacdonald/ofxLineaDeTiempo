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
	
	
	/// display the timeline on its own window. By default, the timeline will fill the window and automatically call it's draw function, so you do not need to draw it in ofApp::draw. As well, it will automatically call generateView() so you dont need to do so.

	timeline.displayOnNewWindow(ofRectangle(100,100,ofGetWidth() - 200, ofGetHeight()-200));
	
	
	
	
	setHelpString();
	
}
void ofApp::setHelpString()
{
	
	helpString =  "[ Key ] : action\n";
	helpString += "[ s ] : Save\n";
	helpString += "[ l ] : Load\n";
	helpString += "[ g ] : Toggle Draw Gui\n";
	helpString += "[ h ] : Show/Hide this help\n";
	helpString += "\nNotice that these actions happen only when the apps main window is in focus,\n the one with this message.";
	
	
	
	ofBitmapFont bf;
	helpStringHeight = bf.getBoundingBox(helpString, 0, 0).height;
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	
	// Dont call timeline.draw(); here as the window created with displayOnNewWindow will do so automatically.

	if(bDrawGui) gui.draw();
	
	if(bDrawHelp) ofDrawBitmapStringHighlight(helpString, 20, ofGetHeight() - helpStringHeight, ofColor(0, 100));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	
	if (key == 's')
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
	else if (key == 'h')
	{
		bDrawHelp ^= true;
	}
	else if (key == 'w')
	{
		if(timeline.hasWindow())
		{
			timeline.closeWindow();
		}
		else
		{
			timeline.displayOnNewWindow(ofRectangle(100,100,ofGetWidth() - 200, ofGetHeight()-200));
		}
	}
}
