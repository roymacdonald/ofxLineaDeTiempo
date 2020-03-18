//
//  TrackGroupView.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#pragma once

#include "LineaDeTiempo/BaseTypes/BaseHasController.h"
#include "LineaDeTiempo/View/TrackView.h"

namespace ofx {
namespace LineaDeTiempo {

class TrackGroupController;
class TrackController;

class TrackGroupView
: public BaseTrackView
, public BaseHasController<TrackGroupController>
{
public:

	
	TrackGroupView(TrackGroupView* parentGroupView, TrackGroupController * controller);
	
	
	virtual ~TrackGroupView() = default;

	
	template< typename TrackViewType>
	TrackViewType* addTrack(TrackController * controller );
	
	
	bool removeTrack(TrackController * controller);


	float getTrackHeaderWidth();
	void setTrackHeaderWidth(float w);

	virtual float getUnscaledHeight() override;
	virtual float updateScaledShape(float y, float yScale, float width) override;
	
protected:
	
	virtual DOM::Element* _getTracksContainer();
	virtual DOM::Element* _getHeadersContainer();
	
	float _groupTopMargin = 10;
	
	virtual void _updateContainers();
	
		float _trackHeaderWidth = 200;
private:
	
	
};


template< typename TrackViewType>
TrackViewType* TrackGroupView::addTrack(TrackController * controller)
{
	static_assert(std::is_base_of<TrackView, TrackViewType>::value,
				  "TrackViewType must inherit from ofx::LineaDeTiempo::TrackView");
	
	auto c = _getTracksContainer();
	auto hc = _getHeadersContainer();
	if(c && hc){
		
		auto t = c->addChild<TrackViewType>();
		auto h = hc->addChild<TrackHeader>(t, _trackHeaderWidth, this);
		
		auto style = make_shared<MUI::Styles>();
		ofColor color;
		color.setHsb(ofRandom(255), ofRandom(150, 255), ofRandom(255));
		
		style->setColor(color, MUI::Styles::ROLE_BACKGROUND);
		
		t->setColor(color);
//		t->setStyles(style);
		h->setStyles(style);
		
//		if(bCreateFullTrackRegion) t->addRegion({0, getTimeControl().getTotalTime()});
		
//		_trackCollection.push_back(t);
//		addElement(t);
		
		_updateContainers();
		
////		tracksView->updateLayout();
//		tracksView->updateContainerLayout();
//
		return t;
	}
	ofLogError("TrackGroupView::addTrack") << "can not add track because container is nullptr";
	return nullptr;
}

} } // ofx::LineaDeTiempo
