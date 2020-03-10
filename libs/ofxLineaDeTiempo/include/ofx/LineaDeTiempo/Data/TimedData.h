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
#include "ofRectangle.h"
#include <glm/gtx/matrix_interpolation.hpp>

//#include "ofJson.h"
#include "LineaDeTiempo/Data/jsonSerializer.h"

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
	

	///\brief get the interpolated value between this TimedData value and the passed TimedData at a certain time
	///\param to the target TimedData you want to interpolate to.
	///\param _time the time at which you want this interpolation to happen. It must be in between this->time and to->time.
	///\returns interpolated DataType

	DataType interpolateTo(const TimedData_<DataType>* to, const uint64_t& _time) const;
	

//	friend std::ostream& operator<<(std::ostream& os, const TimedData_<DataType>& data);
//	friend std::istream& operator>>(std::istream& is, TimedData_<DataType>& data);


	
};
template<typename DataType>
inline std::ostream& operator<<(std::ostream& os, const TimedData_<DataType>& data)
{
	os <<  data.time << ", " << data.value;
	
	return os;
}
template<typename DataType>
inline std::istream& operator>>(std::istream& is, TimedData_<DataType>& data)
{

	is >> data.time;
	is.ignore(2);
	is >> data.value;
	return is;
	
}


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

	///--------------------- ofRectangle
	///

	template<typename DataType>
	typename std::enable_if<std::is_base_of<ofRectangle, DataType>::value || std::is_same<ofRectangle, DataType>::value, DataType>::type
	interpolateTimedValue(const TimedData_<DataType>* from, const TimedData_<DataType>* to, const uint64_t& _time)
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
		
	template<typename PixelType>
	ofColor_<PixelType>
	interpolateTimedValue(const TimedData_<ofColor_<PixelType>>* from, const TimedData_<ofColor_<PixelType>> * to, const uint64_t& _time)
	{
		return from->value.getLerped(to->value , MUI::Math::lerp(_time, from->time, to->time, 0, 1));
	}
	


	


//
//template<typename DataType>
//void to_json(nlohmann::json& j, const TimedData_<DataType>& d) {
//	j = nlohmann::json{{"time", d.time}, {"value", d.value}};
// }
//
//template<typename DataType>
//void from_json(const nlohmann::json& j, TimedData_<DataType>& d) {
//	 j.at("time").get_to(d.time);
//	 j.at("value").get_to(d.value);
// }
//
//template <typename T>
////struct adl_serializer {
//    static void to_json(nlohmann::json& j, const TimedData_<T>& d) {
//		j = nlohmann::json{{"time", d.time}, {"value", d.value}};
//
//    }
//
//    static void from_json(const nlohmann::json& j, TimedData_<T>& d) {
//        j.at("time").get_to(d.time);
//		j.at("value").get_to(d.value);
//
//    }
//};
//




} } // ofx::LineaDeTiempo


namespace nlohmann {
    template <typename T>
    struct adl_serializer<ofx::LineaDeTiempo::TimedData_<T>> {
        static ofx::LineaDeTiempo::TimedData_<T> from_json(const json& j) {
			return {j["value"].get<T>(), j["time"].get<uint64_t>()};
        }

        static void to_json(json& j, ofx::LineaDeTiempo::TimedData_<T> t) {
			j["value"] = t.value;
			j["time"] = t.time;
        }
    };
}
