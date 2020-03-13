//
//  jsonSerializer.cpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

//#include "jsonSerializer.h"
//#include "LineaDeTiempo/Data/jsonSerializer.h"
//#include "ofRectangle.h"

//void from_json(const nlohmann::json& j, ofRectangle& d)
//{
//	d.set(j.at(0).get<float>(),j.at(1).get<float>(),j.at(2).get<float>(),j.at(3).get<float>());
//}
//void to_json(nlohmann::json& j, const ofRectangle & data)
//{
//	j = nlohmann::json{data.x, data.y, data.width, data.height};
//}



	
//template<> void nlohmann::adl_serializer<ofRectangle>::from_json(const nlohmann::json& j, ofRectangle& d)
//{
//	d.set(j.at(0).get<float>(),j.at(1).get<float>(),j.at(2).get<float>(),j.at(3).get<float>());
//}
//template<> void nlohmann::adl_serializer<ofRectangle>::to_json(nlohmann::json& j, const ofRectangle & data)
//{
//	j = json{data.x, data.y, data.width, data.height};
//}



//template <typename T>
//ofx::LineaDeTiempo::TimedData_<T> nlohmann::adl_serializer<ofx::LineaDeTiempo::TimedData_<T>>::from_json(const nlohmann::json& j)
//{
//	return {j["value"].get<T>(), j["time"].get<uint64_t>()};
//}
//template <typename T>
//void nlohmann::adl_serializer<ofx::LineaDeTiempo::TimedData_<T>>::to_json(nlohmann::json& j, ofx::LineaDeTiempo::TimedData_<T> t)
//{
//	j["value"] = t.value;
//	j["time"] = t.time;
//}

