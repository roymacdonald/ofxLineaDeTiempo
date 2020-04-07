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
#include <unordered_map>




#include "LineaDeTiempo/Controller/BaseController.h"


#include <type_traits>
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"
#include "LineaDeTiempo/Utils/ofxTypeTraits.h"
#include "LineaDeTiempo/Utils/ParamHelper.h"

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
	
	typedef  typename std::conditional<is_multi_dim_param<RegionDataType>::value, float, RegionDataType>::type innerDataType;
	
	
	KeyframeCollectionController( KeyframeRegionController_<RegionDataType> * parentRegion, size_t dimensionIndex );
	
	virtual ~KeyframeCollectionController() = default;
	
	KeyframeController<RegionDataType>* addKeyframe(innerDataType value, uint64_t time)
	{
		
		
		auto d = _keyframedData.add(value, time);
		
		
		auto k = addChild<KeyframeController<RegionDataType>>( "k_"+ofToString(_dimensionIndex)+"_"+ofToString(_keyframedData.size()), d, this );
		
		_keyframes.push_back(k);
		
		if(getView())
		{
			k->generateView();
			_keyframesViewMap[k->getView()] = k;
		}
		
		return k;
	}
	
	
	
	
	bool removeKeyframe(KeyframeController<RegionDataType>* keyframe);
	
	void removeAllKeyframes();
	
	innerDataType unnormalizeValue(float val)
	{
		return ParamHelper::getUnnormalized<RegionDataType>(val,
															_dimensionIndex,
															_parentRegion->getParentKeyframeTrack()->getParameter());
	}
	float normalizeValue(innerDataType val)
	{
		return ParamHelper::getNormalized<RegionDataType>(val,
														  _dimensionIndex,
														  _parentRegion->getParentKeyframeTrack()->getParameter());
		
	}
	
	const KeyframedData_<innerDataType>& getKeyframedData() const
	{
		return _keyframedData;
	}
	
	
	///\brief Returns true if the value was updated
	bool update(const uint64_t& t, RegionDataType& param);
	
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	const innerDataType& getCurrentValue() const
	{
		return _keyframedData.getCurrentValue();
	}
	
	const size_t& getDimensionIndex()const;
	
	
	
protected:
	
	
	
	size_t _dimensionIndex = 1;
	
	
	ofEventListener addKeyframeListener;
	void _addKeyframeEventCB(AddKeyframeEventArgs& args);
	
	ofEventListener removeKeyframeListener;
	void _removeKeyframeEventCB(RemoveKeyframesEventArgs& args);
	
	KeyframedData_<innerDataType> _keyframedData;
	
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


} } // ofx::LineaDeTiempo
