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

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------
TrackHeader::TrackHeader(const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group, bool belongsToPanel)
: Widget(id, rect)
, _track(track)
, _group(group)
, _belongsToPanel(belongsToPanel)
{
	if(_track)
	{
		_track->setHeader(this);
	
		auto t = dynamic_cast<TrackView*>(track);
		_bGroupHeader = ! bool(t);
		
		_trackListeners.push(_track->move.newListener(this, &TrackHeader::_trackMoved));
		_trackListeners.push(_track->resize.newListener(this, &TrackHeader::_trackResized));
	}
	
}
//---------------------------------------------------------------------
void TrackHeader::_trackMoved(DOM::MoveEventArgs& e)
{
	_updateFromTrack();
}
//---------------------------------------------------------------------
void TrackHeader::_trackResized(DOM::ResizeEventArgs& e)
{
	_updateFromTrack();
}
//---------------------------------------------------------------------
void TrackHeader::_updateFromTrack()
{
	if(_track && _group){
		
		float indent = 0;
		if(!_belongsToPanel){
			if(!isGroupHeader())
			{
				indent = HeaderViewIndent;
			}
		}
		setShape({ indent, _track->getY(), _group->getTracksHeaderWidth() - indent, _track->getHeight() });
	}
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
void TrackHeader::onDraw() const
{
	if(_track){
		MUI::Widget::onDraw();
		if(!_belongsToPanel){
			ofFill();
			ofSetColor(_track->getColor());
			ofDrawRectangle(0, 0, getWidth(), RegionViewHeaderHeight);
			
			ofSetColor(_track->getTextColor());
			
			
			ofDrawBitmapString( (isGroupHeader()?"group ":"track ") + getTrack()->getId() , 20, (RegionViewHeaderHeight * 0.5 - 7 + 11));
		}
	}
}

} } // ofx::LineaDeTiempo

