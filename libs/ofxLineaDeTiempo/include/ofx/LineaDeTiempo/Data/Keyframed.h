////
////  Keyframed.hpp
////  example
////
////  Created by Roy Macdonald on 4/10/20.
////
//
//#pragma once
//#include <stdint.h>
//#include <vector>
//#include <map>
//#include <set>
//#include "LineaDeTiempo/Data/TimedData.h"
//#include "LineaDeTiempo/Controller/TimeControl.h"
//#include "ofRange.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//
//
//template<typename Type>
//class Keyframed
//: public AbstractSerializable
//{
//public:
//	Keyframed();
//	virtual ~Keyframed(){}
//	
//	
//	bool hasKeyframeAt(const uint64_t& time) const;	
//
//	template <typename... Args>
//	Type* add(Args&&... args, const uint64_t& time);
//
//	
//	bool remove(Type* d);
//	
//	size_t size() const;
//	
//	///\brief remove all
//	void clear();
//	
//	virtual bool update(const uint64_t& time);
//	
//	void sortData();
//		
//	std::string toString() const;
//	
//
//	const std::vector< std::unique_ptr< Type > > & getData() const;
//	
//	
//	void moveAllByTime(const uint64_t& _timeOffset);
//	
//	virtual void fromJson(const ofJson& j) override;
//
//	virtual ofJson toJson() override;
//
//	
//	void enableKeyframing();
//	
//	void disableKeyframing();
//	
//	bool isKeyFramingEnabled() const;
//	
//	ofEvent<bool> keyframingEnableEvent;
//
//	void setEnableKeyframing(bool e);
//	
//	const ofRange64u&  getCurrentRange() const;
//	
//
//	
//	
//protected:
//	
//	virtual void _onAddFailed(const uint64_t& time)
//	{
//		
//	}
//	
////	virtual void _onRemove(Type * k)
////	{
////
////	}
//	
//	bool _bKeyframingEnabled = true;
//	
//	bool _bKeyframingEnabledProxy = true;
//			
//	std::vector< std::unique_ptr< Type > > _data;
//	
//	
//	uint64_t & _getTime(std::unique_ptr<Type>& data);
//	
//	void _loadKeyframes(ofJson& j);
//
//	size_t _findNextIndex( const uint64_t& time);
//	
////private:
//
//	uint64_t _lastUpdateTime = 0;
//	
//	size_t _currentIndex =0;
//	
//	
//	
//	bool _isTimeInDataBounds(const uint64_t& time);
//	
//	ofRange64u _currentRange;
//	
//	std::map<uint64_t, Type* > _timedMap;
//	
//};
//
//
//template<typename Type>
//template <typename... Args>
//Type* Keyframed<Type>::add(Args&&... args, const uint64_t& time)
//{
//	
//	if(!hasKeyframeAt(time))
//	{
//		
//		_data.emplace_back(std::make_unique<Type>(std::forward<Args>(args)...));
//		auto d = _data.back().get();
//		_timedMap[_getTime(_data.back())] =  d;
//		
//		sortData();
//		
//		return d;
//		
//	}
//	else
//	{
//		_onAddFailed(time);
//		ofLogNotice("KeyframeTrackDataManager_<T>::add") << "there is already data at this point. Returning nullptr";
//		return nullptr;
//	}
//	
//}
//
//
//
//}} //ofx::LineaDeTiempo
//
