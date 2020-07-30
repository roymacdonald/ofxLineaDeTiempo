//
//  BaseTrack.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#include "LineaDeTiempo/View/TrackView.h"
#include "MUI/Utils.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/View/TracksPanel.h"

namespace ofx {
namespace LineaDeTiempo {



TrackView::TrackView(DOM::Element* parentView, TrackController* controller,TimeRuler * timeRuler )
: BaseTrackView(controller->getId(), parentView, timeRuler)
//, _unscaledHeight(ConstVars::TrackInitialHeight)
, _controller(controller)

{
	_regionsHeaderStyle = make_shared<MUI::Styles>("regionsHeaderStyle");
	colorListener = BaseTrackView::colorChangeEvent.newListener(this, &TrackView::colorChanged);
	_minHeight = ConstVars::ViewTopHeaderHeight;
}

shared_ptr<MUI::Styles> TrackView::getRegionsHeaderStyle()
{
	return _regionsHeaderStyle;

}


void TrackView::colorChanged(ofColor& color)
{
	_regionsHeaderStyle->setColor(color , MUI::Styles::ROLE_BACKGROUND);
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
//	std::cout << "TrackView::timeToLocalPosition\n";
	auto ruler = getTimeRuler();
	if(ruler)
	{
		return screenToLocal({ruler->timeToScreenPosition(t),0}).x ;
	}
//	return MUI::Math::lerp(t, 0, _controller->getTimeControl()->getTotalTime(), 0, getWidth());
	return 0;
}

uint64_t TrackView::localPositionToTime(float x) const
{
//	std::cout << "TrackView::localPositionToTime\n";
	
	auto ruler = getTimeRuler();
	if(ruler)
	{
		return ruler->screenPositionToTime(localToScreenX(x));
//		return screenToLocal({ruler->timeToScreenPosition(t),0}).x ;
	}
//	return MUI::Math::lerp(x, 0, getWidth(), 0, _controller->getTimeControl()->getTotalTime());
	return 0;
}

float TrackView::getHeightFactor() const
{
	return _heightFactor;
}

void TrackView::setHeightFactor(float factor)
{

	_heightFactor = factor;
//	_unscaledHeight = ConstVars::TrackInitialHeight * _heightFactor;
	auto p = getParentPanel();
	if(p && p->getTracksView())
	{
//		p->getTracksView()->updateVerticalScrollFromContainersHeight();
	}
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
		auto removed = removeChild(region);
		if(removed.get() == nullptr)
		{
			ofLogError("TrackView::removeRegion") << "failed. removeChild returned a  nullptr";
			return false;
		}
		
		ofRemove( _regions, [&](RegionView* r){ return r == removed.get();});
		
		
		return true;
		
	}
	return false;
}

float TrackView::getUnscaledHeight(size_t & numGroups)
{
	return std::max(ConstVars::TrackInitialHeight * _heightFactor, _minHeight );
}
//
//void TrackView::setScaledHeight(float h)
//{
//	std::cout << "TrackView::setScaledHeight " << h << "\n";
//	_minHeight = h;
//	setHeightFactor( h / (ConstVars::TrackInitialHeight *  _verticalScale));
//}


float TrackView::updateYScaled(float y, float yScale)
{
	_verticalScale = yScale;
	auto h = ConstVars::TrackInitialHeight * _heightFactor * yScale;
	setShape({0, y, getWidth(), h});
	return h;
}


void TrackView::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	if(e.widthChanged())
	{
		_updateRegionsWidth();
	}
	if(e.heightChanged())
	{
		_updateRegionsHeight();
	}
}


void TrackView::_updateRegionsHeight()
{
	for(auto r: _regions)
	{
		if(r)
		{
			r->setHeight(getHeight());
			r->updateLayout();
		}
	}
}

void TrackView::_updateRegionsWidth()
{
	for(auto r: _regions)
	{
		if(r)
			r->updateRectFromTimeRange();
	}
}


void TrackView::updateWidth(const float& w)
{
	BaseTrackView::updateWidth(w);
	_updateRegionsWidth();
}


const TrackController * TrackView::getController() const
{
	return _controller;
}


TrackController * TrackView::getController()
{
	return _controller;
}


void TrackView::setMinHeight(float minHeight)
{
	_minHeight = minHeight;
	setHeightFactor( minHeight / (ConstVars::TrackInitialHeight *  _verticalScale));
	setHeight( minHeight);
}


float TrackView::getMinHeight()
{
	return _minHeight;
}



}} //ofx::LineaDeTiempo
