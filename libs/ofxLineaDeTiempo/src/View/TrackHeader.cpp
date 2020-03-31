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


namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------
TrackHeader::TrackHeader(const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group)
: Widget(id, rect)
, _track(track)
, _group(group)
{
	if(_track)
	{
		_track->setHeader(this);
	
		auto t = dynamic_cast<TrackView*>(track);
		if(t)
		{
			setStyles(t->getRegionsStyle());
		}
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
//---------------------------------------------------------------------
void TrackHeader::onDraw() const
{
	if(_track){
	MUI::Widget::onDraw();
	
	ofDrawBitmapStringHighlight(getTrack()->getId() , 20, 20);
	}
}

} } // ofx::LineaDeTiempo

