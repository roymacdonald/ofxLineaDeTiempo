//
//  TrackGroupView.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/TracksPanel.h"
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

namespace ofx {
namespace LineaDeTiempo {

TrackGroupView::TrackGroupView(DOM::Element* parentView, TrackGroupController * controller)
: BaseTrackView(controller->getId(), parentView)
, _parentGroup(dynamic_cast<TrackGroupView*>(parentView))
, _controller(controller)
{

	_tracksContainer = this;
	
	
	_enableParentShapeListener();
}

void TrackGroupView::_parentMoved(DOM::MoveEventArgs& e)
{
	_updateContainers();
}

void TrackGroupView::_parentResized(DOM::ResizeEventArgs& e)
{
	_updateContainers();
}

void TrackGroupView::_enableParentShapeListener()
{
	_parentListeners.push(parent()->move.newListener(this, &TrackGroupView::_parentMoved ));
	_parentListeners.push(parent()->resize.newListener(this, &TrackGroupView::_parentResized));
	
}

void TrackGroupView::_disableParentShapeListener()
{
	_parentListeners.unsubscribeAll();
}

void TrackGroupView::_updateContainers()
{
	
	if(_tracksContainer) _tracksContainer->updateLayout();
	if(_tracksContainer != this)updateLayout();
	
}
bool TrackGroupView::_containersCheck(const std::string & callerName)
{
	if(!_tracksContainer)
	{
		ofLogError("TrackGroupView::"+callerName) << "tracks container is invalid. " << getId();
		return false;
	}
	
	if(!_header)
	{
		ofLogError("TrackGroupView::"+callerName) << "headers container is invalid. " << getId();
		return false;
	}
	return true;
}

bool TrackGroupView::removeTrack(TrackController* controller)
{
	if(controller == nullptr)
	{
		ofLogError("TrackGroupView::removeTrack") << "controller is nulptr";
		return false;
	}
	
	auto track = controller->getView();
	if(!track)
	{
		ofLogError("TrackGroupView::removeTrack") << "track view is invalid. " << getId();
		return false;
	}
	
	if(_containersCheck("removeTrack") == false)
	{
		return false;
	}
//	if(!_tracksContainer)
//	{
//		ofLogError("TrackGroupView::removeTrack") << "tracks container is invalid. " << getId();
//		return false;
//	}
//
//	if(!_headersContainer)
//	{
//		ofLogError("TrackGroupView::removeTrack") << "headers container is invalid. " << getId();
//		return false;
//	}
	
	

	auto tr = _tracksContainer->removeChild(track);
	auto h = _header->removeChild(track->getHeader());

	_updateContainers();
	return true;
	
}

bool TrackGroupView::removeGroup(TrackGroupController * controller)
{
	if(controller == nullptr)
	{
		ofLogError("TrackGroupView::removeGroup") << "controller is nulptr";
		return false;
	}
	
	auto track = controller->getView();
	if(!track)
	{
		ofLogError("TrackGroupView::removeGroup") << "track view is invalid. " << getId();
		return false;
	}
	if(_containersCheck("removeGroup") == false)
	{
		return false;
	}
	
//	if(!_tracksContainer)
//	{
//		ofLogError("TrackGroupView::removeTrack") << "tracks container is invalid. " << getId();
//		return false;
//	}
//
//	if(!_headersContainer)
//	{
//		ofLogError("TrackGroupView::removeTrack") << "headers container is invalid. " << getId();
//		return false;
//	}
	

	auto tr = _tracksContainer->removeChild(track);
	auto h = _header->removeChild(track->getHeader());

	_updateContainers();
	return true;
	
}

//---------------------------------------------------------------------
float TrackGroupView::getTrackHeaderWidth()
{
	return _trackHeaderWidth;
}

//---------------------------------------------------------------------
void TrackGroupView::setTrackHeaderWidth(float w)
{
	if(!ofIsFloatEqual(_trackHeaderWidth, w)){
		_trackHeaderWidth = w;
		updateLayout();
	}
}


float TrackGroupView::getUnscaledHeight()
{
	float h = _groupTopMargin;
	
	for(auto c: children())
	{
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			h+= t->getUnscaledHeight();
		}
	}
	
	return h;
}
float TrackGroupView::updateScaledShape(float y, float yScale, float width)
{
	float h = _groupTopMargin;
	
	for(auto c: children())
	{
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			h+= t->updateScaledShape(h,  yScale, width);
		}
	}
	
	setShape({0, y, width, h});
	updateLayout();
	return h;
}
//void TrackGroupView::updateLayout()
//{
//	std::cout << "TrackGroupView::updateLayout()\n";
//
//	float currentY = _groupTopMargin;
//	for (auto c : children()){
//		auto t = dynamic_cast<BaseTrackView*>(c);
//		if (t){
//			std::cout << getWidth() << "\n";
//			currentY += t->updateScaledShape(currentY, 1, getWidth());
//		}
//	}
//	auto s = getChildShape();
//	
//	setSize(s.width , s.height);
//	
//}

//
//const TrackGroupController * TrackGroupView::getController() const
//{
//	return _controller;
//}
//TrackGroupController * TrackGroupView::getController()
//{
//	return _controller;
//}
//void TrackGroupView::setController(TrackGroupController * controller)
//{
//	_controller = controller;
//}


} } // ofx::LineaDeTiempo
