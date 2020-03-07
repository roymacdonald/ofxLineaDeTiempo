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
DataType TimedData_<DataType>::interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
{
	if(this->time == to->time){
		ofLogWarning("ofxLineaDeTiempo::TimedData::interpolateTo") << "cant interpolate to TimedData that has the same time. This should not happen.";
		return this->value;
	}
	if(this->time > to->time){
		ofLogWarning("ofxLineaDeTiempo::TimedData::interpolateTo") << "needed to flip interpolation. This should not happen";
		return to->interpolateTo(this, _time);
	}
	if(this->time >= _time){
		//			ofLogVerbose("ofxLineaDeTiempo::TimedData::interpolateTo") << "passed time is out of bounds.";
		return this->value;
	}
	if(to->time <= _time){
		//			ofLogVerbose("ofxLineaDeTiempo::TimedData::interpolateTo") << "passed time is out of bounds.";
		return to->value;
	}
	
	return interpolateTimedValue(this, to, _time);
}
	
template class TimedData_<ofColor_<char>>;
template class TimedData_<ofColor_<unsigned char>>;
template class TimedData_<ofColor_<short>>;
template class TimedData_<ofColor_<unsigned short>>;
template class TimedData_<ofColor_<int>>;
template class TimedData_<ofColor_<unsigned int>>;
template class TimedData_<ofColor_<long>>;
template class TimedData_<ofColor_<unsigned long>>;
template class TimedData_<ofColor_<float>>;
template class TimedData_<ofColor_<double>>;

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

} } // ofx::LineaDeTiempo
