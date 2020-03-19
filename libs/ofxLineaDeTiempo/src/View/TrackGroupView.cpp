//
//  TrackGroupView.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Controller/TrackController.h"
namespace ofx {
namespace LineaDeTiempo {

TrackGroupView::TrackGroupView(DOM::Element* parentView, TrackGroupController * controller)
: BaseTrackView(controller->getId(), parentView)
, BaseHasController<TrackGroupController>(controller)
{
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
	auto c = _getTracksContainer();
	if(c) c->updateLayout();
	if(c != this)updateLayout();
	
}


bool TrackGroupView::removeTrack(TrackController* controller)
{
	if(controller == nullptr) return false;

	auto track = controller->getView();
	auto c = _getTracksContainer();
	auto hc = _getHeadersContainer();
	if(c && hc){

		auto tr = c->removeChild(track);
		auto h = hc->removeChild(track->getHeader());

		
//		removeChild(track);
		
//		BaseHasCollection<BaseTrack, false_type>::removeElement(track);
		
//		ofRemove(_trackCollection, [&](BaseTrack* t){
//			return (track->getHeader() == t->getHeader() && track == t);
//		});
		_updateContainers();
		return true;
	}
	return false;
}

DOM::Element* TrackGroupView::_getTracksContainer()
{
	return this;
}
DOM::Element* TrackGroupView::_getHeadersContainer()
{
	return _header;
}

//---------------------------------------------------------------------
float TrackGroupView::getTrackHeaderWidth(){
	return _trackHeaderWidth;
}
//---------------------------------------------------------------------
void TrackGroupView::setTrackHeaderWidth(float w){
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
			h+= t->updateScaledShape(y,  yScale, width);
		}
	}
	
	setShape({0, y, width, h});
	updateLayout();
	return h;
}


} } // ofx::LineaDeTiempo
