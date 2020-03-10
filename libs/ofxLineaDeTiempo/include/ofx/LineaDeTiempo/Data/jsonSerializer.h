//
//  jsonSerializer.hpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/9/20.
//
#pragma once
#include "ofMain.h"


namespace nlohmann {

template <int D, typename T, glm::qualifier Q>
struct adl_serializer<glm::vec<D, T, Q>> {
//	static const string indNames [] = {"x","y","z","w"};
   static void from_json(const json& j, glm::vec<D, T, Q>& d)
	   {
		   for(int i = 0; i < D; i++)
		   {
			   j.at(i).get_to(d[i]);
		   }
//		   j.at("x").get_to(d.x);  j.at("y").get_to(d.y);
	   }
   static void to_json(json& j, const glm::vec<D, T, Q> & d)
	{
//		std::vector<T>v(D);
		j = json::array();
		for(int i = 0; i < D; i++)
		{
			j.emplace_back( d[i]);
//			j.at(i) = d[i];
		}
//		j = json{v};
//	   j = json{{"x", data.x}, {"y", data.y}};
   }
};


//template <>
// struct adl_serializer<glm::vec2> {
//	static void from_json(const json& j, glm::vec2& d)
//		{
//			j.at("x").get_to(d.x);  j.at("y").get_to(d.y);
//		}
//	static void to_json(json& j, const glm::vec2 & data)
//	 {
//		j = json{{"x", data.x}, {"y", data.y}};
//	}
// };
//
//template <>
// struct adl_serializer<glm::vec3> {
//	static void from_json(const json& j, glm::vec3& d)
//		{
//			j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);
//		}
//	static void to_json(json& j, const glm::vec3 & data)
//	 {
//		j = json{{"x", data.x}, {"y", data.y}, {"z", data.z}};
//	}
// };
//template <>
//struct adl_serializer<glm::vec4> {
//   static void from_json(const json& j, glm::vec4& d)
//	   {
//		   j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);   j.at("w").get_to(d.w);
//	   }
//   static void to_json(json& j, const glm::vec4 & data)
//	{
//		j = json{{"x", data.x}, {"y", data.y}, {"z", data.z}, {"w", data.w}};
//   }
//};


template <typename T, glm::qualifier Q>
struct adl_serializer<glm::qua<T, Q>> {
   static void from_json(const json& j, glm::qua<T, Q>& d)
	   {
		   for(int i = 0; i < 4; i++)
		   {
			   j.at(i).get_to(d[i]);
		   }
//		   j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);   j.at("w").get_to(d.w);
	   }
   static void to_json(json& j, const glm::qua<T, Q> & data)
	{
		j = json::array();
				for(int i = 0; i < 4; i++)
				{
					j.emplace_back( data[i]);
		//			j.at(i) = d[i];
				}
//		j = json{{"x", data.x}, {"y", data.y}, {"z", data.z}, {"w", data.w}};
   }
};

template <>
struct adl_serializer<glm::mat4> {
   static void from_json(const json& j, glm::mat4& d)
	   {
		   for(int y = 0; y < 4; y++)
		   {
			   for(int x = 0; x < 4; x++)
			   {
				   j.at(y*4 + x).get_to(d[x][y]);
			   }
		   }
	   }
   static void to_json(json& j, const glm::mat4 & data)
	{
		j = json{	data[0][0],data[1][0],data[2][0],data[3][0],
							data[0][1],data[1][1],data[2][1],data[3][1],
							data[0][2],data[1][2],data[2][2],data[3][2],
							data[0][3],data[1][3],data[2][3],data[3][3]};

   }
};
//template <>
//struct adl_serializer<ofRectangle> {
//	static void from_json(const json& j, ofRectangle& d)
//	{
//		d.set(j.at(0).get<float>(),j.at(1).get<float>(),j.at(2).get<float>(),j.at(3).get<float>());
//	}
//	static void to_json(json& j, const ofRectangle& data)
//	{
//		j = json{data.x, data.y, data.width, data.height};
//	}
//};

template <typename PixelType>
struct adl_serializer<ofColor_<PixelType>> {
	static void from_json(const json& j, ofColor_<PixelType>& color)
	{
		j.at(0).get_to(color.r);
		j.at(1).get_to(color.g);
		j.at(2).get_to(color.b);
		j.at(3).get_to(color.a);
	}
	static void to_json(json& j, const ofColor_<PixelType>& color)
	{
		j = json{color.r, color.g, color.b, color.a};
		
	}
};


}

//void to_json(nlohmann::json& j, const glm::vec2 & data);
//void to_json(nlohmann::json& j, const glm::vec3 & data);
//void to_json(nlohmann::json& j, const glm::vec4 & data);
//void to_json(nlohmann::json& j, const glm::quat & data);
//void to_json(nlohmann::json& j, const glm::mat4 & data);
//void to_json(nlohmann::json& j, const ofRectangle& data);

//
//void to_json(nlohmann::json& j, const ofColor_<char>& data);
//void to_json(nlohmann::json& j, const ofColor_<unsigned char>& data);
//void to_json(nlohmann::json& j, const ofColor_<short>& data);
//void to_json(nlohmann::json& j, const ofColor_<unsigned short>& data);
//void to_json(nlohmann::json& j, const ofColor_<int>& data);
//void to_json(nlohmann::json& j, const ofColor_<unsigned int>& data);
//void to_json(nlohmann::json& j, const ofColor_<long>& data);
//void to_json(nlohmann::json& j, const ofColor_<unsigned long>& data);
//void to_json(nlohmann::json& j, const ofColor_<float>& data);
//void to_json(nlohmann::json& j, const ofColor_<double>& data);



//void from_json(const nlohmann::json& j, glm::vec2& d);
//void from_json(const nlohmann::json& j, glm::vec3& d);
//void from_json(const nlohmann::json& j, glm::vec4& d);
//void from_json(const nlohmann::json& j, glm::quat& d);
//void from_json(const nlohmann::json& j, glm::mat4& d);
//void from_json(const nlohmann::json& j, ofRectangle& d);
//
//void from_json(const nlohmann::json& j, ofColor_<char>& d)  ;
//void from_json(const nlohmann::json& j, ofColor_<unsigned char>& d);
//void from_json(const nlohmann::json& j, ofColor_<short>& d)  ;
//void from_json(const nlohmann::json& j, ofColor_<unsigned short>& d);
//void from_json(const nlohmann::json& j, ofColor_<int>& d)  ;
//void from_json(const nlohmann::json& j, ofColor_<unsigned int>& d);
//void from_json(const nlohmann::json& j, ofColor_<long>& d)  ;
//void from_json(const nlohmann::json& j, ofColor_<unsigned long>& d);
//void from_json(const nlohmann::json& j, ofColor_<float>& d)  ;
//void from_json(const nlohmann::json& j, ofColor_<double>& d)  ;
//
//

//namespace ofx {
//namespace LineaDeTiempo {


//template <typename T>
//struct adl_serializer {
//    static void to_json(json& j, const T& value) {
//        
//    }
//
//    static void from_json(const json& j, T& value) {
//        
//    }
//};





	


//template<typename C>
//void color_to_json(nlohmann::json& j, const ofColor_<C>& color)
//{
//	j = nlohmann::json{color.r, color.g, color.b, color.a};
//}
// void to_json(nlohmann::json& j, const char& data)                     { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const unsigned char& data)            { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const short& data)                    { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const unsigned short& data)           { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const int& data)                      { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const unsigned int& data)             { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const long& data)                     { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const unsigned long& data)            { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const float& data)                    { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const double& data)                   { j = nlohmann::json                        { data}; }
// void to_json(nlohmann::json& j, const long double& data)              { j = nlohmann::json                        { data}; }


//void from_json(const nlohmann::json& j, char& d)           { j.get_to(d); }
//void from_json(const nlohmann::json& j, unsigned char& d)  { j.get_to(d); }
//void from_json(const nlohmann::json& j, short& d)          { j.get_to(d); }
//void from_json(const nlohmann::json& j, unsigned short& d) { j.get_to(d); }
//void from_json(const nlohmann::json& j, int& d)            { j.get_to(d); }
//void from_json(const nlohmann::json& j, unsigned int& d)   { j.get_to(d); }
//void from_json(const nlohmann::json& j, long& d)           { j.get_to(d); }
//void from_json(const nlohmann::json& j, unsigned long& d)  { j.get_to(d); }
//void from_json(const nlohmann::json& j, float& d)          { j.get_to(d); }
//void from_json(const nlohmann::json& j, double& d)         { j.get_to(d); }
//void from_json(const nlohmann::json& j, long double& d)    { j.get_to(d); }
//
//


//
//template<typename DataType>
//void timedData_to_json(nlohmann::json& j, const TimedData_<DataType>& d) {
//	nlohmann::json jd;
//	to_json(jd, d.value);
//
//	j = nlohmann::json{{"time", d.time}, {"value", jd}};
// }
//
//template<typename DataType>
//void timedData_from_json(const nlohmann::json& j, TimedData_<DataType>& d) {
//	 j.at("time").get_to(d.time);
////	 d.value = j.at("value").get<DataType>();
// }
//
//
//









//void from_json(const nlohmann::json& j , TimedData_<glm::vec2>& d)                {timedData_from_json<glm::vec2>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<glm::vec3>& d)                {timedData_from_json<glm::vec3>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<glm::vec4>& d)                {timedData_from_json<glm::vec4>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<glm::quat>& d)                {timedData_from_json<glm::quat>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<glm::mat4>& d)                {timedData_from_json<glm::mat4>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<char>& d)                     {timedData_from_json<char>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<unsigned char>& d)            {timedData_from_json<unsigned char>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<short>& d)                    {timedData_from_json<short>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<unsigned short>& d)           {timedData_from_json<unsigned short>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<int>& d)                      {timedData_from_json<int>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<unsigned int>& d)             {timedData_from_json<unsigned int>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<long>& d)                     {timedData_from_json<long>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<unsigned long>& d)            {timedData_from_json<unsigned long>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<float>& d)                    {timedData_from_json<float>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<double>& d)                   {timedData_from_json<double>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<long double>& d)              {timedData_from_json<long double>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<char>>& d)           {timedData_from_json<ofColor_<char>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<unsigned char>>& d)  {timedData_from_json<ofColor_<unsigned char>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<short>>& d)          {timedData_from_json<ofColor_<short>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<unsigned short>>& d) {timedData_from_json<ofColor_<unsigned short>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<int>>& d)            {timedData_from_json<ofColor_<int>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<unsigned int>>& d)   {timedData_from_json<ofColor_<unsigned int>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<long>>& d)           {timedData_from_json<ofColor_<long>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<unsigned long>>& d)  {timedData_from_json<ofColor_<unsigned long>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<float>>& d)          {timedData_from_json<ofColor_<float>>(j, d);}
//void from_json(const nlohmann::json& j , TimedData_<ofColor_<double>>& d)         {timedData_from_json<ofColor_<double>>(j, d);}






//void to_json(nlohmann::json& j , const  TimedData_<glm::vec2>& d)                {timedData_to_json<glm::vec2>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<glm::vec3>& d)                {timedData_to_json<glm::vec3>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<glm::vec4>& d)                {timedData_to_json<glm::vec4>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<glm::quat>& d)                {timedData_to_json<glm::quat>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<glm::mat4>& d)                {timedData_to_json<glm::mat4>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<char>& d)                     {timedData_to_json<char>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<unsigned char>& d)            {timedData_to_json<unsigned char>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<short>& d)                    {timedData_to_json<short>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<unsigned short>& d)           {timedData_to_json<unsigned short>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<int>& d)                      {timedData_to_json<int>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<unsigned int>& d)             {timedData_to_json<unsigned int>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<long>& d)                     {timedData_to_json<long>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<unsigned long>& d)            {timedData_to_json<unsigned long>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<float>& d)                    {timedData_to_json<float>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<double>& d)                   {timedData_to_json<double>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<long double>& d)              {timedData_to_json<long double>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<char>>& d)           {timedData_to_json<ofColor_<char>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<unsigned char>>& d)  {timedData_to_json<ofColor_<unsigned char>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<short>>& d)          {timedData_to_json<ofColor_<short>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<unsigned short>>& d) {timedData_to_json<ofColor_<unsigned short>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<int>>& d)            {timedData_to_json<ofColor_<int>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<unsigned int>>& d)   {timedData_to_json<ofColor_<unsigned int>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<long>>& d)           {timedData_to_json<ofColor_<long>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<unsigned long>>& d)  {timedData_to_json<ofColor_<unsigned long>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<float>>& d)          {timedData_to_json<ofColor_<float>>(j, d);}
//void to_json(nlohmann::json& j , const  TimedData_<ofColor_<double>>& d)         {timedData_to_json<ofColor_<double>>(j, d);}
//
//







//
//void to_json(nlohmann::json& j, const glm::vec2 & data)
//{
//	j = nlohmann::json{{"x", data.x}, {"y", data.y}};
//}
//void to_json(nlohmann::json& j, const glm::vec3 & data)
//{
//	j = nlohmann::json{{"x", data.x}, {"y", data.y}, {"z", data.z}};
//}
//void to_json(nlohmann::json& j, const glm::vec4 & data)
//{
//	j = nlohmann::json{{"x", data.x}, {"y", data.y}, {"z", data.z}, {"w", data.w}};
//}
//void to_json(nlohmann::json& j, const glm::quat & data)
//{
//	j = nlohmann::json{{"x", data.x}, {"y", data.y}, {"z", data.z}, {"w", data.w}};
//}
//void to_json(nlohmann::json& j, const glm::mat4 & data)
//{
//	j = nlohmann::json{	data[0][0],data[1][0],data[2][0],data[3][0],
//			    		data[0][1],data[1][1],data[2][1],data[3][1],
//			    		data[0][2],data[1][2],data[2][2],data[3][2],
//			    		data[0][3],data[1][3],data[2][3],data[3][3]};
//}
//void to_json(nlohmann::json& j, const ofRectangle& data)
//{
//	j = nlohmann::json{data.x, data.y, data.width, data.height};
//}
//template<typename C>
//void color_to_json(nlohmann::json& j, const ofColor_<C>& color) 
//{
//	j = nlohmann::json{color.r, color.g, color.b, color.a};
//}
//void to_json(nlohmann::json& j, const ofColor_<char>& data)
//{
//	color_to_json<char>(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<unsigned char>& data)
//{
//	color_to_json<unsigned char>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<short>& data)
//{
//	color_to_json<short>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<unsigned short>& data)
//{
//	color_to_json<unsigned short>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<int>& data)
//{
//	color_to_json<int>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<unsigned int>& data)
//{
//	color_to_json<unsigned int>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<long>& data)
//{
//	color_to_json<long>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<unsigned long>& data)
//{
//	color_to_json<unsigned long>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<float>& data)
//{
//	color_to_json<float>(j, data);
//	// color_to_json(j, data);
//}
//void to_json(nlohmann::json& j, const ofColor_<double>& data)
//{
//	color_to_json<double>(j, data);
//	// color_to_json(j, data);
//}
//
//
//
//void from_json(const nlohmann::json& j, glm::vec2& d)
//{
//	j.at("x").get_to(d.x);  j.at("y").get_to(d.y);
//
//}
//void from_json(const nlohmann::json& j, glm::vec3& d)
//{
//	j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);
//}
//void from_json(const nlohmann::json& j, glm::vec4& d)
//{
//	j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);  j.at("w").get_to(d.w);
//}
//void from_json(const nlohmann::json& j, glm::quat& d)
//{
//	j.at("x").get_to(d.x);  j.at("y").get_to(d.y);  j.at("z").get_to(d.z);  j.at("w").get_to(d.w);
//}
//void from_json(const nlohmann::json& j, glm::mat4& d)
//{
//	for(int y = 0; y < 4; y++)
//	{
//		for(int x = 0; x < 4; x++)
//		{
//			j.at(y*4 + x).get_to(d[x][y]);
//		}
//	}
//}
//void from_json(const nlohmann::json& j, ofRectangle& d)
//{
//	
//	j.at(0).get_to(d.x);
//	j.at(1).get_to(d.y);
//	j.at(2).get_to(d.width);
//	j.at(3).get_to(d.height);
//	
//}
//template <typename C> 
//void color_from_json(const nlohmann::json& j, ofColor_<C>& color)
//{
//	j.at(0).get_to(color.r);
//	j.at(1).get_to(color.g);
//	j.at(2).get_to(color.b);
//	j.at(3).get_to(color.a);
//}
//
//void from_json(const nlohmann::json& j, ofColor_<char>& d)
//{
//	color_from_json<char>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<unsigned char>& d)
//{
//	color_from_json<unsigned char>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<short>& d)
//{
//	color_from_json<short>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<unsigned short>& d)
//{
//	color_from_json<unsigned short>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<int>& d)
//{
//	color_from_json<int>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<unsigned int>& d)
//{
//	color_from_json<unsigned int>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<long>& d)
//{
//	color_from_json<long>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<unsigned long>& d)
//{
//	color_from_json<unsigned long>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<float>& d)
//{
//	color_from_json<float>(j, d);
//}
//void from_json(const nlohmann::json& j, ofColor_<double>& d)
//{
//	color_from_json<double>(j, d);
//}
//
//


//template<typename DataType>
//void to_json(nlohmann::json& j, const TimedData_<DataType>& d) {
//	j = nlohmann::json{{"time", d.time}, {"value", nlohmann::json{d.value}}};
// }
//
//template<typename DataType>
//void from_json(const nlohmann::json& j, TimedData_<DataType>& d) {
//	 j.at("time").get_to(d.time);
//	 j.at("value").get_to(d.value);
// }




//} } // ofx::LineaDeTiempo
