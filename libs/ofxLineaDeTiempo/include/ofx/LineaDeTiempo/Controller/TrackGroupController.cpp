//
//  TrackGroupController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//
//
#include "LineaDeTiempo/Controller/TrackGroupController.h"
//#include "LineaDeTiempo/Controller/TrackController.h"
//
namespace ofx {
namespace LineaDeTiempo {


//template<typename TrackControllerType, typename TrackGroupViewType>
//
//TrackGroupController<TrackControllerType, TrackGroupViewType>::TrackGroupController(const std::string& name)
//
//:BaseHasTracks<TrackControllerType,true_type>()
//,BaseViewController<TrackGroupViewType>()
//,BaseHasName(name)
//{
//
//}
//
//template<typename TrackControllerType, typename TrackGroupViewType>
//template<template <typename> class NewTrackControllerType, typename NewTrackGroupViewType>
//
//NewTrackControllerType< NewTrackGroupViewType>*
//TrackGroupController<TrackControllerType, TrackGroupViewType>::
//addTrack(const std::string& trackName, bool bCreateFullLengthTrack)
//{
//	static_assert(std::is_base_of<TrackControllerType<>, NewTrackControllerType>::value,
//					  "TrackGroupController::addTrack failed. NewTrackControllerType must be equal or derived from ofx::LineaDeTiempo::TrackController");
//	static_assert(std::is_base_of<TrackGroupViewType, NewTrackGroupViewType>::value,
//				  "TrackGroupController::addTrack failed. TrackControllerType and TrackViewType must inherit from ofx::LineaDeTiempo::TrackController and ofx::LineaDeTiempo::BaseTrack, respectively");
//	
//	auto uniqueName = getUniqueName(trackName, "Track");
////	auto t = _addTrack<TrackControllerType>(uniqueName, this);
//	auto t = addElement<NewTrackControllerType<NewTrackGroupViewType> >(uniqueName, this);
//
//	if(BaseViewController<TrackGroupViewType>::getView()!=nullptr)
//	{
//		t->generateView(getView(), uniqueName, bCreateFullLengthTrack);
////		t->setView(getView()->addTrack<TrackViewType>(uniqueName, bCreateFullLengthTrack, this));
//	}
//	
//	return t;
//}

//template<typename TrackControllerType, typename TrackGroupViewType>
//bool TrackGroupController<TrackControllerType, TrackGroupViewType>::removeTrack(TrackControllerType* track)
//{
//	if(track == nullptr) return false;
//
//	if(BaseViewController<TrackGroupViewType>::getView()!=nullptr)
//	{
//		track->removeView();
//	}
//
//	removeElement(track);
//
//}



//} } // ofx::LineaDeTiempo
