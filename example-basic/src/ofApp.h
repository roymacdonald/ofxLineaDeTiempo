#pragma once

#include "ofMain.h"
#include "ofxLineaDeTiempo.h"

#include "ofxGui.h"

using namespace ofx::LineaDeTiempo;

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;
	void update() override;
	
	void keyReleased(int key) override;
	

	// simply declare an ofxLineaDeTiempo instance.
	ofxLineaDeTiempo timeline = {"Timeline"};

	
	// just use a regular ofxPanel object. Does not matter how you initialize it or
	// how you add elements to it.
	
	ofxPanel gui;
	
	
	// I personally prefer instancing ofParameters instead of ofxGui's gui elements, as sliders or buttons.
	// But you can do it either way to.
	
	
	
	ofParameter <float>        _param_float        = {"float"        ,        float(0) ,    -1 ,    1};
	ofParameter <bool>         _param_bool         = {"bool"         ,         true};
	ofParameter <void>         _param_void         = {"void"};
	ofParameter <ofColor>      _param_ofColor      = {"ofColor"      , 		ofColor(0,0) ,      ofColor(0,0) ,      ofColor(255,255)};
	ofParameter<glm::vec3>     _param_Vec3         = {"glm::vec3"    ,     glm::vec3(0),        glm::vec3(-1),        glm::vec3(1)};

	// Tip: did you notice the nice way of declaring and initializing the ofParametrs using the curly brackets?
	// That's a newish C++ thing, not specific to ofParameter. These are called initializer lists.
	
	
	// some helper stuff
	bool bDrawGui = true;
	bool bDrawHelp = true;
	
	string helpString;
	float helpStringHeight;
	void setHelpString();
	
	
	
};
