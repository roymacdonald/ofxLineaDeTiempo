#pragma once

#include "ofMain.h"

#include "ofxLineaDeTiempo.h"

#include "ofxGui.h"

//Remember to add this line on your projects otherwise you'll need to prepend a lot ofx::LineaDeTiempo
using namespace ofx::LineaDeTiempo;


class ofApp : public ofBaseApp{

public:

	void setup() override;
	void draw() override;
	void update() override;
		
	void keyReleased(int key) override;
	
	
		
	// simply declare an ofxLineaDeTiempo instance.
	ofxLineaDeTiempo timeline = {"Timeline"};

	
	// This example is the same as core example in the openFrameworks/examples/windowing/multiWindowOneAppExample
	// But with a timeline included. Compare both to see that you need very few lines to make it all work.
	ofParameterGroup parameters;
	ofParameter<float> radius;
	ofParameter<ofColor> color;
	ofxPanel gui;
	
		
	
	//Some extra help text
	void setHelpString();
	string 	helpString;
	float helpStringHeight;
	
};
