//
//  KeyframedData.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include <stdint.h>
#include <vector>
#include <map>
#include "LineaDeTiempo/Data/TimedData.h"
#include "LineaDeTiempo/Controller/TimeControl.h"

namespace ofx {
namespace LineaDeTiempo {


template<typename DataType>
class KeyframedData_
{
public:
	KeyframedData_(std::shared_ptr<TimeControl> timeControl);
	virtual ~KeyframedData_(){}
	
	
	DataType getValueAtTime(const uint64_t& time) const;
	

	TimedData_<DataType>* add(const DataType& value, const uint64_t& time);
	
	bool remove(TimedData_<DataType>* d);
	
	virtual bool update(const uint64_t& time);
	
	void sortData();
	
	const DataType& getCurrentValue() const;
	
	void setValue(const DataType& value, const uint64_t& time, bool bAddKeyIfNotFound);
	
	//TODO: serialize and unserialize
	
	
	void enableKeyframing();
	
	void disableKeyframing();
	
	bool isKeyFramingEnabled() const;
	
	ofEvent<bool> keyframingEnableEvent;
	
	
protected:
	std::vector< std::unique_ptr< TimedData_<DataType> > > _data;
	
	std::map<uint64_t, TimedData_<DataType>*  > _timedMap;
	
	
	static bool _sortData(const std::unique_ptr<TimedData_<DataType>>& a, const std::unique_ptr<TimedData_<DataType>>& b)
	{
		return a->time < b->time;
	}
	
	DataType _currentValue;
	
	std::shared_ptr<TimeControl> _timeControl;
	
private:

	uint64_t _lastUpdateTime = 0;
	
	size_t _currentIndex =0;
	
	size_t _findNextIndex( const uint64_t& time);
	
	bool _isTimeInDataBounds(DataType& d,  const uint64_t& time);
	
	bool _bKeyframingEnabled = true;
	bool _bKeyframingEnabledProxy = true;
	
	void _enableKeyframing(bool e);
	
};


} } // ofx::LineaDeTiempo






