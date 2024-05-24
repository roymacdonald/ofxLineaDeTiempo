#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){
		
	
	ofSetCircleResolution(200);
	ofSetBackgroundColor(0);

	// these come from openFrameworks/examples/windowing/multiWindowOneAppExample
	parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
	parameters.add(color.set("color",100,ofColor(0,0),255));
	gui.setup(parameters, "", 0, 0);
	
	
	/// then simply add your ofxPanel to the timeline.
	timeline.add(gui);
	
	
	/// The timeline also works without its view, so you need to generate it.
	/// This can be done and undone on runtime, in order to show or hide the timeline.
	/// look further down in the keyReleased function to see how to create or destroy the view.
	timeline.generateView();
	
	/// By default ofxLineaDeTiempo will auto adjust itself to fill the whole window in which it is being drawn.
	/// if you uncomment the following line, the timeline's shape will be set and the autofill property will get disabled.
	/// When you do so, the ofxLineaDeTiempo instance will now be drawn with a header bar, which you can clic and drag to drag the whole timeline around. Aswell it will have a handle in its lowerright corner which you can use for resizing the timeline.
	/// Now lets make the timeline to use half of the window so we leave some space for the other graphics to be drawn.
	timeline.setShape(ofRectangle(0,ofGetHeight()/2,ofGetWidth(), ofGetHeight()/2));
	
	///\ Lets load some data into the timeline
	///\ You can save this data pressing the 's' key.
	timeline.load( ofToDataPath("timelineData.json"));
    timeline.getPanel()->getTracksView()->getScrollbarH()->setValue({0,1});
	
	
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
	helpString += "[ f ] : Toggle AutoFillWindow mode\n";
	
	ofBitmapFont bf;
	helpStringWidth = bf.getBoundingBox(helpString, 0, 0).width;
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(color.get());
	ofDrawCircle(ofGetWidth()*0.5,ofGetHeight()*0.25,radius);
	
	
	timeline.draw();

	
	if(bDrawGui) gui.draw();
	
	if(bDrawHelp) ofDrawBitmapStringHighlight(helpString, ofGetWidth() - helpStringWidth , 16, ofColor(0, 100));
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
		timeline.save( ofToDataPath("timelineData.json"));
	
	}
	else if (key == 'l')
	{
		timeline.load( ofToDataPath("timelineData.json"));
	
	}
	else if (key == 'g')
	{
		bDrawGui ^= true;
	}
	else if (key == 'h')
	{
		bDrawHelp ^= true;
	}
	else if (key == OF_KEY_RETURN){
		timeline.getTimeControl()->stop();		
	}
	else if (key == 'f')
	{
		timeline.setAutoFillScreen(!timeline.isAutoFillScreenEnabled());
	}

	
}
