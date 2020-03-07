//
//  TimedData.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include <stdint.h>
#include <vector>
#include <map>
#include <type_traits>
#include "MUI/Utils.h"
#include "ofMath.h"
#include "ofLog.h"
#include <glm/gtx/matrix_interpolation.hpp>


namespace ofx {
namespace LineaDeTiempo {


template<typename DataType>
class TimedData_
{
	TimedData_(){}
	TimedData_(const DataType& _value, const uint64_t& _time):
	value(_value),
	time(_time)
	{}
	virtual ~TimedData_(){}
	
	DataType value;
	uint64_t time;
	
	DataType interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		if(this->time > to->time){
			ofLogWarning("ofxLineaDeTiempo::TimedData::interpolateTo") << "needed to flip interpolation. This should not happen";
			return to->interpolateTo(this, _time);
		}
		return _interpolateTo(to, _time);
	}
	
protected:
	
//	DataType interpolateTo(const TimedData_* to, const uint64_t& _time) const;
	template<>
	typename std::enable_if<std::is_integral<DataType>::value, DataType>::type
	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		
		return ofMap(_time, this->time, to->time, this->value, to->value);
	}
	
	template<>
	typename std::enable_if<std::is_base_of<double, DataType>::value, DataType>::type
	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		
		return MUI::Math::lerp(_time, this->time, to->time, this->value, to->value);
	}
	
	template<>
	typename std::enable_if<std::is_base_of<long double, DataType>::value, DataType>::type
	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		
		return MUI::Math::lerpl(_time, this->time, to->time, this->value, to->value);
	}


	template<int C, typename T, glm::qualifier Q>
	typename std::enable_if<std::is_base_of<glm::vec<C, T, Q>, DataType>::value, DataType>::type
	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		return glm::mix(this->value, to->value, MUI::Math::lerp(_time, this->time, to->time, 0, 1) );
	}

	
	
	template <typename T, glm::qualifier Q = glm::defaultp>
	typename std::enable_if<std::is_base_of<glm::mat<4, 4, T, Q>, DataType>::value, DataType>::type
	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		return glm::interpolate(this->value, to->value, MUI::Math::lerp(_time, this->time, to->time, 0, 1) );
	}
	
	
	template<typename T, glm::qualifier Q = glm::defaultp>
	typename std::enable_if<std::is_base_of<glm::qua<T, Q>, DataType>::value, DataType>::type
	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
	{
		return glm::slerp(this->value, to->value, MUI::Math::lerp(_time, this->time, to->time, 0, 1));
	}
	
	
	

};






//template<length_t C, length_t R, typename T, qualifier Q = defaultp> struct mat;
//template<typename T, qualifier Q = defaultp> struct qua;



} } // ofx::LineaDeTiempo






