//
//  ResizableHandle.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/10/20.
//

#include "ResizableHandle.h"

#include "ofRectangleHelper.h"
#include "Constants.h"
#include "Utils.h"

namespace ofx {
namespace MUI {



ResizableHandle::ResizableHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect):
	Widget(id, rect),
	DOM::OrientedElement(orientation)
{
	ofRectangle r (0,0,SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
	
	
	this->setFocusable(false);
	this->setHighlightOnOver(true);
	
	inHandle = this->addChild<ConstrainedGrabHandle>(id+"_Z_in_handle_", orientation, r);
	outHandle = this->addChild<ConstrainedGrabHandle>(id+"_Z_out_handle_", orientation, r);
	mainHandle =  this->addChild<ConstrainedGrabHandle>(id+"_Z_scroll_handle_", orientation, rect);
	
	
	inHandle->setMoveToFrontOnCapture(false);
	outHandle->setMoveToFrontOnCapture(false);
	mainHandle->setMoveToFrontOnCapture(false);
	
	
	_inHandleConstraint = std::make_unique<Widget>("in_constraint", r);
	_outHandleConstraint = std::make_unique<Widget>("out_constraint", r);
	

	inHandle->constrainTo(_inHandleConstraint.get());
	outHandle->constrainTo(_outHandleConstraint.get());
	
	mainHandle->setConstrainedToParent(true);
	
	handlesListeners.push(inHandle->shapeChanged.newListener(this, &ResizableHandle::_onInHandleShapeChanged,std::numeric_limits<int>::lowest()));
	handlesListeners.push(outHandle->shapeChanged.newListener(this, &ResizableHandle::_onOutHandleShapeChanged,std::numeric_limits<int>::lowest()));
	
	handlesListeners.push(mainHandle->shapeChanged.newListener(this, &ResizableHandle::_onMainHandleShapeChanged,std::numeric_limits<int>::lowest()));
	
	
	mainHandle->moveToBack();
	_updateInHandle();
	_updateOutHandle();
}



void ResizableHandle::updateLayout(){
	if(!hasParent() || mainHandle == nullptr ) return;
	
	auto mn = minPosToNormalizedValue();
	auto mx = maxPosToNormalizedValue();
	
	this->setShape({0,0, parent()->getWidth(), parent()->getHeight()});
		
	mainHandle->moveToBack();
	
	if(!mainHandle->isDragging() && !inHandle->isDragging() && !outHandle->isDragging())
	{
	
		normalizedValueToMinPos(mn);
		normalizedValueToMaxPos(mx);
	}
	
}


void ResizableHandle::_setInHandleConstraint(){
	glm::vec2 size (SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
	glm::vec2 pos = getScreenPosition();//(0,0);
	
	size [dimIndex()]  = mainHandle->getScreenShape().getMax()[dimIndex()] - HANDLE_MIN_SIZE + SCROLL_BAR_SIZE;
	
	_inHandleConstraint->setShape(ofRectangle(pos.x, pos.y, size.x, size.y));
	
	inHandle->constrainTo(_inHandleConstraint.get());
	
}


void ResizableHandle::_setOutHandleConstraint(){
	glm::vec2 pos = getScreenPosition();//(0,0);
	glm::vec2 size (SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
	size[dimIndex()] = getSize()[dimIndex()] + pos[dimIndex()];
	
	pos[dimIndex()] = mainHandle->getScreenPosition()[dimIndex()] + HANDLE_MIN_SIZE - SCROLL_BAR_SIZE;
	
	size[dimIndex()] -= pos[dimIndex()];
	
	_outHandleConstraint->setShape(ofRectangle(pos.x, pos.y, size.x, size.y ));
	
	outHandle->constrainTo(_outHandleConstraint.get());
	
}


bool ResizableHandle::_updateInHandle()
{
	if(inHandle->isDragging())return false;
	return setPosIfNonEqual(inHandle, mainHandle->getPosition());
}


bool ResizableHandle::_updateOutHandle()
{
	if(outHandle->isDragging())return false;
	auto mx =mainHandle->getShape().getMax();
	mx[dimIndex()] -= SCROLL_BAR_SIZE;
	mx[1 - dimIndex()] = 0;

	return setPosIfNonEqual(outHandle, mx);
	
}

void ResizableHandle::_onMainHandleShapeChanged(DOM::ShapeChangeEventArgs& e)
{

	if(!e.resized()){
		_updateInHandle();//move
		_updateOutHandle();//move
	}
	
	_setInHandleConstraint();//move,resize
	_setOutHandleConstraint();//move,resize
}


void ResizableHandle::_onInHandleShapeChanged(DOM::ShapeChangeEventArgs&)
{
	if(inHandle->isDragging()){
		auto hs = mainHandle->getSize();
		auto hp = mainHandle->getPosition();
		auto p = inHandle->getPosition();

		hp[dimIndex()] = p[dimIndex()];
		hs[dimIndex()] = mainHandle->getShape().getMax()[dimIndex()] - p[dimIndex()];

		if(setShapeIfNonEqual(mainHandle, {hp, hs.x, hs.y})){
			_updateOutHandle();
		}
	}
}




void ResizableHandle::_onOutHandleShapeChanged(DOM::ShapeChangeEventArgs&)
{
	if(outHandle->isDragging()){
		auto hs = mainHandle->getSize();
		auto hp = mainHandle->getPosition();
		auto p = outHandle->getShape().getMax();

		hs[dimIndex()] =  p[dimIndex()] - hp[dimIndex()];
		setShapeIfNonEqual(mainHandle, {hp, hs.x, hs.y});
	}
}



float ResizableHandle::minPosToNormalizedValue(){
	return ofMap(mainHandle->getPosition()[dimIndex()], 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE , 0,1, true);
}


float ResizableHandle::maxPosToNormalizedValue(){
	return ofMap(mainHandle->getShape().getMax()[dimIndex()], HANDLE_MIN_SIZE, getSize()[dimIndex()] , 0,1, true);
}


bool ResizableHandle::normalizedValueToMinPos(float val){
	auto p = mainHandle->getPosition();
	p[dimIndex()] = ofMap(val, 0, 1, 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE ,  true);
	if(setPosIfNonEqual(mainHandle, p)){
		_updateInHandle();
		return true;
	}
	return false;
}


bool ResizableHandle::normalizedValueToMaxPos(float val){
	
	auto p = mainHandle->getShape().getMax();

	p[dimIndex()] = ofMap(val, 0, 1, HANDLE_MIN_SIZE, getSize()[dimIndex()],  true);
	if(setShapeIfNonEqual(mainHandle, {mainHandle->getPosition(), p})){
		_updateOutHandle();
		return true;
	}
	return false;
}





} } // ofx::MUI

