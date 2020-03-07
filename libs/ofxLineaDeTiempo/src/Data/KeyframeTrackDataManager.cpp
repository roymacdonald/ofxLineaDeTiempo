////
////  TrackData.cpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/5/20.
////
//
//#include "KeyframeTrackDataManager.h"
//#include "ofUtils.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
////-------------------------------------------------------------------------------
//template<typename T>
//KeyframeTrackDataManager_<T>::KeyframeTrackDataManager_(const ofParameter<T>& param)
//{
//	_param.makeReferenceTo(param);
//
//	_paramListener = _param.newListener(this, &KeyframeTrackDataManager_<T>::_paramChanged);
//
//}
//
////-------------------------------------------------------------------------------
//template<typename T>
//T KeyframeTrackDataManager_<T>::getInterpolatedValueAtTime(const KeyframeTrackData_<T>* prev, const KeyframeTrackData_<T>* next, const uint64_t& time)
//{
//	// TODO: add other types of interpolation
//	return ofMap(time, prev->time, next->time, prev->value, next->value);
//}
//
////-------------------------------------------------------------------------------
//template<typename T>
//T KeyframeTrackDataManager_<T>::getValueAtTime(const uint64_t& time)
//{
//	if(_data.size() == 0)
//	{
//		ofLogError("KeyframeTrackDataManager_<T>::getValueAtTime") << "No data available. Returning default ";
//		return T();
//	}
//	if(time <= _data[0]->time)
//	{
//		return _data[0]->value;
//	}
//	if(_data.back()->time <= time )
//	{
//		return _data.back()->value;
//	}
//
//	for(size_t i = 1; i < _data.size(); i++)
//	{
//		if(_data[i]->time == time)
//		{
//			return _data[i]->value;
//		}
//		else if(_data[i]->time > time)
//		{
//			return getInterpolatedValueAtTime(_data[i-1].get(), _data[i].get(), time);
//		}
//	}
//}
//
////-------------------------------------------------------------------------------
//template<typename T>
//KeyframeTrackData_<T>*  KeyframeTrackDataManager_<T>::add(const T& value, const uint64_t& time)
//{
//	for(auto& d: _data){
//		if(d->time == time)
//		{
//			ofLogNotice("KeyframeTrackDataManager_<T>::add") << "there is already data at this point. Updating to new value";
//			d->value = value;
//			return d.get();
//		}
//	}
//
//	_data.emplace_back(std::make_unique<KeyframeTrackData_<T>>(value, time));
//	sortData();
//}
//
//template<typename T>
//bool KeyframeTrackDataManager_<T>::remove(KeyframeTrackData_<T>* d)
//{
//	auto s = _data.size();
//	ofRemove(_data,
//				[&](std::unique_ptr<KeyframeTrackData_<T>>& i){
//					return i->get() == d;
//				});
//	return s > _data.size();
//}
//
////-------------------------------------------------------------------------------
//template<typename T>
//void KeyframeTrackDataManager_<T>::updateParam(const uint64_t& time)
//{
//	_bModifyingParam = true;
//	_param = getValueAtTime(time);
//	_bModifyingParam = false;
//}
//
////each region has its own event. So we need one listener per region
//ofEventListeners _addedKeyFrameListeners;
//ofEventListeners _removedKeyFrameListeners;
//
//
////-------------------------------------------------------------------------------
//template<typename T>
//void KeyframeTrackDataManager_<T>::_keyFrameAdded(MUI::KeyFrame*& k )
//{
//
//}
////-------------------------------------------------------------------------------
//template<typename T>
//void KeyframeTrackDataManager_<T>::_keyFrameRemoved(MUI::KeyFrame*& k )
//{
//
//}
////-------------------------------------------------------------------------------
//template<typename T>
//void KeyframeTrackDataManager_<T>::_paramChanged(T& p)
//{
//	if(!_bModifyingParam)
//	{
//
//	}
//}
//
//
//
//
////-------------------------------------------------------------------------------
////template<typename T>
////std::vector<KeyframeTrackData_<T>>& KeyframeTrackDataManager_<T>::getData()
////{
////	return _data;
////}
////
//////-------------------------------------------------------------------------------
////template<typename T>
////const std::vector<KeyframeTrackData_<T>>& KeyframeTrackDataManager_<T>::getData() const
////{
////	return _data;
////}
//
////-------------------------------------------------------------------------------
//template<typename T>
//void KeyframeTrackDataManager_<T>::sortData()
//{
//	ofSort(_data, KeyframeTrackDataManager_<T>::_sortData);
//}
//
//} } // ofx::LineaDeTiempo
//
