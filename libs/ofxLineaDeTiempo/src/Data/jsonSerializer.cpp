//
//  jsonSerializer.cpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/9/20.
//

//#include "LineaDeTiempo/Data/jsonSerializer.h"


//using namespace nlohmann;
//
//
//void to_json(json& j, const glm::vec3 & data){ j = json{{"x", data.x}, {"y", data.y}, {"z", data.z}}; }
//void to_json(json& j, const glm::vec4 & data){ j = json{{"x", data.x}, {"y", data.y}, {"z", data.z}, {"w", data.w}}; }
//void to_json(json& j, const glm::quat & data){ j = json{{"x", data.x}, {"y", data.y}, {"z", data.z}, {"w", data.w}}; }
//void to_json(json& j, const glm::mat4 & data)
//{
//	j = json{	data[0][0],data[1][0],data[2][0],data[3][0],
//			    		data[0][1],data[1][1],data[2][1],data[3][1],
//			    		data[0][2],data[1][2],data[2][2],data[3][2],
//			    		data[0][3],data[1][3],data[2][3],data[3][3]};
//}
//void to_json(json& j, const ofRectangle& data){ j = json{data.x, data.y, data.width, data.height};}
//
//template<typename C>
//void color_to_json(json& j, const ofColor_<C>& color)
//{
//	j = json{color.r, color.g, color.b, color.a};
//}
////void to_json(json& j, const char& data)                     { j = json                        { data}; }
////void to_json(json& j, const unsigned char& data)            { j = json                        { data}; }
////void to_json(json& j, const short& data)                    { j = json                        { data}; }
////void to_json(json& j, const unsigned short& data)           { j = json                        { data}; }
////void to_json(json& j, const int& data)                      { j = json                        { data}; }
////void to_json(json& j, const unsigned int& data)             { j = json                        { data}; }
////void to_json(json& j, const long& data)                     { j = json                        { data}; }
////void to_json(json& j, const unsigned long& data)            { j = json                        { data}; }
////void to_json(json& j, const float& data)                    { j = json                        { data}; }
////void to_json(json& j, const double& data)                   { j = json                        { data}; }
////void to_json(json& j, const long double& data)              { j = json                        { data}; }
//
//void to_json(json& j, const ofColor_<char>& data)           { color_to_json<char>(j, data); }
//void to_json(json& j, const ofColor_<unsigned char>& data)  { color_to_json<unsigned char>(j, data); }
//void to_json(json& j, const ofColor_<short>& data)          { color_to_json<short>(j, data); }
//void to_json(json& j, const ofColor_<unsigned short>& data) { color_to_json<unsigned short>(j, data); }
//void to_json(json& j, const ofColor_<int>& data)            { color_to_json<int>(j, data); }
//void to_json(json& j, const ofColor_<unsigned int>& data)   { color_to_json<unsigned int>(j, data); }
//void to_json(json& j, const ofColor_<long>& data)           { color_to_json<long>(j, data); }
//void to_json(json& j, const ofColor_<unsigned long>& data)  { color_to_json<unsigned long>(j, data); }
//void to_json(json& j, const ofColor_<float>& data)          { color_to_json<float>(j, data); }
//void to_json(json& j, const ofColor_<double>& data)         { color_to_json<double>(j, data); }
//
//
//void from_json(const json& j, glm::vec2& d){ j.at("x").get_to(d.x);  j.at("y").get_to(d.y); }
//void from_json(const json& j, glm::vec3& d){ j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z); }
//void from_json(const json& j, glm::vec4& d){ j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);  j.at("w").get_to(d.w); }
//void from_json(const json& j, glm::quat& d){ j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);  j.at("w").get_to(d.w); }
//void from_json(const json& j, glm::mat4& d){
//	for(int y = 0; y < 4; y++)
//	{
//		for(int x = 0; x < 4; x++)
//		{
//			j.at(y*4 + x).get_to(d[x][y]);
//		}
//	}
//}
//void from_json(const json& j, ofRectangle& d)
//{
//	d.set(j.at(0).get<float>(),j.at(1).get<float>(),j.at(2).get<float>(),j.at(3).get<float>());
//
//}
//template <typename C>
//void color_from_json(const json& j, ofColor_<C>& color)  {
//	j.at(0).get_to(color.r);  j.at(1).get_to(color.g);   j.at(2).get_to(color.b);  j.at(3).get_to(color.a);
//
//}
//
//void from_json(const json& j, ofColor_<char>& d)           { color_from_json<char>(j, d); }
//void from_json(const json& j, ofColor_<unsigned char>& d)  { color_from_json<unsigned char>(j, d); }
//void from_json(const json& j, ofColor_<short>& d)          { color_from_json<short>(j, d); }
//void from_json(const json& j, ofColor_<unsigned short>& d) { color_from_json<unsigned short>(j, d); }
//void from_json(const json& j, ofColor_<int>& d)            { color_from_json<int>(j, d); }
//void from_json(const json& j, ofColor_<unsigned int>& d)   { color_from_json<unsigned int>(j, d); }
//void from_json(const json& j, ofColor_<long>& d)           { color_from_json<long>(j, d); }
//void from_json(const json& j, ofColor_<unsigned long>& d)  { color_from_json<unsigned long>(j, d); }
//void from_json(const json& j, ofColor_<float>& d)          { color_from_json<float>(j, d); }
//void from_json(const json& j, ofColor_<double>& d)         { color_from_json<double>(j, d); }
//
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//
//
//}} // ofx::LineaDeTiempo
