//
//  TrackRegion.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#include "LineaDeTiempo/View/TracksClippedView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "MUI/ZoomablePanel.h"

namespace ofx {
namespace LineaDeTiempo {

TracksClippedView::TracksClippedView(const std::string& id, const ofRectangle& rect)
: MUI::ClippedView(id, rect)
{
	
	_containerShapeListener = container->shapeChanged.newListener(this, &TracksClippedView::_onContainerShapeChange);
	
	
}


//---------------------------------------------------------------------
void TracksClippedView::setScrollbars(MUI::ZoomScrollbar* zoomScrollbarH, MUI::ZoomScrollbar* zoomScrollbarV)
{
	
	_zoomScrollbarH = zoomScrollbarH;
	_zoomScrollbarV = zoomScrollbarV;
	
	if(_zoomScrollbarH){
		zoomListeners.push(_zoomScrollbarH->handleChangeEvent.newListener(this, &TracksClippedView::zoomChangedH));
		_zoomScrollbarH->setValue({0,1});
	}
	else
	{
		ofLogVerbose("TracksClippedView::setScrollbars") << "TracksClippedView::setScrollbars  _zoomScrollbarH == nullptr";
	}
	if(_zoomScrollbarV){
		zoomListeners.push(_zoomScrollbarV->handleChangeEvent.newListener(this, &TracksClippedView::zoomChangedV));
		_zoomScrollbarV->setValue({0,1});
	}
	else
	{
		ofLogVerbose("TracksClippedView::setScrollbars") << "TracksClippedView::setScrollbars  _zoomScrollbarV == nullptr";
	}
	
}


//---------------------------------------------------------------------
void TracksClippedView::zoomChangedV(ofRange&)
{
	if(updateState == CONTAINER_SHAPE_CHANGE) return;
		
	updateState = SCROLLBAR_CHANGED;
	updateVerticalLayout();
	updateState = UPDATE_STATE_NONE;
}


//---------------------------------------------------------------------
void TracksClippedView::zoomChangedH(ofRange&)
{
	if(updateState == CONTAINER_SHAPE_CHANGE) return;
	updateState = SCROLLBAR_CHANGED;
	updateTracksWidth();
	updateState = UPDATE_STATE_NONE;
}


//---------------------------------------------------------------------
void TracksClippedView::_onContainerShapeChange(DOM::ShapeChangeEventArgs& e)
{
	if(updateState == SCROLLBAR_CHANGED) return;
	updateState = CONTAINER_SHAPE_CHANGE;
	if(e.changedVertically())
	{
		_containerHeightToZoom();
	}
	if(e.changedHorizontally())
	{
		_containerWidthToZoom();
	}
	updateState = UPDATE_STATE_NONE;
}


//---------------------------------------------------------------------
//this might lead to some redundant updates.
void TracksClippedView::updateLayout()
{
	updateTracksWidth();
	updateVerticalLayout();
}


//---------------------------------------------------------------------
float TracksClippedView::getTracksWidth() const
{
	if(container) return container->getWidth();
	return 0;
}


//---------------------------------------------------------------------
void TracksClippedView::updateTracksWidth()
{
	if(container && _zoomScrollbarH){
		
		auto s = container->getShape();
		
		auto zoom = _zoomScrollbarH->getValue();
		
		s.width = getWidth() / zoom.span();
		
		
		s.x =  s.width * zoom.min * -1.f;
		
		container->setShape(s);
		
		for(auto& child: container->children())
		{
			auto c = dynamic_cast<BaseTrackView*>(child);
			
			c->updateWidth( s.width);
		}
	}
}


//---------------------------------------------------------------------
void TracksClippedView::_containerWidthToZoom()
{
	if(updateState == CONTAINER_SHAPE_CHANGE && _zoomScrollbarH && container)
	{
		ofRange zoom (0, 1);
		
		
		
			auto s = container->getShape();
			
			float span = getWidth()/s.width;
			
			zoom.min = s.x/s.width * -1.f;
			
			zoom.max = zoom.min + span;
			_zoomScrollbarH->setValue(zoom);
		
	}
}


//---------------------------------------------------------------------
void TracksClippedView::_updateTracksUnscaledHeight()
{
	_unscaledHeight = 0;
	
	for (auto c : container->children()){
		auto t = dynamic_cast<BaseTrackView*>(c);
		if (t)	_unscaledHeight += t->getUnscaledHeight();
	}
	
	_unscaledHeight = std::max(_getZoomableHeight(), _unscaledHeight);
	
}


float TracksClippedView::_getZoomableHeight()
{
	auto h = getHeight();
	if(_zoomScrollbarH){
		h -= _zoomScrollbarH->getHeight();
	}
	
	return h;
}


//---------------------------------------------------------------------
void TracksClippedView::_containerHeightToZoom()
{
	if(updateState == CONTAINER_SHAPE_CHANGE && _zoomScrollbarV && container)
	{
		
		ofRange zoom(0,1);
		
		_updateTracksUnscaledHeight();
		
		
			auto s = container->getShape();
			
			float totalHeight = s.height;
			
			zoom.min  = s.y/(totalHeight  * -1.f);
			
			float  yScale = totalHeight/_unscaledHeight;
			
			float span  = _getZoomableHeight()/ (_unscaledHeight * yScale);
			
			zoom.max = zoom.min + span;
			
		_zoomScrollbarV->setValue(zoom);
		
	}
}


//---------------------------------------------------------------------
void TracksClippedView::updateVerticalLayout()
{
	_updateTracksUnscaledHeight();
	
	if(_zoomScrollbarH)
	{
		auto zoom = _zoomScrollbarV->getValue();
		float yScale = _getZoomableHeight()/ (_unscaledHeight * zoom.span());
		
		
		float totalHeight = yScale*_unscaledHeight;
		
		float currentY = 0;
		for (auto c : container->children()){
			auto t = dynamic_cast<BaseTrackView*>(c);
			if (t){
				currentY += t->updateYScaled(currentY, yScale);
			}
		}
		
		if(container){
			auto s = container->getShape();
			s.y =  s.height * zoom.min * -1.f;
			container->setShape(s);
		}
	}
}


} } // ofx::LineaDeTiempo
