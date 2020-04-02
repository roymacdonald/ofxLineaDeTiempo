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
: public AbstractSerializable
{
public:
	KeyframedData_();
	virtual ~KeyframedData_(){}
	
	
	DataType getValueAtTime(const uint64_t& time) ;
	

	TimedData_<DataType>* add(const DataType& value, const uint64_t& time);
	
	bool remove(TimedData_<DataType>* d);
	
	size_t size() const;
	
	///\brief remove all 
	void clear();
	
	virtual bool update(const uint64_t& time);
	
	void sortData();
	
	const DataType& getCurrentValue() const;
	
	void setValue(const DataType& value, const uint64_t& time, bool bAddKeyIfNotFound);
	

	
	std::string toString() const;
	

	
	const std::vector< std::unique_ptr< TimedData_<DataType> > > & getData() const;
	
	
	void moveAllByTime(const uint64_t& _timeOffset);
	
	virtual void fromJson(const ofJson& j) override;

	virtual ofJson toJson() override;

	
	void enableKeyframing();
	
	void disableKeyframing();
	
	bool isKeyFramingEnabled() const;
	
	ofEvent<bool> keyframingEnableEvent;

	void setEnableKeyframing(bool e);
	
	
	
	
	
protected:
	
	bool _bKeyframingEnabled = true;
	
	bool _bKeyframingEnabledProxy = true;
		
	
	std::vector< std::unique_ptr< TimedData_<DataType> > > _data;
	
	std::map<uint64_t, TimedData_<DataType>*  > _timedMap;
	
	
	
	DataType _currentValue;
	
private:

	
	///\brief add value and time to collection
	/// you should not use this. It will not check if it is possible to add an element and will not sort once done.
	/// used internally only.
	void _addToCollection(const DataType& value, const uint64_t& time);
	
	uint64_t _lastUpdateTime = 0;
	
	size_t _currentIndex =0;
	
	size_t _findNextIndex( const uint64_t& time);
	
	bool _isTimeInDataBounds(DataType& d,  const uint64_t& time);
	
};




}} //ofx::LineaDeTiempo

