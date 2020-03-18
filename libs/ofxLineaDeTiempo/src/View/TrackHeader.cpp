//
//  TrackHeader.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "LineaDeTiempo/View/TrackHeader.h"
#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/TrackGroupView.h"

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------
TrackHeader::TrackHeader(BaseTrackView* track, float width, TrackGroupView* group):
	Widget("_header", 0, 0, width, BaseTrackView::initialHeight),
	_track(track),
	_group(group)
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
	if(_track && _group){
		setShape({_track->getX(), _track->getY(), _group->getTrackHeaderWidth(), _track->getHeight() });
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


} } // ofx::LineaDeTiempo

