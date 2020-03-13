//
//  TrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
#include "LineaDeTiempo/BaseTypes/BaseHasParent.h"
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
#include "LineaDeTiempo/BaseTypes/AbstractHasRegions.h"

#include "LineaDeTiempo/Controller/TrackRegionController.h"
//#include "LineaDeTiempo/BaseTypes/BaseTrackController.h"
#include "LineaDeTiempo/View/TrackRegion.h"
#include "LineaDeTiempo/View/Track.h"
#include "ofRange.h"

#include <utility>
#include <type_traits>

namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TracksController;


class BaseTrackController
:public BaseHasParent<TracksController>
,public BaseViewController<BaseTrack>
,public BaseHasName
{
public:
	BaseTrackController(const std::string& name, const std::string& trackViewTypeName, TracksController* parent);
	~BaseTrackController() = default;
	
};

class TrackController
:public BaseTrackController
,public AbstractHasRegions<TrackRegionController, std::true_type>
{
public:

//	typedef RegionViewType regionViewType;
	
	TrackController(const std::string& name, const std::string& trackViewTypeName, TracksController* parent);
	
	virtual ~TrackController() = default;

	
	
	template< template<typename> class RegionControllerType, typename RegionViewType>
	RegionControllerType<RegionViewType>* addRegion(std::string name, const ofRange64u & timeRange)
	{
		static_assert(std::is_base_of<TrackRegionController, RegionControllerType<RegionViewType>>::value or
					  std::is_base_of<TrackRegion, RegionViewType>::value,
					  "TracksController::addTrack failed. TrackControllerType and TrackViewType must inherit from ofx::LineaDeTiempo::TrackController and ofx::LineaDeTiempo::BaseTrack, respectively");
		auto uniqueName = getUniqueName(name, "Region");
	//	auto t = _addTrack<TrackControllerType>(uniqueName, this);
		auto t = addElement<RegionControllerType<RegionViewType>>(uniqueName, this);

		if(getView()!=nullptr)
		{
			t->setView(getView()->addRegion<RegionViewType>(uniqueName, timeRange, this));
		}

		return t;
	}

	template< template<typename> class RegionControllerType, typename RegionViewType>
	RegionControllerType<RegionViewType>* addRegion( const ofRange64u & timeRange)
	{
		return this->addRegion<RegionControllerType<RegionViewType>, RegionViewType>("", timeRange);
	}
	
	
	virtual bool removeRegion(TrackRegionController* region) override
	{
		if(region == nullptr) return false;


		if(getView()!=nullptr)
		{
			getView()->removeRegion(region->getView());

		}

		removeElement(region);

	}
	
	
protected:
	
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
