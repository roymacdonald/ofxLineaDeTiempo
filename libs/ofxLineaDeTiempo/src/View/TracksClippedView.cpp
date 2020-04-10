//
//  TrackRegion.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/18/20.
//

#include "LineaDeTiempo/View/TracksClippedView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
namespace ofx {
namespace LineaDeTiempo {

TracksClippedView::TracksClippedView(const std::string& id, const ofRectangle& rect):
MUI::ClippedView(id, rect)
{

	_zoom[0] = {0,1};
	_zoom[1] = {0,1};
	
	
	_listeners.push(shapeChanged.newListener(this, &TracksClippedView::_onResize));
	_listeners.push(container->childAdded.newListener(this, &TracksClippedView::_onTrackAdded));
	_listeners.push(container->childRemoved.newListener(this, &TracksClippedView::_onTrackRemoved));
	
	_updateTracksWidth();
}
void TracksClippedView::_onResize(DOM::ShapeChangeEventArgs& e)
{
	_updateTracksUnscaledHeight();
}

void TracksClippedView::_onTrackAdded(DOM::ElementEventArgs&)
{
	_updateTracksUnscaledHeight();
}

void TracksClippedView::_onTrackRemoved(DOM::ElementEventArgs&)
{
	_updateTracksUnscaledHeight();
}

void TracksClippedView::setZoomV(ofRange& v)
{
	setZoom(DOM::VERTICAL, v);
}

void TracksClippedView::setZoomH(ofRange& h)
{
	setZoom(DOM::HORIZONTAL, h);
}

////---------------------------------------------------------------------
//void TracksClippedView::setZoom(const std::vector<ofRange>& zooms)
//{
//	if(zooms.size() != 2){
//		ofLogError("Tracks::setZoom")<< "the passed vector's size must be 2";
//		return;
//	}
//
//	for(int i = 0; i < zooms.size(); i++){
//		_zoom[i] = zooms[i];
//		MUI::keepRangeMinSpan(_zoom[i], _minZoom[i], {0,1});
//
//	}
//
//	updateLayout();
//}

//---------------------------------------------------------------------
void TracksClippedView::setZoom(DOM::Orientation index, const ofRange& zoom)
{
	if(index == DOM::HORIZONTAL || index == DOM::VERTICAL){
		_zoom[index] = zoom;
		MUI::keepRangeMinSpan(_zoom[index], _minZoom[index], {0,1});
		if(index == DOM::HORIZONTAL)
		{
			_updateTracksWidth();
			
		}
		else
		{
			_updateVerticalLayout();
		}
	}
}

//---------------------------------------------------------------------
ofRange TracksClippedView::getZoom(DOM::Orientation orientation) const
{
	if(orientation == DOM::HORIZONTAL || orientation == DOM::VERTICAL){
		return _zoom[orientation];
	}
	return {0,1};
}

//---------------------------------------------------------------------
float TracksClippedView::getTracksWidth() const
{
	return _tracksWidth;
}


//---------------------------------------------------------------------
void TracksClippedView::_updateTracksWidth()
{
	_tracksWidth  = ofMap(1, 0, _zoom[0].span(), 0, getWidth());
	
	if(container){
		auto s = container->getShape();
		s.width = _tracksWidth;
	
		s.x =  _tracksWidth * _zoom[0].min * -1.f;
	
		container->setShape(s);
		for(auto& child: container->children())
		{
			auto c = dynamic_cast<BaseTrackView*>(child);
			
			c->updateWidth(_tracksWidth);
		}
	}
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
	
	if(container->numChildren() == 1)
	{
		_numGroups -= 1;
	}
	
	_unscaledHeight = std::max((getHeight() - (_numGroups * ConstVars::ViewTopHeaderHeight)), _unscaledHeight);
	
}

ofRange TracksClippedView::getVerticalZoomFromContainerHeight()
{
	auto cs = getChildShape();
	
	float span;
	
	if(cs.height < getHeight())
	{
		span = 1;
	}
	else
	{
		span  = (getHeight() -(_numGroups * ConstVars::ViewTopHeaderHeight))/ cs.height;
	}
	
	auto zoom = _zoom[1];
	
	zoom.max = zoom.min + span;
	
	if(zoom.max > 1.0f)
	{
		zoom.min -= zoom.max - 1.0f;
	}
	std::cout << " children height: " << cs.height << " viewHeight: " << getHeight()  << " span: " << span << "  zoom: " << zoom << "\n";
	return zoom;
	
}
//---------------------------------------------------------------------
void TracksClippedView::_updateVerticalLayout()
{

	_updateTracksUnscaledHeight();
	
	float yScale = (getHeight() -(_numGroups * ConstVars::ViewTopHeaderHeight))/ (_unscaledHeight * _zoom[1].span());
	
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
		s.y =  totalHeight * _zoom[1].min * -1.f;
		
		s.height = totalHeight;
				
		container->setShape(s);
	}
}


} } // ofx::LineaDeTiempo
