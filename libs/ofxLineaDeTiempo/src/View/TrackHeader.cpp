//
//  TrackHeader.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "TrackHeader.h"
#include "Track.h"
#include "TracksPanel.h"

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------
TrackHeader::TrackHeader(BaseTrack* track, float width, TracksPanel* panel):
	Widget("_header", 0, 0, width, BaseTrack::initialHeight),
	_track(track),
	_panel(panel)
{
	if(_track)
	{
		_track->setHeader(this);
	
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
	if(_track && _panel){
		setShape({_track->getX(), _track->getY(), _panel->getTrackHeaderWidth(), _track->getHeight() });
	}
}


} } // ofx::LineaDeTiempo

