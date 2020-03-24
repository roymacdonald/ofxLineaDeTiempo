//
//  ofxTypeTraits.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#pragma once
#include <type_traits>
#include "ofColor.h"

template< class T >
struct is_ofColor
     : std::integral_constant<
         bool, 
		std::is_same<ofColor_<char>           , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<unsigned char>  , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<short>          , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<unsigned short> , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<int>            , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<unsigned int>   , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<long>           , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<unsigned long>  , typename std::remove_cv<T>::type>::value  ||
		std::is_same<ofColor_<float>          , typename std::remove_cv<T>::type>::value

> {};


template< class T >
struct is_multi_dim_param
     : std::integral_constant<
         bool,
		is_ofColor<T>::value ||

		std::is_same<glm::vec2  , typename std::remove_cv<T>::type>::value  ||
		std::is_same<glm::vec3  , typename std::remove_cv<T>::type>::value  ||
		std::is_same<glm::vec4  , typename std::remove_cv<T>::type>::value  ||
		std::is_same<glm::quat  , typename std::remove_cv<T>::type>::value  ||
		std::is_same<glm::mat4  , typename std::remove_cv<T>::type>::value

> {};
