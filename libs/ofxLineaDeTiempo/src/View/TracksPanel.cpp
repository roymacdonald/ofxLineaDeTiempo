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

: TrackGroupView(parentView, controller, nullptr )
{
	setShape(rect);

	_isPanel = true;
	
	_tracksView = addChild<TracksView>(id + "_tracksView", _makeTracksViewRect());
	_tracksView->setForceShowScrollbars(true);
	_tracksContainer = _tracksView->getContainer();
	
	
	_headersView = addChild<HeadersView>(id + "headersView", _makeHeadersViewRect(), nullptr, nullptr, true);
	_header = _headersView->container;


	_tracksViewListener = _tracksContainer->shapeChanged.newListener(this, &TracksPanel::_tracksViewShapeChanged);
	
	

	_timeRuler = addChild<TimeRuler>(this, controller->getTimeControl(), _makeTimeRulerViewRect());
	_timeRuler->moveToFront();
	_setTracksHeaderWidth(getTracksHeaderWidth());
	updateLayout();
	
	
}



void TracksPanel::setTracksHeaderWidth(float w)
{
	_setTracksHeaderWidth(w);
	updateLayout();
}


void TracksPanel::_tracksViewShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(e.changedVertically())
	{
		auto o = _tracksView->getClippingView()->getOffset();
		o.x =0;
		_headersView->setOffset(o);
		_headersView->container->setHeight(_tracksView->getContainer()->getHeight());
	}
	
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
	ofSetColor(ConstVars::PanelBackgroundColor);
	ofDrawRectangle(0,0, getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(ConstVars::TrackEdgeColor);
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

	return ofRectangle(0,  ConstVars::TimeRulerInitialHeight + CONTAINER_MARGIN, _trackHeaderWidth, getHeight() - (CONTAINER_MARGIN * 2) - SCROLL_BAR_SIZE - ConstVars::TimeRulerInitialHeight );
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


ofx::MUI::ClippedView_<TrackHeader> * TracksPanel::getHeadersView()
{
	return _headersView;
}
const ofx::MUI::ClippedView_<TrackHeader> * TracksPanel::getHeadersView() const
{
	return _headersView;
}

}} // ofx::LineaDeTiempo
