//
//  KeyframeRegionController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once
#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/KeyframeController.h"
#include "LineaDeTiempo/Controller/KeyframeCollectionController.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"
#include "LineaDeTiempo/View/KeyframeView.h"

#include "LineaDeTiempo/Data/KeyframedData.h"
#include <unordered_map>
namespace ofx {
namespace LineaDeTiempo {

template<typename DataType>
class KeyframeTrackController_;

class TrackController;


template<typename DataType>
class KeyframeRegionController_
: public RegionController


{
public:

	KeyframeRegionController_( const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl);
	
	virtual ~KeyframeRegionController_();
	
	virtual void generateView() override;
	virtual void destroyView() override;


	virtual size_t getNumDimensions() const override;
	
	virtual bool update(uint64_t& t) override;
	

	
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	KeyframesRegionView* getKeyframesRegionView();
	const KeyframesRegionView* getKeyframesRegionView() const;
	
	void removeAllKeyframes();
	
	
	KeyframeTrackController_<DataType>* getParentKeyframeTrack();
	const KeyframeTrackController_<DataType>* getParentKeyframeTrack()const;
	
	
	
protected:
	bool _update(const uint64_t& t, ofParameter<DataType>& param);
	
	friend class KeyframeTrackController_< DataType >;
	friend class KeyframeController<DataType>;
	
	std::vector<KeyframeCollectionController<DataType>* > _collections;
	
	
	
	KeyframeTrackController_<DataType>* _parentTrack = nullptr;
	
private:
	
	
	KeyframesRegionView* _keyframesRegionView = nullptr;
	
};


} } // ofx::LineaDeTiempo
