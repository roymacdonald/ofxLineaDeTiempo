//
//  KeyframeCollectionController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/31/20.

#pragma once

#include "LineaDeTiempo/Controller/KeyframeController.h"


#include "LineaDeTiempo/View/KeyframeView.h"

#include "LineaDeTiempo/View/KeyframeCollectionView.h"

#include "LineaDeTiempo/Data/KeyframedData.h"
//#include "LineaDeTiempo/Data/Keyframed.h"
#include <unordered_map>




#include "LineaDeTiempo/Controller/BaseController.h"


#include <type_traits>
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"
#include "LineaDeTiempo/Utils/ofxTypeTraits.h"
#include "LineaDeTiempo/Utils/ParamHelper.h"
#include "ofRange.h"

namespace ofx {
namespace LineaDeTiempo {


template<typename DataType>
class KeyframeRegionController_;



template<typename RegionDataType>
class KeyframeCollectionController
: public BaseController<KeyframeCollectionView>
, public AbstractSerializable
{
public:
	
	typedef  typename std::conditional<is_multi_dim_param<RegionDataType>::value , float, RegionDataType>::type innerDataType;

	
	typedef KeyframedData_<innerDataType> KeyframedDataType;
	
	KeyframeCollectionController( KeyframeRegionController_<RegionDataType> * parentRegion, size_t dimensionIndex );
	
	virtual ~KeyframeCollectionController();

	
	KeyframeController<RegionDataType>* addKeyframe(innerDataType value, uint64_t time);
	
	void sortData();
	
	bool removeKeyframe(KeyframeController<RegionDataType>* keyframe);
	
	void removeAllKeyframes();
	
	innerDataType unnormalizeValue(float val);
	
	float normalizeValue(innerDataType val);
	
	const KeyframedDataType& getKeyframedData() const
	{
		return _keyframedData;
	}
	
	
	///\brief Returns true if the value was updated
	template<typename T>
	bool update(const uint64_t& t, T& param)
	{
//		if(
		_keyframedData.update(t);//)
//		{
			return _paramNeedsUpdate(param);
//		}
		return false;
	}
	

	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	const innerDataType& getCurrentValue() const;
//	{
//		return _keyframedData.getCurrentValue();
//	}
//
	const size_t& getDimensionIndex()const;
	
	void setTimeRange(const ofRange64u& timeRange);
	
	void moveAllKeyframesByTime(const uint64_t & _timeOffset);
	
	KeyframeController<RegionDataType>* getKeyframeAtTime(const uint64_t & time);
	KeyframeController<RegionDataType>* getKeyframeByIndex(const size_t & index);
	
	
protected:
	
	
	
	size_t _dimensionIndex = 1;
	
	
	ofEventListener addKeyframeListener;
	void _addKeyframeEventCB(AddKeyframeEventArgs& args);
	
	ofEventListener removeKeyframeListener;
	void _removeKeyframeEventCB(RemoveKeyframesEventArgs& args);
	
	KeyframedDataType _keyframedData;
	
	std::vector<KeyframeController<RegionDataType>* > _keyframes;
	
	std::unordered_map<KeyframeView*, KeyframeController<RegionDataType>*>_keyframesViewMap;
	
	
	KeyframeRegionController_<RegionDataType> * _parentRegion = nullptr;
	
	template<typename D>
	inline typename std::enable_if<is_multi_dim_param<D>::value  and std::is_floating_point<D>::value, bool>::type
	_paramNeedsUpdate(D& param){
		auto& d = _keyframedData.getCurrentValue();
		if(! ofIsFloatEqual(param[_dimensionIndex],  d))
		{
			param[_dimensionIndex] =  d;
			return true;
		}
		return false;
	}
	
	template<typename D>
	inline typename std::enable_if<is_multi_dim_param<D>::value and not std::is_floating_point<D>::value, bool>::type
	_paramNeedsUpdate(D& param){
		auto& d = _keyframedData.getCurrentValue();
		if(param[_dimensionIndex] !=  d)
		{
			param[_dimensionIndex] =  d;
			return true;
		}
		return false;
	}
	
	
	static bool compareKeyframeControlers(KeyframeController<RegionDataType>*a, KeyframeController<RegionDataType>*b);
	
	
	template<typename D>
	inline typename std::enable_if<not is_multi_dim_param<D>::value  and not std::is_floating_point<D>::value, bool>::type
	_paramNeedsUpdate(D& param){
		if(param !=  _keyframedData.getCurrentValue())
		{
			param =  _keyframedData.getCurrentValue();
			return true;
		}
		return false;
	}
	
	template<typename D>
	inline typename std::enable_if<not is_multi_dim_param<D>::value  and std::is_floating_point<D>::value, bool>::type
	_paramNeedsUpdate(D& param){
		if(! ofIsFloatEqual(param,  _keyframedData.getCurrentValue()))
		{
			param =  _keyframedData.getCurrentValue();
			return true;
		}
		return false;
	}
	
	
	
	
	
private:
	
	
};




template<>
class KeyframeCollectionController<void>
: public BaseController<KeyframeCollectionView>
, public AbstractSerializable
{
public:
	
	
	KeyframeCollectionController( KeyframeRegionController_<void> * parentRegion);
	
	virtual ~KeyframeCollectionController();

	
	KeyframeController<void>* addKeyframe(uint64_t time);
	
	void sortData();
	
	bool removeKeyframe(KeyframeController<void>* keyframe);
	
	void removeAllKeyframes();
	
	
	const KeyframedData_<void>& getKeyframedData() const
	{
		return _keyframedData;
	}
	
	
	bool update(const uint64_t& t, ofParameter<void>& param);
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	virtual void generateView() override;
	virtual void destroyView() override;
		
	void setTimeRange(const ofRange64u& timeRange);
	
	void moveAllKeyframesByTime(const uint64_t & _timeOffset);
	
	KeyframeController<void>* getKeyframeAtTime(const uint64_t & time);
	KeyframeController<void>* getKeyframeByIndex(const size_t & index);
	
	
protected:
	
	
	
	// size_t _dimensionIndex = 1;
	
	
	ofEventListener addKeyframeListener;
	void _addKeyframeEventCB(AddKeyframeEventArgs& args);
	
	ofEventListener removeKeyframeListener;
	void _removeKeyframeEventCB(RemoveKeyframesEventArgs& args);
	
	KeyframedData_<void> _keyframedData;
	
	std::vector<KeyframeController<void>* > _keyframes;
	
	std::unordered_map<KeyframeView*, KeyframeController<void>*>_keyframesViewMap;
	
	
	KeyframeRegionController_<void> * _parentRegion = nullptr;

	static bool compareKeyframeControlers(KeyframeController<void>*a, KeyframeController<void>*b);
	
	
private:
	
	
};













} } // ofx::LineaDeTiempo
