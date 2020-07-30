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
class BaseKeyframedData
: public AbstractSerializable
{
public:
	
	BaseKeyframedData();
	
	virtual ~BaseKeyframedData() = default;
	
	
	virtual bool update(const uint64_t& time) = 0;
	
	void moveAllByTime(const uint64_t& _timeOffset);
	
	void setTimeRange(const ofRange64u& timeRange);
	
	const ofRange64u& getTimeRange();
	
	
	
	void enableKeyframing();
	
	void disableKeyframing();
	
	bool isKeyFramingEnabled() const;
	
	ofEvent<bool> keyframingEnableEvent;

	void setEnableKeyframing(bool e);
	
	
	
	const std::vector< std::unique_ptr< DataType > > & getData() const;
	
	size_t size() const;
	
	void clear();
	
	void sortData();
	

	bool remove(DataType* d);


	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;

	
	
protected:
	
	bool _bKeyframingEnabled = true;
	
	bool _bKeyframingEnabledProxy = true;
	
	ofRange64u _timeRange;
	
	
	size_t _startIndex = 0;
	
	size_t _endIndex = 0;
	
	
	uint64_t _lastUpdateTime = 0;
	
	size_t _currentIndex =0;
	
	
	
	std::vector< std::unique_ptr< DataType > > _data;
	
	std::map<uint64_t, DataType*  > _timedMap;
	
	virtual uint64_t& _getTimeFromData(DataType*) = 0;
	
	
	///\brief add data to collection
	/// you should not use this. It will not check if it is possible to add an element and will not sort once done.
	/// used internally only.
	DataType* _addToCollection(const DataType& data, bool sort);
	
	
	virtual std::string _getTypeName() = 0;
	
};



template<typename DataType>
class KeyframedData_
: public BaseKeyframedData<TimedData_<DataType>>
{
public:
	KeyframedData_() = default;
	virtual ~KeyframedData_() = default;
	
	
	DataType getValueAtTime(const uint64_t& time) ;
	

	TimedData_<DataType>* add(const DataType& value, const uint64_t& time);
	
	
	virtual bool update(const uint64_t& time) override;
	
	
	const DataType& getCurrentValue() const;
	
	void setValue(const DataType& value, const uint64_t& time, bool bAddKeyIfNotFound);
	


	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;

	
	
	
protected:
	
	
	DataType _currentValue = 0;
	
	typedef BaseKeyframedData<TimedData_<DataType>> Base;
	
	
	using Base::_lastUpdateTime;
	using Base::_currentIndex;
	using Base::_data;
	
	using Base::_timedMap;
	
	using Base::_addToCollection;

	virtual uint64_t& _getTimeFromData(TimedData_<DataType>*) override;
	
	virtual std::string _getTypeName() override;
	
private:

	
	
	
	size_t _findNextIndex( const uint64_t& time);
	
	bool _isTimeInDataBounds(DataType& d,  const uint64_t& time);
	
	
	
	
};




template<>
class KeyframedData_<void>
: public BaseKeyframedData<uint64_t>
{
public:
	KeyframedData_() = default;
	virtual ~KeyframedData_() = default;
	
	uint64_t* add(const uint64_t& time);
	
	virtual bool update(const uint64_t& time) override;
	
		
	

protected:
	virtual std::string _getTypeName() override;
	
	virtual uint64_t& _getTimeFromData(uint64_t*) override;
	
private:

	size_t _findNextIndex( const uint64_t& time);
	

	
};





}} //ofx::LineaDeTiempo

