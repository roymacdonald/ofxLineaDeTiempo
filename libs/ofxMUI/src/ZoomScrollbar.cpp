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
: DOM::Element(id, 0, 0, SCROLL_BAR_SIZE,SCROLL_BAR_SIZE)
, DOM::OrientedElement(orientation)
{
	handleValue.set(-1,-1);
	
	
	this->setFocusable(false);

	mainHandle =  this->addChild<ConstrainedGrabHandle>(id+"_Z_scroll_handle_", orientation, ofRectangle (0,0, SCROLL_BAR_SIZE, SCROLL_BAR_SIZE));
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
	
//	_containerShapeListener = _clippedView->container->shapeChanged.newListener(this, &ZoomScrollbar::_onContainerShapeChanged);
	
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
	handle->setHandleSize(SCROLL_BAR_SIZE);
	handle->setMoveToFrontOnCapture(true);
	handle->setTargetMinSize(HANDLE_MIN_SIZE);
	
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
//		if(_clippedView)
//		{
//			_bIgnoreContainerShapeChange=true;
////			_clippedView->setZoom(getOrientation(), handleValue);
//			_bIgnoreContainerShapeChange=false;
//		}
		ofNotifyEvent(handleChangeEvent, r, this);
	}
}

//void ZoomScrollbar::_onContainerShapeChanged(DOM::ShapeChangeEventArgs&)
//{
//	if(!_bIgnoreContainerShapeChange)
//	{
//		updateValueFromClippedView();
//	}
//
//}

void ZoomScrollbar::_onMainHandleShapeChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_bIgnoreMainHandleShapeChange)
	{
//		std::cout << __PRETTY_FUNCTION__ << "\n";
		ofRange r = shapeToNormalizedValue(mainHandle->getShape());
//		r.min = minPosToNormalizedValue();
//		r.max = maxPosToNormalizedValue();
		
	_zoomUpdate(r, true);
	
	
//		if(r != handleValue)
//		{
//			handleValue = r;
//			if(_clippedView)
//			{
//				_clippedView->setZoom(getOrientation(), handleValue);
//			}
//			ofNotifyEvent(handleChangeEvent, r, this);
//		}
	}
}


bool ZoomScrollbar::_setValue(const ofRange& val , bool bUpdateContainer)
{
	handleValue = val;
		
	_bIgnoreMainHandleShapeChange = true;
	
	
	
	auto b = setShapeIfNonEqual(mainHandle, normalizedValueToShape(val));
	
	if( b && bUpdateContainer)
		_zoomUpdate(handleValue, true);
	
	_bIgnoreMainHandleShapeChange = false;
	
	return b;
}


bool ZoomScrollbar::setValue(const ofRange& val){
//	std::cout << "ZoomScrollbar::setValue:  " << val << "\n";
//	if(handleValue == val) return false;
	
	return _setValue(val);
//	handleValue = val;
//
//	_bIgnoreMainHandleShapeChange = true;
//	auto a = normalizedValueToMinPos(handleValue.min);
//	auto b = normalizedValueToMaxPos(handleValue.max);
//	_zoomUpdate(handleValue, true);
//	if(a || b){
////		ofNotifyEvent(handleChangeEvent, handleValue, this);
//
//		_bIgnoreMainHandleShapeChange = false;
//		return true;
//	}
//	_bIgnoreMainHandleShapeChange = false;
//	return false;
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
			shape.set(s.x, s.getMaxY()+CONTAINER_MARGIN, s.width, SCROLL_BAR_SIZE);
		}
		else
		{
			shape.set(s.getMaxX()+CONTAINER_MARGIN, s.y, SCROLL_BAR_SIZE, s.height);
		}
		
		setShape(shape);
		_setValue(handleValue);
//		updateValueFromClippedView();
		
	}
//	else
//	{
//		ofLogError("ZoomScrollbar::_onClippedViewShapeChanged") << " _clipppedView is null.This should not happen";
//	}
}

//hacer que los cambios de forma del container se reflejen en el handle.

void ZoomScrollbar::_onAttachedToViewShapeChanged(DOM::ShapeChangeEventArgs&)
{
//	std::cout << __PRETTY_FUNCTION__ << "\n";
	_updateShape();
}

//
//float ZoomScrollbar::minPosToNormalizedValue()
//{
//	return ofMap( mainHandle->getPosition()[dimIndex()], 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE , 0,1, true);
//}
//
//
//float ZoomScrollbar::maxPosToNormalizedValue(){
//	return ofMap(mainHandle->getShape().getMax()[dimIndex()], HANDLE_MIN_SIZE, getSize()[dimIndex()] , 0,1, true);
//}
//

ofRange ZoomScrollbar::shapeToNormalizedValue(const DOM::Shape& shape)
{
	
	ofRange r;
	
	r.min = ofMap(shape.getPosition()[dimIndex()], 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE , 0,1, true);
	r.max = ofMap(shape.getMax()[dimIndex()], HANDLE_MIN_SIZE, getSize()[dimIndex()] , 0,1, true);
	
	return r;
	
}


DOM::Shape ZoomScrollbar::normalizedValueToShape(const ofRange& val)
{
	
	glm::vec2 mn (0,0);
	glm::vec2 mx ( SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
	
	auto size = getSize()[dimIndex()];
	
	mn[dimIndex()] = ofMap(val.min ,  0,1, 0, size - HANDLE_MIN_SIZE , true);
	mx[dimIndex()] = ofMap(val.max, 0, 1, HANDLE_MIN_SIZE, size , true);
	
	return DOM::Shape(mn, mx);
	
}


//bool ZoomScrollbar::normalizedValueToMinPos(float val){
//	auto p = mainHandle->getPosition();
//	p[dimIndex()] = ofMap(val, 0, 1, 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE ,  true);
//	if(setPosIfNonEqual(mainHandle, p)){
//		return true;
//	}
//	return false;
//}
//
//
//bool ZoomScrollbar::normalizedValueToMaxPos(float val){
//
//	auto p = mainHandle->getShape().getMax();
//
//	p[dimIndex()] = ofMap(val, 0, 1, HANDLE_MIN_SIZE, getSize()[dimIndex()],  true);
//	if(setShapeIfNonEqual(mainHandle, {mainHandle->getPosition(), p})){
//		return true;
//	}
//	return false;
//}


//void ZoomScrollbar::updateValueFromClippedView()
//{
////	std::cout << __PRETTY_FUNCTION__ ;
//	auto t = dynamic_cast<LineaDeTiempo::TracksClippedView*>(_clippedView);
//	if(t)
//	{
//
//		if(_orientation == DOM::HORIZONTAL)
//		{
////			hacer funcion similar a _setValue pero que no sette el zoom del clipped view, ya uqe es de este de donde lo estamos obteniendo
////			std::cout << " H: " << t->containerWidthToZoom() << "\n";
////			_setValue(t->containerWidthToZoom().clamp({0,1}), false);
//		}
//		else
//		{
////			std::cout << " V: " << t->containerHeightToZoom() << "\n";
//
////			_setValue(t->containerHeightToZoom().clamp({0,1}), false);
//		}
//	}
//}


void ZoomScrollbar::onDraw() const
{
	
	ofPushStyle();
	ofNoFill();
	ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER , Styles::STATE_NORMAL));
	ofDrawRectangle(0,0,getWidth(), getHeight());
	
	ofPopStyle();
}


} } // ofx::MUI
