//
//  BaseData.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#pragma once
#include "ofJson.h"

namespace ofx {
namespace LineaDeTiempo {
class AbstractSerializable
{
public:
//	BaseHasName();
//	
//	BaseHasName(const std::string & name);
//	
	virtual ~AbstractSerializable()
	{
		
	}
	virtual void fromJson(const ofJson& j) = 0;

	virtual void toJson(ofJson& j) = 0;
	
	
	
private:
	
};
}} // ofx::LineaDeTiempo

