//
//  BaseHasName.hpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#pragma once
#include <string>

namespace ofx {
namespace LineaDeTiempo {


class BaseHasName
{
public:
	BaseHasName();
	
	BaseHasName(const std::string & name);
	
	virtual ~BaseHasName();
	
	
	const std::string &  getName() const;
	
	void setName(const std::string & name);
	
protected:
	std::string  _name;
};
}} // ofx::LineaDeTiempo
