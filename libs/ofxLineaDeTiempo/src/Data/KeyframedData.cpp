//
//  KeyframedData.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "KeyframedData.h"
#include "ofLog.h"

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------
template<typename T>
KeyframedData_<T>::KeyframedData_(std::shared_ptr<TimeControl> timeControl):
_timeControl(timeControl)
{
	_lastUpdateTime = std::numeric_limits<uint64_t>::max();
}


//---------------------------------------------------------------------------------
template<typename T>
T KeyframedData_<T>::getValueAtTime(const uint64_t& time) const
{
//	if(_data.size() == 0)
//	{
//
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
	T val;
	
	if(!_isTimeInDataBounds(val, time)) return val;
	
	if(_timedMap.count(time)) return _timedMap[time]->value;
	
//	for(size_t i = 1; i < _data.size(); i++)
//	{
////		if(_data[i]->time == time)
////		{
////			return _data[i]->value;
////		}
////		else
//		if(_data[i]->time > time)
//		{
	if(_data.size() < 2)
	{
	ofLogError("KeyframedData_<T>::getValueAtTime") << "it should never get to this point. _data.size is less than 2.";
	}
	
	auto i = _findNextIndex(time);
	if(i <  _data.size()){
		return _data[i-1]->interpolateTo( _data[i].get(), time);
	}
	
	ofLogError("KeyframedData_<T>::getValueAtTime") << "it should never get to this point";
	
	return val;
	
	
}
//---------------------------------------------------------------------------------
template<typename T>
TimedData_<T>* KeyframedData_<T>::add(const T& value, const uint64_t& time)
{
	for(auto& d: _data){
		if(d->time == time)
		{
			ofLogNotice("KeyframeTrackDataManager_<T>::add") << "there is already data at this point. Updating to new value";
			d->value = value;
			return d.get();
		}
	}
	
	_data.emplace_back(std::make_unique<TimedData_<T>>(value, time));
	_timedMap[time] = _data.back().get();
	sortData();
}
//---------------------------------------------------------------------------------
template<typename T>
bool KeyframedData_<T>::remove(TimedData_<T>* d)
{
	auto s = _data.size();
	ofRemove(_data,
				[&](std::unique_ptr<TimedData_<T>>& i){
					if(i->get() == d){
						_timedMap.erase(i->time);
						return true;
					}else{
						return false;
					}
				});
	
	return s > _data.size();
}
//---------------------------------------------------------------------------------
template<typename T>
bool KeyframedData_<T>::update(const uint64_t& time)
{
	if(!_isTimeInDataBounds(_currentValue, time)){
		_lastUpdateTime = time;
		return false;
	}
	
//	if(_timedMap.count(time)){
//		_currentValue = _timedMap[time]->value;
//		_lastUpdateTime = time;
//		return;
//	}
	
	if(_lastUpdateTime == time)
	{
		ofLogError("KeyframedData_<T>::update") << "time reached the maximum time possible or something else went wrong";
		return false;
	}
	
	if(_data[_currentIndex]->time == time){// this block might be unnecesary. TODO: Double check
		_currentValue = _data[_currentIndex]->value;
		_currentIndex++;
		_lastUpdateTime = time;
		return true;
	}
	
	if(_data[_currentIndex]->time < time){
		_currentIndex = _findNextIndex(time);
	}
	
//	if(_data[_currentIndex]->time == time){
//		_currentValue = _data[_currentIndex]->value;
//		_currentIndex++;
//
//
//
//		return;
//	}
	
	if(_currentIndex == 0)
	{
		_lastUpdateTime = time;
		ofLogError("KeyframedData_<T>::update") << "_currentIndex should never be zero. ";
		
		return false;
	}
	
//	if(_lastUpdateTime > time)
//	{
//
//		_currentIndex = _findNextIndex(time);
//		_lastUpdateTime = time;
		
		if(_currentIndex >= _data.size())
		{
			_lastUpdateTime = time;
			ofLogError("KeyframedData_<T>::update") << "_currentIndex >= _data.size()). this should not happen";
			return false;
		}
		
	_currentValue = _data[_currentIndex-1]->interpolateTo( _data[_currentIndex].get(), time);
	
	
	return true;
	
//		if(_data[_currentIndex]->time == time){
//			_currentValue = _data[_currentIndex]->value;
//			_currentIndex++;
//			return;
//		}
//	}
	
	
	
	
	
//	uint64_t _lastUpdateTime = 0;
//
//	size_t _currentIndex =0;
	
	
	
	
}

//---------------------------------------------------------------------------------
template<typename T>
bool KeyframedData_<T>::_isTimeInDataBounds(T& d,  const uint64_t& time)
{
	if(_data.size() == 0)
	{
		ofLogVerbose("KeyframedData_<T>::_isTimeInDataBounds") << "No data available. set to default ";
		d = T();
		return false;
	}
	if(time <= _data[0]->time)
	{
		d = _data[0]->value;
		return false;
	}
	if(_data.back()->time <= time )
	{
		d = _data.back()->value;
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------------
template<typename T>
size_t KeyframedData_<T>::_findNextIndex(const uint64_t& time)
{
	for(size_t i = 1; i < _data.size(); i++)
	{
		if(_data[i]->time > time)
		{
			return i;
		}
	}
	return _data.size();
}


//---------------------------------------------------------------------------------
template<typename T>
void KeyframedData_<T>::sortData()
{
	ofSort(this->_data, KeyframedData_<T>::_sortData);
}
//---------------------------------------------------------------------------------
template<typename T>
const T& KeyframedData_<T>::getCurrentValue() const
{
	return _currentValue;
}
//---------------------------------------------------------------------------------
template<typename T>
void KeyframedData_<T>::setValue(const T& value, const uint64_t& time, bool bAddKeyIfNotFound)
{
	if(_timedMap.count(time))
	{
		if(_timedMap[time])
		{
			_timedMap[time]->value = value;
		}
	}
	else if(bAddKeyIfNotFound)
	{
		add(value, time);
	}
}
//---------------------------------------------------------------------------------
template<typename T>
void KeyframedData_<T>::_enableKeyframing(bool e)
{
	if(_bKeyframingEnabled != e){
		_bKeyframingEnabled = e;
		_bKeyframingEnabledProxy = _bKeyframingEnabled;
		ofNotifyEvent(keyframingEnableEvent, _bKeyframingEnabledProxy, this);
	}
}
//---------------------------------------------------------------------------------
template<typename T>
void KeyframedData_<T>::enableKeyframing()
{
	_enableKeyframing(true);
}
//---------------------------------------------------------------------------------
template<typename T>
void KeyframedData_<T>::disableKeyframing()
{
	_enableKeyframing(false);
}
//---------------------------------------------------------------------------------
template<typename T>
bool KeyframedData_<T>::isKeyFramingEnabled() const
{
	return _bKeyframingEnabled;
}


} } // ofx::LineaDeTiempo

