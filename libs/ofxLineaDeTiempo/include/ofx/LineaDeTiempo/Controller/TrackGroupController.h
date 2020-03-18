//
//  TrackGroupController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//

#pragma once
#include "LineaDeTiempo/BaseTypes/BaseController.h"
//#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
// #include "LineaDeTiempo/BaseTypes/BaseHasTracks.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasGroups.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
//#include "LineaDeTiempo/"
#include "LineaDeTiempo/View/TrackGroupView.h"
//#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"


namespace ofx {
namespace LineaDeTiempo {



class TrackGroupController
:public BaseController
//,public BaseHasTracks<TrackController>
//,public BaseHasGroups<TrackGroupController>//<TrackGroupViewType>>
,public BaseViewController<TrackGroupView>
//,public BaseHasName
{
public:
	
	
	TrackGroupController(const std::string& name, TrackGroupController * parent);
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	
	virtual ~TrackGroupController() = default;
	
	template<typename NewTrackControllerType>
	NewTrackControllerType * addTrack( const std::string& trackName = "")
	{
		
		auto uniqueName = _tracksCollection.makeUniqueName(trackName, "Track");
		
		return BaseController::
		_add< NewTrackControllerType ,TrackController>
		
		( _tracksCollection, uniqueName, this);
		
	}
	
	bool removeTrack(TrackController* track);
	
	
	template<typename NewGroupControllerType>
	NewGroupControllerType * addGroup( const std::string& groupName = "")
	{
		auto uniqueName = _groupsCollection.makeUniqueName(groupName, "Group");
		
		return BaseController::
		_add< NewGroupControllerType, TrackGroupController >
		
		( _groupsCollection,  uniqueName, this);
		
	}
	
	
	
	using BaseViewController<TrackGroupView>::getView;
	using BaseViewController<TrackGroupView>::setView;
	
	bool removeGroup(TrackGroupController* group);
	
	bool removeGroup(const std::string& name)
	{
		return removeGroup(_groupsCollection.at(name));
	}
	
	bool removeGroup(const size_t& index)
	{
		return removeGroup(_groupsCollection.at(index));
	}
	
	TrackGroupController* getGroup(const std::string& name)
	{
		return _groupsCollection.at(name);
	}
	
	const TrackGroupController* getGroup(const std::string& name) const
	{
		return _groupsCollection.at(name);
	}
	
	TrackGroupController* getGroup(const size_t& index)
	{
		return _groupsCollection.at(index);
	}
	
	const TrackGroupController* getGroup(const size_t& index)const
	{
		return _groupsCollection.at(index);
	}
	
	const std::vector<TrackGroupController*>& getGroups()
	{
		return _groupsCollection.getCollection();
	}
	
	const std::vector<const TrackGroupController*>& getGroups() const
	{
		return _groupsCollection.getCollection();
	}
	
	size_t getNumGroups() const
	{
		return _groupsCollection.size();
	}
	
	
	
	bool removeTrack(const std::string& name)
	{
		return removeTrack(_tracksCollection.at(name));
	}
	
	bool removeTrack(const size_t& index)
	{
		return removeTrack(_tracksCollection.at(index));
	}
	
	TrackController* getTrack(const std::string& name)
	{
		return _tracksCollection.at(name);
	}
	
	const TrackController* getTrack(const std::string& name) const
	{
		return _tracksCollection.at(name);
	}
	
	TrackController* getTrack(const size_t& index)
	{
		return _tracksCollection.at(index);
	}
	
	const TrackController* getTrack(const size_t& index)const
	{
		return _tracksCollection.at(index);
	}
	
	const std::vector<TrackController*>& getTracks()
	{
		return _tracksCollection.getCollection();
	}
	
	const std::vector<const TrackController*>& getTracks() const
	{
		return _tracksCollection.getCollection();
	}
	
	size_t getNumTracks() const
	{
		return _tracksCollection.size();
	}
	
	
	
	
	
	TrackGroupController * parentGroup();
	const TrackGroupController * parentGroup() const;
	
protected:
	
	TrackGroupController * _parentGroup = nullptr;
	NamedConstPointerCollection<TrackGroupController> _groupsCollection;
	NamedConstPointerCollection<TrackController> _tracksCollection;
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
