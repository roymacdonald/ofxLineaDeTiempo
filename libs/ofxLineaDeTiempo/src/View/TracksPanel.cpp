//
//  TracksPanel.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "TracksPanel.h"
#include "MUI/Styles.h"
#include "KeyFrames.h"

namespace ofx {
namespace LineaDeTiempo {
using namespace MUI;
TracksPanel::TracksPanel(const std::string& id, const ofRectangle& rect,  std::shared_ptr<LineaDeTiempo::TimeControl> timeControl ):
Widget(id, rect),
_timeControl(timeControl)
{
	
//	tracksView = addChild<TracksScrollPanel>(id + "_tracksView", ofRectangle(rect.x +_trackHeaderWidth,rect.y, rect.width  - _trackHeaderWidth, rect.height ));
	tracksView = addChild<TracksScrollPanel>(id + "_tracksView", _makeTracksViewRect());
	
	tracksView->setForceShowScrollbars(true);
	tracksView->setMoveToFrontOnCapture(false);
//	headersView = addChild<ClippedView_<Widget>>(id + "headersView", ofRectangle(rect.x, rect.y, _trackHeaderWidth, rect.height));
	headersView = addChild<ClippedView>(id + "headersView", _makeHeadersViewRect());
	
	_tracksContainerListeners.push(tracksView->getContainer()->move.newListener(this, &TracksPanel::_tracksMoved));
	_tracksContainerListeners.push(tracksView->getContainer()->resize.newListener(this, &TracksPanel::_tracksResized));

	_playhead = addChild<Playhead>(this, _timeControl);
	setMoveToFrontOnCapture(false);
//	tracksView->setScrollV({0,1});
//	tracksView->setScrollH({0,1});
}

//---------------------------------------------------------------------
void TracksPanel::_tracksMoved(DOM::MoveEventArgs& e)
{
	_updateHeadersFromTracks();
	_playhead->updatePosition();
}
//---------------------------------------------------------------------
void TracksPanel::_tracksResized(DOM::ResizeEventArgs& e)
{
	_updateHeadersFromTracks();
}
//---------------------------------------------------------------------
void TracksPanel::_updateHeadersFromTracks()
{
	
	headersView->setOffset({0, tracksView->getClippingView()->getOffset().y });
	
	
}
//---------------------------------------------------------------------
TrackAndHeader* TracksPanel::addKeyframesTrack(const std::string& name)
{
	return addTrack<KeyFrames>(name, true);
	
}
//---------------------------------------------------------------------
//TrackAndHeader* TracksPanel::addTrack()
//{
//	return addTrack("Track " + ofToString(getNumTracks() + 1));
//}
//---------------------------------------------------------------------
template<typename RegionType>
TrackAndHeader* TracksPanel::addTrack(const std::string& name, bool bCreateFullTrackRegion)
{
	auto c = tracksView->getContainer();
	auto hc = headersView->container;
	if(c && hc){
		auto style = make_shared<Styles>();
		ofColor color;
		color.setHsb(ofRandom(255), ofRandom(150, 255), ofRandom(255));
		
		style->setColor(color, Styles::ROLE_BACKGROUND);
		auto t = c->addChild<Track_<RegionType>>(name, _timeControl);
		auto h = hc->addChild<TrackHeader>(t, _trackHeaderWidth, this);
		
		t->setColor(color);
//		t->setStyles(style);
		h->setStyles(style);
		if(bCreateFullTrackRegion) t->addRegion({0, _timeControl->getTotalTime()});
		
		_trackCollection.push_back( std::move(std::make_unique<TrackAndHeader>(h, t)));
		
		
		tracksView->updateLayout();
		tracksView->updateContainerLayout();
		
		return _trackCollection.back().get();
	}
	ofLogError("TracksPanel::addTrack") << "can not add track because container is nullptr";
	return nullptr;
}
//---------------------------------------------------------------------
TrackAndHeader* TracksPanel::getTrackByIndex(size_t index)
{
	if(index < _trackCollection.size()){
		return _trackCollection[index].get();
	}
	return nullptr;
}
void TracksPanel::onDraw() const
{
	Widget::onDraw();
	
	
	
}
//---------------------------------------------------------------------
//TrackAndHeader* TracksPanel::getTrackByName(const std::string& name)
//{
//	if(container){
//	return dynamic_cast<TrackAndHeader*>(container->findFirstChildById(name));
//	}
//	ofLogError("TracksPanel::getTrackByName") << "can not add track because container is nullptr";
//	return nullptr;
//}
//---------------------------------------------------------------------
bool TracksPanel::removeTrack(TrackAndHeader* track)
{
	if(track == nullptr) return false;
	
	auto c = tracksView->getContainer();
	auto hc = headersView->container;
	if(c && hc){
		
		auto tr = c->removeChild(track->track);
		auto h = hc->removeChild(track->header);
		

		ofRemove(_trackCollection, [&](std::unique_ptr<TrackAndHeader>& t){
			return (track->header == t->header && track->track == t->track);
		});
		return true;
	}
	return false;
}
//---------------------------------------------------------------------
bool TracksPanel::removeTrackByIndex(size_t index)
{
	if(index < _trackCollection.size()){
		return removeTrack(_trackCollection[index].get());
	}
}
////---------------------------------------------------------------------
//bool TracksPanel::removeTrackByName(const std::string& name)
//{
//	auto t = getTrackByName(name);
//	return removeTrack(t);
//}
//---------------------------------------------------------------------
size_t TracksPanel::getNumTracks()
{
	return _trackCollection.size();
}
//---------------------------------------------------------------------
//const std::vector<TrackAndHeader*>& TracksPanel::getTracks() const
//{
//	return _trackCollection;
//}
////---------------------------------------------------------------------
//std::vector<Track*>& TracksPanel::getTracks()
//{
//	return _trackCollection;
//}

//---------------------------------------------------------------------
float TracksPanel::getTrackHeaderWidth(){
	return _trackHeaderWidth;
}
//---------------------------------------------------------------------
void TracksPanel::setTrackHeaderWidth(float w){
	if(!ofIsFloatEqual(_trackHeaderWidth, w)){
		_trackHeaderWidth = w;
		updateLayout();
	}
}
//---------------------------------------------------------------------
void TracksPanel::updateLayout()
{
	if(headersView) headersView->setShape(_makeHeadersViewRect());
	
	for(auto& t:_trackCollection){
		if(t){
			t->header->setSize(_trackHeaderWidth, t->header->getHeight());
		}
	}
	
	if(tracksView)  tracksView->setShape(_makeTracksViewRect());
	if(_playhead){
		_playhead->setSize(_playhead->getWidth(), getHeight());
		_playhead->moveToFront();
		
	}
}
//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeHeadersViewRect()
{
	
	return ofRectangle(0, CONTAINER_MARGIN, _trackHeaderWidth, getHeight() - (CONTAINER_MARGIN * 2) - SCROLL_BAR_SIZE);
}
//---------------------------------------------------------------------
ofRectangle TracksPanel::_makeTracksViewRect()
{
	return ofRectangle(_trackHeaderWidth, 0, getWidth() - _trackHeaderWidth, getHeight());
}
	
//---------------------------------------------------------------------
float TracksPanel::timeToScreenPosition(uint64_t time) const
{
	if(_timeControl && tracksView){
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			return container->localToScreen( {Math::lerp(time, 0, _timeControl->getTotalTime(), 0, clippingView->getTracksWidth()), 0}).x ;
		}
	}
	
	ofLogError("TracksPanel::timeToScreenPosition") << "nullptr. returning 0";

	return 0;
		
	
}
//---------------------------------------------------------------------
uint64_t  TracksPanel::screenPositionToTime(float x) const
{

	if(_timeControl && tracksView)
	{
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			
			return  Math::lerp(container->screenToLocal({x, 0}).x, 0, clippingView->getTracksWidth(), 0, _timeControl->getTotalTime()) ;
		}
	}
	
	ofLogError("TracksPanel::screenPositionToTime") << "nullptr. returning 0";

	return 0;

	
}
//---------------------------------------------------------------------






} } // ofx::LineaDeTiempo
