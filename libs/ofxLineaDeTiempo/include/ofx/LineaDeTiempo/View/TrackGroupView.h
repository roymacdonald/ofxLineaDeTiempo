//
//  TrackGroupView.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#pragma once


#include "LineaDeTiempo/View/KeyframeTrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackGroupController;
class TrackController;
template <typename DataType>
class KeyframeTrackController_;

class TrackGroupView
: public BaseTrackView
{
public:
	
	
	TrackGroupView(DOM::Element* parentView, TrackGroupController * controller, TimeRuler * timeRuler);
	
	
	virtual ~TrackGroupView() = default;
	
	
	template< typename DataType>
	KeyframeTrackView<DataType>* addTrack(TrackController * controller );
	
	
	bool removeTrack(TrackController * controller);
	
	
	TrackGroupView* addGroup(TrackGroupController * controller );
	
	
	bool removeGroup(TrackGroupController * controller);
	
	float getTracksHeaderWidth();
	
	
	virtual float getUnscaledHeight(size_t & numGroups) override;
	virtual float updateYScaled(float y, float yScale) override;
		
	
	virtual void onChildrensChange();
	
protected:
	
	void _onChildrensChange(DOM::ElementEventArgs& );
	
	void _setTracksHeaderWidth(float w);
	
	TrackGroupController* _controller = nullptr;
	
	DOM::Element* _tracksContainer = nullptr;
		
	float _trackHeaderWidth = 200;
	
	bool _containersCheck(const std::string & callerName);
	
	bool _isPanel = false;
	
	
private:
	
	float _getInitialYpos();
	
	ofEventListeners _childrensChangeListeners;
	
	
};
template< typename DataType>
KeyframeTrackView<DataType>* TrackGroupView::addTrack(TrackController * controller )
{

	if(!controller)
	{
		ofLogError("TrackGroupView::addTrack") << "controller is invalid. " << getId();
		return nullptr;
	}
	
	if(_containersCheck("addTrack") == false)
	{
		return nullptr;
	}
	
	auto t = _tracksContainer->addChild<KeyframeTrackView<DataType>>(this, controller, _timeRuler, _header,_isPanel);
	
	ofColor color;
	color.setHsb(ofRandom(255), ofRandom(200, 255), ofRandom(150,255));
	
	t->setColor(color);
	
	return t;
}





} } // ofx::LineaDeTiempo
