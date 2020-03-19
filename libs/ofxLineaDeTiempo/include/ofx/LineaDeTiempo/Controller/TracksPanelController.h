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
//
//
//	No esta heredando correctamente. si uno llama addTrack sobre este objecto se agrega aca pero no al panelView.
//	Como hacer y donde poner el MUI::MUI? Parece que externamente? y que esta clase no herede de TrackGroupController y agregar a esta las funciones para agregar pistas o grupos?
//

	TracksPanelController(const std::string& name);
	
	virtual ~TracksPanelController() = default;
	
	
//	MUI::MUI * getMainView();
//	const MUI::MUI * getMainView() const;

	KeyFrameTrackController* addKeyFrameTrack(const std::string& name);
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	void setWindow(ofAppBaseWindow* window);
	

	
protected:
	
	TracksPanel* _panel = nullptr;
	
	
	ofAppBaseWindow* _currentWindow = nullptr;
	
	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	
	
	ofEventListeners _mainViewListeners;
	
	void _mainViewMoved(DOM::MoveEventArgs&);
	void _mainViewResized(DOM::ResizeEventArgs&);
	
	
};

} } // ofx::LineaDeTiempo
