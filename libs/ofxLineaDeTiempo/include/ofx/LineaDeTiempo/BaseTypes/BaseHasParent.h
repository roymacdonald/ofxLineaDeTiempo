//
//  BaseHasParent.h
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#pragma once

namespace ofx {
namespace LineaDeTiempo {



template<typename ParentType>
class BaseHasParent
{
public:
	BaseHasParent(ParentType* parent)
	:
	_parent(parent)
	{
		
	}

	virtual ~BaseHasParent() = default;
	
	ParentType * parent()
	{
		return _parent;
	}
	
	const ParentType * parent() const
	{
		return _parent;
	}

	void setParent(ParentType* parent)
	{
		_parent = parent;
	}
	
	typedef ParentType parentType;
	
	
	
protected:
	ParentType* _parent = nullptr;
	
};

}}  //ofx::LineaDeTiempo
