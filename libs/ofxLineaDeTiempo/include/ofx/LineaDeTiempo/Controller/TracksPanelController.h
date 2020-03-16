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

#include "LineaDeTiempo/View/TracksPanel.h"
#include "ofx/MUI/MUI.h"

namespace ofx {
namespace LineaDeTiempo {


class TracksPanelController
:public TrackGroupController
,public BaseViewController<TracksPanel>

{
public:

	TracksPanelController(const std::string& name);
	
	virtual ~TracksPanelController() = default;
	
	void createMainView(const ofRectangle& viewport = ofRectangle(0,0,ofGetWidth(), ofGetHeight()), ofAppBaseWindow* window = ofGetWindowPtr());
	
	MUI::MUI * getMainView();
	const MUI::MUI * getMainView() const;

protected:
	
	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	
	
};

} } // ofx::LineaDeTiempo
