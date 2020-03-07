//
//  TracksController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "TracksController.h"

namespace ofx {
namespace LineaDeTiempo {
//-------------------------------------------------------------------------------
TracksController::TracksController(std::shared_ptr<TimeControl> timeControl):
_timeControl(timeControl)
{
	
}
//-------------------------------------------------------------------------------
std::shared_ptr<TimeControl> TracksController::getTimeControl()
{
	return _timeControl;
}
		
	

} } // ofx::LineaDeTiempo
