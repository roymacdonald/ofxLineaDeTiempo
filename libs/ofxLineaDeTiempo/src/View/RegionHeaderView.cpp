//
//  RegionHeaderView.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/27/20.
//


#include "LineaDeTiempo/View/RegionHeaderView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"

namespace ofx {
namespace LineaDeTiempo {


RegionHeaderView::RegionHeaderView(RegionView* parentRegion)
: MUI::ConstrainedGrabHandle("GrabHandle", DOM::HORIZONTAL, ofRectangle(0,0,parentRegion->getWidth(), ConstVars::ViewTopHeaderHeight))
, _parentRegion(parentRegion)
{
	this->constrainTo(_parentRegion->parentTrack());
	
	
	_parentListener = _parentRegion->shapeChanged.newListener(this, &RegionHeaderView::_parentShapeChanged);
	

	setShapeDrawMode(MUI::ShapeDrawMode::TOP_ROUNDED_RECTANGLE);

	
}
void RegionHeaderView::_parentShapeChanged(DOM::ShapeChangeEventArgs & e)
//void RegionHeaderView::_parentResized(DOM::ResizeEventArgs &)
{
	if(e.widthChanged()){
	this->setSize(_parentRegion->getWidth(), ConstVars::ViewTopHeaderHeight);
	}
}

void RegionHeaderView::_onDragging(const DOM::CapturedPointer& pointer)
{
	MUI::ConstrainedGrabHandle::_onDragging(pointer);
	
	float x = _parentRegion->getX() + this->getX();
	_parentRegion->setPosition(x, 0);
	
	this->setPosition(0, 0);
	
}

void RegionHeaderView::onDraw() const
{
	
    MUI::Widget::onDraw();
	if(_parentRegion && _parentRegion->parentTrack())
	{
		ofSetColor(_parentRegion->parentTrack()->getTextColor());
		ofDrawBitmapString(_parentRegion->getId() , 20, (ConstVars::ViewTopHeaderHeight * 0.5 - 7 + 11));
	}
}

} } // ofx::LineaDeTiempo
