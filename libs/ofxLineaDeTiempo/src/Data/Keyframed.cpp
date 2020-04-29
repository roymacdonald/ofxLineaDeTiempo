////
////  Keyframed.cpp
////  example
////
////  Created by Roy Macdonald on 4/10/20.
////
//
//#include "LineaDeTiempo/Data/Keyframed.h"
//#include "ofLog.h"
//#include "ofEvent.h"
//#include <algorithm>
//namespace ofx {
//namespace LineaDeTiempo {
//
//
//
//
////---------------------------------------------------------------------------------
//template<typename T>
//Keyframed<T>::Keyframed()
//{
//	_lastUpdateTime = std::numeric_limits<uint64_t>::max();
//}
//
//
//template<typename T>
//size_t Keyframed<T>::size() const
//{
//	return _data.size();
//}
//
//
//
//template<typename T>
//bool Keyframed<T>::remove(T* d)
//{
//	auto s = _data.size();
//	ofRemove(_data,
//			 [&](std::unique_ptr<TimedData_<T>>& i)
//			 {
//		if(i.get() == d){
//			_timedMap.erase(_getTime(i));
//			return true;
//		}
//		return false;
//	});
//	
//	return s > _data.size();
//}
//
//
//
//template<typename T>
//void Keyframed<T>::clear()
//{
//	_timedMap.clear();
//	_data.clear();
//	
//}
//
//
//
//template<typename T>
//bool Keyframed<T>::hasKeyframeAt(const uint64_t& time) const
//{
//	return _timedMap.count(time);
//}
//
//
//
//template<typename T>
//bool Keyframed<T>::update(const uint64_t& time)
//{
//	
//	if(!_isTimeInDataBounds( time)){
//		_lastUpdateTime = time;
//		return false;
//	}
//	
//	if(_lastUpdateTime == time)
//	{
//		ofLogError("Keyframed<T>::update") << "time reached the maximum time possible or something else went wrong";
//		return false;
//	}
//	
//	ofRange64u updateRange(_lastUpdateTime+1, time );
//	
//	bool bUpdated = false;
//	
////	if(_getTime(_data[_currentIndex]) == time){
//	while(_currentIndex < _data.size() && updateRange.contains(_getTime(_data[_currentIndex]))){
//		_currentIndex++;
//		bUpdated = true;
//	}
//	if(bUpdated){
//	_lastUpdateTime = time;
//	return true;
//	}
//	
//	if(_getTime(_data[_currentIndex]) < time){
//		_currentIndex = _findNextIndex(time);
//	}
//	
//	_lastUpdateTime = time;
//	
//	if(_currentIndex == 0)
//	{
//		ofLogError("Keyframed<T>::update") << "_currentIndex should never be zero. ";
//	}
//	
//	if(_currentIndex >= _data.size())
//	{
//		ofLogError("Keyframed<T>::update") << "_currentIndex >= _data.size()). this should not happen";
//	}
//	
//	return false;
//	
//}
//template<typename T>
//uint64_t & Keyframed<T>::_getTime(std::unique_ptr<T>& data)
//{
//	return data->time;
//}
//template<>
//uint64_t & Keyframed<uint64_t>::_getTime(std::unique_ptr<uint64_t>& data)
//{
//	return *data;
//}
//
//
//
////---------------------------------------------------------------------------------
//template<typename T>
//bool Keyframed<T>::_isTimeInDataBounds(  const uint64_t& time)
//{
//	if(_data.size() == 0)
//	{
//		ofLogVerbose("Keyframed<T>::_isTimeInDataBounds") << "No data available. set to default ";
//		return false;
//	}
//	return _currentRange.contains(time);
////	if(time <= _getTime(_data[0]))
////	{
////		return false;
////	}
////	if(_getTime(_data.back()) <= time )
////	{
////		return false;
////	}
////	return true;
//}
////---------------------------------------------------------------------------------
//template<typename T>
//size_t Keyframed<T>::_findNextIndex(const uint64_t& time)
//{
//	for(size_t i = 0; i < _data.size(); i++)
//	{
//		if(_getTime(_data[i]) > time)
//		{
//			return i;
//		}
//	}
//	return _data.size();
//}
//
//
////---------------------------------------------------------------------------------
//template<typename T>
//void Keyframed<T>::sortData()
//{
//	if(_data.size()){
//	ofSort(this->_data,
//				[](const std::unique_ptr<T>& a, const std::unique_ptr<T>& b)
//				{
//					return a->time < b->time;
//				}
//		   );
//
//		_currentRange.set(_data[0]->time, _data.back()->time);
//	}
//}
//
//template<>
//void Keyframed<uint64_t>::sortData()
//{
//	if(_data.size()){
//		ofSort(this->_data,
//			   [](const std::unique_ptr<uint64_t>& a, const std::unique_ptr<uint64_t>& b)
//			   {
//				   return *a < *b;
//			   });
//		_currentRange.set(*_data[0].get(), *_data.back());
//	}
//}
//
////---------------------------------------------------------------------------------
//template<typename T>
//const std::vector< std::unique_ptr< T > > & Keyframed<T>::getData() const
//{
//	return _data;
//}
//
//
//template<typename T>
//void Keyframed<T>::enableKeyframing()
//{
//	setEnableKeyframing(true);
//}
//
//template<typename T>
//void Keyframed<T>::disableKeyframing()
//{
//	setEnableKeyframing(false);
//}
//
//template<typename T>
//bool Keyframed<T>::isKeyFramingEnabled() const
//{
//	return _bKeyframingEnabled;
//}
//
//
//template<typename T>
//void Keyframed<T>::setEnableKeyframing(bool e)
//{
//	if(_bKeyframingEnabled != e){
//		_bKeyframingEnabled = e;
//		_bKeyframingEnabledProxy = _bKeyframingEnabled;
//		ofNotifyEvent(keyframingEnableEvent, _bKeyframingEnabledProxy, this);
//	}
//}
//
//
////---------------------------------------------------------------------------------
//template<typename T>
//void Keyframed<T>::fromJson(const ofJson& j)
//{
//	try
//	{
//	
//	std::vector<std::string> keys = { "lastUpdateTime", "currentIndex", "bKeyframingEnabled", "keyframe_type", "keyframes", "num_keyframes"};
//
//		for(auto& k : keys)
//		{
//			if(j.count(k) == 0)
//			{
//				ofLogError("Keyframed<T>::fromJson") << "failed key check. no key : \"" << k << "\". Probably json file is malformed or corrupt.";
//			}
//		}
//
//
//		if(j.at("keyframe_type").get<std::string>() != std::string(typeid(T).name()) || !j.at("keyframes").is_array())
//		{
//			ofLogError("Keyframed<T>::fromJson") << "failed. probably json file is malformed or corrupt.";
//			return;
//		}
//		
//
////		_currentValue = j.at("currentValue").get<T>();
//		_lastUpdateTime = j.value("lastUpdateTime", _lastUpdateTime);
//		_currentIndex = j.value("currentIndex", _currentIndex);
//		 
//		bool _eK = j.value("bKeyframingEnabled", true);
//		 
//		setEnableKeyframing(_eK);
//
//		auto k = j.at("keyframes");
//		_loadKeyframes(k);
//		
////		for(auto& k: j.at("keyframes")){
////			_addToCollection(k.at("value").get<T>(), k.at("time").get<uint64_t>());
////		}
//		if(j.at("num_keyframes") != j.at("keyframes").size())
//		{
//			ofLogError("Keyframed<T>::fromJson") << "key frame number differs from what is on json file. probably json file is malformed or corrupt.";
//		}
//	}
//	catch (nlohmann::json::type_error& e)
//	{
//		std::cout << e.what() << '\n';
//	}
//	catch (nlohmann::json::out_of_range& e)
//	{
//		std::cout << e.what() << '\n';
//	}
//}
//
//template<typename T>
//void Keyframed<T>::_loadKeyframes(ofJson& keys)
//{
//	for(auto& k: keys){
//		add(k.at("value").get<T>(), k.at("time").get<uint64_t>());
//	}
//}
//template<>
//void Keyframed<uint64_t>::_loadKeyframes(ofJson& keys)
//{
//	for(auto& k: keys){
//		add(k.get<uint64_t>());
//	}
//	
//}
//
////---------------------------------------------------------------------------------
//template<typename T>
//ofJson Keyframed<T>::toJson()
//{
//	ofJson j;
//
//	j["lastUpdateTime"] = _lastUpdateTime;
//	j["currentIndex"] = _currentIndex;
//	j["bKeyframingEnabled"] = isKeyFramingEnabled();
//	j["keyframe_type"] = std::string(typeid(T).name());
//	j["keyframes"] = nlohmann::json::array();
//	for(auto& d: _data){
//		if(d) j["keyframes"].emplace_back(*(d.get())) ;
//	}
//	j["num_keyframes"] = j["keyframes"].size();
//	
//	return j;
//}
//
////---------------------------------------------------------------------------------
//template<typename T>
//void Keyframed<T>::moveAllByTime(const uint64_t& _timeOffset)
//{
//	for(auto& d: _data)
//	{
//		_getTime(d) += _timeOffset;
//	}
//}
//
//}} //ofx::LineaDeTiempo
//
