//
//  TrackHeader.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "LineaDeTiempo/View/TrackHeader.h"
#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "LineaDeTiempo/Utils/FontUtils.h"

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------
TrackHeader::TrackHeader(const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group, bool belongsToPanel)
: DOM::Element(id, rect)
, _track(track)
, _group(group)
, _belongsToPanel(belongsToPanel)
{
	_follower = make_unique<MUI::Follower>(this);
	if(_track)
	{
//		std::cout << "TrackHeader::\n";
		
		
		_track->setHeader(this);
		auto t = dynamic_cast<TrackView*>(track);
		_bGroupHeader = ! bool(t);
		
		if(!_bGroupHeader)
		{
		
			_edgeHandle = addChild<MUI::EdgeHandle>("TrackHeaderResizeHandle", DOM::RECT_BOTTOM, this);

//			_edgeHandleListener = _edgeHandle->shapeChanged.newListener(this, &TrackHeader::_onEdgeHandleChange);
		}
		
		
//		_trackListener = _track->shapeChanged.newListener(this, &TrackHeader::_trackShapeChanged);
//		_updateShape();
		
		
		float indent = (!_belongsToPanel && !isGroupHeader())?ConstVars::HeaderViewIndent.get():0.f;
		
		setShape({ indent, _track->getY(), _group->getTracksHeaderWidth() - indent, _track->getHeight() });
		
	}
}

//
//void TrackHeader::_trackShapeChanged(DOM::ShapeChangeEventArgs& e)
//{
//	if(!bIgnoreTrackHeightChange)
//	{
//		if(e.changedVertically())
//		{
//			_updateShape();
//		}
//	}
//}


float TrackHeader::_getMinHeight()
{
	return ConstVars::ViewTopHeaderHeight;
}


//void TrackHeader::_onEdgeHandleChange(DOM::ShapeChangeEventArgs& e)
//{
////	if(_edgeHandle && !_edgeHandle->isFollowingTarget() && _edgeHandle->isDragging() && e.yChanged() && _track && !ofIsFloatEqual(getHeight(), _track->getHeight()))
////	{
////		_updateTrackHeight();
////	}
//}


//void TrackHeader::_updateTrackHeight()
//{
//	auto t = dynamic_cast<TrackView*>(_track);
//	if(t)
//	{
//		bIgnoreTrackHeightChange = true;
//		t->setTrackHeight(std::max(getHeight() , _getMinHeight()));
//		_updateEdgeHandle();
//		bIgnoreTrackHeightChange = false;
//	}
//}
//
//
//void TrackHeader::_updateShape()
//{
//	if(_track && _group){
//
//		float indent = 0;
//		if(!_belongsToPanel){
//			if(!isGroupHeader())
//			{
//				indent = ConstVars::HeaderViewIndent;
//			}
//		}
//		setShape({ indent, _track->getY(), _group->getTracksHeaderWidth() - indent, _track->getHeight() });
//	}
//	_updateEdgeHandle();
//}


//void TrackHeader::_updateEdgeHandle()
//{
//	if(_edgeHandle)
//	{
//		_edgeHandle->setTargetMinSize(_getMinHeight());
//		_edgeHandle->moveToFront();
//	}
//}


//---------------------------------------------------------------------
BaseTrackView* TrackHeader::getTrack()
{
	return _track;
}
//---------------------------------------------------------------------
const BaseTrackView* TrackHeader::getTrack() const
{
	return _track;
}
//---------------------------------------------------------------------
bool TrackHeader::isGroupHeader() const
{
	return  _bGroupHeader;
}

//---------------------------------------------------------------------
TrackGroupView* TrackHeader::getTrackGroup()
{
	return _group;
}

//---------------------------------------------------------------------
const TrackGroupView* TrackHeader::getTrackGroup() const
{
	return _group;
}

//---------------------------------------------------------------------
void TrackHeader::onDraw() const
{
	if(_track){

		if(!_belongsToPanel){
			
			ofFill();

			ofSetColor(ConstVars::TrackBackgroundColor);
			ofDrawRectangle(0, 0, getWidth(), getHeight());
			
			ofSetColor(_track->getColor());
			ofDrawRectangle(0, 0, getWidth(), ConstVars::ViewTopHeaderHeight);
			
			ofNoFill();
			ofSetColor(ConstVars::TrackEdgeColor);
			ofDrawRectangle(0, 0, getWidth(), getHeight());
			
			
			ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
			
			auto & font = getStyles()->getFont(MUI::SMALL);

			font.drawString(getTrack()->getId() , 20, getTextVCenteredPos({0,0,0, ConstVars::ViewTopHeaderHeight} , font));
			
		}
	}
}

MUI::Follower*  TrackHeader::getFollower()
{
	return _follower.get();
}

} } // ofx::LineaDeTiempo

