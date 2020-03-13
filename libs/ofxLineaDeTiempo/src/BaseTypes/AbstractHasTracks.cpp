//
//  AbstractHasTracks.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/12/20.
//

//#include "LineaDeTiempo/BaseTypes/AbstractHasTracks.h"
//
//namespace ofx {
//namespace LineaDeTiempo {


//template<typename TrackType, bool bUseUniquePtr>
//AbstractHasTracks<TrackType, bUseUniquePtr>::AbstractHasTracks():
//BaseHasCollection<TrackType,bUseUniquePtr>()
//{
//
//}

//template<typename TrackType, bool bUseUniquePtr>
//bool AbstractHasTracks<TrackType, bUseUniquePtr>::removeTrack(const std::string& name)
//{
////	return removeTrack(getTrack(name));
//	return removeTrack(BaseHasCollection<TrackType,bUseUniquePtr>::findFirstElementByName(name));
//}
//
//template<typename TrackType, bool bUseUniquePtr>
//bool AbstractHasTracks<TrackType, bUseUniquePtr>::removeTrack(const size_t& index)
//{
////	return removeTrack(getTrack(index));
//	return removeTrack(BaseHasCollection<TrackType,bUseUniquePtr>::getElementByIndex(index));
//}
//
//template<typename TrackType, bool bUseUniquePtr>
//TrackType* AbstractHasTracks<TrackType, bUseUniquePtr>::getTrack(const std::string& name)
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::findFirstElementByName(name);
//}
//
//template<typename TrackType, bool bUseUniquePtr>
//const TrackType* AbstractHasTracks<TrackType, bUseUniquePtr>::getTrack(const std::string& name) const
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::findFirstElementByName(name);
//}
//
//template<typename TrackType, bool bUseUniquePtr>
//TrackType* AbstractHasTracks<TrackType, bUseUniquePtr>::getTrack(const size_t& index)
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::getElementByIndex(index);
//}
//
//template<typename TrackType, bool bUseUniquePtr>
//const TrackType* AbstractHasTracks<TrackType, bUseUniquePtr>::getTrack(const size_t& index)const
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::getElementByIndex(index);
//}
//
//
//// template<typename TrackType, bool bUseUniquePtr>
//// bool AbstractHasTracks<TrackType, bUseUniquePtr>::removeTrack(TrackType* track)
//// {
//// 	if(track == nullptr) return false;
//// 	return (removeElement(track) == nullptr);
//
//// }
//
//template<typename TrackType, bool bUseUniquePtr>
//const std::vector<TrackType*>& AbstractHasTracks<TrackType, bUseUniquePtr>::getTracks()
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::getCollection();
//}
//
//template<typename TrackType, bool bUseUniquePtr>
//const std::vector<const TrackType*>& AbstractHasTracks<TrackType, bUseUniquePtr>::getTracks() const
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::getCollection();
//}
//
//
//
//template<typename TrackType, bool bUseUniquePtr>
//size_t AbstractHasTracks<TrackType, bUseUniquePtr>::getNumTracks() const
//{
//	return BaseHasCollection<TrackType,bUseUniquePtr>::getNumElements();
//}





//}} //ofx::LineaDeTiempo
