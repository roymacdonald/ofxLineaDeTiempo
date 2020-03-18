//
//  TrackGroupView.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/Controller/TrackGroupController.h"
#include "LineaDeTiempo/Controller/TrackController.h"
namespace ofx {
namespace LineaDeTiempo {

TrackGroupView::TrackGroupView(TrackGroupView* parentGroupView, TrackGroupController * controller)
: BaseTrackView(controller->getId(), parentGroupView)
, BaseHasController<TrackGroupController>(controller)
{
}

//
//template< typename TrackViewType>
//TrackViewType* TrackGroupView::addTrack(TrackController * controller)
//{
//	static_assert(std::is_base_of<TrackView, TrackViewType>::value,
//				  "TrackViewType must inherit from ofx::LineaDeTiempo::TrackView");
//	
//	auto c = _getTracksContainer();
//	auto hc = _getHeadersContainer();
//	if(c && hc){
//		
//		auto t = c->addChild<TrackViewType>();
//		auto h = hc->addChild<TrackHeader>(t, _trackHeaderWidth, this);
//		
//		auto style = make_shared<MUI::Styles>();
//		ofColor color;
//		color.setHsb(ofRandom(255), ofRandom(150, 255), ofRandom(255));
//		
//		style->setColor(color, MUI::Styles::ROLE_BACKGROUND);
//		
//		t->setColor(color);
////		t->setStyles(style);
//		h->setStyles(style);
//		
////		if(bCreateFullTrackRegion) t->addRegion({0, getTimeControl().getTotalTime()});
//		
////		_trackCollection.push_back(t);
////		addElement(t);
//		
//		_updateContainers();
//		
//////		tracksView->updateLayout();
////		tracksView->updateContainerLayout();
////		
//		return t;
//	}
//	ofLogError("TrackGroupView::addTrack") << "can not add track because container is nullptr";
//	return nullptr;
//}

void TrackGroupView::_updateContainers()
{
	auto c = _getTracksContainer();
	if(c) c->updateLayout();
	updateLayout();
}


bool TrackGroupView::removeTrack(TrackController* controller)
{
	if(controller == nullptr) return false;

	auto track = controller->getView();
	auto c = _getTracksContainer();
	auto hc = _getHeadersContainer();
	if(c && hc){

		auto tr = c->removeChild(track);
		auto h = hc->removeChild(track->getHeader());

		
//		removeChild(track);
		
//		BaseHasCollection<BaseTrack, false_type>::removeElement(track);
		
//		ofRemove(_trackCollection, [&](BaseTrack* t){
//			return (track->getHeader() == t->getHeader() && track == t);
//		});
		_updateContainers();
		return true;
	}
	return false;
}

DOM::Element* TrackGroupView::_getTracksContainer()
{
	return this;
}
DOM::Element* TrackGroupView::_getHeadersContainer()
{
	return _header;
}

//---------------------------------------------------------------------
float TrackGroupView::getTrackHeaderWidth(){
	return _trackHeaderWidth;
}
//---------------------------------------------------------------------
void TrackGroupView::setTrackHeaderWidth(float w){
	if(!ofIsFloatEqual(_trackHeaderWidth, w)){
		_trackHeaderWidth = w;
		updateLayout();
	}
}


float TrackGroupView::getUnscaledHeight()
{
	float h = _groupTopMargin;
	
	for(auto c: children())
	{
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			h+= t->getUnscaledHeight();
		}
	}
	
	return h;
}
float TrackGroupView::updateScaledShape(float y, float yScale, float width)
{

	float h = _groupTopMargin;
	
	for(auto c: children())
	{
		auto t = dynamic_cast<BaseTrackView*>(c);
		if(t)
		{
			h+= t->updateScaledShape(y,  yScale, width);
		}
	}
	
	setShape({0, y, width, h});
	updateLayout();
	return h;
}


} } // ofx::LineaDeTiempo
