//
//  BaseTrack.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#pragma once



#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/RegionView.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasController.h"

namespace ofx {
namespace LineaDeTiempo {

class TrackGroupView;
class TrackController;

class TrackView
: public BaseTrackView
//, public BaseHasController<TrackController>

{
public:

	TrackView(DOM::Element* parentView, TrackController* controller);
	virtual ~TrackView() = default;
	
	float getHeightFactor() const;
	void setHeightFactor(float factor);
	
	shared_ptr<MUI::Styles> getRegionsStyle();
	
	virtual void setColor(const ofColor& color) override;
	
	
	ofRectangle timeRangeToRect(const ofRange64u& time) const;
	
	ofRange64u  rectToTimeRange(const ofRectangle& rect) const;
	
	float timeToLocalPosition(const uint64_t& t) const;
	
	uint64_t localPositionToTime(float x) const;
	
	float timeToScreenPosition(uint64_t time) const;
	
	uint64_t  screenPositionToTime(float x) const;

	virtual void updateLayout() override;
	
	
	
	template< typename RegionViewType, typename RegionControllerType>
	RegionViewType* addRegion(RegionControllerType  * controller )
	{
		static_assert(std::is_base_of<RegionView, RegionViewType>::value,
						  "TrackView::AddRegion : RegionViewType must inherit from ofx::LineaDeTiempo::RegionView");
		static_assert(std::is_base_of<RegionController, RegionControllerType>::value,
					  "TrackView:: RegionControllerType must be of type ofx::LineaDeTiempo::RegionController or derived from it");
		
		auto r = addChild<RegionViewType>(this,controller, _regionsStyle);
		r->setStyles( _regionsStyle);
		return r;

	}
	
	
	bool removeRegion(RegionController * controller);
	
	virtual float getUnscaledHeight() override;
	virtual float updateScaledShape(float y, float yScale, float width) override;

	
//	virtual const TrackController * getController() const override;
//	
//	virtual TrackController * getController() override;
//	
//	virtual void setController(TrackController * controller) override;
//	
	
protected:

	float _heightFactor = 1;
	float _unscaledHeight;
	shared_ptr<MUI::Styles> _regionsStyle = nullptr;

	TrackController* _controller = nullptr;
	
};




} } // ofx::LineaDeTiempo

