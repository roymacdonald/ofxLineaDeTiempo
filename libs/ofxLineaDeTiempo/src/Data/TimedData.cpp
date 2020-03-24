//
//  TimedData.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/7/20.
//

#include "LineaDeTiempo/Data/TimedData.h"



namespace ofx {
namespace LineaDeTiempo {



template<typename DataType>
void TimedData_<DataType>::fromJson(const ofJson& j)
{
	j.at("value").get_to(value);
	j.at("time").get_to(time);
}

template<typename DataType>
void TimedData_<DataType>::toJson(ofJson& j)
{
	j["value"] = this->value;
	j["time"] = this->time;
}

//template<typename DataType>
//void TimedData_<DataType>::setTime(uint64_t _time)
//{
//
//#ifdef USE_EVENTS_FOR_TIMED_DATA_CHANGE
//#ifdef COMPARE_TIME_ON_SETTER
//	if(time == _time) return;
//#endif
//	ofNotifyEvent(timeChangedEvent, _time, this);
//#endif
//	time = _time;
//}
//template<typename DataType>
//const uint64_t& TimedData_<DataType>::getTime() const
//{
//	return time;
//}





} } // ofx::LineaDeTiempo




