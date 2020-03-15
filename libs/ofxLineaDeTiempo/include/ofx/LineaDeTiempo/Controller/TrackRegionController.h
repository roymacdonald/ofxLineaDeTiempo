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
#include "LineaDeTiempo/View/TrackRegionView.h"
#include <type_traits>

namespace ofx {
namespace LineaDeTiempo {


template< template<typename> class RegionControllerType, typename RegionViewType>
class TrackController;

template<typename RegionViewType>
class TrackRegionController:
public BaseViewController<TrackRegion>,
public BaseHasParent<TrackController<TrackRegionController<RegionViewType> > > ,
public BaseHasName
{
public:
	
	TrackRegionController(const std::string& name, TrackController<TrackRegionController<RegionViewType>> * parent);
	
	virtual ~TrackRegionController() = default;
	
	
	
	
protected:
	
//	BaseData* _data;

private:
	
	
};


} } // ofx::LineaDeTiempo
