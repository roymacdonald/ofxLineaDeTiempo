//
//  BaseHasTracks.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/11/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"



namespace ofx {
namespace LineaDeTiempo {

template<typename TrackType>
class BaseHasTracks

{
public:

	
	virtual ~BaseHasTracks() = default;

	
	
	virtual bool removeTrack(TrackType* track) = 0 ;
	
	

	 bool removeTrack(const std::string& name)
	 {
	 	return removeTrack(_tracksCollection.at(name));
	 }

	 bool removeTrack(const size_t& index)
	 {
		 return removeTrack(_tracksCollection.at(index));
	 }

	 TrackType* getTrack(const std::string& name)
	 {
	 	 return _tracksCollection.at(name);
	 }

	 const TrackType* getTrack(const std::string& name) const
	 {
	 	 return _tracksCollection.at(name);
	 }

	 TrackType* getTrack(const size_t& index)
	 {
	 	 return _tracksCollection.at(index);
	 }

	 const TrackType* getTrack(const size_t& index)const
	 {
		 return _tracksCollection.at(index);
	 }

	 const std::vector<TrackType*>& getTracks()
	 {
	 	return _tracksCollection.getCollection();
	 }

	 const std::vector<const TrackType*>& getTracks() const
	 {
		 return _tracksCollection.getCollection();
	 }

	 size_t getNumTracks() const
	 {
		 return _tracksCollection.size();
	 }


	
	typedef TrackType trackType;
	
	
	
protected:
	
	NamedConstPointerCollection<TrackType> _tracksCollection;



};

}} //ofx::LineaDeTiempo
