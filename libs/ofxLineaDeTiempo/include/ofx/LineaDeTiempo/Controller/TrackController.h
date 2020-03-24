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
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "ofRange.h"
#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"
#include "DOM/Node.h"

#include "LineaDeTiempo/Utils/CollectionHelper.h"
#include "LineaDeTiempo/BaseTypes/BaseHasTimeControl.h"

namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TrackGroupController;


class TrackController
: public DOM::Node
, public BaseHasTimeControl
//, public BaseHasRegions<RegionController>
, public BaseViewController<TrackView>

{
public:
	
	//	typedef RegionViewType regionViewType;
	
	TrackController(const std::string& name, TrackGroupController* parent, TimeControl* timeControl);
	
	virtual ~TrackController() = default;
	
	
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	using BaseViewController<TrackView>::getView;
	
	
	
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


	using BaseHasTimeControl::getTimeControl;
	

	void enableTimeUpdate();
	void disableTimeUpdate();
	bool isUpdatingTime();
	
	virtual void update(uint64_t& t) = 0;
	
protected:
	
	
	
	NamedConstPointerCollection<RegionController> _regionsCollection;

	

	template<typename NewRegionControllerType>//, typename NewRegionViewType>
	NewRegionControllerType * _addRegion( const std::string& regionName, const ofRange64u& timeRange)
	{
		
		
				auto uniqueName = _regionsCollection.makeUniqueName(regionName, "Region");
		
		return CollectionHelper::
		
		_add < NewRegionControllerType, TrackController, RegionController >
		
		( _regionsCollection, this, uniqueName, timeRange, this, getTimeControl());
		
	}

	
	bool _removeRegion(RegionController* track);

//	TrackGroupController * _parentGroup = nullptr;
	
	TrackGroupView* _getTrackGroupView();
//
	template<typename ViewType>
	void _generateView()
	{
		static_assert(std::is_base_of<TrackView, ViewType>::value, "TrackController::_generateView: template type ViewType must be equal to ofx::LineaDeTiempo::TrackView or derived from it");
		if(getView()) return;
		auto view = _getTrackGroupView();
		if(view)
		{
			setView(view->addTrack<ViewType>(this));

		}

		generateChildrenViews(this);
	}
	
	
private:
	ofEventListener _timeChangedListener;
	bool _bListeningTimeChange = false;
	
	
	
	
};


} } // ofx::LineaDeTiempo
