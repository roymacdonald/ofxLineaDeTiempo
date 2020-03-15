//
//  TrackGroupController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//

#pragma once
#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/AbstractHasTracks.h"
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
#include "LineaDeTiempo/"


#include "LineaDeTiempo/View/TrackGroupView.h"


namespace ofx {
namespace LineaDeTiempo {


template<TrackControllerType, typename TrackGroupViewType>

class TrackGroupController

:public AbstractHasTracks<TrackControllerType,true_type>
,public BaseViewController<TrackGroupViewType>
,public BaseHasName
{
public:

	typedef TrackGroupViewType trackGroupViewType;
	typedef TrackControllerType trackControllerType;
	
	
	
	TrackGroupController(const std::string& name)
	:AbstractHasTracks<TrackControllerType,true_type>()
	,BaseViewController<TrackGroupViewType>()
	,BaseHasName(name)
	{
	}
	
	virtual ~TrackGroupController() = default;
	
	template<template <typename> class NewTrackControllerType, typename NewTrackViewType>
	NewTrackControllerType<NewTrackGroupViewType> * addTrack( const std::string& trackName = "", bool bCreateFullLengthTrack = true)
	{
		static_assert(std::is_base_of<TrackControllerType, NewTrackControllerType<NewTrackViewType> >::value,
						  "TrackGroupController::addTrack failed. NewTrackControllerType must be equal or derived from ofx::LineaDeTiempo::TrackController");
//		static_assert(std::is_base_of<TrackGroupViewType, NewTrackGroupViewType>::value,
//					  "TrackGroupController::addTrack failed. TrackControllerType and TrackViewType must inherit from ofx::LineaDeTiempo::TrackController and ofx::LineaDeTiempo::BaseTrack, respectively");
//
		auto uniqueName = getUniqueName(trackName, "Track");
	//	auto t = _addTrack<TrackControllerType>(uniqueName, this);
		auto t = addElement<NewTrackControllerType<NewTrackGroupViewType> >(uniqueName, this);

		if(BaseViewController<TrackGroupViewType>::getView()!=nullptr)
		{
			t->generateView(getView(), uniqueName, bCreateFullLengthTrack);
	//		t->setView(getView()->addTrack<TrackViewType>(uniqueName, bCreateFullLengthTrack, this));
		}
		
		return t;
	}

	// this is overriding a pure virtual function
	virtual bool removeTrack(TrackControllerType* track) override
	{
		if(track == nullptr) return false;
		
		if(BaseViewController<TrackGroupViewType>::getView()!=nullptr)
		{
			track->removeView();
		}
		
		removeElement(track);
		
	}

	
protected:
	
	
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
