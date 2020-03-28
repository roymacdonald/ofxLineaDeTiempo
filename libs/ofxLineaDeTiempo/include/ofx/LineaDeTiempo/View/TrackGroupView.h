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

	
	TrackGroupView(DOM::Element* parentView, TrackGroupController * controller);
	
	
	virtual ~TrackGroupView() = default;

	
	template< typename TrackViewType>
	TrackViewType* addTrack(TrackController * controller );
	
	
	bool removeTrack(TrackController * controller);


	template< typename GroupViewType>
	GroupViewType* addGroup(TrackGroupController * controller );
	
	
	bool removeGroup(TrackGroupController * controller);

//	virtual void updateLayout() override;
	
	float getTrackHeaderWidth();
	void setTrackHeaderWidth(float w);

	virtual float getUnscaledHeight() override;
	virtual float updateScaledShape(float y, float yScale, float width) override;
	
protected:
	
	virtual DOM::Element* _getTracksContainer();
	virtual DOM::Element* _getHeadersContainer();
	
	
	void _enableParentShapeListener();
	void _disableParentShapeListener();
	void _parentMoved(DOM::MoveEventArgs& e);
	void _parentResized(DOM::ResizeEventArgs& e);
	
	ofEventListeners _parentListeners;
	
	
	float _groupTopMargin =25;
	
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
		
		auto t = c->addChild<TrackViewType>(this, controller);
		auto h = hc->addChild<TrackHeader>(t, _trackHeaderWidth, this);
				
		ofColor color;
		color.setHsb(ofRandom(255), ofRandom(200, 255), ofRandom(150,255));
		
		t->setColor(color);
		
		
		_updateContainers();
		
		return t;
	}
	ofLogError("TrackGroupView::addTrack") << "can not add track because container is nullptr";
	return nullptr;
}


template< typename GroupViewType>
GroupViewType* TrackGroupView::addGroup(TrackGroupController * controller )
{
	static_assert(std::is_base_of<TrackGroupView, GroupViewType>::value,
				  "TrackViewType must inherit from ofx::LineaDeTiempo::TrackView");
	
	auto c = _getTracksContainer();
	auto hc = _getHeadersContainer();
	if(c && hc){
		
		auto t = c->addChild<GroupViewType>(this, controller);
		auto h = hc->addChild<TrackHeader>(t, _trackHeaderWidth, this);
				
		_updateContainers();
		
		return t;
	}
	ofLogError("TrackGroupView::addTrack") << "can not add track because container is nullptr";
	return nullptr;
}




} } // ofx::LineaDeTiempo
