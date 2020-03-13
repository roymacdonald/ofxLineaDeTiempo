////
////  TracksController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/6/20.
////
//
#pragma once
#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/AbstractHasTracks.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"

#include "LineaDeTiempo/Controller/TrackController.h"

#include "LineaDeTiempo/View/TracksPanel.h"
#include "ofx/MUI/MUI.h"

namespace ofx {
namespace LineaDeTiempo {


class TracksController
:public AbstractHasTracks<TrackController,true_type>
,public BaseViewController<TracksPanel>
,public BaseHasName
{
public:

	TracksController(const std::string& name);
	
	virtual ~TracksController() = default;
	
	void createMainView(const ofRectangle& viewport = ofRectangle(0,0,ofGetWidth(), ofGetHeight()), ofAppBaseWindow* window = ofGetWindowPtr());
	
	template<template <typename> class TrackControllerType, typename TrackViewType>
	TrackControllerType<TrackViewType>* addTrack( const std::string& trackName = "", bool bCreateFullLengthTrack = true);


	virtual bool removeTrack(TrackController* track) override;

protected:
	
	std::unique_ptr<MUI::MUI> _mainView = nullptr;
	
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
