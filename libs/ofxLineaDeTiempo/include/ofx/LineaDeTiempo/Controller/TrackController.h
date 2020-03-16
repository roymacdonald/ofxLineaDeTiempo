//
//  TrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/BaseController.h"

#include "LineaDeTiempo/BaseTypes/BaseHasRegions.h"
#include "LineaDeTiempo/Controller/RegionController.h"

#include "LineaDeTiempo/View/TrackView.h"
#include "ofRange.h"

//#include <utility>
//#include <type_traits>

namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TrackGroupController;


//template< template<typename> class RegionControllerType, typename RegionViewType>
class TrackController
: public BaseController
, public BaseHasRegions<RegionController>
//, public BaseViewController<TrackView>

{
public:
	
	//	typedef RegionViewType regionViewType;
	
	TrackController(const std::string& name, TrackGroupController* parent);
	
	virtual ~TrackController() = default;
	
	
	template<typename NewRegionControllerType>//, typename NewRegionViewType>
	NewRegionControllerType * addRegion( const std::string& regionName, const ofRange64u& timeRange);
	
	virtual bool removeRegion(RegionController* track) override;
	
//	using BaseViewController<TrackView>::getView;
//
//	using BaseViewController<TrackView>::setView;
//
	
	using BaseHasRegions<RegionController>::removeRegion;
	
	using BaseHasRegions<RegionController>::getRegion;
	
	using BaseHasRegions<RegionController>::getRegions;
	
	using BaseHasRegions<RegionController>::getNumRegions;
	
	
	TrackGroupController * parentGroup();
	
	const TrackGroupController * parentGroup() const;
	
protected:
	
	TrackGroupController * _parentGroup = nullptr;
	
	
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
