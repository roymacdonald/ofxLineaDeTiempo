//
//  ZoomScrollbar.cpp
//  example
//
//  Created by Roy Macdonald on 4/20/20.
//

#include "ZoomScrollbar.h"

#include "ClippedView.h"
#include "Constants.h"
#include "Utils.h"

namespace ofx {
namespace MUI {

float ZoomScrollbar::scrollSpeed = 0.02;

ZoomScrollbar::ZoomScrollbar(const std::string& id, DOM::Orientation orientation, ClippedView* clippedView)
: DOM::Element(id, 0, 0, SCROLL_BAR_SIZE,SCROLL_BAR_SIZE)
, DOM::OrientedElement(orientation)
, _clippedView(clippedView)
{
	handleValue.set(0,1);
	ofRectangle r (0,0, SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
	
	this->setFocusable(false);
//	this->setHighlightOnOver(true);
//		EdgeHandle(const std::string& id, DOM::RectEdge edge, DOM::Element* target, EdgeHandleAlignment edgeAlignment = ALIGN_CENTER, bool bAutoHide = true);
		mainHandle =  this->addChild<ConstrainedGrabHandle>(id+"_Z_scroll_handle_", orientation, r);
		mainHandle->setConstrainedToParent(true);
	
		inHandle = this->addChild<EdgeHandle>(id+"_Z_in_handle_", (orientation == DOM::HORIZONTAL? DOM::RECT_LEFT:DOM::RECT_TOP), mainHandle, ALIGN_INSIDE, false );
		outHandle = this->addChild<EdgeHandle>(id+"_Z_out_handle_", (orientation == DOM::HORIZONTAL? DOM::RECT_RIGHT:DOM::RECT_BOTTOM), mainHandle, ALIGN_INSIDE, false );
		
		
	//	inHandle->setShapeDrawMode( (orientation == DOM::HORIZONTAL)? ShapeDrawMode::LEFT_ROUNDED_RECTANGLE : ShapeDrawMode::TOP_ROUNDED_RECTANGLE);
	//	outHandle->setShapeDrawMode( (orientation == DOM::HORIZONTAL)? ShapeDrawMode::RIGHT_ROUNDED_RECTANGLE : ShapeDrawMode::BOTTOM_ROUNDED_RECTANGLE);
		
	_setIOHandle(outHandle);
	_setIOHandle(inHandle);
		
		mainHandle->setMoveToFrontOnCapture(false);
		
		
//		_inHandleConstraint = std::make_unique<Widget>("in_constraint", r);
//		_outHandleConstraint = std::make_unique<Widget>("out_constraint", r);
//

//		inHandle->constrainTo(_inHandleConstraint.get());
//		outHandle->constrainTo(_outHandleConstraint.get());
//

		
//		handlesListeners.push(inHandle->shapeChanged.newListener(this, &ZoomScrollbar::_onInHandleShapeChanged,std::numeric_limits<int>::lowest()));
//		handlesListeners.push(outHandle->shapeChanged.newListener(this, &ZoomScrollbar::_onOutHandleShapeChanged,std::numeric_limits<int>::lowest()));
//
		_mainHandleListener = mainHandle->shapeChanged.newListener(this, &ZoomScrollbar::_onMainHandleShapeChanged,std::numeric_limits<int>::lowest());
		
		
		mainHandle->moveToBack();
//		_updateInHandle();
//		_updateOutHandle();
	
	_clippedViewShapeListener = _clippedView->shapeChanged.newListener(this, &ZoomScrollbar::_onClippedViewShapeChanged);
	
	_scrollListener = ofEvents().mouseScrolled.newListener(this, &ZoomScrollbar::_onScrollEvent,std::numeric_limits<int>::lowest());
	
	
	_updateShape();
}
void ZoomScrollbar::_setIOHandle(EdgeHandle* handle)
{
	handle->setHandleSize(SCROLL_BAR_SIZE);
	handle->setMoveToFrontOnCapture(true);
	handle->setTargetMinSize(HANDLE_MIN_SIZE);
	
}

bool ZoomScrollbar::_onScrollEvent(ofMouseEventArgs & e){
	
	if(getScreenShape().inside(e) || (_clippedView && _clippedView->getScreenShape().inside(e))){
		return scroll((_orientation == DOM::HORIZONTAL)? e.scrollX: e.scrollY);
	}
	return false;
}


//void ZoomScrollbar::_setInHandleConstraint(){
//	glm::vec2 size (SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
//	glm::vec2 pos = getScreenPosition();//(0,0);
//
//	size [dimIndex()]  = mainHandle->getScreenShape().getMax()[dimIndex()] - HANDLE_MIN_SIZE + SCROLL_BAR_SIZE;
//
//	_inHandleConstraint->setShape(ofRectangle(pos.x, pos.y, size.x, size.y));
//
//	inHandle->constrainTo(_inHandleConstraint.get());
//
//}
//
//
//void ZoomScrollbar::_setOutHandleConstraint(){
//	glm::vec2 pos = getScreenPosition();//(0,0);
//	glm::vec2 size (SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
//	size[dimIndex()] = getSize()[dimIndex()] + pos[dimIndex()];
//
//	pos[dimIndex()] = mainHandle->getScreenPosition()[dimIndex()] + HANDLE_MIN_SIZE - SCROLL_BAR_SIZE;
//
//	size[dimIndex()] -= pos[dimIndex()];
//
//	_outHandleConstraint->setShape(ofRectangle(pos.x, pos.y, size.x, size.y ));
//
//	outHandle->constrainTo(_outHandleConstraint.get());
//
//}
//
//
//bool ZoomScrollbar::_updateInHandle()
//{
//	if(inHandle->isDragging())return false;
//	return setPosIfNonEqual(inHandle, mainHandle->getPosition());
//}
//
//
//bool ZoomScrollbar::_updateOutHandle()
//{
//	if(outHandle->isDragging())return false;
//	auto mx =mainHandle->getShape().getMax();
//	mx[dimIndex()] -= SCROLL_BAR_SIZE;
//	mx[1 - dimIndex()] = 0;
//
//	return setPosIfNonEqual(outHandle, mx);
//
//}
//
void ZoomScrollbar::_onMainHandleShapeChanged(DOM::ShapeChangeEventArgs& e)
{

//	if(!e.resized()){
//		_updateInHandle();//move
//		_updateOutHandle();//move
//	}
//
//	_setInHandleConstraint();//move,resize
//	_setOutHandleConstraint();//move,resize
//
	
	ofRange r;
	r.min = minPosToNormalizedValue();
	r.max = maxPosToNormalizedValue();
	
	if(r != handleValue)
	{
		handleValue = r;
		if(_clippedView)
		{
			_clippedView->setZoom(getOrientation(), handleValue);
		}
		ofNotifyEvent(handleChangeEvent, r, this);
	}
	
	
	
}

//
//void ZoomScrollbar::_onInHandleShapeChanged(DOM::ShapeChangeEventArgs&)
//{
//	if(inHandle->isDragging()){
//		auto hs = mainHandle->getSize();
//		auto hp = mainHandle->getPosition();
//		auto p = inHandle->getPosition();
//
//		hp[dimIndex()] = p[dimIndex()];
//		hs[dimIndex()] = mainHandle->getShape().getMax()[dimIndex()] - p[dimIndex()];
//
//		if(setShapeIfNonEqual(mainHandle, {hp, hs.x, hs.y})){
//			_updateOutHandle();
//		}
//	}
//}
//



//void ZoomScrollbar::_onOutHandleShapeChanged(DOM::ShapeChangeEventArgs&)
//{
//	if(outHandle->isDragging()){
//		auto hs = mainHandle->getSize();
//		auto hp = mainHandle->getPosition();
//		auto p = outHandle->getShape().getMax();
//
//		hs[dimIndex()] =  p[dimIndex()] - hp[dimIndex()];
//		setShapeIfNonEqual(mainHandle, {hp, hs.x, hs.y});
//	}
//}


bool ZoomScrollbar::setValue(const ofRange& val){
	if(handleValue == val) return false;
	handleValue = val;
	return _updateValue();
}


bool ZoomScrollbar::_updateValue()
{
	auto a = normalizedValueToMinPos(handleValue.min);
	auto b = normalizedValueToMaxPos(handleValue.max);
	if(a || b){
		ofNotifyEvent(handleChangeEvent, handleValue, this);
		return true;
	}
	return false;
}

bool ZoomScrollbar::scroll(float amt){
	
	float val = scrollSpeed * amt;
	return addToValue(val);
}


void ZoomScrollbar::_updateShape()
{
	if(_clippedView){
		auto s = _clippedView->getShape();
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
				
		updateValueFromClippedView();
		
	}
	else
	{
		ofLogError("ZoomScrollbar::_onClippedViewShapeChanged") << " _clipppedView is null.This should not happen";
	}
}


void ZoomScrollbar::_onClippedViewShapeChanged(DOM::ShapeChangeEventArgs&)
{
	_updateShape();
}


float ZoomScrollbar::minPosToNormalizedValue()
{
	return ofMap( mainHandle->getPosition()[dimIndex()], 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE , 0,1, true);
}


float ZoomScrollbar::maxPosToNormalizedValue(){
	return ofMap(mainHandle->getShape().getMax()[dimIndex()], HANDLE_MIN_SIZE, getSize()[dimIndex()] , 0,1, true);
}


bool ZoomScrollbar::normalizedValueToMinPos(float val){
	auto p = mainHandle->getPosition();
	p[dimIndex()] = ofMap(val, 0, 1, 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE ,  true);
	if(setPosIfNonEqual(mainHandle, p)){
		return true;
	}
	return false;
}


bool ZoomScrollbar::normalizedValueToMaxPos(float val){
	
	auto p = mainHandle->getShape().getMax();
	
	p[dimIndex()] = ofMap(val, 0, 1, HANDLE_MIN_SIZE, getSize()[dimIndex()],  true);
	if(setShapeIfNonEqual(mainHandle, {mainHandle->getPosition(), p})){
		return true;
	}
	return false;
}


void ZoomScrollbar::updateValueFromClippedView()
{
//	std::cout << "ZoomScrollbar::updateValueFromClippedView()\n";
//	ofRange r;
//	auto s = _clippedView->container->getShape();
//	r.min = ofMap(0, s.getMin()[dimIndex()], s.getMax()[dimIndex()], 0, 1, true);
//	auto span = ofClamp( _clippedView->getSize()[dimIndex()]/_clippedView->container->getSize()[dimIndex()], 0, 1);
//
//	r.max =r.min + span;
//
//	setValue(r);
	
}


void ZoomScrollbar::onDraw() const
{
	ofPushStyle();
	ofNoFill();
	ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER , Styles::STATE_NORMAL));
	ofDrawRectangle(0,0,getWidth(), getHeight());

	ofPopStyle();
}

//
//ZoomScrollbar::ZoomScrollbar(const std::string& id, DOM::Orientation orientation, ClippedView* clippedView)
//: DOM::Element(id, 0, 0, SCROLL_BAR_SIZE,SCROLL_BAR_SIZE)
//, DOM::OrientedElement(orientation)
//, _clippedView(clippedView)
//{
//
//	ofRectangle handleRect (0,0, SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
//
//	this->setFocusable(false);
//	//		this->setHighlightOnOver(true);
//
//	_mainHandle =  this->addChild<ConstrainedGrabHandle>(id+"_Z_scroll_handle_", orientation, handleRect);
//
//	DOM::RectEdge inEdge = (orientation == DOM::HORIZONTAL)?DOM::RECT_LEFT:DOM::RECT_TOP ;
//	DOM::RectEdge outEdge = (orientation == DOM::HORIZONTAL)?DOM::RECT_RIGHT:DOM::RECT_BOTTOM ;
//
//	_inHandle = this->addChild<EdgeHandle>(id+"_Z_in_handle_", inEdge, _mainHandle, ALIGN_INSIDE, false);
//	_outHandle = this->addChild<EdgeHandle>(id+"_Z_out_handle_", outEdge, _mainHandle, ALIGN_INSIDE, false);
//
//	_inConstraint = this->addChild<DOM::Element>("_inConstraint", handleRect);
//	_outConstraint = this->addChild<DOM::Element>("_outConstraint", handleRect);
//
//	_inHandle->constrainTo(_inConstraint);
//	_outHandle->constrainTo(_outConstraint);
//
//	_inHandle->setHandleSize(SCROLL_BAR_SIZE);
//	_outHandle->setHandleSize(SCROLL_BAR_SIZE);
//
//	_mainHandle->setMoveToFrontOnCapture(false);
//	_outHandle->setMoveToFrontOnCapture(false);
//	_inHandle->setMoveToFrontOnCapture(false);
//
//	_mainHandle->setConstrainedToParent(true);
////	_inHandle->setConstrainedToParent(true);
////	_outHandle->setConstrainedToParent(true);
//
//
//	_mainHandleListener = _mainHandle->shapeChanged.newListener(this, &ZoomScrollbar::_onMainHandleShapeChanged,std::numeric_limits<int>::lowest());
//
//
//	_mainHandle->moveToBack();
//
//
//	_clippedViewShapeListener = _clippedView->shapeChanged.newListener(this, &ZoomScrollbar::_onClippedViewShapeChanged);
//
//	_scrollListener = ofEvents().mouseScrolled.newListener(this, &ZoomScrollbar::_onScrollEvent,std::numeric_limits<int>::lowest());
//
//
//	_updateShape();
//}
//
//
//bool ZoomScrollbar::_onScrollEvent(ofMouseEventArgs & e){
//
//	if(getScreenShape().inside(e) || (_clippedView && _clippedView->getScreenShape().inside(e))){
//		return scroll((_orientation == DOM::HORIZONTAL)? e.scrollX: e.scrollY);
//	}
//	return false;
//}
//
//
//
//void ZoomScrollbar::_onMainHandleShapeChanged(DOM::ShapeChangeEventArgs& args)
//{
////	if(_mainHandle)
////	{
////		auto s = _mainHandle->getSize();
////		if( s[dimIndex()] < HANDLE_MIN_SIZE)
////		{
////
////
////			auto shape = _mainHandle->getShape();
////
////			ofRange r(shape.getMin()[dimIndex()], 1);
////			r.max = HANDLE_MIN_SIZE +r.min;
////
////			MUI::keepRangeMinSpan(r, float(HANDLE_MIN_SIZE), {0.f, getSize()[dimIndex()]});
////
////			s[dimIndex()] = r.max - r.min;
////
////			auto pos = shape.getPosition();
////			pos[dimIndex()] = r.min;
////
////			_mainHandle->setShape({ pos,s.x, s.y});
////			return;
////		}
////	}
//	if(args.resized())
//	{
//
//	if(_inConstraint){
//		auto s = getSize();
//		s[dimIndex()] = _mainHandle->getShape().getMax()[dimIndex()] - HANDLE_MIN_SIZE + SCROLL_BAR_SIZE;
//		_inConstraint->setShape({0,0,s.x, s.y});
//	}
//
//
//	if(_outConstraint)
//	{
//
//		auto s = getSize();
//		auto mn = _mainHandle->getShape().getMin();
//		mn[dimIndex()] += HANDLE_MIN_SIZE - SCROLL_BAR_SIZE;
//		s[dimIndex()] -= mn[dimIndex()];
//		_outConstraint->setShape({mn.x, mn.y, s.x, s.y});
//
//	}
//
//	}
//
//	ofRange r;
//	r.min = minPosToNormalizedValue();
//	r.max = maxPosToNormalizedValue();
//
//	if(r != handleValue)
//	{
//		handleValue = r;
//		ofNotifyEvent(handleChangeEvent, r, this);
//		if(_clippedView)
//		{
//			_clippedView->setZoom(getOrientation(), handleValue);
//		}
//	}
//}
//
//
//bool ZoomScrollbar::setValue(const ofRange& val){
//	if(handleValue == val) return false;
//	handleValue = val;
//	return _updateValue();
//}
//
//
//bool ZoomScrollbar::_updateValue()
//{
//	auto a = normalizedValueToMinPos(handleValue.min);
//	auto b = normalizedValueToMaxPos(handleValue.max);
//	if(a || b){
//		ofNotifyEvent(handleChangeEvent, handleValue, this);
//		return true;
//	}
//	return false;
//}
//
//bool ZoomScrollbar::scroll(float amt){
//
//	float val = scrollSpeed * amt;
//	return addToValue(val);
//}
//
//
//void ZoomScrollbar::_updateShape()
//{
//	if(_clippedView){
//		auto s = _clippedView->getShape();
//		ofRectangle shape;
//
//		if(_orientation == DOM::HORIZONTAL)
//		{
//			shape.set(s.x, s.getMaxY()+CONTAINER_MARGIN, s.width, SCROLL_BAR_SIZE);
//		}
//		else
//		{
//			shape.set(s.getMaxX()+CONTAINER_MARGIN, s.y, SCROLL_BAR_SIZE, s.height);
//		}
//
//		setShape(shape);
//
//		updateValueFromClippedView();
//
//	}
//	else
//	{
//		ofLogError("ZoomScrollbar::_onClippedViewShapeChanged") << " _clipppedView is null.This should not happen";
//	}
//}
//
//
//void ZoomScrollbar::_onClippedViewShapeChanged(DOM::ShapeChangeEventArgs&)
//{
//	_updateShape();
//}
//
//
//float ZoomScrollbar::minPosToNormalizedValue()
//{
//	return ofMap(_mainHandle->getPosition()[dimIndex()], 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE , 0,1, true);
//}
//
//
//float ZoomScrollbar::maxPosToNormalizedValue(){
//	return ofMap(_mainHandle->getShape().getMax()[dimIndex()], HANDLE_MIN_SIZE, getSize()[dimIndex()] , 0,1, true);
//}
//
//
//bool ZoomScrollbar::normalizedValueToMinPos(float val){
//	auto p = _mainHandle->getPosition();
//	p[dimIndex()] = ofMap(val, 0, 1, 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE ,  true);
//	return setPosIfNonEqual(_mainHandle, p);
//}
//
//
//bool ZoomScrollbar::normalizedValueToMaxPos(float val){
//
//	auto p = _mainHandle->getShape().getMax();
//
//	p[dimIndex()] = ofMap(val, 0, 1, HANDLE_MIN_SIZE, getSize()[dimIndex()],  true);
//	return setShapeIfNonEqual(_mainHandle, {_mainHandle->getPosition(), p});
//}
//
//
//void ZoomScrollbar::updateValueFromClippedView()
//{
////	std::cout << "ZoomScrollbar::updateValueFromClippedView()\n";
////	ofRange r;
////	auto s = _clippedView->container->getShape();
////	r.min = ofMap(0, s.getMin()[dimIndex()], s.getMax()[dimIndex()], 0, 1, true);
////	auto span = ofClamp( _clippedView->getSize()[dimIndex()]/_clippedView->container->getSize()[dimIndex()], 0, 1);
////
////	r.max =r.min + span;
////
////	setValue(r);
//
//}
//
//
//void ZoomScrollbar::onDraw() const
//{
//	ofPushStyle();
//	ofNoFill();
//	ofSetColor(getStyles()->getColor(Styles::ROLE_BORDER , Styles::STATE_NORMAL));
//	ofDrawRectangle(0,0,getWidth(), getHeight());
//
//	ofSetColor(ofColor::yellow);
//	ofDrawRectangle(_inConstraint->getShape());
//	ofSetColor(ofColor::magenta);
//	ofDrawRectangle(_outConstraint->getShape());
//
//	ofPopStyle();
//}



} } // ofx::MUI

//
