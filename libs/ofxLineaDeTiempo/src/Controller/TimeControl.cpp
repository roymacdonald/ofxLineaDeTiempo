//
//  TimeControl.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/21/20.
//

#include "TimeControl.h"

namespace ofx {
namespace LineaDeTiempo {

std::string Debug::str = "";


//---------------------------------------------------------------------
TimeControl::TimeControl()
{
//	std::cout << "New TimeControl\n";
	_updateListener = ofEvents().update.newListener(this, &TimeControl::_update);
}
//---------------------------------------------------------------------
void TimeControl::play()
{
	_setState(PLAYING);
	
}
//---------------------------------------------------------------------
void TimeControl::stop()
{
	_setState(STOPPED);
}
//---------------------------------------------------------------------
void TimeControl::tooglePlay()
{
	if(!isPlaying())
	{
		play();
	}
	else
	{
		pause();
	}
}
//---------------------------------------------------------------------
void TimeControl::pause()
{
	_setState(PAUSED);
}
//---------------------------------------------------------------------
void TimeControl::setLooping(bool looping)
{
	_bLoop = looping;
	
}
//---------------------------------------------------------------------
bool TimeControl::isPlaying()  const
{
	return _state == PLAYING;
}
//---------------------------------------------------------------------
bool TimeControl::isStopped()  const
{
	return _state == STOPPED;
}
//---------------------------------------------------------------------
bool TimeControl::isPaused() const
{
	return _state == PAUSED;
}
//---------------------------------------------------------------------
bool TimeControl::isLooping() const
{
	return _bLoop;
}
//---------------------------------------------------------------------
void TimeControl::setInTime(uint64_t inTime)
{
	_inTime.time = inTime;
}
//---------------------------------------------------------------------
void TimeControl::setOutTime(uint64_t outTime)
{
	_outTime.time = outTime;
}
//---------------------------------------------------------------------
uint64_t TimeControl::getInTime() const
{
	return _inTime.time;
}
//---------------------------------------------------------------------
uint64_t TimeControl::getOutTime() const
{
	return _outTime.time;
}
//---------------------------------------------------------------------
void TimeControl::setInTimeEnabled(bool enableInTime)
{
	_inTime.enabled = enableInTime;
}
//---------------------------------------------------------------------
void TimeControl::setOutTimeEnabled(bool enableOutTime)
{
	_outTime.enabled = enableOutTime;
}
//---------------------------------------------------------------------
bool TimeControl::isInTimeEnabled() const
{
	return _inTime.enabled;
}
//---------------------------------------------------------------------
bool TimeControl::isOutTimeEnabled() const
{
	return _outTime.enabled;
}
//---------------------------------------------------------------------
void TimeControl::setCurrentTime(const uint64_t& currentTime)
{
	_currentTime = currentTime;
	_notifyCurrentTime();
}
//---------------------------------------------------------------------
const uint64_t& TimeControl::getCurrentTime() const
{
	return _currentTime;
}
//---------------------------------------------------------------------
uint64_t TimeControl::_getEndTime()
{
	if(_outTime.enabled ) return _outTime.time;
	return _totalTime;
}
//---------------------------------------------------------------------
uint64_t TimeControl::_getStartTime()
{
	if(_inTime.enabled) return _inTime.time;
	return 0;
	
}
//---------------------------------------------------------------------
void TimeControl::_update(ofEventArgs&)
{
	if(_state == PLAYING)
	{
		
		uint64_t t;
#ifdef USE_MILLIS
//		_currentTime += ofGetElapsedTimeMillis() - _prevUpdateTime ;
		t = ofGetElapsedTimeMillis();
#else
//		_currentTime = ofGetElapsedTimeMicros() - _playStartTime;
		t = ofGetElapsedTimeMicros();
#endif
		// TODO: might need to handle in a more precise way the looping.
		
		_currentTime += t - _prevUpdateTime ;
		
		_prevUpdateTime = t;
		
		//
		if(_currentTime >= _getEndTime() ){
			setCurrentTime(_getEndTime());
			if(_bLoop){
				setCurrentTime( _getStartTime());
//				_currentTime = _getStartTime();
			}else
			{
				pause();
			}
		}else{
			_notifyCurrentTime();
		}
		
	}
}
//---------------------------------------------------------------------
void TimeControl::_notifyCurrentTime()
{
	Debug::str = "";
	_currentTimeCopy = _currentTime;
	ofNotifyEvent(currentTimeUpdateEvent, _currentTimeCopy, this);
}
//---------------------------------------------------------------------
void TimeControl::_setState(TimeControlState state)
{
	if(_state != state){
		_state = state;
		if(_state == STOPPED)
		{
			_currentTime = _getStartTime();
			
			ofNotifyEvent(stopEvent,this);
		}
		else if(_state == PLAYING)
		{
			#ifdef USE_MILLIS
			_playStartTime = ofGetElapsedTimeMillis();
			#else
			_playStartTime = ofGetElapsedTimeMicros();
			#endif
			
//			_playStartTime =
			_prevUpdateTime = _playStartTime;// _currentTime;
			
			ofNotifyEvent(playEvent,this);
		}
		else if(_state == PAUSED)
		{
			ofNotifyEvent(pauseEvent,this);
		}
		
		// TODO: handle individual states
	}
	
	
	
	
	
}

//---------------------------------------------------------------------
const uint64_t&  TimeControl::getTotalTime() const
{
	return _totalTime;
}
//---------------------------------------------------------------------
void TimeControl::setTotalTime(const uint64_t&  t)
{
	_totalTime = t;

}
//---------------------------------------------------------------------
TimeControlState TimeControl::getState() const
{
	return _state;
}
std::string TimeControl::getDebugString()
{
	stringstream ss;
	ss << "_totalTime: " << _totalTime << "\n";
	ss << "_currentTime: " << _currentTime << "\n";
	ss << "_inTime: " << _inTime.time << " enabled: " << boolalpha << _inTime.enabled << "\n";
	ss << "_outTime: " << _outTime.time << " enabled: " << boolalpha << _outTime.enabled << "\n";
	ss << "_bLoop: " << _bLoop << "\n";
	ss << "_playStartTime: " << _playStartTime << "\n";
	ss << "_state: " << _state << "\n";
	return ss.str();
}
//---------------------------------------------------------------------
void TimeControl::drawDebug(float x, float y)
{
	
	
	ofDrawBitmapStringHighlight(getDebugString(), x, y);
	
}

void TimeControl::fromJson(const ofJson& j)
{
	
	j["_totalTime"].get_to( _totalTime);
	j["_currentTime"].get_to( _currentTime);
	j["_inTime"]["enabled"].get_to( _inTime.enabled);
	j["_inTime"]["time"].get_to( _inTime.time);
	j["_outTime"]["enabled"].get_to( _outTime.enabled);
	j["_outTime"]["time"].get_to( _outTime.time);
	j["_bLoop"].get_to( _bLoop);
	j["_playStartTime"].get_to( _playStartTime);
	j["_prevUpdateTime"].get_to( _prevUpdateTime);
	j["_state"].get_to( _state);
	

}

ofJson TimeControl::toJson()
{
	ofJson j;
	j["class"] = "TimeControl";
	

	j["_totalTime"]          = _totalTime;
	j["_currentTime"]        = _currentTime;
	j["_inTime"]["enabled"]  = _inTime.enabled;
	j["_inTime"]["time"]     = _inTime.time;
	j["_outTime"]["enabled"] = _outTime.enabled;
	j["_outTime"]["time"]    = _outTime.time;
	j["_bLoop"]              = _bLoop;
	j["_playStartTime"]      = _playStartTime;
	j["_prevUpdateTime"]     = _prevUpdateTime;
	j["_state"]              = _state;
	
	


	return j;
}



} } // ofx::LineaDeTiempo
