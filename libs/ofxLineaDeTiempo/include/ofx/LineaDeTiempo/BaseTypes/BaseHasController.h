//
//  BaseHasController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/13/20.
//

#pragma once

namespace ofx {
namespace LineaDeTiempo {


template<typename ControllerType>
class BaseHasController
{
public:
	
	BaseHasController()
	{
		
	}
	BaseHasController(ControllerType* controller)
	:
	_controller(controller)
	{
		
	}
	
	virtual ~BaseHasController() = default;

	const ControllerType * getController() const
	{
		return _controller;
	}

	ControllerType * getController()
	{
		return _controller;
	}

	void setController(ControllerType * controller)
	{
		_controller = controller;
	}
	

	typedef ControllerType viewType;
	
	
private:
ControllerType* _controller = nullptr;


};

} } // ofx::LineaDeTiempo
