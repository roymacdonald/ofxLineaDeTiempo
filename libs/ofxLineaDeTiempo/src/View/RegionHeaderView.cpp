//
//  RegionHeaderView.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/27/20.
//


#include "LineaDeTiempo/View/RegionHeaderView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/Constants.h"

namespace ofx {
namespace LineaDeTiempo {


RegionHeaderView::RegionHeaderView(RegionView* parentRegion)
: MUI::ConstrainedGrabHandle("GrabHandle", DOM::HORIZONTAL, ofRectangle(0,0,parentRegion->getWidth(), RegionViewHeaderHeight))
, _parentRegion(parentRegion)
{
	this->constrainTo(_parentRegion->parentTrack());
	
	
	_parentListeners.push(_parentRegion->resize.newListener(this, &RegionHeaderView::_parentResized));
	

	setShapeDrawMode(MUI::ShapeDrawMode::TOP_ROUNDED_RECTANGLE);

	
}

void RegionHeaderView::_parentResized(DOM::ResizeEventArgs &)
{
	this->setSize(_parentRegion->getWidth(), RegionViewHeaderHeight);
}

void RegionHeaderView::_onDragging(const DOM::CapturedPointer& pointer)
{
	MUI::ConstrainedGrabHandle::_onDragging(pointer);
	
	float x = _parentRegion->getX() + this->getX();
	_parentRegion->setPosition(x, 0);
	
	this->setPosition(0, 0);
	
}


} } // ofx::LineaDeTiempo
