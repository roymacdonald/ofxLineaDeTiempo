#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){
	ofSetCircleResolution(200);
	ofSetBackgroundColor(0);

	// these come from openFrameworks/examples/windowing/multiWindowOneAppExample
	parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
	parameters.add(color.set("color",100,ofColor(0,0),255));
	gui.setup(parameters);
	
	
	/// then simply add your ofxPanel to the timeline.
	timeline.add(gui);
	
	
	/// display the timeline on its own window. By default, the timeline will fill the window and automatically call it's draw function, so you do not need to draw it in ofApp::draw. As well, it will automatically call generateView() so you dont need to do so.

	timeline.displayOnNewWindow(ofRectangle(100,100,ofGetWidth() - 200, ofGetHeight()-200));

	///\ Lets load some data into the timeline
	///\ You can save this data pressing the 's' key.
	timeline.load( ofToDataPath("timelineData.json"));
	
	
	setHelpString();

	
}
void ofApp::setHelpString()
{

	helpString =  "[ Key ] : action\n";
	helpString += "[ w ] : Create or destroy timeline window\n";
	helpString += "[ s ] : Save\n";
	helpString += "[ l ] : Load\n";
	helpString += "[ g ] : Toggle Draw Gui\n";
	helpString += "[ h ] : Show/Hide this help\n";
	
	helpString += "\nNotice that these actions happen only when the apps main window (the one with this message) is in focus.";



	ofBitmapFont bf;
	helpStringHeight = bf.getBoundingBox(helpString, 0, 0).height;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(color);
	ofDrawCircle(ofGetWidth()*0.5,ofGetHeight()*0.5,radius);
	ofDrawBitmapStringHighlight(helpString, 20, ofGetHeight() - helpStringHeight, ofColor(0, 100));

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	
	if (key == 's')
	{
		timeline.save( ofToDataPath("timelineData.json"));
	}
	else if (key == 'l')
	{
		timeline.load(  ofToDataPath("timelineData.json"));
	}
	else if (key == ' ')
	{
		timeline.getTimeControl()->tooglePlay();
	}
	else if (key == 'p')
	{
		cout << "Window PointerEvent map: "<<endl;
		for(auto& m : ofx::PointerEventsManager::instance()._windowEventMap)
		{
			if(m.first){
				cout << m.first->getWindowPosition() << ", " << m.first->getWindowSize();
			}
			else
			{
				cout << "Invalid window pointer";
			}
			
			if(m.second)
			{
				cout << "  _  " << m.second.get();
			}
			else
			{
				cout << "  - invalid events pointer";
			}
			
			 cout << endl;
			
		}
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
