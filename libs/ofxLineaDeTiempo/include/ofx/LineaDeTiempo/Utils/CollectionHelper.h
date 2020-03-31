//
//  CollectionHelper.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/18/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"
#include "ofLog.h"
#include "DOM/Node.h"
#include "DOM/Element.h"

namespace ofx {
namespace LineaDeTiempo {
namespace CollectionHelper{

template<
typename NewControllerType
,typename ParentElementType
,typename CollectionType
,typename... Args
>
NewControllerType * _add( NamedConstPointerCollection<CollectionType>& collection, ParentElementType * parentElement, Args&&... args)
{
	
	static_assert(std::is_base_of<DOM::Node, ParentElementType>::value or
				  std::is_base_of<DOM::Element, ParentElementType>::value,
	
				" CollectionHelper _add(...) failed. ElementType must be equal to or derived from ofxDOM::Node or ofxDom::Element");
	
	static_assert(std::is_base_of<CollectionType, NewControllerType>::value,
				  
				  "CollectionHelper _add(...) failed. TemplateType must be equal to or derived from another Templated Type");
	
	static_assert(std::is_base_of<DOM::Node, NewControllerType>::value or
				  std::is_base_of<DOM::Element, NewControllerType>::value,
				  
				  "CollectionHelper _add(...) failed. TemplateType must be equal to or derived from another Templated Type");
	
	
	auto t = parentElement->template addChild<NewControllerType >(std::forward<Args>(args)...);
	
	collection.add(t);

	return t;
}

template<typename ElementType, typename ParentType>

bool _remove( ElementType* toRemove, ParentType* parentElement, NamedConstPointerCollection<ElementType>& collection )
{
	static_assert(std::is_base_of<DOM::Node, ElementType>::value or
				  std::is_base_of<DOM::Element, ElementType>::value,
	
				" CollectionHelper _remove(...) failed. ElementType must be equal to or derived from ofxDOM::Node or ofxDom::Element");

	static_assert(std::is_base_of<DOM::Node, ParentType>::value or
				  std::is_base_of<DOM::Element, ParentType>::value,
	
				" CollectionHelper _remove(...) failed. ParentType must be equal to or derived from ofxDOM::Node or ofxDom::Element");

	
	
	
	
//	auto e = dynamic_cast<ElementType*>(toRemove);
	if(toRemove){
		toRemove->destroyView();
		auto g = parentElement->removeChild(toRemove);
		if(g)
		{
			
			collection.remove(toRemove);
			
			
			return true;
			
		}
		else
		{
			ofLogError("CollectionHelper::_remove") << "failed. could not remove the element from its parent";
		}
	}
	ofLogError("CollectionHelper::_remove") << "failed. element to remove is invalid. (nullptr)";
	return false;
	
}




}}} //ofx::LineaDeTiempo::CollectionHelper
