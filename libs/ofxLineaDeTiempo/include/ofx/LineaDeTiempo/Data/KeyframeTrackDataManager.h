////
////  TrackData.h
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/5/20.
////
//
//#pragma once
//#include "ofParameter.h"
//#include "KeyFrames.h"
//namespace ofx {
//namespace LineaDeTiempo {
//
//
//template<typename T>
//class KeyframeTrackData_
//{
//public:
//	KeyframeTrackData_(MUI::KeyFrame* k):
//	UI_keyframe(k)
//	{
//		if(k){
//			value = k->getValue();
//			time = k->getTime();
//		}
//	}
//
//	T value;
//	uint64_t time;
//	MUI::KeyFrame* UI_keyframe = nullptr;
//};
//
//template<typename T>
//class KeyframeTrackDataManager_
//{
//public:
//	KeyframeTrackDataManager_(const ofParameter<T>& param);
//	~KeyframeTrackDataManager_(){}
//
//
//	T getValueAtTime(const uint64_t& time);
//
//
//	KeyframeTrackData_<T>* add(const T& value, const uint64_t& time);
//
//	bool remove(KeyframeTrackData_<T>* d);
//
//
//	void updateParam(const uint64_t& time);
//
//
////	std::vector<KeyframeTrackData_<T>>& getData();
////	const std::vector<KeyframeTrackData_<T>>& getData() const;
//
//	static T getInterpolatedValueAtTime(const KeyframeTrackData_<T>* prev, const KeyframeTrackData_<T>* next, const uint64_t& time);
//
//	void sortData();
//
//protected:
//	std::vector<std::unique_ptr<KeyframeTrackData_<T>>> _data;
//
//	static bool _sortData(const std::unique_ptr<KeyframeTrackData_<T>>& a, const std::unique_ptr<KeyframeTrackData_<T>>& b)
//	{
//		return a->time < b->time;
//	}
//
//
//	ofParameter<T> _param;
//
//private:
//	//each region has its own event. So we need one listener per region
//	ofEventListeners _addedKeyFrameListeners;
//	ofEventListeners _removedKeyFrameListeners;
//
//	ofEventListener _paramListener;
//
//
//	void _keyFrameAdded(MUI::KeyFrame*& k );
//	void _keyFrameRemoved(MUI::KeyFrame*& k );
//	void _paramChanged(T& p);
//
//
//	// this is set to true when the param is being modified by the manager, so it does not generate an infinite loop because of the cyclic callbacks.
//	bool _bModifyingParam = false;
//
//};
//} } // ofx::LineaDeTiempo
