//
//  TracksController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "LineaDeTiempo/Controller/TracksController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

namespace ofx {
namespace LineaDeTiempo {



TracksController::TracksController(const std::string& name)
:BaseViewController<TracksPanel>()
,AbstractHasTracks<TrackController,true_type>()
,BaseHasName(name)
{
	
}

void TracksController::createMainView(const ofRectangle& viewport, ofAppBaseWindow* window)
{
	_mainView = std::make_unique<MUI::MUI>(window);
	_mainView->setShape(viewport);
	BaseViewController<TracksPanel>::createView(_mainView.get(), getName(), viewport, this);
}

template<template <typename> class TrackControllerType, typename TrackViewType>
TrackControllerType<TrackViewType>* TracksController::addTrack(const std::string& trackName, bool bCreateFullLengthTrack)
{
	static_assert(std::is_base_of<TrackController, TrackControllerType<TrackViewType>>::value or
				  std::is_base_of<TrackRegion, TrackViewType>::value,
				  "TracksController::addTrack failed. TrackControllerType and TrackViewType must inherit from ofx::LineaDeTiempo::TrackController and ofx::LineaDeTiempo::BaseTrack, respectively");
	auto uniqueName = getUniqueName(trackName, "Track");
//	auto t = _addTrack<TrackControllerType>(uniqueName, this);
	auto t = addElement<TrackControllerType>(uniqueName, this);

	if(getView()!=nullptr)
	{
		t->setView(getView()->addTrack<TrackViewType>(uniqueName, bCreateFullLengthTrack, this));
	}
	
	return t;
}
bool TracksController::removeTrack(TrackController* track)
{
	if(track == nullptr) return false;
	

	if(getView()!=nullptr)
	{
		getView()->removeTrack(track->getView());
		
	}
	
	removeElement(track);
	
}






} } // ofx::LineaDeTiempo
