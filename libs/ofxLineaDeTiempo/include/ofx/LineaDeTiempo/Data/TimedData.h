//
//  TimedData.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include <stdint.h>
#include <type_traits>
#include "LineaDeTiempo/Data/jsonSerializer.h"
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"
#include "ofEvent.h"


namespace ofx {
namespace LineaDeTiempo {


template<class DataType>
class TimedData_: public AbstractSerializable
{
public:
	
	TimedData_(){}
	TimedData_(const DataType& _value, const uint64_t& _time)
	: value(_value)
	, time(_time)
	{}
	virtual ~TimedData_(){}
	
	DataType value;
	uint64_t time = 0;
	

	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;
	
};

template<class DataType>
inline std::ostream& operator<<(std::ostream& os, const TimedData_<DataType>& data)
{
	os <<  data.getTime() << ", " << data.value;

	return os;
}
template<class DataType>
inline std::istream& operator>>(std::istream& is, TimedData_<DataType>& data)
{
	is >> data.time;
	is.ignore(2);
	is >> data.value;
	return is;

}


} } // ofx::LineaDeTiempo


namespace nlohmann{
template <typename T>
struct adl_serializer<ofx::LineaDeTiempo::TimedData_<T>> {
	static ofx::LineaDeTiempo::TimedData_<T> from_json(const json& j)
	{
		
		return {j["value"].get<T>(), j["time"].get<uint64_t>()};
	}

	static void to_json(json& j, ofx::LineaDeTiempo::TimedData_<T> t)
	{
		j["value"] = t.value;
		j["time"] = t.time;
	}
};

}
