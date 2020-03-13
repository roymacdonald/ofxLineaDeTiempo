//
//  Interpolator.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include "LineaDeTiempo/Data/TimedData.h"
#include <vector>
#include <map>
#include <type_traits>
#include "MUI/Utils.h"
#include "ofMath.h"
#include "ofLog.h"
#include "ofColor.h"
#include "ofRectangle.h"
#include <glm/gtx/matrix_interpolation.hpp>


namespace ofx {
namespace LineaDeTiempo {


class Interpolator
{
public:
	
	
	
	template<typename DataType>
	static DataType interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		if(from->time == to->time){
			ofLogWarning("ofxLineaDeTiempo::Interpolator::interpolateTimedData") << "cant interpolate to TimedData that has the same time. This should not happen.";
			return from->value;
		}
		if(from->time > to->time){
			ofLogWarning("ofxLineaDeTiempo::Interpolator::interpolateTimedData") << "needed to flip interpolation. This should not happen";
			return _interpolateTimedData(to, from, _time);
		}
		if(from->time >= _time){
			//			ofLogVerbose("ofxLineaDeTiempo::Interpolator::interpolateTimedData") << "passed time is out of bounds.";
			return from->value;
		}
		if(to->time <= _time){
			//			ofLogVerbose("ofxLineaDeTiempo::Interpolator::interpolateTimedData") << "passed time is out of bounds.";
			return to->value;
		}
	
		return _interpolateTimedData(from, to, _time);
	}
	
	
protected:
	
	template<typename DataType>
	static DataType _interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		ofLogError("ofxLineaDeTiempo::Interpolator::interpolateTimedData") << "Unsupported data type. can not interpolate";
	}
	
	
	template<typename DataType>
	static typename std::enable_if<std::is_integral<DataType>::value, DataType>::type
	_interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return ofMap(_time, from->time, to->time, from->value, to->value);
	}

	template<typename DataType>
	static typename std::enable_if<std::is_base_of<float, DataType>::value || std::is_same<float, DataType>::value, DataType>::type
	_interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return ofMap(_time, from->time, to->time, from->value, to->value);
	}

	//------------- interpolate double precision floating point numbers (double)
	template<typename DataType>
	static typename std::enable_if<std::is_base_of<double, DataType>::value || std::is_same<double, DataType>::value, DataType>::type
	_interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return MUI::Math::lerp(_time, from->time, to->time, from->value, to->value);
	}

	//------------- interpolate long double precision floating point numbers (long double)
	template<typename DataType>
	static typename std::enable_if<std::is_base_of<long double, DataType>::value || std::is_same<long double, DataType>::value, DataType>::type
	_interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return MUI::Math::lerpl(_time, from->time, to->time, from->value, to->value);
	}

	///--------------------- ofRectangle
	///

	template<typename DataType>
	static typename std::enable_if<std::is_base_of<ofRectangle, DataType>::value || std::is_same<ofRectangle, DataType>::value, DataType>::type
	_interpolateTimedData(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
	{
		return ofRectangle(glm::mix(from->value.getPosition(), to->value.getPosition(), MUI::Math::lerp(_time, from->time, to->time, 0, 1)),
						   ofMap(_time, from->time, to->time, from->value.width, to->value.width),
						   ofMap(_time, from->time, to->time, from->value.height, to->value.height)
						   );
	}


	///--------------------- GLM
	///
	//------------- interpolate any GLM vector
	template<int C, typename T, glm::qualifier Q >
	static glm::vec<C,T,Q> 
	_interpolateTimedData(const TimedData_<glm::vec<C, T, Q> >* from, const TimedData_<glm::vec<C, T, Q> >* to, const uint64_t& _time)
	{
		return glm::mix(from->value, to->value, MUI::Math::lerp(_time, from->time, to->time, 0, 1) );
	}


	//------------- interpolate any GLM mat4
	// =====  this is a GLM experimental feature.
	// =====  It should work well with translation and rotation, but not with scaling
	template <typename T, glm::qualifier Q = glm::defaultp>
	static glm::mat<4, 4, T, Q> 
	_interpolateTimedData(const TimedData_<glm::mat<4, 4, T, Q>>* from, const TimedData_<glm::mat<4, 4, T, Q>>* to, const uint64_t& _time)
	{
		return glm::interpolate(from->value, to->value, (T) (MUI::Math::lerp(_time, from->time, to->time, 0, 1)));
	}

	//-------------- interpolate any GLM quaternion, using spherical linear interpolation (slerp)
	template<typename T, glm::qualifier Q = glm::defaultp>
//	static typename std::enable_if<std::is_base_of<glm::qua<T, Q>, DataType>::value, DataType>::type
	glm::qua<T, Q> 
	_interpolateTimedData(const TimedData_<glm::qua<T, Q>>* from, const TimedData_<glm::qua<T, Q>>* to, const uint64_t& _time)
	{
		return glm::slerp(from->value, to->value, (T) (MUI::Math::lerp(_time, from->time, to->time, 0, 1)));
	}

	///--------------------- ofColor
	///

	template<typename PixelType>
	static ofColor_<PixelType>
	_interpolateTimedData(const TimedData_<ofColor_<PixelType>>* from, const TimedData_<ofColor_<PixelType>> * to, const uint64_t& _time)
	{
		return from->value.getLerped(to->value , MUI::Math::lerp(_time, from->time, to->time, 0, 1));
	}
};

} } // ofx::LineaDeTiempo
