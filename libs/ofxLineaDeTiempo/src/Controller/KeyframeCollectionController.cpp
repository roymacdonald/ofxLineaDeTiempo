//
//  KeyframeCollectionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/31/20.
//


#include "LineaDeTiempo/Controller/KeyframeCollectionController.h"
#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Utils/ofxTypeTraits.h"
#include "LineaDeTiempo/Utils/ConstVars.h"

#include "ofMath.h"

namespace ofx {
namespace LineaDeTiempo {


template<typename D>
KeyframeCollectionController<D>::KeyframeCollectionController( KeyframeRegionController_<D> * parentRegion, size_t dimensionIndex )
: BaseController(GetNameForDimension(dimensionIndex, type_dimensions<D>::value) , parentRegion, parentRegion->getTimeControl())
, _parentRegion(parentRegion)
, _dimensionIndex(dimensionIndex)
{
	
	_dataTypeName = typeid(D).name();

	
}


template<typename D>
KeyframeCollectionController<D>::~KeyframeCollectionController()
{
	destroyView();
}


template<typename D>
KeyframeController<D>* KeyframeCollectionController<D>::addKeyframe(KeyframeCollectionController<D>::innerDataType value, uint64_t time)
{
	
	
	auto d = _keyframedData.add(value, time);
	
	if(d){
		auto k = addChild<KeyframeController<D>>( "k_"+ofToString(_dimensionIndex)+"_"+ofToString(_keyframedData.size()), d, this );
		
		_keyframes.push_back(k);
		
		
		if(getView())
		{
			k->generateView();
			_keyframesViewMap[k->getView()] = k;
		}
		sortData();
		return k;
	}
	return nullptr;
}

template<typename D>
bool KeyframeCollectionController<D>::removeKeyframe(KeyframeController<D>* keyframe)
{
	if(keyframe->getView())
	{
		_keyframesViewMap.erase(keyframe->getView());
		keyframe->destroyView();
	}
	
	_keyframedData.remove(keyframe->getData());
	ofRemove(_keyframes, [&](KeyframeController<D>* k){
		return k == keyframe;
	});
	
	
	return (removeChild(keyframe) != nullptr);
	
	
	
}

template<typename D>
void KeyframeCollectionController<D>::removeAllKeyframes()
{
	DOM::Node::removeAllChildren();
	_keyframedData.clear();
	_keyframesViewMap.clear();
	_keyframes.clear();
}


template<typename D>
const size_t& KeyframeCollectionController<D>::getDimensionIndex()const
{
	return _dimensionIndex;
}

template<typename D>
void KeyframeCollectionController<D>::generateView()
{
	if(getView() == nullptr){
		auto p = _parentRegion;
		if(p && p->getKeyframesRegionView())
		{
			
			auto views = p->getKeyframesRegionView()->getViews();
			if(_dimensionIndex < views.size())
			{
				setView(views[_dimensionIndex]);
				
				auto cv = views[_dimensionIndex];
				
				if(cv){
					addKeyframeListener = cv -> addKeyframeEvent.newListener(this,&KeyframeCollectionController<D>::_addKeyframeEventCB);
					
					removeKeyframeListener = cv->removeKeyframeEvent.newListener(this, &KeyframeCollectionController<D>::_removeKeyframeEventCB);
				}
			}
		}
		
		generateChildrenViews(this);
		_keyframesViewMap.clear();
		for(auto k: _keyframes)
		{
			if(k && k->getView())
			{
				_keyframesViewMap[k->getView()] = k;
			}
		}
	}
}

template<typename D>
void KeyframeCollectionController<D>::destroyView()
{
	if(getView()){
		destroyChildrenViews(this);
		_keyframesViewMap.clear();
		
		addKeyframeListener.unsubscribe();
		removeKeyframeListener.unsubscribe();
		setView(nullptr);
	}
}


template<typename D>
void KeyframeCollectionController<D>::_addKeyframeEventCB(AddKeyframeEventArgs& args)
{
	

	
	if(_parentRegion && _parentRegion->getParentKeyframeTrack())
	{
//		std::cout << "_addKeyframeEventCB :  args.normalizedValue: "  << args.normalizedValue  << "\n";
		
//		std::cout << "KeyframeCollectionController<D>::_addKeyframeEventCB   value: " << args.normalizedValue << "  time: " << args.time
		
//		ss	<< "unnormalized: " <<  ParamHelper::getUnnormalized(args.normalizedValue, _dimensionIndex, _parentRegion->getParentKeyframeTrack()->getParameter()) << "\n";
	
		addKeyframe( ParamHelper::getUnnormalized(args.normalizedValue,
												  _dimensionIndex,
												  _parentRegion->getParentKeyframeTrack()->getParameter())
					, args.time);
	
//	KeyframeCollectionView::debugString += ss.str();
	}
}

template<typename D>
bool KeyframeCollectionController<D>::compareKeyframeControlers(KeyframeController<D>*a, KeyframeController<D>*b)
{
	return a->getData()->time < b->getData()->time ;
}
template<typename D>
void KeyframeCollectionController<D>::sortData()
{
	ofSort(_keyframes, KeyframeCollectionController<D>::compareKeyframeControlers);
	
	_keyframedData.sortData();
	
	if(getView()) getView()->updateKeyframeSort();
	
}

template<typename D>
void KeyframeCollectionController<D>::_removeKeyframeEventCB(RemoveKeyframesEventArgs& args)
{
	for(auto k: args.keyframes){
		if(!k)
		{
			ofLogWarning("KeyframeCollectionController<D>::_removeKeyframeEventCB") << "failed because a nullptr was passed to it. This should not happen.";
			continue;
		}
		if(_keyframesViewMap.count(k))
		{
			removeKeyframe(_keyframesViewMap[k]);
		}
	}
}
template<typename D>
typename KeyframeCollectionController<D>::innerDataType KeyframeCollectionController<D>::unnormalizeValue(float val)
{
	return ParamHelper::getUnnormalized<D>(val,
											_dimensionIndex,
											_parentRegion->getParentKeyframeTrack()->getParameter());
}

template<typename D>
float KeyframeCollectionController<D>::normalizeValue(KeyframeCollectionController<D>::innerDataType val)
{
	return ParamHelper::getNormalized<D>(val,
										_dimensionIndex,
										_parentRegion->getParentKeyframeTrack()->getParameter());
}

template<>
bool KeyframeCollectionController<bool>::unnormalizeValue(float val)
{
	return round(val);
}

template<>
float KeyframeCollectionController<bool>::normalizeValue(bool val)
{
	return (val?1.0f:0.0f );
}

template<typename D>
const typename  KeyframeCollectionController<D>::innerDataType& KeyframeCollectionController<D>::getCurrentValue() const
{
	return _keyframedData.getCurrentValue();
}


template<typename D>
KeyframeController<D>* KeyframeCollectionController<D>::getKeyframeAtTime(const uint64_t & time)
{
	for(auto k : _keyframes)
	{
		
		// TODO : the data has a table with the times of each keyframe, so there is no need to iterate over all these. Make use of it.
		if(k && k -> getData() && (k -> getData()->time ) == time  )
		{
			return k;
		}
	}
	return nullptr;
}
template<typename D>
KeyframeController<D>* KeyframeCollectionController<D>::getKeyframeByIndex(const size_t & index)
{
	if(index >= _keyframes.size()) return nullptr;
	return _keyframes[index];
}








//



//template<>
//float KeyframeCollectionController<void>::unnormalizeValue(float val)
//{
//	return val;
//}
//
//template<>
//float KeyframeCollectionController<void>::normalizeValue(float val)
//{
//	return 0;
//}
//



template<typename D>
void KeyframeCollectionController<D>::fromJson(const ofJson& j)
{
	
//	std::cout << "KeyframeCollectionController<D>::fromJson\n";
	
	setId(j["name"]);
	
	if(j.count("_keyframedData")== 0 || j.count("_dataTypeName") == 0)
	{
		ofLogError("KeyframeCollectionController<T>::fromJson") << "failed. Malformed json. DataTypeName or keyframedData elements not present";
		return;
	}
	auto dt = j["_dataTypeName"].get<std::string>();
	
	if(dt != getDataTypeName())
	{
		ofLogError("KeyframeCollectionController<T>::fromJson") << "failed. DataType seems to be different to the one saved on file";
		return;
	}
	
	removeAllKeyframes();
	
	KeyframedData_<KeyframeCollectionController<D>::innerDataType> key_data;
	
	key_data.fromJson(j["_keyframedData"]);
	
	for(auto& d: key_data.getData())
	{
		addKeyframe(d->value, d->time);
	}
}

template<typename D>
ofJson KeyframeCollectionController<D>::toJson()
{
	ofJson j;
	j["class"] = "KeyframeCollectionController";
	j["name"] = getId();
	j["_dataTypeName"] = _dataTypeName;
	
	
	j["_keyframedData"] = _keyframedData.toJson();
	
	
	return j;
	
}

template<typename D>
void KeyframeCollectionController<D>::setTimeRange(const ofRange64u& timeRange)
{
	_keyframedData.setTimeRange(timeRange);
}

//template<typename D>
//void KeyframeCollectionController<D>::moveAllKeyframesByTime(const uint64_t & _timeOffset)
//{
//	_keyframedData.moveAllByTime(_timeOffset);
//	if(getView()) getView()->updateLayout();
//}

//template<typename D>
//const D& KeyframeCollectionController<D>::getCurrentValue() const
//{
//	return _keyframedData.getCurrentValue();
//}
//
//template<typename D>
//D KeyframeCollectionController<D>::unnormalizeValue(float val)
//{
//	return ParamHelper::getUnnormalized<D>(val,
//										_dimensionIndex,
//										_parentRegion->getParentKeyframeTrack()->getParameter());
//}

//template<typename D>
//float KeyframeCollectionController<D>::normalizeValue(D val)
//{
//	return ParamHelper::getNormalized<D>(val,
//	_dimensionIndex,
//	_parentRegion->getParentKeyframeTrack()->getParameter());
//
//
//}



KeyframeCollectionController<void>::KeyframeCollectionController( KeyframeRegionController_<void> * parentRegion)
: BaseController(parentRegion->getId() , parentRegion, parentRegion->getTimeControl())
, _parentRegion(parentRegion)
{
	
	_dataTypeName = typeid(void).name();

}



KeyframeCollectionController<void>::~KeyframeCollectionController()
{
	destroyView();
}



KeyframeController<void>* KeyframeCollectionController<void>::addKeyframe( uint64_t time)
{
	
	
	auto d = _keyframedData.add(time);
	
	if(d){
		auto k = addChild<KeyframeController<void>>( "k_"+ofToString(_keyframedData.size()), d, this );
		
		_keyframes.push_back(k);
		
		if(getView())
		{
			k->generateView();
			_keyframesViewMap[k->getView()] = k;
		}
		sortData();
		return k;
	}
	return nullptr;
}


bool KeyframeCollectionController<void>::removeKeyframe(KeyframeController<void>* keyframe)
{
	
	
	
	if(keyframe->getView())
	{
		_keyframesViewMap.erase(keyframe->getView());
		keyframe->destroyView();
	}
	
	_keyframedData.remove(keyframe->getData());
	ofRemove(_keyframes, [&](KeyframeController<void>* k){
		return k == keyframe;
	});

	return (removeChild(keyframe) != nullptr);
	
	
	
}


void KeyframeCollectionController<void>::removeAllKeyframes()
{
	DOM::Node::removeAllChildren();
	_keyframedData.clear();
	_keyframesViewMap.clear();
	_keyframes.clear();
}


void KeyframeCollectionController<void>::generateView()
{
	if(getView() == nullptr){
		auto p = _parentRegion;
		if(p && p->getKeyframesRegionView())
		{
			
			auto views = p->getKeyframesRegionView()->getViews();
			if(views.size())
			{
				setView(views[0]);
				
				auto cv = views[0];
				
				if(cv){
					addKeyframeListener = cv -> addKeyframeEvent.newListener(this,&KeyframeCollectionController<void>::_addKeyframeEventCB);
					
					removeKeyframeListener = cv->removeKeyframeEvent.newListener(this, &KeyframeCollectionController<void>::_removeKeyframeEventCB);
				}
			}
		}
		
		generateChildrenViews(this);
		_keyframesViewMap.clear();
		for(auto k: _keyframes)
		{
			if(k && k->getView())
			{
				_keyframesViewMap[k->getView()] = k;
			}
		}
	}
}


void KeyframeCollectionController<void>::destroyView()
{
	if(getView()){
		destroyChildrenViews(this);
		_keyframesViewMap.clear();
		
		addKeyframeListener.unsubscribe();
		removeKeyframeListener.unsubscribe();
		setView(nullptr);
	}
}



void KeyframeCollectionController<void>::_addKeyframeEventCB(AddKeyframeEventArgs& args)
{
	
	addKeyframe( args.time);
}


bool KeyframeCollectionController<void>::compareKeyframeControlers(KeyframeController<void>*a, KeyframeController<void>*b)
{
	return *(a->getData()) < *(b->getData()) ;
}

void KeyframeCollectionController<void>::sortData()
{
	ofSort(_keyframes, KeyframeCollectionController<void>::compareKeyframeControlers);
	
	_keyframedData.sortData();
	
	if(getView()) getView()->updateKeyframeSort();
	
}


void KeyframeCollectionController<void>::_removeKeyframeEventCB(RemoveKeyframesEventArgs& args)
{
	for(auto k: args.keyframes){
		if(!k)
		{
			ofLogWarning("KeyframeCollectionController<D>::_removeKeyframeEventCB") << "failed because a nullptr was passed to it. This should not happen.";
			continue;
		}
		if(_keyframesViewMap.count(k))
		{
			removeKeyframe(_keyframesViewMap[k]);
		}
	}
}

	
bool KeyframeCollectionController<void>::update(const uint64_t& t, ofParameter<void>& param)
{
	if(_keyframedData.update(t))
	{
		param.trigger();
		return true;
	}
	return false;
}

void KeyframeCollectionController<void>::setTimeRange(const ofRange64u& timeRange)
{
	_keyframedData.setTimeRange(timeRange);
}
	

void KeyframeCollectionController<void>::moveAllKeyframesByTime(const uint64_t & _timeOffset)
{
	_keyframedData.moveAllByTime(_timeOffset);
	if(getView()) getView()->updateLayout();
}

KeyframeController<void>* KeyframeCollectionController<void>::getKeyframeAtTime(const uint64_t & time)
{
	for(auto k : _keyframes)
	{
		if(k && k -> getData() && *(k -> getData()) == time  )
		{
			return k;
		}
	}
	return nullptr;
}

KeyframeController<void>* KeyframeCollectionController<void>::getKeyframeByIndex(const size_t & index)
{
	if(index >= _keyframes.size()) return nullptr;
	return _keyframes[index];
}




void KeyframeCollectionController<void>::fromJson(const ofJson& j)
{
	
//	std::cout << "KeyframeCollectionController<D>::fromJson\n";
	
	setId(j["name"]);
	
	if(j.count("_keyframedData")== 0 || j.count("_dataTypeName") == 0)
	{
		ofLogError("KeyframeCollectionController<void>::fromJson") << "failed. Malformed json. DataTypeName or keyframedData elements not present";
		return;
	}
	auto dt = j["_dataTypeName"].get<std::string>();
	
	if(dt != getDataTypeName())
	{
		ofLogError("KeyframeCollectionController<T>::fromJson") << "failed. DataType seems to be different to the one saved on file";
		return;
	}
	
	removeAllKeyframes();
	
	KeyframedData_<void> key_data;
	
	key_data.fromJson(j["_keyframedData"]);
	
	for(auto& d: key_data.getData())
	{
		addKeyframe(*d);
	}
}


ofJson KeyframeCollectionController<void>::toJson()
{
	ofJson j;
	j["class"] = "KeyframeCollectionController";
	j["name"] = getId();
	j["_dataTypeName"] = _dataTypeName;
	
	
	j["_keyframedData"] = _keyframedData.toJson();
	
	
	return j;
	
}





template class KeyframeCollectionController<glm::vec2>;
template class KeyframeCollectionController<glm::vec3>;
template class KeyframeCollectionController<glm::vec4>;

template class KeyframeCollectionController<bool>;


template class KeyframeCollectionController<ofColor>;
template class KeyframeCollectionController<ofShortColor>;
template class KeyframeCollectionController<ofFloatColor>;


template class KeyframeCollectionController<int8_t>;
template class KeyframeCollectionController<uint8_t>;
template class KeyframeCollectionController<int16_t>;
template class KeyframeCollectionController<uint16_t>;
template class KeyframeCollectionController<int32_t>;
template class KeyframeCollectionController<uint32_t>;
template class KeyframeCollectionController<int64_t>;
template class KeyframeCollectionController<uint64_t>;
template class KeyframeCollectionController<float>;
template class KeyframeCollectionController<double>;
#ifndef TARGET_LINUX
template class KeyframeCollectionController<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;
#endif




} } // ofx::LineaDeTiempo

