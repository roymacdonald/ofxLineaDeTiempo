//
//  TracksController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include "TimeControl.h"

namespace ofx {
namespace LineaDeTiempo {

class TracksController
{
public:

	TracksController(std::shared_ptr<TimeControl> timeControl);
	
	std::shared_ptr<TimeControl> getTimeControl();
	
	
	
	
protected:
	
	std::shared_ptr<TimeControl> _timeControl;
	
private:
	
	
};


} } // ofx::LineaDeTiempo
