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
, _controller(controller)

{
	_regionsHeaderStyle = make_shared<MUI::Styles>("regionsHeaderStyle");
	colorListener = BaseTrackView::colorChangeEvent.newListener(this, &TrackView::colorChanged);
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
	auto ruler = getTimeRuler();
	if(ruler)
	{
		return screenToLocal({ruler->timeToScreenPosition(t),0}).x ;
	}
	return 0;
}


uint64_t TrackView::localPositionToTime(float x) const
{
	auto ruler = getTimeRuler();
	if(ruler)
	{
		return ruler->screenPositionToTime(localToScreenX(x));
	}
	return 0;
}


float TrackView::getHeightFactor() const
{
	return _heightFactor;
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

float TrackView::getUnscaledHeight()
{
	return ConstVars::TrackInitialHeight * _heightFactor;
}


float TrackView::updateYScaled(float y, float yScale)
{
    auto h = getUnscaledHeight() * yScale;
    if(h >=  (MUI::ConstVars::isHiDpiEnabled() ? 36: 18)){
        _verticalScale = yScale;
        _bIgnoreHeightChange = true;
        setShape({0, y, getWidth(), h});
        _bIgnoreHeightChange = false;
        return h;
    }
    return 0;
}


void TrackView::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	if(e.widthChanged())
	{
		_updateRegionsWidth();
	}
	if(e.heightChanged())
	{
		if(!_bIgnoreHeightChange )
		{
			_heightFactor =  e.shape.height / (ConstVars::TrackInitialHeight *  _verticalScale);
		}
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


}} //ofx::LineaDeTiempo
