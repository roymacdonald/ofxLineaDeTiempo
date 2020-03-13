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

template<typename DataType>
void TimedData_<DataType>::setTime(uint64_t _time)
{
		
#ifdef USE_EVENTS_FOR_TIMED_DATA_CHANGE
#ifdef COMPARE_TIME_ON_SETTER
	if(time == _time) return;
#endif
	ofNotifyEvent(timeChangedEvent, _time, this);
#endif
	time = _time;
}
template<typename DataType>
const uint64_t& TimedData_<DataType>::getTime() const
{
	return time;
}

//template class TimedData_<ofRectangle>;

template class TimedData_<ofColor_<char>>;
template class TimedData_<ofColor_<unsigned char>>;
template class TimedData_<ofColor_<short>>;
template class TimedData_<ofColor_<unsigned short>>;
template class TimedData_<ofColor_<int>>;
template class TimedData_<ofColor_<unsigned int>>;
template class TimedData_<ofColor_<long>>;
template class TimedData_<ofColor_<unsigned long>>;
template class TimedData_<ofColor_<float>>;
//template class TimedData_<ofColor_<double>>;

template class TimedData_<glm::vec2>;
template class TimedData_<glm::vec3>;
template class TimedData_<glm::vec4>;
template class TimedData_<glm::quat>;
template class TimedData_<glm::mat4>;


template class TimedData_<char>;
template class TimedData_<unsigned char>;
template class TimedData_<short>;
template class TimedData_<unsigned short>;
template class TimedData_<int>;
template class TimedData_<unsigned int>;
template class TimedData_<long>;
template class TimedData_<unsigned long>;
template class TimedData_<float>;
template class TimedData_<double>;
//template class TimedData_<long double>;



} } // ofx::LineaDeTiempo




