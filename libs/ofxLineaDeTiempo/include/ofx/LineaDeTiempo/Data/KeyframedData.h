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
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
namespace ofx {
namespace LineaDeTiempo {


template<typename DataType>
class KeyframedData_: public BaseHasName
{
public:
	KeyframedData_();
	KeyframedData_(const std::string & name);//, std::shared_ptr<TimeControl> timeControl);
	virtual ~KeyframedData_(){}
	
	
	DataType getValueAtTime(const uint64_t& time) ;
	

	TimedData_<DataType>* add(const DataType& value, const uint64_t& time);
	
	bool remove(TimedData_<DataType>* d);
	
	///\brief remove all 
	void clear();
	
	virtual bool update(const uint64_t& time);
	
	void sortData();
	
	const DataType& getCurrentValue() const;
	
	void setValue(const DataType& value, const uint64_t& time, bool bAddKeyIfNotFound);
	

	
	friend std::ostream& operator<<(std::ostream& os, const KeyframedData_<DataType>& data);
	friend std::istream& operator>>(std::istream& is, KeyframedData_<DataType>& data);

	
	
	void enableKeyframing();
	
	void disableKeyframing();
	
	bool isKeyFramingEnabled() const;
	
	ofEvent<bool> keyframingEnableEvent;
	
	const std::vector< std::unique_ptr< TimedData_<DataType> > > & getData() const;
	
	
	void moveAllByTime(const uint64_t& _timeOffset);
	
	void fromJson(const ofJson& j);
	
	void toJson(ofJson& j);
	
	
protected:
	std::vector< std::unique_ptr< TimedData_<DataType> > > _data;
	
	std::map<uint64_t, TimedData_<DataType>*  > _timedMap;
	
	
	static bool _sortData(const std::unique_ptr<TimedData_<DataType>>& a, const std::unique_ptr<TimedData_<DataType>>& b)
	{
		return a->time < b->time;
	}
	
	DataType _currentValue;
	
//	std::shared_ptr<TimeControl> _timeControl;
	
private:

	
	///\brief add value and time to collection
	/// you should not use this. It will not check if it is possible to add an element and will not sort once done.
	/// used internally only.
	void _addToCollection(const DataType& value, const uint64_t& time);
	
	uint64_t _lastUpdateTime = 0;
	
	size_t _currentIndex =0;
	
	size_t _findNextIndex( const uint64_t& time);
	
	bool _isTimeInDataBounds(DataType& d,  const uint64_t& time);
	
	bool _bKeyframingEnabled = true;
	bool _bKeyframingEnabledProxy = true;
	
	void _enableKeyframing(bool e);
	
//	std::string _name;
};


} } // ofx::LineaDeTiempo



namespace nlohmann{
template <typename T>
struct adl_serializer<ofx::LineaDeTiempo::KeyframedData_<T>> {
	static void from_json(const json& j, ofx::LineaDeTiempo::KeyframedData_<T> & k)
	{
		k.fromJson(j);
		
	}

	static void to_json(json& j, ofx::LineaDeTiempo::KeyframedData_<T> k)
	{
		k.toJson(j);
	}
};

}

