//
//  BaseTrack.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#pragma once



#include "LineaDeTiempo/View/BaseTrackView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/BaseTypes/BaseHasController.h"
#include "LineaDeTiempo/BaseTypes/BaseHasRegions.h"

namespace ofx {
namespace LineaDeTiempo {

class TrackGroupView;
class TrackController;

class TrackView
: public BaseTrackView
//, public BaseHasRegions<RegionView>
, public BaseHasController<TrackController>

{
public:

	TrackView(TrackGroupView* parentGroupView, TrackController* controller);
	virtual ~TrackView() = default;
	
	float getHeightFactor() const;
	void setHeightFactor(float factor);
	
	shared_ptr<MUI::Styles> getRegionsStyle();
	
	virtual void setColor(const ofColor& color) override;
	
	
//	using BaseHasRegions<RegionView>::removeRegion;
//	using BaseHasRegions<RegionView>::getRegion;
//	using BaseHasRegions<RegionView>::getRegions;
//	using BaseHasRegions<RegionView>::getNumRegions;
	
	
	ofRectangle timeRangeToRect(const ofRange64u& t) const;
	
	float timeToLocalPosition(const uint64_t& t) const;
	
	uint64_t localPositionToTime(float x) const;
	
	float timeToScreenPosition(uint64_t time) const;
	
	uint64_t  screenPositionToTime(float x) const;

	virtual void updateLayout() override;
	
	
//    using DOM::Element::isEnabled;
//    using DOM::Element::isFocusable;
//    using DOM::Element::isFocused;
//    using DOM::Element::isHidden;
//    using DOM::Element::isLocked;
//    using DOM::Element::getHeight;
//    using DOM::Element::getScreenX;
//    using DOM::Element::getScreenY;
//    using DOM::Element::getWidth;
//    using DOM::Element::getX;
//    using DOM::Element::getY;
//    using DOM::Element::getCenterPosition;
//    using DOM::Element::getPosition;
//    using DOM::Element::getScreenCenterPosition;
//    using DOM::Element::getScreenPosition;
//    using DOM::Element::localToScreen;
//    using DOM::Element::parentToScreen;
//    using DOM::Element::screenToLocal;
//    using DOM::Element::screenToParent;
//    using DOM::Element::getChildShape;
//    using DOM::Element::getScreenShape;
//    using DOM::Element::getShape;
//    using DOM::Element::getTotalShape;
//    using DOM::Element::getSize;
//
//    using DOM::Element::setEnabled;
//    using DOM::Element::setFocusable;
//    using DOM::Element::setHidden;
//    using DOM::Element::setLocked;
//    using DOM::Element::setPosition;
//    using DOM::Element::setShape;
//    using DOM::Element::setSize;
//
	
	template< typename RegionViewType>
	RegionViewType* addRegion(RegionController * controller )
	{
		static_assert(std::is_base_of<RegionView, RegionViewType>::value,
						  "TrackView::AddRegion : RegionViewType must inherit from ofx::LineaDeTiempo::RegionView");
			
		auto r = addChild<RegionViewType>(this,controller);
		r->setStyles( _regionsStyle);
		return r;

	}
	
	
	bool removeRegion(RegionController * controller);
	
	virtual float getUnscaledHeight() override;
	virtual float updateScaledShape(float y, float yScale, float width) override;
protected:
	float _heightFactor = 1;
	float _unscaledHeight;
	shared_ptr<MUI::Styles> _regionsStyle = nullptr;

	
};




} } // ofx::LineaDeTiempo

