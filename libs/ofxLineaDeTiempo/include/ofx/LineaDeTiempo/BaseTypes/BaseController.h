//
//  BaseController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#pragma once
#include "DOM/Node.h"
#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"
#include "LineaDeTiempo/BaseTypes/BaseViewController.h"

namespace ofx {
namespace LineaDeTiempo {


//template<typename ViewType>
class BaseController
:public DOM::Node<BaseController>
//,public BaseViewController<ViewType>
{
public:
	BaseController (const std::string& id, BaseController* parent = nullptr):
	DOM::Node<BaseController>(id, parent)
	{
		
	}
	
	virtual ~BaseController()
	{
		
	}
	
	virtual void generateView() = 0;
	virtual void destroyView() = 0;
	
	
protected:
	
	template<
	 typename NewControllerType
	,typename CollectionType
	,typename... Args
	>
		NewControllerType * _add( NamedConstPointerCollection<CollectionType>& collection, Args&&... args)
		{
//			static_assert(std::is_base_of<ControllerType<ViewType>,NewControllerType<NewViewType>>::value,
//
//			" failed. TemplateType must be equal to or derived from another Templated Type");
			
			static_assert(std::is_base_of<CollectionType, NewControllerType>::value,
			
			" failed. TemplateType must be equal to or derived from another Templated Type");
			
			static_assert(std::is_base_of<BaseController, NewControllerType>::value,
			
			" failed. TemplateType must be equal to or derived from another Templated Type");
					
			
			auto t = addChild<NewControllerType >(std::forward<Args>(args)...);
			
			collection.add(t);
				
			t->generateView();
//			auto vc = dynamic_cast<BaseViewController<ViewType>* >(this);
//			if(vc){
//
//				if(vc->getView() != nullptr)
//				{
//					auto tv = dynamic_cast<BaseViewController<NewViewType>* >(t);
//
//					tv->createView(vc->getView());
//				}
//			}
			return t;
		}

	template< typename CollectionType>
	
		bool _remove( BaseController* toRemove,  NamedConstPointerCollection<CollectionType>& collection )
		{
		
			auto e = dynamic_cast<CollectionType*>(toRemove);
			if(e){
			auto g = removeChild(e);
			if(g)
			{
			
				collection.remove(e);
			
				e->destroyView();
				
				return true;
			
			}
			}
			ofLogError("BaseController::_remove : failed.");
			return false;
			
		}


	
};


}} //ofx::LineaDeTiempo
