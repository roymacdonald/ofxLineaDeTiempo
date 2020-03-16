//
//  BaseTrack.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#pragma once


#include "LineaDeTiempo/Controller/TimeControl.h"
#include "LineaDeTiempo/BaseTypes/BaseHasController.h"
#include "LineaDeTiempo/BaseTypes/BaseHasHeader.h"
#include "LineaDeTiempo/BaseTypes/BaseHasRegions.h"
#include "LineaDeTiempo/View/TrackHeader.h"
#include "LineaDeTiempo/View/RegionView.h"

#include "DOM/Element.h"
#include "MUI/BaseClasses.h"
#include "MUI/Styles.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackGroupView;
class TrackController;

class TrackView
: public DOM::Element
, public BaseHasLayout
, public BaseHasHeader<TrackHeader>
, public BaseHasRegions<RegionView>
, public BaseHasController<TrackController>
{
public:

	TrackView(TrackGroupView* parentGroupView, TrackController* controller);
	virtual ~TrackView() = default;
	
	static const float initialHeight;
	
	float getHeightFactor();
	void setHeightFactor(float factor);
	
	
	
	void setColor(const ofColor& color);
	const ofColor& getColor();

	static ofColor backgroundColor;
	static ofColor edgeColor;
	
	virtual void onDraw() const override;
	
	
	shared_ptr<MUI::Styles> getRegionsStyle();
	
	
	ofRectangle timeRangeToRect(const ofRange64u& t) const;
	
	float timeToLocalPosition(const uint64_t& t) const;
	
	uint64_t localPositionToTime(float x) const;
	
	float timeToScreenPosition(uint64_t time) const;
	
	uint64_t  screenPositionToTime(float x) const;

	virtual void updateLayout() override;
	
	
	TrackGroupView* parentGroup();
	const TrackGroupView* parentGroup() const;
	
	
	using BaseHasRegions<RegionView>::removeRegion;
	using BaseHasRegions<RegionView>::getRegion;
	using BaseHasRegions<RegionView>::getRegions;
	using BaseHasRegions<RegionView>::getNumRegions;
	
	
    using DOM::Element::isEnabled;
    using DOM::Element::isFocusable;
    using DOM::Element::isFocused;
    using DOM::Element::isHidden;
    using DOM::Element::isLocked;
    using DOM::Element::getHeight;
    using DOM::Element::getScreenX;
    using DOM::Element::getScreenY;
    using DOM::Element::getWidth;
    using DOM::Element::getX;
    using DOM::Element::getY;
    using DOM::Element::getCenterPosition;
    using DOM::Element::getPosition;
    using DOM::Element::getScreenCenterPosition;
    using DOM::Element::getScreenPosition;
    using DOM::Element::localToScreen;
    using DOM::Element::parentToScreen;
    using DOM::Element::screenToLocal;
    using DOM::Element::screenToParent;
    using DOM::Element::getChildShape;
    using DOM::Element::getScreenShape;
    using DOM::Element::getShape;
    using DOM::Element::getTotalShape;
    using DOM::Element::getSize;

    using DOM::Element::setEnabled;
    using DOM::Element::setFocusable;
    using DOM::Element::setHidden;
    using DOM::Element::setLocked;
    using DOM::Element::setPosition;
    using DOM::Element::setShape;
    using DOM::Element::setSize;
	
	
	
	
protected:
	
	
	float _heightFactor = 1;
	
	ofColor _color;
	
	shared_ptr<MUI::Styles> _regionsStyle = nullptr;


	TrackGroupView* _parentGroupView;
protected:
	
};




} } // ofx::LineaDeTiempo

