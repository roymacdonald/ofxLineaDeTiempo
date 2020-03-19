//
//  BaseController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include "ofx/DOM/Element.h"
#include "ofx/DOM/Node.h"

namespace ofx {
namespace LineaDeTiempo {

class BaseHasViews{
public:
	virtual void generateView() = 0;
	virtual void destroyView() = 0;
};
template<typename ViewType>
class BaseViewController
: public BaseHasViews
{
public:
	static_assert(std::is_base_of<DOM::Element, ViewType>::value,
				  "BaseViewController: Templated ViewType must be equal or derived from DOM::Element");
	
	virtual ~BaseViewController() = default;

	const ViewType * getView() const
	{
		return _view;
	}

	ViewType * getView()
	{
		return _view;
	}

	void setView(ViewType * view)
	{
		_view = view;
	}
	
	bool hasView() const
	{
		return (_view != nullptr);
	}
	
	void destroyChildrenViews(DOM::Node * parent){
		if(!parent) return;
		for(auto child : parent->children())
		{
			auto c = dynamic_cast<BaseHasViews*>(child);
			if(c) c->destroyView();
		}
	}
	
	void generateChildrenViews(DOM::Node * parent){
		if(!parent) return;
		for(auto child : parent->children())
		{
			auto c = dynamic_cast<BaseHasViews*>(child);
			if(c) c->generateView();
		}
	}
	
	
//	template< typename... Args>
//	ViewType* createView(DOM::Element * parentView, Args&&... args)
//	{
//		if(!parentView)return nullptr;
//		
//		_view = _parentView->addChild<ViewType>(std::forward<Args>(args)...);
//		return _view;
//	}
//	
//	bool removeView()
//	{
//		if(!_view || !_parentView) return false;
//		
//		bool ret = (_parentView->removeChild(_view) != nullptr);
//		
//		return ret;
//	}
	

	
	
	typedef ViewType viewType;
protected:
//	DOM::Element * _parentView = nullptr;
	ViewType* _view = nullptr;
	
};

} } // ofx::LineaDeTiempo
