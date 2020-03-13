//
//  BaseHasParent.h
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#include "LineaDeTiempo/BaseTypes/BaseHasParent.h"

namespace ofx {
namespace LineaDeTiempo {



template<typename ParentType>
BaseHasParent<ParentType>::BaseHasParent(ParentType* parent):
_parent(parent)
{
	
}
//template<typename ParentType>
//BaseHasParent<ParentType>::~BaseHasParent()
//{
//	
//}
template<typename ParentType>
void BaseHasParent<ParentType>::setParent(ParentType* parent)
{
	_parent = parent;
}

template<typename ParentType>
ParentType * BaseHasParent<ParentType>::parent()
{
	return _parent;
}

template<typename ParentType>
const ParentType * BaseHasParent<ParentType>::parent() const
{
	return _parent;
}



}}  //ofx::LineaDeTiempo
