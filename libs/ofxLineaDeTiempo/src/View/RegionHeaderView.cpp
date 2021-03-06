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
#include "LineaDeTiempo/Utils/FontUtils.h"
namespace ofx {
namespace LineaDeTiempo {


RegionHeaderView::RegionHeaderView(RegionView* parentRegion)
	: MUI::ConstrainedGrabHandle("GrabHandle", DOM::HORIZONTAL, { 0,0,parentRegion->getWidth(), ConstVars::ViewTopHeaderHeight })
, _parentRegion(parentRegion)
{
	this->constrainTo(_parentRegion->parentTrack());
	
	
	_parentListener = _parentRegion->shapeChanged.newListener(this, &RegionHeaderView::_parentShapeChanged);
	

	setShapeDrawMode(MUI::ShapeDrawMode::TOP_ROUNDED_RECTANGLE);

	
}
void RegionHeaderView::_parentShapeChanged(DOM::ShapeChangeEventArgs & e)
{
	
	if(_parentRegion && e.widthChanged()){
		this->setSize(_parentRegion->getWidth(), ConstVars::ViewTopHeaderHeight);
	}
}

void RegionHeaderView::_onDragging(const DOM::CapturedPointer& pointer)
{
	MUI::ConstrainedGrabHandle::_onDragging(pointer);
	
//	float x = _parentRegion->getX() + this->getX();
	_parentRegion->moveRegionX(this->getX());
//	_parentRegion->setPosition(x, 0);
	
	this->setPosition(0, 0);
	
}

void RegionHeaderView::onDraw() const
{
	
    MUI::Widget::onDraw();
	if(_parentRegion && _parentRegion->parentTrack())
	{
		
		ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
		auto & font = getStyles()->getFont(MUI::SMALL);
		
		font.drawString(_parentRegion->getId(), 20, getTextVCenteredPos({0,0,0, ConstVars::ViewTopHeaderHeight} , font));
		
		
//		
	}
}

} } // ofx::LineaDeTiempo
