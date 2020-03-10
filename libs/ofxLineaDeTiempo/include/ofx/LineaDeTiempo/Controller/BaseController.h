//
//  BaseController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

//#pragma once
//#include "LineaDeTiempo/Controller/Nestable.h"
//#include "LineaDeTiempo/Controller/TimeControl.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//template<typename ChildType, typename ParentType>
//class BaseController: public Nestable_<ChildType, ParentType>
//{
//public:
//	BaseController(const std::string& id, TimeControl* timeControl):
//	Nestable_<ChildType, ParentType>(id),
//	_timeControl(timeControl)
//	{
//		
//	}
//	
//	virtual ~BaseController(){
//		
//	}
//	
//	
//	TimeControl* getTimeControl()
//	{
//		return _timeControl;
//	}
//	
//	const TimeControl* getTimeControl() const
//	{
//		return _timeControl;
//	}
//	
//	
//protected:
//	
//private:
//	TimeControl* _timeControl = nullptr;
//	
//};
//
//
//} } // ofx::LineaDeTiempo
