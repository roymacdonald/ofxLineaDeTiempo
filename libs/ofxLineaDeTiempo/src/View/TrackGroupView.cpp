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

TrackGroupView::TrackGroupView(DOM::Element* parentView, TrackGroupController * controller, TrackHeaderGroup* headerGroup, TimeRuler * timeRuler)
: BaseTrackView(controller->getId(), parentView, timeRuler)
, _controller(controller)
{

	_tracksContainer = this;
	
	if(headerGroup){
		_groupHeader = headerGroup->addGroupHeader(getId() + "_groupHeader", this, _isPanel);
	
		setHeader(_groupHeader);
	}
	
	
	_childrensChangeListeners.push(childAdded.newListener(this, &TrackGroupView::_onChildrensChange));
	_childrensChangeListeners.push(childRemoved.newListener(this, &TrackGroupView::_onChildrensChange));
	
}
void TrackGroupView::_onChildrensChange(DOM::ElementEventArgs& )
{
	onChildrensChange();
}


void TrackGroupView::onChildrensChange()
{
	if(_parentGroupView)
	{
		_parentGroupView->onChildrensChange();
	}
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
	if(!_groupHeader)
	{
		ofLogError("TrackGroupView::"+callerName) << "headersGRoup container is invalid. " << getId();
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
	if(tr){
		return _groupHeader->removeTrackHeader(track->getHeader());
	}
//	auto h = _header->removeChild(track->getHeader());
	ofLogError("TrackGroupView::removeTrack") << "could not remove track. Probably it does not belong to this group. " << getId();
	return false;
	
}


TrackGroupView* TrackGroupView::addGroup(TrackGroupController * controller )
{	
	if(!controller)
	{
		ofLogError("TrackGroupView::addGroup") << "controller is invalid. " << getId();
		return nullptr;
	}
	
	if(_containersCheck("addGroup") == false)
	{
		return nullptr;
	}
	
	
	auto t = _tracksContainer->addChild<TrackGroupView>(this, controller, _groupHeader, _timeRuler);
//	_groupHeader->addGroupHeader(getId()+ "_groupHeader", t, _isPanel);
//	auto h = _header->addChild<TrackHeader>( "_header", ofRectangle(0, 0, _trackHeaderWidth, ConstVars::TrackInitialHeight), t , this, _isPanel);

	return t;
	
}


bool TrackGroupView::removeGroup(TrackGroupController * controller)
{
	if(controller == nullptr)
	{
		ofLogError("TrackGroupView::removeGroup") << "controller is nulptr";
		return false;
	}
	if(_containersCheck("removeGroup") == false)
	{
		return false;
	}
	auto track = dynamic_cast<TrackGroupView*>(controller->getView());
	if(!track)
	{
		ofLogError("TrackGroupView::removeGroup") << "group view is invalid. " << getId();
		return false;
	}

		

	auto tr = _tracksContainer->removeChild(track);
//	auto h = _header->removeChild(track->getHeader());
	if(tr){
			return _groupHeader->removeGroupHeader(track->getGroupHeader());
		}
		ofLogError("TrackGroupView::removeGroup") << "could not remove group. Probably it does not belong to this group. " << getId();
		return false;
		
	
	
//	_updateContainers();
//	return true;
	
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

float TrackGroupView::getUnscaledHeight()
{
	
	float h = _getInitialYpos();//_isPanel?0:ConstVars::ViewTopHeaderHeight.get();
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


void  TrackGroupView::updateVerticalLayout()
{
	float h = _getInitialYpos();
	
	for(auto c: children())
	{
		auto g = dynamic_cast<TrackGroupView*>(c);
		if(g)
		{
			g->updateVerticalLayout();
		}
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			t->setPosition(t->getX(), h);
			
			h += t->getHeight();
		}
	}
	setHeight(h);
}

void TrackGroupView::onUpdate()
{
	if(isChildShapeInvalidated())
	{
//		std::cout << "TrackGroupView::onUpdate()  " << getId() << "\n";
		updateVerticalLayout();
	}
}




} } // ofx::LineaDeTiempo
