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
	if(e.changedVertically())
	{
		_headersView->setOffset(_tracksView->getClippingView()->getOffset());
		_headersView->container->setHeight(_tracksView->getContainer()->getHeight());
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
	_setHeaderHandleShape();
	_setCornerHandleViewRect();
}


void TracksPanel::_setHeaderHandleShape()
{
	if(_headerHandle)
	{
		_headerHandle->setShape({0,0, getWidth(), ConstVars::ViewTopHeaderHeight});
	}
}


void TracksPanel::_cornerHandleChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_ignoreCornerHandleChange && e.moved() && parent())
	{
		_ignoreCornerHandleChange = true;

		auto ps = parent()->getScreenPosition();
		auto c = _cornerHandle->getScreenShape().getMax();


		parent()->setSize(c.x -ps.x, c.y -ps.y);

		_ignoreCornerHandleChange = false;
	}
}


void TracksPanel::_headerHandleChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_ignoreHeaderHandleChange && e.moved() && parent())
	{
		_ignoreHeaderHandleChange = true;
		parent()->setPosition( _headerHandle->getScreenPosition());
		_headerHandle->setPosition(0, 0);
		_ignoreHeaderHandleChange = false;
	}
}


void TracksPanel::useHandles(bool b)
{
	if(bUsingHandles != b)
	{
		bUsingHandles = b;
		if(bUsingHandles){
			
			_cornerHandle = addChild<MUI::Widget>("Corner Handle", ofRectangle(getWidth() - SCROLL_BAR_SIZE, getHeight() - SCROLL_BAR_SIZE, SCROLL_BAR_SIZE, SCROLL_BAR_SIZE));
			_setCornerHandleViewRect();
			_cornerHandle->setDraggable(true);
			
			_cornerHandleListener = _cornerHandle->shapeChanged.newListener(this, &TracksPanel::_cornerHandleChanged);
			
			
			_headerHandle = addChild<MUI::Label>("ofxLineaDeTiempo");
			_headerHandle->setDraggable(true);
			updateLayout();
			_headerHandleListener = _headerHandle->shapeChanged.newListener(this, &TracksPanel::_headerHandleChanged);
		}
		else
		{
			removeChild(_headerHandle);
			removeChild(_cornerHandle);
			
			
			_headerHandleListener.unsubscribe();
			_cornerHandleListener.unsubscribe();
		}
		
	}
}


void TracksPanel::_setCornerHandleViewRect()
{
	if(_cornerHandle)
	{
		_cornerHandle->setShape({getWidth() - SCROLL_BAR_SIZE, getHeight() - SCROLL_BAR_SIZE, SCROLL_BAR_SIZE, SCROLL_BAR_SIZE});
		_cornerHandle->moveToFront();
	}
}


//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTimeRulerViewRect()
{
	float h = (bUsingHandles?(float)ConstVars::ViewTopHeaderHeight:0.0f) ;
	return ofRectangle(0, h, getWidth(), ConstVars::TimeRulerInitialHeight);
}
//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeHeadersViewRect()
{
	float h = (bUsingHandles?(float)ConstVars::ViewTopHeaderHeight:0.0f) ;
	return ofRectangle(0,  h + ConstVars::TimeRulerInitialHeight + CONTAINER_MARGIN, _trackHeaderWidth, getHeight() - (CONTAINER_MARGIN * 2) - SCROLL_BAR_SIZE - ConstVars::TimeRulerInitialHeight - h);
}

//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTracksViewRect()
{
	float h = (bUsingHandles?(float)ConstVars::ViewTopHeaderHeight:0.0f) ;
	return ofRectangle(_trackHeaderWidth, h + ConstVars::TimeRulerInitialHeight , getWidth() - _trackHeaderWidth, getHeight() - ConstVars::TimeRulerInitialHeight - h);
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

}} // ofx::LineaDeTiempo
