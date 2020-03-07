#pragma once

#include "ofMain.h"
#include "MUI.h"
#include "TracksPanel.h"

class ofxLineaDeTiempo: public ofx::MUI::MUI{
public:
	
	ofxLineaDeTiempo();
	
    void setup();
    void draw();
	void update();
	
	void keyReleased(ofKeyEventArgs& args);

	
	virtual void onDraw() const override;
	

	ofx::LineaDeTiempo::TracksPanel * tr = nullptr;
	
	ofx::LineaDeTiempo::TrackAndHeader* t1 = nullptr;
	
	std::shared_ptr<ofx::LineaDeTiempo::TimeControl> timeControl = nullptr;
	
	
	ofEventListener keyListener;
	
};
