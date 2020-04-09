//
//  BaseTrack.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#pragma once



#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/TimeRuler.h"
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

	TrackView(DOM::Element* parentView, TrackController* controller, TimeRuler * timeRuler );
	virtual ~TrackView() = default;
	
	float getHeightFactor() const;
	void setHeightFactor(float factor);
	
	shared_ptr<MUI::Styles> getRegionsHeaderStyle();
	
	
	ofRectangle timeRangeToRect(const ofRange64u& time) const;
	
	ofRange64u  rectToTimeRange(const ofRectangle& rect) const;
	
	float timeToLocalPosition(const uint64_t& t) const;
	
	uint64_t localPositionToTime(float x) const;
	
	
	
	virtual void updateLayout() override;
	
	
	
	template< typename RegionViewType, typename RegionControllerType>
	RegionViewType* addRegion(RegionControllerType  * controller )
	{
		static_assert(std::is_base_of<RegionView, RegionViewType>::value,
						  "TrackView::AddRegion : RegionViewType must inherit from ofx::LineaDeTiempo::RegionView");
		static_assert(std::is_base_of<RegionController, RegionControllerType>::value,
					  "TrackView:: RegionControllerType must be of type ofx::LineaDeTiempo::RegionController or derived from it");
		
		auto r = addChild<RegionViewType>(this,controller, _regionsHeaderStyle);
		_regions.push_back(r);
		return r;

	}
	
	
	bool removeRegion(RegionController * controller);
	
	virtual float getUnscaledHeight(size_t & numGroups) override;
	virtual float updateYScaled(float y, float yScale) override;

	
	const TrackController * getController() const;
	
	TrackController * getController();

	
	
	
protected:

	
	virtual void _onShapeChange(const DOM::ShapeChangeEventArgs& ) override;
	
	
	
	float _heightFactor = 1;
	float _unscaledHeight;
	
	shared_ptr<MUI::Styles> _regionsHeaderStyle = nullptr;
	
	std::vector<RegionView*> _regions;
	
	void colorChanged(ofColor& color);
	
	ofEventListener colorListener;
	
	TrackController* _controller = nullptr;
	
	
	void _updateRegionsHeight();
	
	void _updateRegionsWidth();
};




} } // ofx::LineaDeTiempo

