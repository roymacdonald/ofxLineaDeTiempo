//
//  TracksPanel.cpp
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#include "LineaDeTiempo/View/TracksPanel.h"
#include "MUI/Styles.h"


#include "LineaDeTiempo/Controller/TimeControl.h"
#include "LineaDeTiempo/Controller/TracksController.h"

#include "LineaDeTiempo/View/TrackHeader.h"


namespace ofx {
namespace LineaDeTiempo {
//using namespace MUI;
TracksPanel::TracksPanel(const std::string& id, const ofRectangle& rect, TracksController* controller)//,  std::shared_ptr<LineaDeTiempo::TimeControl> timeControl ):
:AbstractHasTracks<BaseTrack,false_type>()
,BaseHasController<TracksController>(controller)
,MUI::Widget(id, rect)
,BaseHasLayout()
{
	
//	tracksView = addChild<TracksScrollPanel>(id + "_tracksView", ofRectangle(rect.x +_trackHeaderWidth,rect.y, rect.width  - _trackHeaderWidth, rect.height ));
	tracksView = Widget::addChild<MUI::TracksScrollPanel>(id + "_tracksView", _makeTracksViewRect());
	
	tracksView->setForceShowScrollbars(true);
	tracksView->setMoveToFrontOnCapture(false);
//	headersView = addChild<ClippedView_<Widget>>(id + "headersView", ofRectangle(rect.x, rect.y, _trackHeaderWidth, rect.height));
	headersView = addChild<MUI::ClippedView>(id + "headersView", _makeHeadersViewRect());
	
	_tracksContainerListeners.push(tracksView->getContainer()->move.newListener(this, &TracksPanel::_tracksMoved));
	_tracksContainerListeners.push(tracksView->getContainer()->resize.newListener(this, &TracksPanel::_tracksResized));

	_playhead = addChild<Playhead>(this);//, _timeControl);
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
//Track_<KeyFrames>* TracksPanel::addKeyframesTrack(const std::string& name)
//{
//	return addTrack<Track_<KeyFrames>, KeyFrames>(name, true);
//	
//}
//---------------------------------------------------------------------
//BaseTrack* TracksPanel::addTrack()
//{
//	return addTrack("Track " + ofToString(getNumTracks() + 1));
//}
//---------------------------------------------------------------------
template< template<typename> class TrackViewType, typename RegionViewType >
TrackViewType<RegionViewType>* TracksPanel::addTrack(const std::string& name, bool bCreateFullTrackRegion)
{
	static_assert(std::is_base_of<Track_<RegionViewType>, TrackViewType<RegionViewType>>::value,
				  "TrackViewType<RegionViewType> must inherit from ofx::LineaDeTiempo::Track_<RegionViewType>");
	
	
	auto c = tracksView->getContainer();
	auto hc = headersView->container;
	if(c && hc){
		
		auto t = c->addChild<TrackViewType<RegionViewType>>(name);
		auto h = hc->addChild<TrackHeader>(t, _trackHeaderWidth, this);
		
		auto style = make_shared<MUI::Styles>();
		ofColor color;
		color.setHsb(ofRandom(255), ofRandom(150, 255), ofRandom(255));
		
		style->setColor(color, MUI::Styles::ROLE_BACKGROUND);
		
		t->setColor(color);
//		t->setStyles(style);
		h->setStyles(style);
		
		if(bCreateFullTrackRegion) t->addRegion({0, getTimeControl().getTotalTime()});
		
//		_trackCollection.push_back(t);
		addElement(t);
		
		tracksView->updateLayout();
		tracksView->updateContainerLayout();
		
		return t;
	}
	ofLogError("TracksPanel::addTrack") << "can not add track because container is nullptr";
	return nullptr;
}

void TracksPanel::onDraw() const
{
	Widget::onDraw();
}
//---------------------------------------------------------------------
bool TracksPanel::removeTrack(BaseTrack* track)
{
	if(track == nullptr) return false;

	auto c = tracksView->getContainer();
	auto hc = headersView->container;
	if(c && hc){

		auto tr = c->removeChild(track);
		auto h = hc->removeChild(track->getHeader());

		BaseHasCollection<BaseTrack, false_type>::removeElement(track);
		
//		ofRemove(_trackCollection, [&](BaseTrack* t){
//			return (track->getHeader() == t->getHeader() && track == t);
//		});
		return true;
	}
	return false;
}

//---------------------------------------------------------------------
//size_t TracksPanel::getNumTracks() const
//{
//	return _trackCollection.size();
//}
////---------------------------------------------------------------------
//const std::vector<const BaseTrack*>& TracksPanel::getTracks() const
//{
//
//}
////---------------------------------------------------------------------
//std::vector<BaseTrack*>& TracksPanel::getTracks()
//{
//
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
	
	for(auto& t: getCollection()){
		if(t){
			t->getHeader()->setSize(_trackHeaderWidth, t->getHeader()->getHeight());
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
	if(tracksView){
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			return container->localToScreen( {MUI::Math::lerp(time, 0, getTimeControl().getTotalTime(), 0, clippingView->getTracksWidth()), 0}).x ;
		}
	}
	
	ofLogError("TracksPanel::timeToScreenPosition") << "nullptr. returning 0";

	return 0;
		
	
}
//---------------------------------------------------------------------
uint64_t  TracksPanel::screenPositionToTime(float x) const
{

	if(tracksView)
	{
		auto container = tracksView->getContainer();
		auto clippingView = tracksView->getClippingView();
		if(container && clippingView)
		{
			
			return  MUI::Math::lerp(container->screenToLocal({x, 0}).x, 0, clippingView->getTracksWidth(), 0, getTimeControl().getTotalTime()) ;
		}
	}
	
	ofLogError("TracksPanel::screenPositionToTime") << "nullptr. returning 0";

	return 0;

	
}
//---------------------------------------------------------------------






} } // ofx::LineaDeTiempo
