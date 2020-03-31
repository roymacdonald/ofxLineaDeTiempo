//
//  BaseTrack.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#include "LineaDeTiempo/View/TrackView.h"
#include "MUI/Utils.h"
#include "LineaDeTiempo/Controller/TrackController.h"

namespace ofx {
namespace LineaDeTiempo {



TrackView::TrackView(DOM::Element* parentView, TrackController* controller)
: BaseTrackView(controller->getId(), parentView)
, _unscaledHeight(TrackInitialHeight)
, _controller(controller)
{
	_regionsStyle = make_shared<MUI::Styles>();
}

shared_ptr<MUI::Styles> TrackView::getRegionsStyle()
{
	return _regionsStyle;
}

void TrackView::setColor(const ofColor& color)
{
	BaseTrackView::setColor(color);
	_regionsStyle->setColor(_color, MUI::Styles::ROLE_BACKGROUND);
}

ofRange64u  TrackView::rectToTimeRange(const ofRectangle& rect) const
{
	ofRange64u t;
	t.min = localPositionToTime(rect.getMinX());
	t.max = localPositionToTime(rect.getMaxX());
	return t;
}

ofRectangle TrackView::timeRangeToRect(const ofRange64u& t) const
{
	ofRectangle r (timeToLocalPosition(t.min), 0,timeToLocalPosition(t.max), getHeight());
	r.width -= r.x;
	return r;
}

float TrackView::timeToLocalPosition(const uint64_t& t) const
{
	return MUI::Math::lerp(t, 0, _controller->getTimeControl()->getTotalTime(), 0, getWidth());
}

uint64_t TrackView::localPositionToTime(float x) const
{
	return MUI::Math::lerp(x, 0, getWidth(), 0, _controller->getTimeControl()->getTotalTime());
}

float TrackView::timeToScreenPosition(uint64_t time) const
{
	return DOM::Element::localToScreen({timeToLocalPosition(time),0}).x;
}

uint64_t  TrackView::screenPositionToTime(float x) const
{
	return localPositionToTime(DOM::Element::screenToLocal({x,0}).x);
}

float TrackView::getHeightFactor() const
{
	return _heightFactor;
}

void TrackView::setHeightFactor(float factor)
{
	_heightFactor = factor;
	_unscaledHeight = TrackInitialHeight * _heightFactor;
}

bool TrackView::removeRegion(RegionController * controller)
{
	if(controller == nullptr)
	{
		ofLogError("TrackView::removeRegion") << "failed. RegionController is nullptr";
		return false;
	}

	auto region = controller->getView();
	if(region){

		if(removeChild(region) == nullptr)
		{
			ofLogError("TrackView::removeRegion") << "failed. removeChild returned a  nullptr";
			return false;
		}
		return true;
		
	}
	return false;
}

float TrackView::getUnscaledHeight()
{
	return _unscaledHeight;
}

float TrackView::updateScaledShape(float y, float yScale, float width)
{
	auto h = TrackInitialHeight * _heightFactor * yScale;
	setShape({0, y, width, h});
	updateLayout();
	return h;
}

void TrackView::updateLayout()
{
	for(auto c: children())
	{
		if(c) c->updateLayout();
	}
}

//
//const TrackController * TrackView::getController() const
//{
//	return _controller;
//}
//TrackController * TrackView::getController()
//{
//	return _controller;
//}
//void TrackView::setController(TrackController * controller)
//{
//	_controller = controller;
//}



}} //ofx::LineaDeTiempo
