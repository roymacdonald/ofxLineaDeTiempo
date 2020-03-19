//
//  TracksPanel.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "LineaDeTiempo/View/TracksPanel.h"
#include "MUI/Styles.h"


#include "LineaDeTiempo/Controller/TimeControl.h"

#include "LineaDeTiempo/Controller/TracksPanelController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

#include "LineaDeTiempo/View/TrackHeader.h"



namespace ofx {
namespace LineaDeTiempo {
//using namespace MUI;
TracksPanel::TracksPanel(const std::string& id, DOM::Element* parentView, const ofRectangle& rect, TracksPanelController* controller)
//const std::string& name, TrackGroupView* parentGroupView, TrackGroupController * controller
: TrackGroupView(parentView, controller)

{
	std::cout << "TrackGroupView " << id << "  " << rect << string((controller != nullptr)?controller->getId():"null controller") << "\n";
	
	
//	setParent(controller->getMainView());
//	tracksView = addChild<TracksScrollPanel>(id + "_tracksView", ofRectangle(rect.x +_trackHeaderWidth,rect.y, rect.width  - _trackHeaderWidth, rect.height ));
	setShape(rect);
	tracksView = DOM::Element::addChild<MUI::TracksScrollPanel>(id + "_tracksView", _makeTracksViewRect());
	
	tracksView->setForceShowScrollbars(true);
	tracksView->setMoveToFrontOnCapture(false);
//	headersView = addChild<ClippedView_<Widget>>(id + "headersView", ofRectangle(rect.x, rect.y, _trackHeaderWidth, rect.height));
	headersView = addChild<MUI::ClippedView>(id + "headersView", _makeHeadersViewRect());
	
	_tracksContainerListeners.push(tracksView->getContainer()->move.newListener(this, &TracksPanel::_tracksMoved));
	_tracksContainerListeners.push(tracksView->getContainer()->resize.newListener(this, &TracksPanel::_tracksResized));

	_playhead = addChild<Playhead>(this);//, _timeControl);
//	MUI::Widget::setMoveToFrontOnCapture(false);
//	tracksView->setScrollV({0,1});
//	tracksView->setScrollH({0,1});
}
TracksClippedView* TracksPanel::getClippingView()
{
	return tracksView->getClippingView();
}
const TracksClippedView* TracksPanel::getClippingView()const
{
	return tracksView->getClippingView();
}
DOM::Element* TracksPanel::getContainer()
{
	return tracksView->getContainer();
}
const DOM::Element* TracksPanel::getContainer() const
{
	return tracksView->getContainer();
}
//---------------------------------------------------------------------
void TracksPanel::_tracksMoved(DOM::MoveEventArgs& e)
{
	_updateHeadersFromTracks();
	_playhead->updatePosition();
}
//---------------------------------------------------------------------
void TracksPanel::_tracksResized(DOM::ResizeEventArgs& e)
{
	_updateHeadersFromTracks();
}
//---------------------------------------------------------------------
void TracksPanel::_updateHeadersFromTracks()
{
	headersView->setOffset({0, tracksView->getClippingView()->getOffset().y });
	
}

void TracksPanel::_updateContainers(){
	tracksView->updateLayout();
	tracksView->updateContainerLayout();
}

//---------------------------------------------------------------------
void TracksPanel::updateLayout()
{
	std::cout << __PRETTY_FUNCTION__ << "\n";
	if(headersView) headersView->setShape(_makeHeadersViewRect());
	
	for(auto& t: children()){
		
		if(t){
			auto tt = dynamic_cast<TrackView*>(t);
			if(tt){
				tt->getHeader()->setSize(_trackHeaderWidth, tt->getHeader()->getHeight());
			}
		}
	}
	
	if(tracksView)  tracksView->setShape(_makeTracksViewRect());
	if(_playhead){
		_playhead->setSize(_playhead->getWidth(), getHeight());
		_playhead->moveToFront();
		
	}
}
//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeHeadersViewRect()
{
	
	return ofRectangle(0, CONTAINER_MARGIN, _trackHeaderWidth, getHeight() - (CONTAINER_MARGIN * 2) - SCROLL_BAR_SIZE);
}
//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTracksViewRect()
{
	return ofRectangle(_trackHeaderWidth, 0, getWidth() - _trackHeaderWidth, getHeight());
}
	
//---------------------------------------------------------------------
float TracksPanel::timeToScreenPosition(uint64_t time) const
{
	if(tracksView){
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			return container->localToScreen( {MUI::Math::lerp(time, 0, getTimeControl().getTotalTime(), 0, clippingView->getTracksWidth()), 0}).x ;
		}
	}
	
	ofLogError("TracksPanel::timeToScreenPosition") << "nullptr. returning 0";

	return 0;
		
	
}
//---------------------------------------------------------------------
uint64_t  TracksPanel::screenPositionToTime(float x) const
{

	if(tracksView)
	{
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			
			return  MUI::Math::lerp(container->screenToLocal({x, 0}).x, 0, clippingView->getTracksWidth(), 0, getTimeControl().getTotalTime()) ;
		}
	}
	
	ofLogError("TracksPanel::screenPositionToTime") << "nullptr. returning 0";

	return 0;

	
}
//---------------------------------------------------------------------



DOM::Element* TracksPanel::_getTracksContainer()
{
	return tracksView->getContainer();
}

DOM::Element* TracksPanel::_getHeadersContainer()
{
	return headersView->container;
}




} } // ofx::LineaDeTiempo
