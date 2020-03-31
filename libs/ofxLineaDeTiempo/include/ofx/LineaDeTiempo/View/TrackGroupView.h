//
//  TrackGroupView.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#pragma once

//#include "LineaDeTiempo/BaseTypes/BaseHasController.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"

namespace ofx {
namespace LineaDeTiempo {

class TrackGroupController;
class TrackController;

class TrackGroupView
: public BaseTrackView
//, public BaseHasController<TrackGroupController>
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
	
	
	virtual void _updateContainers();
	
	
//	virtual const TrackGroupController * getController() const override;
//	
//	virtual TrackGroupController * getController() override;
//	
//	virtual void setController(TrackGroupController * controller) override;
//	
//	
	
	
protected:
	
	
	TrackGroupController* _controller = nullptr;
	
	DOM::Element* _tracksContainer = nullptr;
//	DOM::Element* _headersContainer = nullptr;
	
	void _enableParentShapeListener();
	void _disableParentShapeListener();
	void _parentMoved(DOM::MoveEventArgs& e);
	void _parentResized(DOM::ResizeEventArgs& e);
	
	ofEventListeners _parentListeners;
	
	
	float _groupTopMargin =25;

	
		float _trackHeaderWidth = 200;
	
	bool _containersCheck(const std::string & callerName);
	

	TrackGroupView* _parentGroup = nullptr;

private:
	
	
};


template< typename TrackViewType>
TrackViewType* TrackGroupView::addTrack(TrackController * controller)
{
	static_assert(std::is_base_of<TrackView, TrackViewType>::value,
				  "TrackViewType must inherit from ofx::LineaDeTiempo::TrackView");
	if(!controller)
	{
		ofLogError("TrackGroupView::addTrack") << "controller is invalid. " << getId();
		return nullptr;
	}
	
	if(_containersCheck("addTrack") == false)
	{
		return nullptr;
	}
	
//	if(_tracksContainer && _headersContainer){
		
		auto t = _tracksContainer->addChild<TrackViewType>(this, controller);
		auto h = _header->addChild<TrackHeader>( "_header", ofRectangle(0, 0, _trackHeaderWidth, TrackInitialHeight), t , this);
				
		ofColor color;
		color.setHsb(ofRandom(255), ofRandom(200, 255), ofRandom(150,255));
		
		t->setColor(color);
		
		
		_updateContainers();
		
		return t;
//	}
//	ofLogError("TrackGroupView::addTrack") << "can not add track because container is nullptr";
//	return nullptr;
}


template< typename GroupViewType>
GroupViewType* TrackGroupView::addGroup(TrackGroupController * controller )
{
	static_assert(std::is_base_of<TrackGroupView, GroupViewType>::value,
				  "TrackViewType must inherit from ofx::LineaDeTiempo::TrackView");
	
	if(!controller)
	{
		ofLogError("TrackGroupView::addGroup") << "controller is invalid. " << getId();
		return nullptr;
	}
	
	if(_containersCheck("addGroup") == false)
	{
		return nullptr;
	}
		
		auto t = _tracksContainer->addChild<GroupViewType>(this, controller);
		auto h = _header->addChild<TrackHeader>( "_header", ofRectangle(0, 0, _trackHeaderWidth, TrackInitialHeight), t , this);
				
		_updateContainers();
		
		return t;
//	}
//	ofLogError("TrackGroupView::addTrack") << "can not add track because container is nullptr";
//	return nullptr;
}




} } // ofx::LineaDeTiempo
