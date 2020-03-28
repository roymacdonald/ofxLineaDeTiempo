//
//  KeyframeRegionController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"

namespace ofx {
namespace LineaDeTiempo {


template<typename T>
KeyframeRegionController_<T>::KeyframeRegionController_(const std::string& name, const ofRange64u& timeRange, TrackController* parentTrack, TimeControl* timeControl)
: RegionController(name, timeRange, parentTrack, timeControl)
, _parentTrack(dynamic_cast<KeyframeTrackController_<T>*>(parentTrack))
{

	
}

template<typename T>
void KeyframeRegionController_<T>::generateView()
{
	if(getView() == nullptr){
		auto p = dynamic_cast<TrackController*>(parent());
		if(p && p->getView())
		{
			_keyframesRegionView = p->getView()->addRegion<KeyframesRegionView, KeyframeRegionController_<T>>(this);
			
			setView(_keyframesRegionView);
			
			
			addKeyframeListener = _keyframesRegionView->addKeyframeEvent.newListener(this,&KeyframeRegionController_<T>::_addKeyframeAtScreenPos);
			
			removeKeyframeListener = _keyframesRegionView->removeKeyframeEvent.newListener(this, &KeyframeRegionController_<T>::_removeKeyframe);
			
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
template<typename T>
void KeyframeRegionController_<T>::destroyView()
{
	if(getView()){
		destroyChildrenViews(this);
		_keyframesViewMap.clear();
		
		auto p = dynamic_cast<TrackController*>(parent());
		if(p && p->getView())
		{
			
			if(p->getView()->removeRegion(this) == false)
			{
				ofLogError("KeyframeRegionController_<T>::destroyView") << "Could not remove track correctly. " << getId();
			}
			addKeyframeListener.unsubscribe();
			removeKeyframeListener.unsubscribe();
			setView(nullptr);
			_keyframesRegionView = nullptr;
		}
	}
}

template<typename T>
KeyframeController<T>* KeyframeRegionController_<T>::addKeyframe(T value, uint64_t time)
{
	auto d = _keyframedData.add(value, time);
	
	auto k = addChild<KeyframeController<T>>( "k_"+ofToString(_keyframedData.size()), d, this );
	
	_keyframes.push_back(k);
	
	if(getView())
	{
		k->generateView();
		_keyframesViewMap[k->getView()] = k;
	}
	
	return k;
}
template<typename T>
bool KeyframeRegionController_<T>::removeKeyframe(KeyframeController<T>* keyframe)
{
	_keyframedData.remove(keyframe->getData());
	
	if(keyframe->getView())
	{
		_keyframesViewMap.erase(keyframe->getView());
		keyframe->destroyView();
		
	}
	
	return (removeChild(keyframe) != nullptr);
}



template<typename T>
void KeyframeRegionController_<T>::_removeKeyframe(KeyframeView*& v)
{
	if(!v)
	{
		ofLogWarning("KeyframeRegionController_<T>::_removeKeyframe") << "failed because a nullptr was passed to it. This should not happen.";
		return;
	}
	if(_keyframesViewMap.count(v))
	{
		removeKeyframe(_keyframesViewMap[v]);
	}
}

template<typename T>
void KeyframeRegionController_<T>::update(uint64_t& t)
{
	std::cout << "-";
	if(_keyframedData.update(t))
	{
		if(_parentTrack)
		{
			if(_parentTrack->getParameter().get() != _keyframedData.getCurrentValue())
				_parentTrack->getParameter().set(_keyframedData.getCurrentValue());
		}
		
	}
}
//template<typename T>
//void KeyframeRegionController_<T>::_keyframeAdded(KeyframeView * view)
//{
//	if(view && _viewDataMap.count(view) == 0)
//	{
//		auto k = _keyframedData.add(_parentTrack->getUnnormalizedValue(view->getValue()),
//									view->getTime());
//
//		if(k)
//		{
//			_viewDataMap[view] = k;
//		}
//	}
//}
//
//template<typename T>
//void KeyframeRegionController_<T>::_keyframeRemoved(KeyframeView * view)
//{
//	if(view && _viewDataMap.count(view))
//	{
//		_keyframedData.remove(_viewDataMap[view]);
//
//		_viewDataMap.erase(view);
//	}
//}
//
//template<typename T>
//void KeyframeRegionController_<T>::_keyframesRemoved(std::vector<KeyframeView *>& keyframes)
//{
//	for(auto k : keyframes)
//	{
//		_keyframeRemoved(k);
//	}
//}

template<typename T>
void KeyframeRegionController_<T>::_addKeyframeAtScreenPos(glm::vec2& pos)
{
	
	if(getView() && _parentTrack && _parentTrack->getView()){
		//		std::cout << "pos : " << pos;
		
		auto time = _parentTrack->getView()->screenPositionToTime(pos.x);
		
		//		std::cout << "  time: " << time ;
		
		auto r = getView()->getScreenShape();
		
		auto & p = _parentTrack->getParameter();
		auto value = ofMap(pos.y, r.getMinY(), r.getMaxY() - KeyframeView::defaultKeyframeSize, p.getMin(), p.getMax(), true);
		
		//		std::cout << "  value: " << value << "\n";
		
		this->addKeyframe(value, time);
		
		//		Esta transformacion de coordenadas no esta funcando bien.
		//		HAcer que se solo una funcion la que hace la transformacion.
		
	}
}

template<typename T>
const KeyframedData_<T>& KeyframeRegionController_<T>::getKeyframedData() const
{
	return _keyframedData;
}




//template<typename T>
//void KeyframeRegionController_<T>::updateKeyframeTimeAndValue(KeyframeView* keyframe)
//{
//	if(_viewDataMap.count(keyframe) && _parentTrack)
//	{
//		_viewDataMap[keyframe]->time = keyframe->getTime();
//		_viewDataMap[keyframe]->value = _parentTrack->getUnnormalizedValue(keyframe->getValue());
//	}
//}

template class KeyframeRegionController_<int8_t>;
template class KeyframeRegionController_<int16_t>;
template class KeyframeRegionController_<int32_t>;
template class KeyframeRegionController_<int64_t>;
template class KeyframeRegionController_<uint8_t>;
template class KeyframeRegionController_<uint16_t>;
template class KeyframeRegionController_<uint32_t>;
template class KeyframeRegionController_<uint64_t>;
template class KeyframeRegionController_<size_t>;
template class KeyframeRegionController_<float>;

//template class KeyframeRegionController_<int>;
//template class KeyframeRegionController_<float>;

} } // ofx::LineaDeTiempo

