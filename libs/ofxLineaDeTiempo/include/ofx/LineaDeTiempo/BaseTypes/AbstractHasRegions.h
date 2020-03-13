////
////  BaseRegionController.hpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/11/20.
////
//
#pragma once

#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
#include <type_traits>


namespace ofx {
namespace LineaDeTiempo {
//
template<typename RegionType, typename bUseUniquePtr>
class AbstractHasRegions:
public BaseHasCollection<RegionType, bUseUniquePtr>
{
public:

	AbstractHasRegions():
	BaseHasCollection<RegionType, bUseUniquePtr>()
	{
		
	}
	
	virtual ~AbstractHasRegions() = default;
	
	virtual bool removeRegion(RegionType* region) = 0 ;
	
	
	bool removeRegion(const std::string& name)
	{
	//	return removeRegion(getRegion(name));
		return removeRegion(BaseHasCollection<RegionType,bUseUniquePtr>::findFirstElementByName(name));
	}

	bool removeRegion(const size_t& index)
	{
	//	return removeRegion(getRegion(index));
		return removeRegion(BaseHasCollection<RegionType,bUseUniquePtr>::getElementByIndex(index));
	}

	RegionType* getRegion(const std::string& name)
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::findFirstElementByName(name);
	}

	const RegionType* getRegion(const std::string& name) const
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::findFirstElementByName(name);
	}

	RegionType* getRegion(const size_t& index)
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::getElementByIndex(index);
	}

	const RegionType* getRegion(const size_t& index)const
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::getElementByIndex(index);
	}

	const std::vector<RegionType*>& getRegions()
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::getCollection();
	}

	const std::vector<const RegionType*>& getRegions() const
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::getCollection();
	}

	size_t getNumRegions() const
	{
		return BaseHasCollection<RegionType,bUseUniquePtr>::getNumElements();
	}

	
	
	
protected:
	
	

};

}} //ofx::LineaDeTiempo
