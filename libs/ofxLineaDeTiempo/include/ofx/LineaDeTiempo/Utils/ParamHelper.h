//
//  ParamHelper.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 4/1/20.
//

#pragma once
#include "ofParameter.h"
#include "LineaDeTiempo/Utils/ofxTypeTraits.h"

namespace ofx {
namespace LineaDeTiempo {
namespace ParamHelper{


template<typename DataType>
typename std::enable_if<is_multi_dim_param<DataType>::value, float>::type
getUnnormalized(const float&  val, const size_t& dim, const ofParameter<DataType>& param){
	return ofMap(val, 0, 1, param.getMin()[dim], (float)param.getMax()[dim], true);
}

template<typename DataType>
typename std::enable_if<! is_multi_dim_param<DataType>::value, DataType>::type
getUnnormalized(const float&  val, const size_t& dim, const ofParameter<DataType>& param){
	return ofMap(val, 0, 1, (float)param.getMin(), param.getMax(), true);
}


template<typename DataType>
typename std::enable_if<! is_multi_dim_param<DataType>::value, float>::type
getNormalized(const DataType& val, const size_t& dim, const ofParameter<DataType>& param)
{
	return ofMap((float)val, param.getMin(), param.getMax(), 0, 1, true);
}


template<typename DataType>
typename std::enable_if<is_multi_dim_param<DataType>::value, float>::type
getNormalized(const float& val, const size_t& dim, const ofParameter<DataType>& param)
{
	return ofMap(val, param.getMin()[dim], param.getMax()[dim], 0, 1, true);
}




}}} //ofx::LineaDeTiempo::ParamHelper





