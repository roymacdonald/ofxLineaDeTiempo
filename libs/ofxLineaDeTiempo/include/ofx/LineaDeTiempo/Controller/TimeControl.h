//
//  TimeControl.hpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/21/20.
//

#pragma once
#include "ofMain.h"
#include "ofRange.h"
#include <map>


namespace ofx {
namespace LineaDeTiempo {






enum TimeControlState{
	STOPPED,
	PAUSED,
	PLAYING
};

#define USE_MILLIS

struct TimeBound
{
	uint64_t time = 0;
	bool enabled = false;
	
};

class TimeControl
{
public:
	
	TimeControl();
	
	void play();
	void stop();
	void pause();
	
	void tooglePlay();
	
	
	void setLooping(bool looping);
	
	bool isPlaying() const;
	bool isStopped() const;
	bool isPaused() const;
	bool isLooping() const;
	
	
	///\ brief set the in point
	///\param inTime must be between zero and getTotalTime();
	void setInTime(uint64_t inTime);
	
	///\ brief set the out point
	///\param outTime must be between zero and getTotalTime();
	void setOutTime(uint64_t outTime);
	
	uint64_t getInTime() const;
	uint64_t getOutTime() const;
	
	void setInTimeEnabled(bool enableInTime);
	void setOutTimeEnabled(bool enableOutTime);
	
	bool isInTimeEnabled() const;
	bool isOutTimeEnabled() const;
	
	
	
	void setCurrentTime(const uint64_t& currentTime);
	const uint64_t& getCurrentTime() const;

	ofEvent<uint64_t> currentTimeUpdateEvent;

	uint64_t getTotalTime() const;
	void setTotalTime(uint64_t t);


	TimeControlState getState() const;
	
//	ofEvent<ofRange64u> updatedTimeRangeEvent;
	
	void drawDebug(float x, float y);
	
protected:
	
	
	
	void _update(ofEventArgs&);
	
	uint64_t _totalTime = 10000;
	
//	ofParameter<uint64_t> _totalTime = {"Total Time", 10000, 0, std::numeric_limits<uint64_t>::max()};//millis or micros?

	uint64_t _currentTime = 0;
	
	
	TimeBound  _inTime;
	TimeBound  _outTime;
	
	bool _bLoop = false;
	
	
	void _setState(TimeControlState state);
	
	
	uint64_t _getEndTime();
	uint64_t _getStartTime();
	
	uint64_t _currentTimeCopy=0;//this is whats sent on the ofEvent currentTimeUpdateEvent. As it is sent as a non-const reference it can be modified externaly and make the time control to behave strangely if the original was sent.
	
	void _notifyCurrentTime();
	
private:
	ofEventListener _updateListener;
	uint64_t _playStartTime = 0;
	
	uint64_t _prevUpdateTime =0;
	
	TimeControlState _state;
};


//
//static TimeControl & getTimeControl(const std::string& id = "default"){
////	static std::unique_ptr<std::map<std::string, TimeControl>> m;
////	if(!m){
////		// esto ocurrira una sola vez
////		m = make_unique<std::map<std::string, TimeControl>>();
////
////		//cualquier otro codigo que sea necesario para inicializar correctamente la variable
////	}
////
////	return (*m)[id];
////	static std::unique_ptr<int> i = make_unique<int>(0);
////	std::cout << "getTimeControl " << *i << "\n";
////	
//	static std::unique_ptr<TimeControl> m = make_unique<TimeControl>();
//	
//	return *m;
//
//	
//	
//}





} } // ofx::LineaDeTiempo
