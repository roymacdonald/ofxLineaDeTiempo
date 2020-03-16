//
//  BaseController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include "ofx/DOM/Element.h"
namespace ofx {
namespace LineaDeTiempo {


template<typename ViewType>
class BaseViewController
{
public:
	static_assert(std::is_base_of<DOM::Element, ViewType>::value,
				  "BaseViewController: Templated ViewType must be equal or derived from DOM::Element");
	
	virtual ~BaseViewController();

	const ViewType * getView() const;

	ViewType * getView();

	void setView(ViewType * view);
	
	template <typename... Args>
	ViewType* createView(DOM::Element * _parentView, Args&&... args)
	{
		if(!_parentView)return nullptr;
		_view = _parentView->addChild<ViewType>(std::forward<Args>(args)...);
		return _view;
	}
	
	bool removeView()
	{
		if(!_view || !_parentView) return false;
		
		bool ret = (_parentView->removeChild(_view) != nullptr);
		
		return ret;
	}
	

	typedef ViewType viewType;
protected:
	DOM::Element * _parentView = nullptr;
	ViewType* _view = nullptr;
	
//	std::string _trackViewTypeName;

private:



};

} } // ofx::LineaDeTiempo
