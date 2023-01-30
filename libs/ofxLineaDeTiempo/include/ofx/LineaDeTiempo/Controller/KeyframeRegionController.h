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
	
	virtual void setTimeRange(const ofRange64u& t, bool updateView = true) override;
	
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	KeyframesRegionView* getKeyframesRegionView();
	const KeyframesRegionView* getKeyframesRegionView() const;
	
	void removeAllKeyframes();
	
	
	KeyframeTrackController_<DataType>* getParentKeyframeTrack();
	const KeyframeTrackController_<DataType>* getParentKeyframeTrack()const;
	
	const std::vector<KeyframeCollectionController<DataType>* >& getKeyframesCollection() const;
	
	template<typename T = DataType>
	typename std::enable_if< (not std::is_void<T>::value and (type_dimensions<T>::value > 1)),  KeyframeController<T>* >::type
	addKeyframe(const T& data,  uint64_t time )
	{
		/// the following static assert is simply to make sure that the functions template is the same a the class' DataType
		/// This is done because enable if only works with templated functions
		static_assert(std::is_same<T, DataType>(), "Cannot add keyframe with a different data type");
		
		bool bRet = false;
		for(size_t i = 0; i < this->_collections.size(); i++)
		{
			if(this->_collections[i]) {
				bRet &= (this->_collections[i]->addKeyframe(data[i], time) != nullptr);
			}
		}
		return bRet;
	}
	
	template<typename T = DataType>
	typename std::enable_if< not std::is_void<T>::value and type_dimensions<T>::value == 1,  KeyframeController<T>* >::type
	addKeyframe(const T& data,  uint64_t time )
	{
		static_assert(std::is_same<T, DataType>(), "Cannot add keyframe with a different data type");
		
		if(this->_collections.size() && this->_collections[0]) {
            return this->_collections[0]->addKeyframe(data, time);
		}
		return nullptr;
	}
	
	template<typename T = DataType>
	typename std::enable_if<std::is_void<T>::value,   KeyframeController<T>* >::type
	addKeyframe( uint64_t time )
	{
		static_assert(std::is_same<T, DataType>(), "Cannot add keyframe with a different data type");
		
		if(this->_collections.size() && this->_collections[0]) {
			return (this->_collections[0]->addKeyframe(time));
			
		}
		return nullptr;
	}
	
	
	bool removeKeyFrameAtTime(const uint64_t& time);
	
	
	
	
	
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
