//
//  TracksPanel.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "LineaDeTiempo/View/TracksPanel.h"

#include "LineaDeTiempo/Controller/TimeControl.h"

#include "LineaDeTiempo/Controller/TracksPanelController.h"
#include "LineaDeTiempo/Controller/TrackController.h"

#include "LineaDeTiempo/View/TrackHeader.h"
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {

TracksPanel::TracksPanel(const std::string& id, const ofRectangle& rect, DOM::Element* parentView, TracksPanelController* controller)

: TrackGroupView(parentView, controller, nullptr, nullptr )
{
	setShape(rect);

	_isPanel = true;
	
	_tracksView = addChild<TracksView>(id + "_tracksView", _makeTracksViewRect());
	_tracksView->setForceShowScrollbars(true);
	_tracksContainer = _tracksView->getContainer();


	_tracksView->getClippingView()->setScrollbars(_tracksView->getScrollbarH(), _tracksView->getScrollbarV());
	
	
	
	
	_headersView = addChild<HeadersView>(id + "headersView", _makeHeadersViewRect(), nullptr, true);
	setHeader(_headersView->container);
	_groupHeader = _headersView->container;
	
	

	int followType = MUI::FOLLOW_Y | MUI::FOLLOW_HEIGHT;
	int followMode = MUI::FOLLOW_SCREEN;
	_follower = std::make_unique<MUI::Follower>(_tracksContainer);
	_follower->mutuallyFollow(_header->getFollower(), followType, followMode);
	
	
	
	
	_tracksViewListener = _tracksContainer->shapeChanged.newListener(this, &TracksPanel::_tracksViewShapeChanged);
	
	
	_totalTimeChangedListener =  controller->getTimeControl()->totalTimeChangedEvent.newListener(this, &TracksPanel::_totalTimeChanged);
	
	
	
	

	_timeRuler = addChild<TimeRuler>(this, controller->getTimeControl(), _makeTimeRulerViewRect(), _tracksView->getScrollbarH());
	_timeRuler->moveToFront();
	_setTracksHeaderWidth(getTracksHeaderWidth());
	
	
	updateLayout();
	
	
}

void TracksPanel::_totalTimeChanged()
{
	///this is ugly. It should go elsewhere.
	auto t = getTracksView();
	if(t)
	{
		t->getClippingView()->updateLayout();
	}
}

void TracksPanel::setTracksHeaderWidth(float w)
{
	_setTracksHeaderWidth(w);
	updateLayout();
}


void TracksPanel::_tracksViewShapeChanged(DOM::ShapeChangeEventArgs& e)
{
//	if(e.changedVertically())
//	{
//		auto o = _tracksView->getClippingView()->getOffset();
//		o.x =0;
//		_headersView->setOffset(o);
//		_headersView->container->setHeight(_tracksView->getContainer()->getHeight());
//	}
	
}

void TracksPanel::_viewShapeChanged(DOM::ShapeChangeEventArgs& e)
{

//	if(e.resized()){
		setSize(e.shape.width, e.shape.height);
		updateLayout();
	if(_tracksView && _tracksView->getClippingView())
		_tracksView->getClippingView()->updateLayout();
//	}
}

void TracksPanel::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
//	if(e.resized()){
		updateLayout();
	if(_tracksView && _tracksView->getClippingView())
		_tracksView->getClippingView()->updateLayout();
//	}
}
//---------------------------------------------------------------------
void TracksPanel::onUpdate()
{
	if(_bLayoutNeedsUpdate)
	{
		updateLayout();
		_bLayoutNeedsUpdate = false;
	}
}
//---------------------------------------------------------------------
void TracksPanel::onDraw() const
{
		
	ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
	
	ofFill();
	ofSetColor(ConstVars::PanelBackgroundColor.get());
	ofDrawRectangle(0,0, getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(ConstVars::TrackEdgeColor.get());
	ofDrawRectangle(0,0, getWidth(), getHeight());
	
}

//---------------------------------------------------------------------
void TracksPanel::updateLayout()
{
	if(_headersView)
	{
		_headersView->setShape(_makeHeadersViewRect());
		_headersView->updateLayout();
	}
	if(_tracksView)
	{
		_tracksView->setShape(_makeTracksViewRect());
		_tracksView->updateLayout();
	}
	if(_timeRuler){
		_timeRuler->setShape(_makeTimeRulerViewRect());
		_timeRuler->updateLayout();
	}
}


//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTimeRulerViewRect()
{
	return ofRectangle(0, 0, getWidth(), ConstVars::TimeRulerInitialHeight);
}
//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeHeadersViewRect()
{

	return ofRectangle(0,  ConstVars::TimeRulerInitialHeight + MUI::ConstVars::getContainerMargin(), _trackHeaderWidth, getHeight() - (MUI::ConstVars::getContainerMargin() * 2) - MUI::ConstVars::getScrollBarSize() - ConstVars::TimeRulerInitialHeight );
}

//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTracksViewRect()
{
	return ofRectangle(_trackHeaderWidth,  ConstVars::TimeRulerInitialHeight , getWidth() - _trackHeaderWidth, getHeight() - ConstVars::TimeRulerInitialHeight );
}


TracksPanelController* TracksPanel::getController()
{
	return _controller;
}


const TracksPanelController* TracksPanel::getController() const
{
	return _controller;
}


TracksPanel::TracksView* TracksPanel::getTracksView()
{
	return _tracksView;
}


const TracksPanel::TracksView* TracksPanel::getTracksView() const
{
	return _tracksView;
}


ofx::MUI::ClippedView_<TrackHeaderGroup> * TracksPanel::getHeadersView()
{
	return _headersView;
}
const ofx::MUI::ClippedView_<TrackHeaderGroup> * TracksPanel::getHeadersView() const
{
	return _headersView;
}


void TracksPanel::onChildrensChange()
{
	if(_tracksView)
	{
		_tracksView->getClippingView()->updateLayout();
	}
}

bool TracksPanel::setVerticalScrollZoom(const ofRange& val )
{
    return setScrollZoom(val, DOM::HORIZONTAL);
}

bool TracksPanel::setHorizontalScrollZoom(const ofRange& val )
{
    return setScrollZoom(val, DOM::VERTICAL);
}

ofRange TracksPanel::getVerticalScrollZoom()
{
    return getScrollZoom(DOM::VERTICAL);
}

ofRange TracksPanel::getHorizontalScrollZoom()
{
    return getScrollZoom(DOM::HORIZONTAL);
}

bool TracksPanel::setScrollZoom(const ofRange& val, DOM::Orientation orientation )
{
    if(_tracksView)
    {
        MUI::ZoomScrollbar * scroll = nullptr;
        if(orientation == DOM::HORIZONTAL){
            scroll = _tracksView->getScrollbarH();
        }else{
            scroll = _tracksView->getScrollbarV();
        }
        
        if(scroll){
            return scroll->setValue(val);
        }
    }
    
    ofLogError("TracksPanel::setScrollZoom") << "there is no view. cant set scroll/zoom values.";
    return false;
}

ofRange  TracksPanel::getScrollZoom(DOM::Orientation orientation)
{
    if(_tracksView)
    {
        MUI::ZoomScrollbar * scroll = nullptr;
        if(orientation == DOM::HORIZONTAL){
            scroll = _tracksView->getScrollbarH();
        }else{
            scroll = _tracksView->getScrollbarV();
        }
        
        if(scroll){
            return scroll->getValue();
        }
    }
    
    ofLogError("TracksPanel::getScrollZoom") << "there is no view. cant set scroll/zoom values.";
    
    return ofRange();

}



}} // ofx::LineaDeTiempo
