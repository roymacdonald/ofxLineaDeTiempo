//
//  jsonSerializer.hpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/9/20.
//
#pragma once

#include "json.hpp"
#include "ofColor.h"
//#include "ofVectorMath.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/common.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/quaternion.hpp"




namespace nlohmann {




template <int D, typename T, glm::qualifier Q>
struct adl_serializer<glm::vec<D, T, Q>> {
	static void from_json(const json& j, glm::vec<D, T, Q>& d)
	{
		for(int i = 0; i < D; i++)
		{
			j.at(i).get_to(d[i]);
		}
	}
	static void to_json(json& j, const glm::vec<D, T, Q> & d)
	{
		j = json::array();
		for(int i = 0; i < D; i++)
		{
			j.emplace_back( d[i]);
		}
	}
};


template <typename T, glm::qualifier Q>
struct adl_serializer<glm::qua<T, Q>> {
	static void from_json(const json& j, glm::qua<T, Q>& d)
	{
		for(int i = 0; i < 4; i++)
		{
			j.at(i).get_to(d[i]);
		}
	}
	static void to_json(json& j, const glm::qua<T, Q> & data)
	{
		j = json::array();
		for(int i = 0; i < 4; i++)
		{
			j.emplace_back( data[i]);
		}
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
