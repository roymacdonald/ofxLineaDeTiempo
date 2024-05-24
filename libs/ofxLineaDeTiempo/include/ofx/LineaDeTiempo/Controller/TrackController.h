//
//  TrackController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/8/20.
//

#pragma once

#include "LineaDeTiempo/Controller/BaseController.h"

#include "LineaDeTiempo/Controller/RegionController.h"

#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "ofRange.h"
#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"

#include "LineaDeTiempo/Utils/CollectionHelper.h"

#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"

namespace ofx {
namespace LineaDeTiempo {

//parent type forward declaration
class TrackGroupController;


class TrackController
: public BaseController<TrackView>
, public AbstractSerializable

{
public:
	
	//	typedef RegionViewType regionViewType;
	
	TrackController(const std::string& name, TrackGroupController* parent, TimeControl* timeControl);
	
	virtual ~TrackController();
	
	virtual void destroyView() override;
	

	bool removeRegion(RegionController* track);
	
	
	bool removeRegion(const std::string& name);
	
	
	bool removeRegion(const size_t& index);
	
	
	RegionController* getRegion(const std::string& name);
	
	
	const RegionController* getRegion(const std::string& name) const;
	
	
	RegionController* getRegion(const size_t& index);
	
	
	const RegionController* getRegion(const size_t& index)const;
	
	
	const std::vector<RegionController*>& getRegions();
	
	
	const std::vector<const RegionController*>& getRegions() const;
	
	
	size_t getNumRegions() const;
	
	
	
	
	void enableTimeUpdate();
	
	void disableTimeUpdate();
	
	bool isUpdatingTime();
	
	void update(uint64_t& t);
	
	
	const size_t& getCurrentRegionIndex() const;
	

	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;

	
				
protected:
	
	
	
	size_t _currentRegion = 0;
	
	
	NamedConstPointerCollection<RegionController> _regionsCollection;
	
	
	
	template<typename NewRegionControllerType>//, typename NewRegionViewType>
	NewRegionControllerType * _addRegion( const std::string& regionName, const ofRange64u& timeRange)
	{
		
		auto uniqueName = _regionsCollection.makeUniqueName(regionName, "Region");
		
		return CollectionHelper::
		
		_add < NewRegionControllerType, TrackController, RegionController >
		
		( _regionsCollection, this, uniqueName, timeRange, this, getTimeControl());
		
	}
	

	/// as regions need to be templated, in order to avoid the parsing of the data type I'll delegate it to the derived class which already "know" which templated type to use.
	virtual void _addRegionFromJson(const std::string& name, ofJson j)= 0;
	

	
	TrackGroupView* _getTrackGroupView();

	
	void _findCurrentRegion();
	void _resetCurrentRegion();
	void _findRegionAtCurrentTime(const size_t& startIndex);

	
	ofEventListeners _timeControlListeners;

	void _makeFromJson(const ofJson& json);
	
private:
	ofEventListener _timeChangedListener;
	bool _bListeningTimeChange = false;
	
	
	
	
};


} } // ofx::LineaDeTiempo
