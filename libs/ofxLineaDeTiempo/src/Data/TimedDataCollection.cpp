////
////  TimedDataCollection.cpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/10/20.
////
//
//#include "TimedDataCollection.h"
//#include "ofLog.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
////---------------------------------------------------------------------------------
////template<typename T>
////TimedDataCollection_<T>::TimedDataCollection_():TimedDataCollection_("")
////{
////
////}
//
//template<typename T>
//TimedDataCollection_<T>::TimedDataCollection_(const std::string & name):
//BaseHasCollection<TimedData_<T>>(name)
//{
//	_lastUpdateTime = std::numeric_limits<uint64_t>::max();
//}
//
//
////---------------------------------------------------------------------------------
////template<typename T>
////T TimedDataCollection_<T>::getValueAtTime(const uint64_t& time) const
////{
////	//	if(_data.size() == 0)
////	//	{
////	//
////	//		return T();
////	//	}
////	//	if(time <= _data[0]->time)
////	//	{
////	//		return _data[0]->value;
////	//	}
////	//	if(_data.back()->time <= time )
////	//	{
////	//		return _data.back()->value;
////	//	}
////	T val;
////
////	if(!_isTimeInDataBounds(val, time)) return val;
////
////	if(_timedMap.count(time)) return _timedMap[time]->value;
////
////	//	for(size_t i = 1; i < _data.size(); i++)
////	//	{
////	////		if(_data[i]->time == time)
////	////		{
////	////			return _data[i]->value;
////	////		}
////	////		else
////	//		if(_data[i]->time > time)
////	//		{
////	if(_data.size() < 2)
////	{
////		ofLogError("TimedDataCollection_<T>::getValueAtTime") << "it should never get to this point. _data.size is less than 2.";
////	}
////
////	auto i = _findNextIndex(time);
////	if(i <  _data.size()){
////		return _data[i-1]->interpolateTo( _data[i].get(), time);
////	}
////
////	ofLogError("TimedDataCollection_<T>::getValueAtTime") << "it should never get to this point";
////
////	return val;
////
////
////}
////---------------------------------------------------------------------------------
////template<typename T>
////TimedData_<T>* TimedDataCollection_<T>::add(const T& value, const uint64_t& time)
////{
//
////	if(_timedMap.count(time))
////	{
////		ofLogNotice("TimedDataCollection_<T>::add") << "there is already data at this point. Updating to new value";
////		_timedMap[time]->value = value;
////		return _timedMap[time];
////	}
////	//	for(auto& d: _data){
////	//		if(d->time == time)
////	//		{
////	//			ofLogNotice("KeyframeTrackDataManager_<T>::add") << "there is already data at this point. Updating to new value";
////	//			d->value = value;
////	//			return d.get();
////	//		}
////	//	}
////
////	_addToCollection(value, time);
//
//	//	_data.emplace_back(std::make_unique<TimedData_<T>>(value, time));
//	//	_timedMap[time] = _data.back().get();
////	sortData();
////}
//
////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::_addedElementToCollection(TimedData_<T>* newElement)
////{
////		if(_timedMap.count(time))
////		{
////			ofLogNotice("TimedDataCollection_<T>::add") << "there is already data at this point. Updating to new value";
////			_timedMap[time]->value = value;
////			return _timedMap[time];
////		}
//
//
////	_timedMap[time] = _data.back().get();
//
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::_removedElementFromCollection(TimedData_<T>* removedElement)
////{
////
////}
////
////
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::_addToCollection(const T& value, const uint64_t& time)
////{
////	_data.emplace_back(std::make_unique<TimedData_<T>>(value, time));
////	_timedMap[time] = _data.back().get();
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////bool TimedDataCollection_<T>::remove(TimedData_<T>* d)
////{
////	auto s = _data.size();
////	ofRemove(_data,
////			 [&](std::unique_ptr<TimedData_<T>>& i){
////		if(i->get() == d){
////			_timedMap.erase(i->time);
////			return true;
////		}else{
////			return false;
////		}
////	});
////
////	return s > _data.size();
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::clear()
////{
////	_timedMap.clear();
////	_data.clear();
////
////}
//
//template<typename T>
//void TimedDataCollection_<T>::updateTimeRange()
//{
//	_timeRange.min = std::numeric_limits<uint64_t>::max();
//	_timeRange.max = 0;
//
//	for(auto& c: BaseHasCollection<TimedData_<T>>::_collection)
//	{
//		if(_timeRange.min > c->time) _timeRange.min = c->time;
//		if(_timeRange.max < c->time) _timeRange.max = c->time;
//	}
//}
////---------------------------------------------------------------------------------
//template<typename T>
//const ofRange_<uint64_t>& TimedDataCollection_<T>::getTimeRange() const
//{
//	return _timeRange;
//}
////---------------------------------------------------------------------------------
//template<typename T>
//bool TimedDataCollection_<T>::update(const uint64_t& time)
//{
//	if(!_isTimeInDataBounds(_currentValue, time)){
//		_lastUpdateTime = time;
//		return false;
//	}
//
//	//	if(_timedMap.count(time)){
//	//		_currentValue = _timedMap[time]->value;
//	//		_lastUpdateTime = time;
//	//		return;
//	//	}
//
//	if(_lastUpdateTime == time)
//	{
//		ofLogError("TimedDataCollection_<T>::update") << "time reached the maximum time possible or something else went wrong";
//		return false;
//	}
//
//	if(_data[_currentIndex]->time == time){// this block might be unnecesary. TODO: Double check
//		_currentValue = _data[_currentIndex]->value;
//		_currentIndex++;
//		_lastUpdateTime = time;
//		return true;
//	}
//
//	if(_data[_currentIndex]->time < time){
//		_currentIndex = _findNextIndex(time);
//	}
//
//	//	if(_data[_currentIndex]->time == time){
//	//		_currentValue = _data[_currentIndex]->value;
//	//		_currentIndex++;
//	//
//	//
//	//
//	//		return;
//	//	}
//
//	if(_currentIndex == 0)
//	{
//		_lastUpdateTime = time;
//		ofLogError("TimedDataCollection_<T>::update") << "_currentIndex should never be zero. ";
//
//		return false;
//	}
//
//	//	if(_lastUpdateTime > time)
//	//	{
//	//
//	//		_currentIndex = _findNextIndex(time);
//	//		_lastUpdateTime = time;
//
//	if(_currentIndex >= _data.size())
//	{
//		_lastUpdateTime = time;
//		ofLogError("TimedDataCollection_<T>::update") << "_currentIndex >= _data.size()). this should not happen";
//		return false;
//	}
//
//	_currentValue = _data[_currentIndex-1]->interpolateTo( _data[_currentIndex].get(), time);
//
//
//	return true;
//
//	//		if(_data[_currentIndex]->time == time){
//	//			_currentValue = _data[_currentIndex]->value;
//	//			_currentIndex++;
//	//			return;
//	//		}
//	//	}
//
//
//
//
//
//	//	uint64_t _lastUpdateTime = 0;
//	//
//	//	size_t _currentIndex =0;
//
//
//
//
//}
//
////---------------------------------------------------------------------------------
//template<typename T>
//bool TimedDataCollection_<T>::_isTimeInDataBounds(T& d,  const uint64_t& time)
//{
//	if(_data.size() == 0)
//	{
//		ofLogVerbose("TimedDataCollection_<T>::_isTimeInDataBounds") << "No data available. set to default ";
//		d = T();
//		return false;
//	}
//	if(time <= _data[0]->time)
//	{
//		d = _data[0]->value;
//		return false;
//	}
//	if(_data.back()->time <= time )
//	{
//		d = _data.back()->value;
//		return false;
//	}
//	return true;
//}
////---------------------------------------------------------------------------------
//template<typename T>
//size_t TimedDataCollection_<T>::_findNextIndex(const uint64_t& time)
//{
//	for(size_t i = 1; i < _data.size(); i++)
//	{
//		if(_data[i]->time > time)
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
//void TimedDataCollection_<T>::sortData()
//{
//	ofSort(this->_data, TimedDataCollection_<T>::_sortData);
//}
//////---------------------------------------------------------------------------------
////template<typename T>
////const T& TimedDataCollection_<T>::getCurrentValue() const
////{
////	return _currentValue;
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::setValue(const T& value, const uint64_t& time, bool bAddKeyIfNotFound)
////{
////	if(_timedMap.count(time))
////	{
////		if(_timedMap[time])
////		{
////			_timedMap[time]->value = value;
////		}
////	}
////	else if(bAddKeyIfNotFound)
////	{
////		add(value, time);
////	}
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::_enableKeyframing(bool e)
////{
////	if(_bKeyframingEnabled != e){
////		_bKeyframingEnabled = e;
////		_bKeyframingEnabledProxy = _bKeyframingEnabled;
////		ofNotifyEvent(keyframingEnableEvent, _bKeyframingEnabledProxy, this);
////	}
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::enableKeyframing()
////{
////	_enableKeyframing(true);
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////void TimedDataCollection_<T>::disableKeyframing()
////{
////	_enableKeyframing(false);
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////bool TimedDataCollection_<T>::isKeyFramingEnabled() const
////{
////	return _bKeyframingEnabled;
////}
//////---------------------------------------------------------------------------------
////template<typename T>
////const std::vector< std::unique_ptr< TimedData_<T> > > & TimedDataCollection_<T>::getData() const
////{
////	return _data;
////}
////
////
//
////---------------------------------------------------------------------------------
//template<typename T>
//void TimedDataCollection_<T>::fromJson(const ofJson& j)
//{
//
//		if(j.at("keyframe_type").get<std::string>() != std::string(typeid(T).name()) ||
//		   !j.at("keyframes").is_array()
//		   )
//		{
//			ofLogError("TimedDataCollection_<T>::fromJson") << "failed. probably json file is malformed or corrupt.";
//			return;
//		}
//
//		j.at("name").get_to(_name);
////		j.at("currentValue").get_to(_currentValue);
//		j.at("lastUpdateTime").get_to(_lastUpdateTime);
//		j.at("currentIndex").get_to(_currentIndex);
////		j.at("bKeyframingEnabled").get_to(_bKeyframingEnabled);
//
//
//		for(auto& k: j.at("keyframes")){
//			_addToCollection(k.at("value").get<T>(), k.at("time").get<uint64_t>());
//		}
//		if(j.at("num_keyframes") != j.at("keyframes").size())
//		{
//			ofLogError("TimedDataCollection_<T>::fromJson") << "key frame number differs from what is on json file. probably json file is malformed or corrupt.";
//		}
//
//}
//
////---------------------------------------------------------------------------------
//template<typename T>
//void TimedDataCollection_<T>::toJson(ofJson& j)
//{
//	j["name"] = _name;
//	j["currentValue"] = _currentValue;
//	j["lastUpdateTime"] = _lastUpdateTime;
//	j["currentIndex"] = _currentIndex;
//	j["bKeyframingEnabled"] = _bKeyframingEnabled;
//	j["keyframe_type"] = std::string(typeid(T).name());
//	j["keyframes"] = nlohmann::json::array();
//	for(auto& d: _data){
//		if(d) j["keyframes"].emplace_back(&d.get()) ;
//	}
//	j["num_keyframes"] = j["keyframes"].size();
//}
//
//
////---------------------------------------------------------------------------------
//template<typename T>
//void TimedDataCollection_<T>::moveAllByTime(const uint64_t& _timeOffset)
//{
//	for(auto& d: _data){
//		d->time += _timeOffset;
//	}
//}
//
////template<typename DataType>
////std::ostream& operator<<(std::ostream& os, const TimedDataCollection_<DataType>& data)
////{
////	os << data._name << ", "
////	<< data._currentValue << ", "
////	<< data._lastUpdateTime << ", "
////	<< data._currentIndex << ", "
////	<< data._bKeyframingEnabled << ", "
////	<< data._data.size();
////	for(auto& d: data._data){
////		os << ", " << d ;
////	}
////	return os;
////}
////template<typename DataType>
////std::istream& operator>>(std::istream& is, TimedDataCollection_<DataType>& data)
////{
////
////	is >> data._name;
////	is.ignore(2);
////	is >> data._currentValue;
////	is.ignore(2);
////	is >> data._lastUpdateTime;
////	is.ignore(2);
////	is >> data._currentIndex;
////	is.ignore(2);
////	is >> data._bKeyframingEnabled;
////	is.ignore(2);
////	size_t size;
////	is >> size;
////	//	<< data._data.size();
////	DataType d;
////
////	data.clear();
////
////	for(size_t i =0; i < size; i++)
////	{
////		is.ignore(2);
////		is >> d;
////		data._addToCollection(d.value, d.time);
////
////	}
////	data.sortData();
////	return is;
////
////}
//
//
//
//} } // ofx::LineaDeTiempo
//