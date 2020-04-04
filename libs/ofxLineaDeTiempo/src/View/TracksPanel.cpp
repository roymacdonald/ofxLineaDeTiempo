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
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {

TracksPanel::TracksPanel(const std::string& id, DOM::Element* parentView, const ofRectangle& rect, TracksPanelController* controller)

: TrackGroupView(parentView, controller)

{
	setShape(rect);
	tracksView = DOM::Element::addChild<MUI::TracksScrollPanel>(id + "_tracksView", _makeTracksViewRect());
	
	tracksView->setForceShowScrollbars(true);
	tracksView->setMoveToFrontOnCapture(false);

	headersView = addChild<MUI::ClippedView_<TrackHeader>>(id + "headersView", _makeHeadersViewRect(), nullptr, nullptr, true);
	
	_tracksContainerListeners.push(tracksView->getContainer()->move.newListener(this, &TracksPanel::_tracksMoved));
	_tracksContainerListeners.push(tracksView->getContainer()->resize.newListener(this, &TracksPanel::_tracksResized));

	_playhead = tracksView->getContainer()->addChild<Playhead>(this, controller->getTimeControl());//, _timeControl);

	
	_timeRuler = addChild<TimeRuler>(this, controller->getTimeControl());
	
	
	_tracksContainer = tracksView->getContainer();
	_header = headersView->container;
	
	
	_parentListener = parentView->resize.newListener(this, &TracksPanel::_parentViewResized);
	

	_regionsStyle = make_shared<MUI::Styles>();
	_regionsStyle->setColor(RegionBackgroundColor, MUI::Styles::ROLE_BACKGROUND);
	
	_isPanel = true;
	
}

void TracksPanel::_setup()
{
	if(tracksView)
	{
		tracksView->setScrollH({0,1});
		tracksView->setScrollV({0,1});
		_setTracksHeaderWidth(getTracksHeaderWidth());
	}
}


void TracksPanel::setTracksHeaderWidth(float w)
{
	_setTracksHeaderWidth(w);
	
}

shared_ptr<MUI::Styles> TracksPanel::getRegionsStyle()
{
	return _regionsStyle;
}


void TracksPanel::_parentViewResized(DOM::ResizeEventArgs&)
{
	updateLayout();
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
//---------------------------------------------------------------------
void TracksPanel::_updateContainers(){
	tracksView->updateLayout();
	tracksView->updateContainerLayout();
}
//---------------------------------------------------------------------
void TracksPanel::onDraw() const
{
	BaseTrackView::onDraw();
	ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
}

//---------------------------------------------------------------------
void TracksPanel::updateLayout()
{
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
	if(_timeRuler)_timeRuler->updateLayout();
}

//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeHeadersViewRect()
{
	
	return ofRectangle(0, TimeRulerInitialHeight + CONTAINER_MARGIN, _trackHeaderWidth, getHeight() - (CONTAINER_MARGIN * 2) - SCROLL_BAR_SIZE - TimeRulerInitialHeight);
}

//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTracksViewRect()
{
	return ofRectangle(_trackHeaderWidth, TimeRulerInitialHeight , getWidth() - _trackHeaderWidth, getHeight() - TimeRulerInitialHeight );
}
	

//---------------------------------------------------------------------
float TracksPanel::timeToScreenPosition(uint64_t time) const
{
	if(tracksView){
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			return container->localToScreen( {MUI::Math::lerp(time, 0, _controller->getTimeControl()->getTotalTime(), 0, clippingView->getTracksWidth()), 0}).x ;
		}
	}
	
	ofLogError("TracksPanel::timeToScreenPosition") << "nullptr. returning 0";

	return 0;
		
	
}

//---------------------------------------------------------------------
uint64_t  TracksPanel::screenPositionToTime(float x) const
{

	
	//TODO: get rid of this functions
	if(tracksView)
	{
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			
			return  MUI::Math::lerp(container->screenToLocal({x, 0}).x, 0, clippingView->getTracksWidth(), 0, _controller->getTimeControl()->getTotalTime()) ;
		}
	}
	
	ofLogError("TracksPanel::screenPositionToTime") << "nullptr. returning 0";

	return 0;

	
}

 


}
} // ofx::LineaDeTiempo
