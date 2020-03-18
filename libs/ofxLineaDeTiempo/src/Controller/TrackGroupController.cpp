//
//  TrackGroupController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//
//
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/View/TrackGroupView.h"

//
namespace ofx {
namespace LineaDeTiempo {


TrackGroupController::TrackGroupController(const std::string& name, TrackGroupController * parent)
:BaseController(name, parent)
,_parentGroup(parent)
//,BaseHasTracks<TrackController>()
//,BaseHasGroups<TrackGroupController>()
,BaseViewController<TrackGroupView>()
{
}


void TrackGroupController::generateView()
{
	if(_parentGroup && _parentGroup->getView())
	{
		setView(_parentGroup->getView()->addChild<TrackGroupView>(_parentGroup->getView(), this));
	}
}
void TrackGroupController::destroyView()
{
	if(_parentGroup && _parentGroup->getView())
	{
		_parentGroup->getView()->removeChild(_parentGroup->getView());
		setView(nullptr);
	}
}

//template<typename NewTrackControllerType>
//NewTrackControllerType * TrackGroupController::addTrack( const std::string& trackName)
//{
//
//	auto uniqueName = _tracksCollection.makeUniqueName(trackName, "Track");
//
//	return BaseController::
//	_add< NewTrackControllerType ,TrackController>
//
//	( _tracksCollection, uniqueName, this);
//
//}

bool TrackGroupController::removeTrack(TrackController* track)
{
	
	return BaseController::_remove<TrackController>( track,   _tracksCollection);
	
}


//template<typename NewGroupControllerType>
//NewGroupControllerType * TrackGroupController::addGroup( const std::string& groupName)
//{
//	auto uniqueName = _groupsCollection.makeUniqueName(groupName, "Group");
//	
//	return BaseController::
//	_add< NewGroupControllerType, TrackGroupController >
//	
//	( _groupsCollection,  uniqueName, this);
//	
//}

bool TrackGroupController::removeGroup(TrackGroupController* group)
{
	
	//		return _remove <TrackGroupController<TrackGroupViewType>>( group,   _groupsCollection);
	return BaseController::_remove( group,   _groupsCollection);
}


TrackGroupController * TrackGroupController::parentGroup()
{
	return _parentGroup;
}

const TrackGroupController * TrackGroupController::parentGroup() const
{
	return _parentGroup;
}


} } // ofx::LineaDeTiempo

