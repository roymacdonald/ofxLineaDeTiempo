////
////  AbstractHasTracks.h
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/11/20.
////
//
#pragma once
//
//

#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
#include <type_traits>

namespace ofx {
namespace LineaDeTiempo {
//
template<typename TrackType, typename bUseUniquePtr>
class AbstractHasTracks:
public BaseHasCollection<TrackType, bUseUniquePtr>
{
public:

//	AbstractHasTracks();

	AbstractHasTracks():
	BaseHasCollection<TrackType, bUseUniquePtr>()
	{
		
	}
	
	virtual ~AbstractHasTracks() = default;
	virtual bool removeTrack(TrackType* track) = 0 ;
	
	bool removeTrack(const std::string& name)
	{
	//	return removeTrack(getTrack(name));
		return removeTrack(BaseHasCollection<TrackType,bUseUniquePtr>::findFirstElementByName(name));
	}

	bool removeTrack(const size_t& index)
	{
	//	return removeTrack(getTrack(index));
		return removeTrack(BaseHasCollection<TrackType,bUseUniquePtr>::getElementByIndex(index));
	}

	TrackType* getTrack(const std::string& name)
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::findFirstElementByName(name);
	}

	const TrackType* getTrack(const std::string& name) const
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::findFirstElementByName(name);
	}

	TrackType* getTrack(const size_t& index)
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::getElementByIndex(index);
	}

	const TrackType* getTrack(const size_t& index)const
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::getElementByIndex(index);
	}

	const std::vector<TrackType*>& getTracks()
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::getCollection();
	}

	const std::vector<const TrackType*>& getTracks() const
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::getCollection();
	}

	size_t getNumTracks() const
	{
		return BaseHasCollection<TrackType,bUseUniquePtr>::getNumElements();
	}

	

	
	
protected:
	
	

};

}} //ofx::LineaDeTiempo
