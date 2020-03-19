//
//  TrackGroupController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//
//
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/Utils/CollectionHelper.h"
//
namespace ofx {
namespace LineaDeTiempo {


TrackGroupController::TrackGroupController(const std::string& name, TrackGroupController * parent)
: DOM::Node(name, parent)
//,_parentGroup(parent)
//,BaseHasTracks<TrackController>()
//,BaseHasGroups<TrackGroupController>()
,BaseViewController<TrackGroupView>()
{
}

void TrackGroupController::generateView()
{
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		setView(p->getView()->template addChild<TrackGroupView>(p->getView(), this));
	}
	for(auto child : children())
	{
		auto c = dynamic_cast<BaseHasViews*>(child);
		if(c) c->generateView();
	}
}
void TrackGroupController::destroyView()
{
	for(auto child : children())
	{
		auto c = dynamic_cast<BaseHasViews*>(child);
		if(c) c->destroyView();
	}
	
	
	auto p = dynamic_cast<TrackGroupController*>(parent());
	if(p && p->getView())
	{
		p->getView()->removeChild(getView());
		setView(nullptr);
	}
}


//void TrackGroupController::generateView()
//{
//	if(_parentGroup && _parentGroup->getView())
//	{
//		setView(_parentGroup->getView()->addChild<TrackGroupView>(_parentGroup->getView(), this));
//	}
//}
//void TrackGroupController::destroyView()
//{
//	if(_parentGroup && _parentGroup->getView())
//	{
//		_parentGroup->getView()->removeChild(_parentGroup->getView());
//		setView(nullptr);
//	}
//}

bool TrackGroupController::removeTrack(TrackController* track)
{
	return CollectionHelper::_remove<TrackController, TrackGroupController>( track, this,   _tracksCollection);
}

bool TrackGroupController::removeGroup(TrackGroupController* group)
{
	return CollectionHelper::_remove<TrackGroupController, TrackGroupController>( group,this,   _groupsCollection);
}


//TrackGroupController * TrackGroupController::parentGroup()
//{
//	return _parentGroup;
//}
//
//const TrackGroupController * TrackGroupController::parentGroup() const
//{
//	return _parentGroup;
//}


} } // ofx::LineaDeTiempo

