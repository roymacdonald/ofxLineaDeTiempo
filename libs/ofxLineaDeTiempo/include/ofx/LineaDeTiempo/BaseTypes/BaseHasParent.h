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
	BaseHasParent(ParentType* parent);

	virtual ~BaseHasParent() = default;
	
	ParentType * parent();
	
	const ParentType * parent() const;

	void setParent(ParentType* parent);
	
	typedef ParentType parentType;
	
	
	
protected:
	ParentType* _parent = nullptr;
	
};


}}  //ofx::LineaDeTiempo
