//
//  BaseTrack.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#pragma once


#include "LineaDeTiempo/Controller/TimeControl.h"
#include "LineaDeTiempo/BaseTypes/BaseHasHeader.h"


#include "LineaDeTiempo/BaseTypes/BaseHasTimeControl.h"

#include "LineaDeTiempo/View/TrackHeader.h"

#include "DOM/Element.h"
#include "MUI/Styles.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackGroupView;


class BaseTrackView
: public DOM::Element
, public BaseHasHeader<TrackHeader>
{
public:

	
	BaseTrackView(const std::string& id, DOM::Element* parentView);
	
	virtual ~BaseTrackView() = default;
	
	
	virtual void setColor(const ofColor& color);
	const ofColor& getColor() const;

	static ofColor backgroundColor;
	static ofColor edgeColor;
	static const float initialHeight;
	
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
	
//	TrackGroupView* parentGroup();
//	const TrackGroupView* parentGroup() const;
//
//
	
	
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
	
	virtual float getUnscaledHeight() = 0;
	virtual float updateScaledShape(float y, float yScale, float width) = 0;
	
	
protected:
	
	
	
	
	ofColor _color;
	

//	TrackGroupView* _parentGroupView;
	
protected:
	
};




} } // ofx::LineaDeTiempo

