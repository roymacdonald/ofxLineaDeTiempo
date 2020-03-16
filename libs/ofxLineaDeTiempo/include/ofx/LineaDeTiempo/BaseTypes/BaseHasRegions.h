//
//  BaseRegionController.hpp
//  regionsAndTimeTest
//
//  Created by Roy Macdonald on 3/11/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"

namespace ofx {
namespace LineaDeTiempo {
//
template<typename RegionType>
class BaseHasRegions
{
public:

	// BaseHasRegions(){}
	
	virtual ~BaseHasRegions() = default;
	
	virtual bool removeRegion(RegionType* region) = 0 ;
	

	

	 bool removeRegion(const std::string& name)
	 {
	 	return _regionsCollection.remove(name);
	 }

	 bool removeRegion(const size_t& index)
	 {
	 	 return _regionsCollection.remove(index);
	 }

	 RegionType* getRegion(const std::string& name)
	 {
	 	 return _regionsCollection.at(name);
	 }

	 const RegionType* getRegion(const std::string& name) const
	 {
	 	 return _regionsCollection.at(name);
	 }

	 RegionType* getRegion(const size_t& index)
	 {
	 	 return _regionsCollection.at(index);
	 }

	 const RegionType* getRegion(const size_t& index)const
	 {
		 return _regionsCollection.at(index);
	 }

	 const std::vector<RegionType*>& getRegions()
	 {
	 	return _regionsCollection.getCollection();
	 }

	 const std::vector<const RegionType*>& getRegions() const
	 {
		 return _regionsCollection.getCollection();
	 }

	 size_t getNumRegions() const
	 {
		 return _regionsCollection.size();
	 }


	
	typedef RegionType regionType;
	
		
	protected:
		
		NamedConstPointerCollection<RegionType> _regionsCollection;




};
//
//template<typename RegionType>
//class BaseRegionsController
//: public BaseHasRegions<RegionType>
//, public DOM::Node<RegionType>
//{
//public:
//
//	BaseRegionsController(const std::string& id)
//	:DOM::Node<RegionType>(id)
//	{
//		
//	}
//	
//	virtual ~BaseRegionsController() = default;
//	
//	
//	virtual bool removeRegion(const std::string& name)
//	{
//		return removeRegion(DOM::Node<RegionType>::findFirstElementById(name));
//	}
//
//	virtual bool removeRegion(const size_t& index)
//	{
//		return removeRegion(DOM::Node<RegionType>::getChildByIndex(index));
//	}
//
//	virtual RegionType* getRegion(const std::string& name)
//	{
//		return DOM::Node<RegionType>::findFirstChildByName(name);
//	}
//
//	virtual const RegionType* getRegion(const std::string& name) const
//	{
//		return DOM::Node<RegionType>::findFirstChildByName(name);
//	}
//
//	virtual RegionType* getRegion(const size_t& index)
//	{
//		return DOM::Node<RegionType>::getChildByIndex(index);
//	}
//
//	virtual const RegionType* getRegion(const size_t& index)const
//	{
//		return DOM::Node<RegionType>::getChildByIndex(index);
//	}
//
//	virtual const std::vector<RegionType*>& getRegions()
//	{
//		return DOM::Node<RegionType>::children();
//	}
//
//	virtual const std::vector<const RegionType*>& getRegions() const
//	{
//		return DOM::Node<RegionType>::children();
//	}
//
//	virtual size_t getNumRegions() const
//	{
//		return DOM::Node<RegionType>::getNumChildren();
//	}
//	
//	
//	
//protected:
//	
//	
//
//};

}} //ofx::LineaDeTiempo
