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

TracksPanel::TracksPanel(const std::string& id, DOM::Element* parentView, const ofRectangle& rect, TracksPanelController* controller)

: TrackGroupView(parentView, controller, nullptr )
{
	setShape(rect);

	_isPanel = true;
	
	_tracksView = addChild<TracksView>(id + "_tracksView", _makeTracksViewRect());
	_tracksView->setForceShowScrollbars(true);
	_tracksView->setMoveToFrontOnCapture(false);
	_tracksContainer = _tracksView->getContainer();
	
	
	_headersView = addChild<HeadersView>(id + "headersView", _makeHeadersViewRect(), nullptr, nullptr, true);
	_header = _headersView->container;


	_viewListener =  parentView->shapeChanged.newListener(this, &TracksPanel::_viewShapeChanged);

	_tracksViewListener = _tracksContainer->shapeChanged.newListener(this, &TracksPanel::_tracksViewShapeChanged);
	

	_regionsStyle = make_shared<ofx::MUI::Styles>();
	_regionsStyle->setColor(RegionBackgroundColor,ofx::MUI::Styles::ROLE_BACKGROUND);
	

	_timeRuler = addChild<TimeRuler>(this, controller->getTimeControl(), _makeTimeRulerViewRect());
	_timeRuler->moveToFront();
	
	updateLayout();
	
	
}

void TracksPanel::_setup()
{
	if(_tracksView)
	{
		_tracksView->setScrollH({0,1});
		_tracksView->setScrollV({0,1});
		_setTracksHeaderWidth(getTracksHeaderWidth());
		updateLayout();
	}
}

void TracksPanel::setTracksHeaderWidth(float w)
{
	
	_setTracksHeaderWidth(w);
	updateLayout();
}
void TracksPanel::_tracksViewShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(e.yChanged())
	{
		_headersView->setOffset(_tracksView->getClippingView()->getOffset());
	}
	
}

void TracksPanel::_viewShapeChanged(DOM::ShapeChangeEventArgs& e)
{

	if(e.resized()){
		setSize(e.shape.width, e.shape.height);
		updateLayout();
	}
}
//---------------------------------------------------------------------
void TracksPanel::onDraw() const
{
	Element::onDraw();
	ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
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
	return ofRectangle(0, 0, getWidth(), TimeRulerInitialHeight);
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


TracksPanelController* TracksPanel::getController()
{
	return _controller;
}
const TracksPanelController* TracksPanel::getController() const
{
	return _controller;
}


ofx::MUI::TracksScrollPanel* TracksPanel::getTracksView()
{
	return _tracksView;
}
const ofx::MUI::TracksScrollPanel* TracksPanel::getTracksView() const
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

shared_ptr<MUI::Styles> TracksPanel::getRegionsStyle()
{
	return _regionsStyle;
}


const shared_ptr<MUI::Styles> TracksPanel::getRegionsStyle() const
{
	return _regionsStyle;
}




}} // ofx::LineaDeTiempo
