//
//  BaseHasController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/13/20.
//

#include "LineaDeTiempo/BaseTypes/BaseHasController.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename ControllerType>
BaseHasController<ControllerType>::BaseHasController()
{
	
}
template<typename ControllerType>
BaseHasController<ControllerType>::BaseHasController(ControllerType* controller):
_controller(controller)
{
	
}
		
template<typename ControllerType>
	const ControllerType * BaseHasController<ControllerType>::getController() const
{
	return _controller;
}

template<typename ControllerType>
ControllerType * BaseHasController<ControllerType>::getController()
{
	return _controller;
}

template<typename ControllerType>
void BaseHasController<ControllerType>::setController(ControllerType * controller)
{
	_controller = controller;
}
	


} } // ofx::LineaDeTiempo

