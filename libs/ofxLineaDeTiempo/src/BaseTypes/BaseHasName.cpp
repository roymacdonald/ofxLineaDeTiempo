//
//  BaseHasName.cpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#include "BaseHasName.h"

namespace ofx {
namespace LineaDeTiempo {


BaseHasName::BaseHasName()
{
	
}

BaseHasName::BaseHasName(const std::string & name):
_name(name)
{
	
}

BaseHasName::~BaseHasName()
{
	
}

const std::string &  BaseHasName::getName() const
{
	return _name;
}

void BaseHasName::setName(const std::string & name)
{
	_name = name;
}

}} //ofx::LineaDeTiempo
