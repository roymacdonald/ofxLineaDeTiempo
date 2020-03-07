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
#include "ofColor.h"
#include <glm/gtx/matrix_interpolation.hpp>


namespace ofx {
namespace LineaDeTiempo {


template<class DataType>
class TimedData_
{
public:
	TimedData_(){}
	TimedData_(const DataType& _value, const uint64_t& _time):
	value(_value),
	time(_time)
	{}
	virtual ~TimedData_(){}
	
	DataType value;
	uint64_t time;
	
	//TODO: serialize and unserialize
	
	DataType interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const;
//	{
//		if(this->time == to->time){
//			ofLogWarning("ofxLineaDeTiempo::TimedData::interpolateTo") << "cant interpolate to TimedData that has the same time. This should not happen.";
//			return this->value;
//		}
//		if(this->time > to->time){
//			ofLogWarning("ofxLineaDeTiempo::TimedData::interpolateTo") << "needed to flip interpolation. This should not happen";
//			return to->interpolateTo(this, _time);
//		}
//		if(this->time >= _time){
////			ofLogVerbose("ofxLineaDeTiempo::TimedData::interpolateTo") << "passed time is out of bounds.";
//			return this->value;
//		}
//		if(to->time <= _time){
////			ofLogVerbose("ofxLineaDeTiempo::TimedData::interpolateTo") << "passed time is out of bounds.";
//			return to->value;
//		}
//
//		return _interpolateTo(to, _time);
//	}
	
protected:
	

	
	///\brief get the interpolated value between this TimedData value and the passed TimedData at a certain time
	///  This applies to all the following template specializations
	///\param to the target TimedData you want to interpolate to.
	///\param _time the time at which you want this interpolation to happen. It must be in between this->time and to->time.
	///\returns interpolated DataType
	

	///--------------------- numbers
	///
	//------------- interpolate float and any kind of integer number, (default)
//	template<>
//	typename std::enable_if<std::is_integral<DataType>::value || std::is_base_of<float, DataType>::value, DataType>::type
//	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
//	{
//		return ofMap(_time, this->time, to->time, this->value, to->value);
//	}
//
//	//------------- interpolate double precision floating point numbers (double)
//	template<>
//	typename std::enable_if<std::is_base_of<double, DataType>::value, DataType>::type
//	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
//	{
//		return MUI::Math::lerp(_time, this->time, to->time, this->value, to->value);
//	}
//
//	//------------- interpolate long double precision floating point numbers (long double)
//	template<>
//	typename std::enable_if<std::is_base_of<long double, DataType>::value, DataType>::type
//	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
//	{
//		return MUI::Math::lerpl(_time, this->time, to->time, this->value, to->value);
//	}
//
//	///--------------------- GLM
//	///
//	//------------- interpolate any GLM vector
//	template<int C, typename T, glm::qualifier Q>
//	typename std::enable_if<std::is_base_of<glm::vec<C, T, Q>, DataType>::value, DataType>::type
//	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
//	{
//		return glm::mix(this->value, to->value, MUI::Math::lerp(_time, this->time, to->time, 0, 1) );
//	}
//
//
//	//------------- interpolate any GLM mat4
//	// =====  this is a GLM experimental feature.
//	// =====  It should work well with translation and rotation, but not with scaling
//	template <typename T, glm::qualifier Q = glm::defaultp>
//	typename std::enable_if<std::is_base_of<glm::mat<4, 4, T, Q>, DataType>::value, DataType>::type
//	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
//	{
//		return glm::interpolate(this->value, to->value, MUI::Math::lerp(_time, this->time, to->time, 0, 1) );
//	}
//
//	//-------------- interpolate any GLM quaternion, using spherical linear interpolation (slerp)
//	template<typename T, glm::qualifier Q = glm::defaultp>
//	typename std::enable_if<std::is_base_of<glm::qua<T, Q>, DataType>::value, DataType>::type
//	_interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const
//	{
//		return glm::slerp(this->value, to->value, MUI::Math::lerp(_time, this->time, to->time, 0, 1));
//	}
//
//	///--------------------- ofColor
//	///
//	//-------------- interpolate any ofColor (ofFloatColor, ofShortColor, ofColor, or any other ofColor_<PixelType>
////	template<typename PixelType>
////	typename std::enable_if< std::is_base_of< ofColor_<PixelType>, DataType>::value, DataType>::type
////	_interpolateTo(const TimedData_< DataType<PixelType> > * to, const uint64_t& _time) const
////	{
////		return this->value.getLerped(to , MUI::Math::lerp(_time, this->time, to->time, 0, 1));
////	}
//
//
//	/// aaargghh! I can not template the ofColor !
//	/// TODO: fix
//	template<>
//	typename std::enable_if< std::is_base_of<ofColor, DataType> ::value, DataType >::type
//	_interpolateTo(const TimedData_<DataType> * to, const uint64_t& _time) const
//	{
//		return this->value.getLerped(to , MUI::Math::lerp(_time, this->time, to->time, 0, 1));
//	}
	
//	template<>
//		typename std::enable_if<
//
//					std::is_base_of<ofColor_<char>, DataType> ::value ||
//					std::is_base_of<ofColor_<unsigned char>, DataType> ::value ||
//					std::is_base_of<ofColor_<short>, DataType> ::value ||
//					std::is_base_of<ofColor_<unsigned short>, DataType> ::value ||
//					std::is_base_of<ofColor_<int>, DataType> ::value ||
//					std::is_base_of<ofColor_<unsigned int>, DataType> ::value ||
//					std::is_base_of<ofColor_<long>, DataType> ::value ||
//					std::is_base_of<ofColor_<unsigned long>, DataType> ::value ||
//					std::is_base_of<ofColor_<float>, DataType> ::value ||
//					std::is_base_of<ofColor_<double>, DataType> ::value,
//				 DataType >::type
//		_interpolateTo(const TimedData_<DataType> * to, const uint64_t& _time) const
//		{
//			return this->value.getLerped(to , MUI::Math::lerp(_time, this->time, to->time, 0, 1));
//		}
//
	
	

};

//typename std::enable_if<std::is_integral<DataType>::value || std::is_base_of<float, DataType>::value, DataType>::type
	template<typename DataType>
	typename std::enable_if<std::is_integral<DataType>::value, DataType>::type
	interpolateTimedValue(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return ofMap(_time, from->time, to->time, from->value, to->value);
	}
	
	template<typename DataType>
	typename std::enable_if<std::is_base_of<float, DataType>::value || std::is_same<float, DataType>::value, DataType>::type
	interpolateTimedValue(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return ofMap(_time, from->time, to->time, from->value, to->value);
	}

	//------------- interpolate double precision floating point numbers (double)
	template<typename DataType>
	typename std::enable_if<std::is_base_of<double, DataType>::value || std::is_same<double, DataType>::value, DataType>::type
	interpolateTimedValue(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return MUI::Math::lerp(_time, from->time, to->time, from->value, to->value);
	}
	
	//------------- interpolate long double precision floating point numbers (long double)
	template<typename DataType>
	typename std::enable_if<std::is_base_of<long double, DataType>::value || std::is_same<long double, DataType>::value, DataType>::type
	interpolateTimedValue(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return MUI::Math::lerpl(_time, from->time, to->time, from->value, to->value);
	}

	///--------------------- GLM
	///
	//------------- interpolate any GLM vector
	template<int C, typename T, glm::qualifier Q >
	glm::vec<C,T,Q> interpolateTimedValue(const TimedData_<glm::vec<C, T, Q> >* from, const TimedData_<glm::vec<C, T, Q> >* to, const uint64_t& _time)
	{
		return glm::mix(from->value, to->value, MUI::Math::lerp(_time, from->time, to->time, 0, 1) );
	}

	
	//------------- interpolate any GLM mat4
	// =====  this is a GLM experimental feature.
	// =====  It should work well with translation and rotation, but not with scaling
	template <typename T, glm::qualifier Q = glm::defaultp>
	glm::mat<4, 4, T, Q> interpolateTimedValue(const TimedData_<glm::mat<4, 4, T, Q>>* from, const TimedData_<glm::mat<4, 4, T, Q>>* to, const uint64_t& _time)
	{
		return glm::interpolate(from->value, to->value, (T) (MUI::Math::lerp(_time, from->time, to->time, 0, 1)));
	}
	
	//-------------- interpolate any GLM quaternion, using spherical linear interpolation (slerp)
	template<typename T, glm::qualifier Q = glm::defaultp>
//	typename std::enable_if<std::is_base_of<glm::qua<T, Q>, DataType>::value, DataType>::type
	glm::qua<T, Q> interpolateTimedValue(const TimedData_<glm::qua<T, Q>>* from, const TimedData_<glm::qua<T, Q>>* to, const uint64_t& _time)
	{
		return glm::slerp(from->value, to->value, (T) (MUI::Math::lerp(_time, from->time, to->time, 0, 1)));
	}

	///--------------------- ofColor
	///
	//-------------- interpolate any ofColor (ofFloatColor, ofShortColor, ofColor, or any other ofColor_<PixelType>
//	template<typename PixelType>
//	typename std::enable_if< std::is_base_of< ofColor_<PixelType>, DataType>::value, DataType>::type
//	interpolateTimedValue(const TimedData_< DataType<PixelType> > * to, const uint64_t& _time) const
//	{
//		return from->value.getLerped(to , MUI::Math::lerp(_time, from->time, to->time, 0, 1));
//	}
	
	
	template<typename PixelType>
	ofColor_<PixelType>
	interpolateTimedValue(const TimedData_<ofColor_<PixelType>>* from, const TimedData_<ofColor_<PixelType>> * to, const uint64_t& _time)
	{
		return from->value.getLerped(to->value , MUI::Math::lerp(_time, from->time, to->time, 0, 1));
	}





	
	
} } // ofx::LineaDeTiempo






