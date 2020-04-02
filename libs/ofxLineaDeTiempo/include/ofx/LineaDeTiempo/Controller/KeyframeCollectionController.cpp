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

//template<typename D>
//KeyframeController<D>* KeyframeCollectionController<D>::addKeyframe(innerDataType value, uint64_t time)
//{
//	auto d = _keyframedData.add(value, time);
//
//	auto k = addChild<KeyframeController<D>>( "k_"+ofToString(_dimensionIndex)+"_"+ofToString(_keyframedData.size()), d, this );
//
//	_keyframes.push_back(k);
//
//	if(getView())
//	{
//		k->generateView();
//		_keyframesViewMap[k->getView()] = k;
//	}
//
//	return k;
//}

template<typename D>
bool KeyframeCollectionController<D>::removeKeyframe(KeyframeController<D>* keyframe)
{
	
	_keyframedData.remove(keyframe->getData());
	
	if(keyframe->getView())
	{
		_keyframesViewMap.erase(keyframe->getView());
		keyframe->destroyView();
	}
	
	return (removeChild(keyframe) != nullptr);
	
	
	
}

template<typename D>
void KeyframeCollectionController<D>::removeAllKeyframes()
{
	_keyframedData.clear();
	_keyframesViewMap.clear();
	DOM::Node::removeAllChildren();
	
}


template<typename D>
const size_t& KeyframeCollectionController<D>::getDimensionIndex()const
{
	return _dimensionIndex;
}

template<typename D>
bool KeyframeCollectionController<D>::update(const uint64_t& t, D& param)
{

	if(_keyframedData.update(t))
	{
		return _paramNeedsUpdate(param);
	}
	return false;
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
void KeyframeCollectionController<D>::fromJson(const ofJson& j)
{
	
	std::cout << "KeyframeCollectionController<D>::fromJson\n";
	
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




template class KeyframeCollectionController<char>;
template class KeyframeCollectionController<unsigned char>;
template class KeyframeCollectionController<signed char>;
template class KeyframeCollectionController<short>;
template class KeyframeCollectionController<unsigned short>;
template class KeyframeCollectionController<int>;
template class KeyframeCollectionController<unsigned int>;
template class KeyframeCollectionController<long>;
template class KeyframeCollectionController<unsigned long>;
template class KeyframeCollectionController<long long>;
template class KeyframeCollectionController<unsigned long long>;
template class KeyframeCollectionController<float>;
//template class KeyframeCollectionController<double, double>;
//template class KeyframeCollectionController<long double, long double>;


template class KeyframeCollectionController<glm::vec2>;
template class KeyframeCollectionController<glm::vec3>;


} } // ofx::LineaDeTiempo

