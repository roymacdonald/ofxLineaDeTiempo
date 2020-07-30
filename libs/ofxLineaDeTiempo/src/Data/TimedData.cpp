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
ofJson TimedData_<DataType>::toJson()
{
	ofJson j;
	j["value"] = this->value;
	j["time"] = this->time;
	return j;
}

template class TimedData_<bool>;
template class TimedData_<char>;
template class TimedData_<unsigned char>;
template class TimedData_<signed char>;
template class TimedData_<short>;
template class TimedData_<unsigned short>;
template class TimedData_<int>;
template class TimedData_<unsigned int>;
template class TimedData_<long>;
template class TimedData_<unsigned long>;
template class TimedData_<long long>;
template class TimedData_<unsigned long long>;
template class TimedData_<float>;
template class TimedData_<double>;



} } // ofx::LineaDeTiempo




