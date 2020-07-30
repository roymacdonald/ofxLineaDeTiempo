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
//	updateTracksWidth();
	
	
	
	
}

void TracksClippedView::setScrollbars(MUI::ZoomScrollbar* zoomScrollbarH, MUI::ZoomScrollbar* zoomScrollbarV)
{
	
	_zoomScrollbarH = zoomScrollbarH;
	_zoomScrollbarV = zoomScrollbarV;
	
	if(_zoomScrollbarH){
		zoomListeners.push(_zoomScrollbarH->handleChangeEvent.newListener(this, &TracksClippedView::zoomChangedH));
	}
	else
	{
		ofLogVerbose("TracksClippedView::setScrollbars") << "TracksClippedView::setScrollbars  _zoomScrollbarH == nullptr";
	}
	if(_zoomScrollbarV){
		zoomListeners.push(_zoomScrollbarV->handleChangeEvent.newListener(this, &TracksClippedView::zoomChangedV));
	}
	else
	{
		ofLogVerbose("TracksClippedView::setScrollbars") << "TracksClippedView::setScrollbars  _zoomScrollbarV == nullptr";
	}
	
	updateTracksWidth();
}

void TracksClippedView::zoomChangedV(ofRange&)
{
	updateVerticalLayout();
		
}


void TracksClippedView::zoomChangedH(ofRange&)
{
	updateTracksWidth();
}


//---------------------------------------------------------------------
//void TracksClippedView::setZoom(DOM::Orientation index, const ofRange& zoom)
//{
//	MUI::ClippedView::setZoom(index, zoom);
//	
//	if(index == DOM::HORIZONTAL)
//	{
//		updateTracksWidth();
//	}
//	else if( index == DOM::VERTICAL)
//	{
//		updateVerticalLayout();
//	}
//}

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
//	std::cout << "TracksClippedView::updateTracksWidth()  " << _zoom[0] << "\n";
//	_tracksWidth  = ofMap(1, 0, _zoom[0].span(), 0, getWidth(), true);
	
//	if(!ofIsFloatEqual(_tracksWidth, getWidth()/_zoom[0].span() ))
//	{
//		std::cout << "TracksClippedView::_currentWidthToZoom() map and div not equal\n";
//	}
	if(container && _zoomScrollbarH){
		
		auto s = container->getShape();
		
		auto zoom = _zoomScrollbarH->getValue();
		
		s.width = getWidth() / zoom.span();
//		s.width = _tracksWidth;
	
		s.x =  s.width * zoom.min * -1.f;
	
		container->setShape(s);
//		std::cout << container->getWidth() << " --  " << s.width << "\n";
		for(auto& child: container->children())
		{
			auto c = dynamic_cast<BaseTrackView*>(child);
			
			c->updateWidth( s.width);
			
//			std::cout << container->getWidth() - s.width << "\n";
//			std::cout << container->getWidth()  << "\n";
//			std::cout << s.width << "\n";
//			std::cout << c->getWidth() << "\n";
		}
		
//		auto a = s.width;
//		auto b = container->getShape().width;
		
//		if(!ofIsFloatEqual( a, b))
//		{
//			std::cout << "+++  " << a << "  " << b << "\n";
//		}
	}
	
//	if( !(_zoom[0] == containerWidthToZoom()))
//		std::cout << "===  " << _zoom[0] << "\n===  " << containerWidthToZoom() << "\n";
	
}


ofRange TracksClippedView::containerWidthToZoom()
{
	ofRange zoom (0, 1);

	
	if(container){
		auto s = container->getShape();
	
		float span = getWidth()/s.width;
	
		zoom.min = s.x/s.width * -1.f;
		
		zoom.max = zoom.min + span;
	
	}
	return zoom;
}


//---------------------------------------------------------------------
void TracksClippedView::_updateTracksUnscaledHeight()
{
	_unscaledHeight = 0;
	_numGroups = 0;
	
	for (auto c : container->children()){
		auto t = dynamic_cast<BaseTrackView*>(c);
		if (t)	_unscaledHeight += t->getUnscaledHeight(_numGroups);
	}
	
//	if(container->numChildren() == 1)
//	{
//		_numGroups = 0;
//	}
	
	_unscaledHeight = std::max(_getZoomableHeight(), _unscaledHeight);
	
}


float TracksClippedView::_getZoomableHeight()
{
	return getHeight() -(_numGroups * ConstVars::ViewTopHeaderHeight);
}


ofRange TracksClippedView::containerHeightToZoom()
{

	ofRange zoom(0,1);
	
	_updateTracksUnscaledHeight();
	
	
	if(container){
		
		auto s = container->getShape();
		
		float totalHeight = s.height;
		
		zoom.min  = s.y/(totalHeight  * -1.f);
		
		float  yScale = totalHeight/_unscaledHeight;

		float span  = _getZoomableHeight()/ (_unscaledHeight * yScale);
	
		zoom.max = zoom.min + span;
		
	}

	return zoom;
}
	

//---------------------------------------------------------------------
void TracksClippedView::updateVerticalLayout()
{
	//	std::cout << "TracksClippedView::updateVerticalLayout()  " << _zoom[1] << "\n";
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
			s.y =  totalHeight * zoom.min * -1.f;
			
			s.height = totalHeight;
			
			container->setShape(s);
		}
	}
}


} } // ofx::LineaDeTiempo
