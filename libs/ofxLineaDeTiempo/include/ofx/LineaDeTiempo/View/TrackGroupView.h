//
//  TrackGroupView.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#pragma once

#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackGroupController;
class TrackController;

class TrackGroupView
: public BaseTrackView
{
public:
	
	
	TrackGroupView(DOM::Element* parentView, TrackGroupController * controller, TimeRuler * timeRuler);
	
	
	virtual ~TrackGroupView() = default;
	
	
	template< typename TrackViewType>
	TrackViewType* addTrack(TrackController * controller );
	
	
	bool removeTrack(TrackController * controller);
	
	
	template< typename GroupViewType>
	GroupViewType* addGroup(TrackGroupController * controller );
	
	
	bool removeGroup(TrackGroupController * controller);
	
	float getTracksHeaderWidth();
	
	
	virtual float getUnscaledHeight(size_t & numGroups) override;
	virtual float updateYScaled(float y, float yScale) override;
	
	
//	virtual void _updateContainers();
	
	
protected:
	void _setTracksHeaderWidth(float w);
	
	TrackGroupController* _controller = nullptr;
	
	DOM::Element* _tracksContainer = nullptr;
	
//	void _enableParentShapeListener();
//	void _disableParentShapeListener();
//	void _parentMoved(DOM::MoveEventArgs& e);
//	void _parentResized(DOM::ResizeEventArgs& e);
	
//	ofEventListeners _parentListeners;
	
	
	
	float _trackHeaderWidth = 200;
	
	bool _containersCheck(const std::string & callerName);
	
	bool _isPanel = false;
	
	
private:
	
	float _getInitialYpos();
	
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
	
	auto t = _tracksContainer->addChild<TrackViewType>(this, controller, _timeRuler);
	auto h = _header->addChild<TrackHeader>( "_header", ofRectangle(0, 0, _trackHeaderWidth, TrackInitialHeight), t , this, _isPanel);
	
	ofColor color;
	color.setHsb(ofRandom(255), ofRandom(200, 255), ofRandom(150,255));
	
	t->setColor(color);
	
	
//	_updateContainers();
	
	return t;
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
	
	
	auto t = _tracksContainer->addChild<GroupViewType>(this, controller, _timeRuler);
	auto h = _header->addChild<TrackHeader>( "_header", ofRectangle(0, 0, _trackHeaderWidth, TrackInitialHeight), t , this, _isPanel);
	
//	_updateContainers();
	
	return t;
	
}




} } // ofx::LineaDeTiempo
