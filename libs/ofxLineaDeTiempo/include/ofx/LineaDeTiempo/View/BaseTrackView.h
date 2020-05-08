//
//  BaseTrack.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/15/20.
//

#pragma once


#include "LineaDeTiempo/Controller/TimeControl.h"
//#include "LineaDeTiempo/BaseTypes/BaseHasHeader.h"

#include "LineaDeTiempo/View/TrackHeader.h"
#include "LineaDeTiempo/View/TimeRuler.h"
#include "DOM/Element.h"
#include "MUI/Styles.h"


namespace ofx {
namespace LineaDeTiempo {

class TrackGroupView;
class TracksPanel;


class BaseTrackView
: public DOM::Element
//, public BaseHasHeader<TrackHeader>
{
public:

	
	BaseTrackView(const std::string& id, DOM::Element* parentView, TimeRuler * timeRuler);
	
	virtual ~BaseTrackView() = default;
	
	
	virtual void setColor(const ofColor& color);
	const ofColor& getColor() const;
	ofEvent<ofColor> colorChangeEvent;
	
	const ofColor& getTextColor() const;
	
	virtual void onDraw() const override;


	void setHeader(TrackHeader* header);
	
	TrackHeader* getHeader();
	
	const TrackHeader* getHeader() const;


	TrackGroupView* getParentGroupView();
	
	TracksPanel* getParentPanel();
	
	
	TimeRuler * getTimeRuler();
	
	const TimeRuler * getTimeRuler() const;
	
	void updateWidth(const float& w);
	
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
	
	virtual float getUnscaledHeight(size_t & numGroups) = 0;
	virtual float updateYScaled(float y, float yScale) = 0;
	
	
protected:
	TimeRuler* _timeRuler = nullptr;
	
	TrackHeader* _header = nullptr;
	
	TrackGroupView* _parentGroupView = nullptr;
	
	
	ofColor _color;
	ofColor _textColor;
protected:
	
};




} } // ofx::LineaDeTiempo

