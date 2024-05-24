//
//  ZoomScrollbar.cpp
//  example
//
//  Created by Roy Macdonald on 4/20/20.
//

#include "MUI/ZoomScrollbar.h"

#include "MUI/Constants.h"
#include "MUI/Utils.h"
#include "LineaDeTiempo/View/TracksClippedView.h"


namespace ofx {
namespace MUI {

float ZoomScrollbar::scrollSpeed = 0.02;

ZoomScrollbar::ZoomScrollbar(const std::string& id, DOM::Orientation orientation, DOM::Element* attachedToElement)
: DOM::Element(id, 0, 0, ConstVars::getScrollBarSize(),ConstVars::getScrollBarSize())
, DOM::OrientedElement(orientation)
{
	handleValue.set(-1,-1);
	
	
	this->setFocusable(false);

	mainHandle =  this->addChild<ConstrainedGrabHandle>(id+"_Z_scroll_handle_", orientation, ofRectangle (0,0, ConstVars::getScrollBarSize(), ConstVars::getScrollBarSize()));
	mainHandle->setConstrainedToParent(true);
	mainHandle->setMoveToFrontOnCapture(false);

	
	inHandle = this->addChild<EdgeHandle>(id+"_Z_in_handle_", (orientation == DOM::HORIZONTAL? DOM::RECT_LEFT:DOM::RECT_TOP), mainHandle, ALIGN_INSIDE, false );
	outHandle = this->addChild<EdgeHandle>(id+"_Z_out_handle_", (orientation == DOM::HORIZONTAL? DOM::RECT_RIGHT:DOM::RECT_BOTTOM), mainHandle, ALIGN_INSIDE, false );
	
	
	_setIOHandle(outHandle);
	_setIOHandle(inHandle);
	
	
		
	_mainHandleListener = mainHandle->shapeChanged.newListener(this, &ZoomScrollbar::_onMainHandleShapeChanged,std::numeric_limits<int>::lowest());
	
	
	mainHandle->moveToBack();
	
	
	_scrollListener = ofEvents().mouseScrolled.newListener(this, &ZoomScrollbar::_onScrollEvent,std::numeric_limits<int>::lowest());
	
	attachTo(attachedToElement);
	
	_updateShape();
	_setValue({0.f, 1.f});
}

void ZoomScrollbar::attachTo(DOM::Element* attachedToElement)
{
	_attachedToElement = attachedToElement;
	if(_attachedToElement)
	{
		_attachedToViewShapeListener = _attachedToElement->shapeChanged.newListener(this, &ZoomScrollbar::_onAttachedToViewShapeChanged);
		_updateShape();
	}
	else
	{
		_attachedToViewShapeListener.unsubscribe();
	}
}


void ZoomScrollbar::_setIOHandle(EdgeHandle* handle)
{
	handle->setHandleSize(ConstVars::getScrollBarSize());
	handle->setMoveToFrontOnCapture(true);
	handle->setTargetMinSize(ConstVars::getHandleMinSize());
	
}


bool ZoomScrollbar::_onScrollEvent(ofMouseEventArgs & e){
	
	if(getScreenShape().inside(e) || (_attachedToElement && _attachedToElement->getScreenShape().inside(e))){
		return scroll((_orientation == DOM::HORIZONTAL)? e.scrollX: e.scrollY);
	}
	return false;
}


void ZoomScrollbar::_zoomUpdate(ofRange r, bool forceUpdate)
{
	if(forceUpdate || !ofIsFloatEqual(r.min, handleValue.min)  || ofIsFloatEqual(r.max, handleValue.max))
	{
		handleValue = r;

		ofNotifyEvent(handleChangeEvent, r, this);
	}
}


void ZoomScrollbar::_onMainHandleShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_bIgnoreMainHandleShapeChange)
	{
		ofRange r = _shapeToNormalizedValue(mainHandle->getShape());
		_zoomUpdate(r, true);
	}
}


bool ZoomScrollbar::_setValue(const ofRange& val , bool bUpdateContainer)
{
	handleValue = val;
		
	_bIgnoreMainHandleShapeChange = true;
	
	
	
	auto b = setShapeIfNonEqual(mainHandle, _normalizedValueToShape(val));
	
	if( b && bUpdateContainer)
		_zoomUpdate(handleValue, true);
	
	_bIgnoreMainHandleShapeChange = false;
	
	return b;
}


bool ZoomScrollbar::setValue(const ofRange& val){
	return _setValue(val);
}


bool ZoomScrollbar::scroll(float amt){
	
	float val = scrollSpeed * amt;
	return addToValue(val);
}


void ZoomScrollbar::_updateShape()
{
	if(_attachedToElement){
		auto s = _attachedToElement->getShape();
		ofRectangle shape;
		
		if(_orientation == DOM::HORIZONTAL)
		{
			shape.set(s.x, s.getMaxY()+ConstVars::getContainerMargin(), s.width, ConstVars::getScrollBarSize());
		}
		else
		{
			shape.set(s.getMaxX()+ConstVars::getContainerMargin(), s.y, ConstVars::getScrollBarSize(), s.height);
		}
		
		setShape(shape);
		_setValue(handleValue);
	}
}


void ZoomScrollbar::_onAttachedToViewShapeChanged(DOM::ShapeChangeEventArgs&)
{
	_updateShape();
}


ofRange ZoomScrollbar::_shapeToNormalizedValue(const DOM::Shape& shape)
{
	
	ofRange r;
	
	r.min = ofMap(shape.getPosition()[dimIndex()], 0, getSize()[dimIndex()] - ConstVars::getHandleMinSize() , 0,1, true);
	r.max = ofMap(shape.getMax()[dimIndex()], ConstVars::getHandleMinSize(), getSize()[dimIndex()] , 0,1, true);
	
	return r;
	
}


DOM::Shape ZoomScrollbar::_normalizedValueToShape(const ofRange& val)
{
	
	glm::vec2 mn (0,0);
	glm::vec2 mx ( ConstVars::getScrollBarSize(), ConstVars::getScrollBarSize());
	
	auto size = getSize()[dimIndex()];
	
	mn[dimIndex()] = ofMap(val.min ,  0,1, 0, size - ConstVars::getHandleMinSize() , true);
	mx[dimIndex()] = ofMap(val.max, 0, 1, ConstVars::getHandleMinSize(), size , true);
	
	return DOM::Shape(mn, mx);
	
}


void ZoomScrollbar::onDraw() const
{
	
	ofPushStyle();
	
	ofNoFill();
	ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER_BACKGROUND , Styles::STATE_NORMAL));
	ofDrawRectangle(0,0,getWidth(), getHeight());
	
	ofPopStyle();
}


} } // ofx::MUI
