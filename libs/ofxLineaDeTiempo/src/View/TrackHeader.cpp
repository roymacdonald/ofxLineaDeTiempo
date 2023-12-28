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
	_follower = std::make_unique<MUI::Follower>(this);
	if(_track)
	{
		
		_track->setHeader(this);
		auto t = dynamic_cast<TrackView*>(track);
		_bGroupHeader = ! bool(t);
		
		if(!_bGroupHeader)
		{
			_edgeHandle = addChild<MUI::EdgeHandle>("TrackHeaderResizeHandle", DOM::RECT_BOTTOM, this);
		}
				
		float indent = (!_belongsToPanel && !isGroupHeader())?ConstVars::HeaderViewIndent.get():0.f;
		
		setShape({ indent, _track->getY(), _group->getTracksHeaderWidth() - indent, _track->getHeight() });
		
	}
}

float TrackHeader::_getMinHeight()
{
	return ConstVars::ViewTopHeaderHeight;
}


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

			ofSetColor(ConstVars::TrackBackgroundColor.get());
			ofDrawRectangle(0, 0, getWidth(), getHeight());
			
			ofSetColor(_track->getColor());
			ofDrawRectangle(0, 0, getWidth(), ConstVars::ViewTopHeaderHeight);
			
			ofNoFill();
			ofSetColor(ConstVars::TrackEdgeColor.get());
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

