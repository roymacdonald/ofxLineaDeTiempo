//
//  TrackGroupController.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//

#pragma once
#include "LineaDeTiempo/BaseTypes/BaseController.h"
//#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "LineaDeTiempo/BaseTypes/BaseHasTracks.h"
#include "LineaDeTiempo/BaseTypes/BaseHasGroups.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
//#include "LineaDeTiempo/"
//#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Controller/TrackController.h"


namespace ofx {
namespace LineaDeTiempo {


//template <typename TrackGroupViewType>
class TrackGroupController
:public BaseController
,public BaseHasTracks<TrackController>
,public BaseHasGroups<TrackGroupController>//<TrackGroupViewType>>
//,public BaseViewController<TrackGroupView>
//,public BaseHasName
{
public:

	
	TrackGroupController(const std::string& name, TrackGroupController * parent)
	:BaseController(name, parent)
	,_parentGroup(parent)
	,BaseHasTracks<TrackController>()
	,BaseHasGroups<TrackGroupController>()
//	,BaseViewController<TrackGroupView>()
	{
	}
	
	virtual ~TrackGroupController() = default;
	
	template<typename NewTrackControllerType>//, typename NewTrackViewType>
	NewTrackControllerType * addTrack( const std::string& trackName = "")
	{
		
		auto uniqueName = _tracksCollection.makeUniqueName(trackName, "Track");
		
		return BaseController::_add
			<
				 NewTrackControllerType
				
				,TrackController
			>
			( _tracksCollection, uniqueName, this);
		
		
	}
	
	virtual bool removeTrack(TrackController* track) override
	{
		
		
		return BaseController::_remove<TrackController>( track,   _tracksCollection);
		
	}
	
	
	template<typename NewGroupControllerType>//, typename NewGroupViewType>
	NewGroupControllerType * addGroup( const std::string& groupName = "")
	{
		auto uniqueName = _groupsCollection.makeUniqueName(groupName, "Group");
		
		
		return BaseController::_add
			<
				 NewGroupControllerType
//				,NewGroupViewType
				,TrackGroupController
			>
		
		( _groupsCollection,  uniqueName, this);
		
	}
	
	virtual bool removeGroup(TrackGroupController* group) override
	{
		
//		return _remove <TrackGroupController<TrackGroupViewType>>( group,   _groupsCollection);
		return BaseController::_remove( group,   _groupsCollection);
	}
	
	
//	using BaseViewController<TrackGroupView>::getView;
//
//	using BaseViewController<TrackGroupView>::setView;
//
		
	using BaseHasTracks<TrackController>::removeTrack;

	using BaseHasTracks<TrackController>::getTrack;

	using BaseHasTracks<TrackController>::getTracks;

	using BaseHasTracks<TrackController>::getNumTracks;
	
	
	using BaseHasGroups<TrackGroupController>::removeGroup;

	using BaseHasGroups<TrackGroupController>::getGroup;
	 
	using BaseHasGroups<TrackGroupController>::getGroups;

	using BaseHasGroups<TrackGroupController>::getNumGroups;


	
	TrackGroupController * parentGroup()
	{
		return _parentGroup;
	}
	
	const TrackGroupController * parentGroup() const
	{
		return _parentGroup;
	}
	
protected:
	
	TrackGroupController * _parentGroup = nullptr;
	
	
private:
	
	
};


} } // ofx::LineaDeTiempo
