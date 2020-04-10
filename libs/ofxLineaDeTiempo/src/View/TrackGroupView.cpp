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

TrackGroupView::TrackGroupView(DOM::Element* parentView, TrackGroupController * controller, TimeRuler * timeRuler)
: BaseTrackView(controller->getId(), parentView, timeRuler)
, _controller(controller)
{

	_tracksContainer = this;
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
	

	auto tr = _tracksContainer->removeChild(track);
	auto h = _header->removeChild(track->getHeader());

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
		

	auto tr = _tracksContainer->removeChild(track);
	auto h = _header->removeChild(track->getHeader());

//	_updateContainers();
	return true;
	
}

//---------------------------------------------------------------------
float TrackGroupView::getTracksHeaderWidth()
{
	return _trackHeaderWidth;
}

//---------------------------------------------------------------------
void TrackGroupView::_setTracksHeaderWidth(float w)
{
	if(!ofIsFloatEqual(_trackHeaderWidth, w)){
		_trackHeaderWidth = w;
		
		auto indent = ConstVars::HeaderViewIndent;
		if(_isPanel)
		{
			indent = 0;
		}
		
		for(auto c : _tracksContainer->children<TrackGroupView>())
		{
			c->_setTracksHeaderWidth(_trackHeaderWidth - indent);
			
		}
		
		
		updateLayout();
	}
}

float TrackGroupView::_getInitialYpos()
{
	auto p = dynamic_cast<TrackGroupView*>(parent());
	if(!p && numSiblings() == 0)
	{
		return 0;
	}
	return ConstVars::ViewTopHeaderHeight;
}

float TrackGroupView::getUnscaledHeight(size_t & numGroups)
{
	numGroups++;
	
	float h = 0;
	for(auto c: children())
	{
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			h+= t->getUnscaledHeight(numGroups);
		}
	}
	return h;
}
float TrackGroupView::updateYScaled(float y, float yScale)
{
	float h = _getInitialYpos();
	
	for(auto c: children())
	{
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			h+= t->updateYScaled(h,  yScale);
		}
	}
	
	setShape({0, y, getWidth(), h});
	return h;
}



} } // ofx::LineaDeTiempo
