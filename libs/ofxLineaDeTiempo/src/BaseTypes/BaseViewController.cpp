//
//  BaseController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
//
namespace ofx {
namespace LineaDeTiempo {


template<typename ViewType>

BaseViewController<ViewType>::~BaseViewController()
{
		
}
	
template<typename ViewType>
const ViewType * BaseViewController<ViewType>::getView() const
{
	return _view;
}
	
template<typename ViewType>
ViewType * BaseViewController<ViewType>::getView()
{
	return _view;
}

template<typename ViewType>
void BaseViewController<ViewType>::setView(ViewType * view)
{
	_view = view;
}



} } // ofx::LineaDeTiempo
