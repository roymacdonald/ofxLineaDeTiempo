////
////  TrackRegionController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/6/20.
////
//
#pragma once
#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
#include "LineaDeTiempo/BaseTypes/BaseHasParent.h"
//#include "LineaDeTiempo/BaseTypes/BaseData.h"
//#include "LineaDeTiempo/Controller/TrackRegionController.h"
#include "LineaDeTiempo/View/TrackRegion.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackController;


class TrackRegionController:
public BaseViewController<TrackRegion>,
public BaseHasParent<TrackController>,
public BaseHasName
{
public:
	
	TrackRegionController(const std::string& name, TrackController * parent);
	
	virtual ~TrackRegionController() = default;
	
	
	
	
protected:
	
//	BaseData* _data;

private:
	
	
};


} } // ofx::LineaDeTiempo
