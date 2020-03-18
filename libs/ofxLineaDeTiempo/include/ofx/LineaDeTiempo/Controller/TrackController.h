//
//  TrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/BaseController.h"

//#include "LineaDeTiempo/BaseTypes/BaseHasRegions.h"
#include "LineaDeTiempo/Controller/RegionController.h"

#include "LineaDeTiempo/View/TrackView.h"
#include "ofRange.h"
#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"

namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TrackGroupController;


class TrackController
: public BaseController
//, public BaseHasRegions<RegionController>
, public BaseViewController<TrackView>

{
public:
	
	//	typedef RegionViewType regionViewType;
	
	TrackController(const std::string& name, TrackGroupController* parent);
	
	virtual ~TrackController() = default;
	
	
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	using BaseViewController<TrackView>::getView;
	
	
	TrackGroupController * parentGroup();
	
	const TrackGroupController * parentGroup() const;
	
	
	 bool removeRegion(const std::string& name)
	 {
	 	 return _removeRegion(_regionsCollection.at(name));
	 }

	 bool removeRegion(const size_t& index)
	 {
	 	 return _removeRegion(_regionsCollection.at(index));
	 }

	 RegionController* getRegion(const std::string& name)
	 {
	 	 return _regionsCollection.at(name);
	 }

	 const RegionController* getRegion(const std::string& name) const
	 {
	 	 return _regionsCollection.at(name);
	 }

	 RegionController* getRegion(const size_t& index)
	 {
	 	 return _regionsCollection.at(index);
	 }

	 const RegionController* getRegion(const size_t& index)const
	 {
		 return _regionsCollection.at(index);
	 }

	 const std::vector<RegionController*>& getRegions()
	 {
	 	return _regionsCollection.getCollection();
	 }

	 const std::vector<const RegionController*>& getRegions() const
	 {
		 return _regionsCollection.getCollection();
	 }

	 size_t getNumRegions() const
	 {
		 return _regionsCollection.size();
	 }


	
	
		
	protected:
		
		NamedConstPointerCollection<RegionController> _regionsCollection;

	

	template<typename NewRegionControllerType>//, typename NewRegionViewType>
	NewRegionControllerType * _addRegion( const std::string& regionName, const ofRange64u& timeRange)
	{
		
		auto uniqueName = _regionsCollection.makeUniqueName(regionName, "Region");
		
		return BaseController::
		
		_add < NewRegionControllerType, RegionController >
		
		( _regionsCollection, uniqueName, timeRange, this);
		
	}

	
	bool _removeRegion(RegionController* track);

	TrackGroupController * _parentGroup = nullptr;
	
private:
	
	
};


} } // ofx::LineaDeTiempo
