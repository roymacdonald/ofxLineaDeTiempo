//
//  BaseHasCollection.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/28/20.
//


#pragma once

#include <vector>

namespace ofx {
namespace LineaDeTiempo {

template<typename ElementType>
class BaseHasCollection{
public:

	virtual ~BaseHasCollection() = default;
	
	
	virtual std::vector<ElementType*> & getCollection() = 0;

	virtual const std::vector<ElementType*> & getCollection() const= 0;

	virtual void removeElements(std::vector<ElementType*> &) = 0;
	
};



}}//ofx::LineaDeTiempo
