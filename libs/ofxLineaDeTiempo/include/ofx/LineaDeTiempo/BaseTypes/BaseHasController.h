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
	
	BaseHasController();
	BaseHasController(ControllerType* controller);
	
	virtual ~BaseHasController() = default;

	const ControllerType * getController() const;

	ControllerType * getController();

	void setController(ControllerType * controller);
	

	typedef ControllerType viewType;
protected:
	
private:
ControllerType* _controller = nullptr;
	




};

} } // ofx::LineaDeTiempo
