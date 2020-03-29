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



} } // ofx::LineaDeTiempo




