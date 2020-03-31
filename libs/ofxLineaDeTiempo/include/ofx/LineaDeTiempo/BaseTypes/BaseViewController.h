////
////  BaseController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/6/20.
////
//
//#pragma once
//#include "ofx/DOM/Element.h"
//#include "ofx/DOM/Node.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//#define DEFAULT_BASE_VIEW_CONTROLLER_DESTRUCTOR = default;//\
//{\
//	if(hasView())\
//	{\
//		destroyView();\
//	}\
//}\
//
//
//class BaseHasViews{
//public:
//	virtual void generateView() = 0;
//	virtual void destroyView() = 0;
//};
//template<typename ViewType>
//class BaseViewController
//: public BaseHasViews
//{
//public:
//	static_assert(std::is_base_of<DOM::Element, ViewType>::value,
//				  "BaseViewController: Templated ViewType must be equal or derived from DOM::Element");
//	
//	virtual ~BaseViewController() = default;
//
//
//	const ViewType * getView() const;
//
//	ViewType * getView();
//
//	void setView(ViewType * view);
//	
//	bool hasView() const;
//	
//	void destroyChildrenViews(DOM::Node * parent);
//	
//	void generateChildrenViews(DOM::Node * parent);
//	
//	typedef ViewType viewType;
//protected:
//
//	ViewType* _view = nullptr;
//	
//};
//
//} } // ofx::LineaDeTiempo
