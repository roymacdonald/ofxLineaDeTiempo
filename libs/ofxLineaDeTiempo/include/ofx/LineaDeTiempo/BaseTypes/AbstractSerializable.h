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
	virtual ~AbstractSerializable()
	{
		
	}
	virtual void fromJson(const ofJson& j) = 0;

	virtual ofJson toJson() = 0;
	
	
	
private:
	
};
}} // ofx::LineaDeTiempo

