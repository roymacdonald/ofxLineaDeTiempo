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
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"


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
: public AbstractSerializable

{
public:
	
	TimeControl();
	
	void play();
	void stop();
	void pause();
	
	void tooglePlay();
	
	
	///\brief Will go back to the in time and play from there
	void trigger();
	
	
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
	ofEvent<void> playEvent;
	ofEvent<void> pauseEvent;
	ofEvent<void> stopEvent;
	ofEvent<TimeControlState> stateChangeEvent;
	ofEvent<void> totalTimeChangedEvent;
	
	
	const uint64_t&  getTotalTime() const;
	void setTotalTime(const uint64_t&  t);


	TimeControlState getState() const;
	
	
	void drawDebug(float x, float y);
	std::string getDebugString();
	
	virtual void fromJson(const ofJson& j) override;
	virtual ofJson toJson() override;
	
protected:
	
	
	
	void _update(ofEventArgs&);
	
	uint64_t _totalTime = 10000;
	

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





} } // ofx::LineaDeTiempo
