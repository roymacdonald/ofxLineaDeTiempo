////
////  TracksController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/6/20.
////
//
#pragma once
#include "LineaDeTiempo/BaseTypes/BaseViewController.h"


//#include "LineaDeTiempo/BaseTypes/BaseController.h"

#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Controller/KeyFrameTrackController.h"

#include "LineaDeTiempo/View/TracksPanel.h"

#include "ofx/MUI/MUI.h"

namespace ofx {
namespace LineaDeTiempo {


class TracksPanelController
:public TrackGroupController

{
public:

	TracksPanelController(const std::string& name);
	
	virtual ~TracksPanelController() = default;
	
//	void createMainView(const ofRectangle& viewport = ofRectangle(0,0,ofGetWidth(), ofGetHeight()), ofAppBaseWindow* window = ofGetWindowPtr());
	
	MUI::MUI * getMainView();
	const MUI::MUI * getMainView() const;

	KeyFrameTrackController* addKeyFrameTrack(const std::string& name);
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	void setWindow(ofAppBaseWindow* window);
	

protected:
	
	TracksPanel* _panel;
	
	ofAppBaseWindow* _currentWindow = nullptr;
	
	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	
	
	ofEventListeners _mainViewListeners;
	
	void _mainViewMoved(DOM::MoveEventArgs&);
	void _mainViewResized(DOM::ResizeEventArgs&);
	
	
};

} } // ofx::LineaDeTiempo
