//
//  BaseHasTimeControl.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/21/20.
//

#pragma once
#include "LineaDeTiempo/Controller/TimeControl.h"


namespace ofx {
namespace LineaDeTiempo {



class BaseHasTimeControl
{
public:
	BaseHasTimeControl(	TimeControl* timeControl, const std::string& className)
	{
		if(timeControl){
			_timeControl = timeControl;
		}
	}
	
	~BaseHasTimeControl() = default;
	
	TimeControl * getTimeControl()
	{
		return _timeControl;
	}
	
	const TimeControl * getTimeControl() const
	{
		return _timeControl;
	}
protected:
	
	void _setTimeControl(TimeControl * timeControl)
	{
		_timeControl = timeControl;
	}
	
private:
	TimeControl * _timeControl = nullptr;
	
	
	
	
};

} } // ofx::LineaDeTiempo
