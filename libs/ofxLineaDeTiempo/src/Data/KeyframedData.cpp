//
//  KeyframedData.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "KeyframedData.h"
#include "ofLog.h"
#include "LineaDeTiempo/Controller/Interpolator.h"
#include "ofEvent.h"
#include "ofEventUtils.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename T>
BaseKeyframedData<T>::BaseKeyframedData()
{
	_lastUpdateTime = std::numeric_limits<uint64_t>::max();
}


template<typename T>
void BaseKeyframedData<T>::enableKeyframing()
{
	setEnableKeyframing(true);
}


template<typename T>
void BaseKeyframedData<T>::disableKeyframing()
{
	setEnableKeyframing(false);
}


template<typename T>
bool BaseKeyframedData<T>::isKeyFramingEnabled() const
{
	return _bKeyframingEnabled;
}


template<typename T>
void BaseKeyframedData<T>::setEnableKeyframing(bool e)
{
	if(_bKeyframingEnabled != e){
		_bKeyframingEnabled = e;
		_bKeyframingEnabledProxy = _bKeyframingEnabled;
		ofNotifyEvent(keyframingEnableEvent, _bKeyframingEnabledProxy, this);
	}
}


template<typename T>
void BaseKeyframedData<T>::setTimeRange(const ofRange64u& timeRange)
{
	_timeRange = timeRange;

	_startIndex = 0;
	_endIndex = _data.size() -1;
	
	bool setStart = true;
	bool setEnd = true;
	
	uint64_t t;
	
	for(size_t i = 0; i < _data.size(); i++)
	{
		t = _getTimeFromData(_data[i].get());
		if(setStart && _timeRange.min <= t)
		{
			_startIndex = i;
			setStart = false;
		}
		else if(setEnd && _timeRange.max >= t)
		{
			_endIndex = i;
			setEnd = false;
		}
		if(!setStart && !setEnd)
		{
			break;
		}
	}
}


template<typename T>
const ofRange64u& BaseKeyframedData<T>::getTimeRange()
{
	return _timeRange;
}


template<typename T>
const std::vector< std::unique_ptr< T > > & BaseKeyframedData<T>::getData() const
{
	return _data;
}


template<typename T>
size_t BaseKeyframedData<T>::size() const
{
	return _data.size();
}


template<typename T>
void BaseKeyframedData<T>::clear()
{
		_timedMap.clear();
		_data.clear();
}


template<typename T>
bool BaseKeyframedData<T>::remove(T* d)
{
	auto s = _data.size();
	ofRemove(_data,
			 [&](std::unique_ptr<T>& i)
			 {
		if(i.get() == d){
			_timedMap.erase(_getTimeFromData(d));
			return true;
		}else{
			return false;
		}
	});
	
	return s > _data.size();
}

template<typename T>
void BaseKeyframedData<T>::sortData()
{
	ofSort(this->_data,
				[this](const std::unique_ptr<T>& a, const std::unique_ptr<T>& b)
				{
					return this->_getTimeFromData(a.get()) < this->_getTimeFromData(b.get());
				}
		   );
}


template<typename T>
void BaseKeyframedData<T>::moveAllByTime(const uint64_t& _timeOffset)
{
	for(auto& d: _data){
		_getTimeFromData(d.get()) += _timeOffset;
	}
}



//---------------------------------------------------------------------------------
template<typename T>
void BaseKeyframedData<T>::fromJson(const ofJson& j)
{
	try
	{
	
	std::vector<std::string> keys = { "lastUpdateTime", "currentIndex", "bKeyframingEnabled", "keyframe_type", "keyframes", "num_keyframes"};

		for(auto& k : keys)
		{
			if(j.count(k) == 0)
			{
				ofLogError("KeyframedData_<T>::fromJson") << "failed key check. no key : \"" << k << "\". Probably json file is malformed or corrupt.";
			}
		}


		if(j.at("keyframe_type").get<std::string>() != _getTypeName() || !j.at("keyframes").is_array())
		{
			ofLogError("KeyframedData_<T>::fromJson") << "failed. probably json file is malformed or corrupt.";
			return;
		}
		

//		_currentValue = j.at("currentValue").get<T>();
		_lastUpdateTime = j.value("lastUpdateTime", _lastUpdateTime);
		_currentIndex = j.value("currentIndex", _currentIndex);
		 
		bool _eK = j.value("bKeyframingEnabled", true);
		 
		setEnableKeyframing(_eK);


		for(auto& k: j.at("keyframes")){
			_addToCollection(k.get<T>(), false);//, k.at("time").get<uint64_t>());
		}
		if(j.at("num_keyframes") != j.at("keyframes").size())
		{
			ofLogError("KeyframedData_<T>::fromJson") << "key frame number differs from what is on json file. probably json file is malformed or corrupt.";
		}
	}
	catch (nlohmann::json::type_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (nlohmann::json::out_of_range& e)
	{
		std::cout << e.what() << '\n';
	}
}

//---------------------------------------------------------------------------------
template<typename T>
ofJson BaseKeyframedData<T>::toJson()
{
	ofJson j;
//	j["name"] = _name;
//	j["currentValue"] = _currentValue;
	j["lastUpdateTime"] = _lastUpdateTime;
	j["currentIndex"] = _currentIndex;
	j["bKeyframingEnabled"] = isKeyFramingEnabled();
	j["keyframe_type"] = _getTypeName();
	j["keyframes"] = nlohmann::json::array();
	for(auto& d: _data){
		if(d) j["keyframes"].emplace_back(*(d.get())) ;
	}
	j["num_keyframes"] = j["keyframes"].size();
	
	return j;
}



template<typename T>
T* BaseKeyframedData<T>::_addToCollection( const T& data, bool sort)
{
	_data.emplace_back(std::make_unique<T>(data));
	auto d = _data.back().get();
	_timedMap[_getTimeFromData(d)] = d;
	
	if(sort) sortData();
	return d;
}


//---------------------------------------------------------------------------------
template<typename T>
T KeyframedData_<T>::getValueAtTime(const uint64_t& time)
{

	T val;
	
	if(!_isTimeInDataBounds(val, time)) return val;
	
	if(_timedMap.count(time)) return _timedMap[time]->value;
	
	if(_data.size() < 2)
	{
		ofLogError("KeyframedData_<T>::getValueAtTime") << "it should never get to this point. _data.size is less than 2.";
		return val;
	}
	
	auto i = _findNextIndex(time);
	if( 0 < i && i <  _data.size()){

		
		return _currentValue = Interpolator::interpolateTimedData(_data[i-1].get() , _data[i].get(), time);
		
	}
	
	ofLogError("KeyframedData_<T>::getValueAtTime") << "it should never get to this point";
	
	return val;
	
	
}


//---------------------------------------------------------------------------------
template<typename T>
TimedData_<T>* KeyframedData_<T>::add(const T& value, const uint64_t& time)
{
	
	if(_timedMap.count(time))
	{
		ofLogNotice("KeyframedData_<T>::add") << "there is already data at this point. Updating to new value. Returning nullptr";
		_timedMap[time]->value = value;
		return nullptr;
	}
	return _addToCollection(TimedData_<T>(value, time), true);
	
}

//---------------------------------------------------------------------------------
template<typename T>
bool KeyframedData_<T>::update(const uint64_t& time)
{
	
	auto prev = _currentValue;
	_currentValue = getValueAtTime(time);
	
	return (prev != _currentValue);
	
	
	if(!_isTimeInDataBounds(_currentValue, time)){
		_lastUpdateTime = time;
//		return false;
		return (prev != _currentValue);
	}
	
	if(_lastUpdateTime == time)
	{
		ofLogError("KeyframedData_<T>::update") << "time reached the maximum time possible or something else went wrong";
		return false;
	}
	
	
	if(_data[_currentIndex]->time == time){// this block might be unnecesary. TODO: Double check
		
		_currentValue = _data[_currentIndex]->value;
		_currentIndex++;
		_lastUpdateTime = time;
		return (prev != _currentValue);
	}
	
	if(_data[_currentIndex]->time < time){
		_currentIndex = _findNextIndex(time);
	}
	
	
	if(_currentIndex == 0)
	{
		_lastUpdateTime = time;
		ofLogError("KeyframedData_<T>::update") << "_currentIndex should never be zero. ";
		
		return false;
	}
	
	if(_currentIndex >= _data.size())
	{
		_lastUpdateTime = time;
		ofLogError("KeyframedData_<T>::update") << "_currentIndex >= _data.size()). this should not happen";
		return false;
	}
	
//	std::cout <<" KeyframedData<D>::update\n";
	
	
	_currentValue = Interpolator::interpolateTimedData(_data[_currentIndex-1].get() , _data[_currentIndex].get(), time);
	
	return (prev != _currentValue);
	

	
	
	
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
	for(size_t i = 0; i < _data.size(); i++)
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
void KeyframedData_<T>::fromJson(const ofJson& j)
{
	BaseKeyframedData<TimedData_<T>>::fromJson(j);
	
	try {
		_currentValue = j.at("currentValue").get<T>();

	}
	catch (nlohmann::json::type_error& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (nlohmann::json::out_of_range& e)
	{
		std::cout << e.what() << '\n';
	}
	
}

//---------------------------------------------------------------------------------
template<typename T>
ofJson KeyframedData_<T>::toJson()
{
	ofJson j = BaseKeyframedData<TimedData_<T>>::toJson();
	j["currentValue"] = _currentValue;
	
	return j;
}



template<typename T>
std::string KeyframedData_<T>::_getTypeName()
{
	return std::string(typeid(T).name());
}



template<typename T>
uint64_t&  KeyframedData_<T>::_getTimeFromData(TimedData_<T>* d)
{
	return d->time;
}

//---------------------------------------------------------------------------------


uint64_t* KeyframedData_<void>::add(const uint64_t& time)
{
	
	if(_timedMap.count(time))
	{
		ofLogNotice("KeyframedData_<void>::add") << "there is already data at this point. Updating to new value. Returning nullptr";
		return nullptr;
	}
	return _addToCollection(time, true);
	
}
//---------------------------------------------------------------------------------


bool KeyframedData_<void>::update(const uint64_t& time)
{
	if(!_timeRange.contains( time)){
		_lastUpdateTime = time;
		return false;
	}
	
	if(_lastUpdateTime == time)
	{
		_lastUpdateTime = time;
		return false;
	}
	
	
	if(_lastUpdateTime > time)
	{
		_currentIndex = _findNextIndex(time);
	}
	
	
	bool needsTrigger = false;
	
///	TODO: Optimize this. Instead of using the for loop over all the keyframes only check the ones after the lastTriggeredIndex. This approach needs to listen to the timeController so the lastTriggeredIndex is reset when play starts
	
	while( _currentIndex < _data.size() && *_data[_currentIndex] <= time){
		needsTrigger = true;
		++_currentIndex;
	}

	_lastUpdateTime = time;
	
	if(needsTrigger) return true;
	
	
	return false;
	
}


//---------------------------------------------------------------------------------


size_t KeyframedData_<void>::_findNextIndex(const uint64_t& time)
{
	for(size_t i = 0; i < _data.size(); i++)
	{
		if(*_data[i] >= time)
		{
			return i;
		}
	}
	return _data.size();
}


std::string KeyframedData_<void>::_getTypeName()
{
	return std::string(typeid(void).name());
}


uint64_t& KeyframedData_<void>::_getTimeFromData(uint64_t* d)
{
	return *d;
}





template class BaseKeyframedData<uint64_t>;//void

template class BaseKeyframedData<TimedData_<bool>>;
template class BaseKeyframedData<TimedData_<char>>;
template class BaseKeyframedData<TimedData_<unsigned char>>;
template class BaseKeyframedData<TimedData_<signed char>>;
template class BaseKeyframedData<TimedData_<short>>;
template class BaseKeyframedData<TimedData_<unsigned short>>;
template class BaseKeyframedData<TimedData_<int>>;
template class BaseKeyframedData<TimedData_<unsigned int>>;
template class BaseKeyframedData<TimedData_<long>>;
template class BaseKeyframedData<TimedData_<unsigned long>>;
template class BaseKeyframedData<TimedData_<long long>>;
template class BaseKeyframedData<TimedData_<unsigned long long>>;
template class BaseKeyframedData<TimedData_<float>>;
template class BaseKeyframedData<TimedData_<double>>;



template class KeyframedData_<bool>;
template class KeyframedData_<char>;
template class KeyframedData_<unsigned char>;
template class KeyframedData_<signed char>;
template class KeyframedData_<short>;
template class KeyframedData_<unsigned short>;
template class KeyframedData_<int>;
template class KeyframedData_<unsigned int>;
template class KeyframedData_<long>;
template class KeyframedData_<unsigned long>;
template class KeyframedData_<long long>;
template class KeyframedData_<unsigned long long>;
template class KeyframedData_<float>;
template class KeyframedData_<double>;
//template class KeyframedData_<long double>;

} } // ofx::LineaDeTiempo

