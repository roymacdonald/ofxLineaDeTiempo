////
////  TimedDataCollection.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/10/20.
////
//
//
//#pragma once
//#include <stdint.h>
//#include <vector>
//#include <map>
//#include "LineaDeTiempo/Data/TimedData.h"
//#include "LineaDeTiempo/Controller/TimeControl.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
//#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"
//#include "ofRange.h"
//
//
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//
//template<typename DataType>
//class TimedDataCollection_:
//public BaseHasCollection<TimedData_<DataType>>,
//public AbstractSerializable
//{
//public:
////	TimedDataCollection_();
//	TimedDataCollection_(const std::string & name);
//	virtual ~TimedDataCollection_(){}
//
//
////	DataType getValueAtTime(const uint64_t& time) const;
////
////	const DataType& getCurrentValue() const;
//
//
//	TimedData_<DataType>* add(const DataType& value, const uint64_t& time);
//
//
//	virtual bool update(const uint64_t& time);
//
//	virtual void sortData() override;
//
//
////	void setValue(const DataType& value, const uint64_t& time, bool bAddKeyIfNotFound);
//
//
//
////	friend std::ostream& operator<<(std::ostream& os, const TimedDataCollection_<DataType>& data);
////	friend std::istream& operator>>(std::istream& is, TimedDataCollection_<DataType>& data);
//
//
//
////	void enableKeyframing();
////
////	void disableKeyframing();
////
////	bool isKeyFramingEnabled() const;
////
////	ofEvent<bool> keyframingEnableEvent;
//
//
//
//
//	void moveAllByTime(const uint64_t& _timeOffset);
//
//	virtual void fromJson(const ofJson& j) override;
//
//	virtual void toJson(ofJson& j) override;
//
//
//	const ofRange_<uint64_t>& getTimeRange() const;
//
//protected:
//
//
//
////	virtual void _addedElementToCollection(TimedData_<DataType>* newElement) override;
////	virtual void _removedElementFromCollection(TimedData_<DataType>* removedElement) override;
////
//
////	std::map<uint64_t, TimedData_<DataType>*  > _timedMap;
//
//
//	static bool _sortData(const std::unique_ptr<TimedData_<DataType>>& a, const std::unique_ptr<TimedData_<DataType>>& b)
//	{
//		return a->time < b->time;
//	}
//
////	DataType _currentValue;
//
////	std::shared_ptr<TimeControl> _timeControl;
//
//	ofRange_<uint64_t> _timeRange;
//
//	void updateTimeRange();
//
//private:
//
//
//	///\brief add value and time to collection
//	/// you should not use this. It will not check if it is possible to add an element and will not sort once done.
//	/// used internally only.
//	void _addToCollection(const DataType& value, const uint64_t& time);
//
//	uint64_t _lastUpdateTime = 0;
//
//	size_t _currentIndex =0;
//
//	size_t _findNextIndex( const uint64_t& time);
//
//	bool _isTimeInDataBounds(DataType& d,  const uint64_t& time);
//
////	bool _bKeyframingEnabled = true;
////	bool _bKeyframingEnabledProxy = true;
////
////	void _enableKeyframing(bool e);
//
////	std::string _name;
//};
//
//
//} } // ofx::LineaDeTiempo
//
//
//
//namespace nlohmann{
//template <typename T>
//struct adl_serializer<ofx::LineaDeTiempo::TimedDataCollection_<T>> {
//	static void from_json(const json& j, ofx::LineaDeTiempo::TimedDataCollection_<T> & k)
//	{
//		k.fromJson(j);
//
//	}
//
//	static void to_json(json& j, ofx::LineaDeTiempo::TimedDataCollection_<T> k)
//	{
//		k.toJson(j);
//	}
//};
//
//}
//
