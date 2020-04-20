//
//  EdgeHandle.cpp
//  edgeHandle
//
//  Created by Roy Macdonald on 2/21/20.
//

#include "EdgeHandle.h"
#include "Constants.h"

namespace ofx {
namespace MUI {

const uint64_t EdgeHandle::onOverDrawDelay = 100;

//---------------------------------------------------------------------------------------
EdgeHandle::EdgeHandle(const std::string& id, DOM::RectEdge edge, DOM::Element* target):
ConstrainedGrabHandle(id, DOM::ofRectangleHelper::getOrientationFromEdge(edge), getEdgeRect(target, edge)),
_target(target),
_edge(edge)
{
	setConstrainedToParent(false);
	_targetListener = target->shapeChanged.newListener(this, &EdgeHandle::_targetShapeChanged);
	setHidden(true);
}


void EdgeHandle::_targetShapeChanged(DOM::ShapeChangeEventArgs&)
{
	if(isDragging()) return;
	if(_target)
	{
		_followingTarget = true;
		setShape(getEdgeRect(_target, _edge));
		_followingTarget = false;
	}
}


void EdgeHandle::_onDragging(const DOM::CapturedPointer& pointer)
{
	ConstrainedGrabHandle::_onDragging(pointer);
	if(parent()){
		float val = 0;
		auto c = getCenterPosition() +  parent()->getPosition();
		
		if(_edge == DOM::RECT_TOP || _edge == DOM::RECT_BOTTOM)
		{
			val = c.y;
		}
		else
		{
			val = c.x;
		}
		
		
		DOM::ofRectangleHelper::setEdge(_target, val , _edge, false);
		
		
	}
}


ofRectangle EdgeHandle::getEdgeRect(DOM::Element* element, DOM::RectEdge edge)
{
	ofRectangle r;
	if(element){
		if (edge == DOM::RECT_TOP)
		{
			r.set(0, - EDGE_HANDLE_SIZE*0.5, element->getWidth(), EDGE_HANDLE_SIZE);
		}
		else if (edge == DOM::RECT_BOTTOM)
		{
			r.set(0, element->getHeight() - EDGE_HANDLE_SIZE*0.5, element->getWidth(), EDGE_HANDLE_SIZE);
		}
		else if (edge == DOM::RECT_RIGHT)
		{
			r.set( element->getWidth() - EDGE_HANDLE_SIZE*0.5, 0,EDGE_HANDLE_SIZE, element->getHeight());
		}
		else if (edge == DOM::RECT_LEFT)
		{
			r.set( - EDGE_HANDLE_SIZE*0.5, 0,EDGE_HANDLE_SIZE, element->getHeight());
		}
		return r;
	}
	ofLogError("EdgeHandle::getEdgeRect") << "failed. parent is null";
	return r;
	
}


void EdgeHandle::_onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
	Widget::_onPointerCaptureEvent(e);
	
	if (e.type() == PointerEventArgs::GOT_POINTER_CAPTURE && _pointerCaptureTime == 0)
	{
		_pointerCaptureTime = ofGetElapsedTimeMillis();
		
	}
	else if (e.type() == PointerEventArgs::LOST_POINTER_CAPTURE)
	{
		_pointerCaptureTime = 0;
		setHidden(true);
	}
}


void EdgeHandle::onUpdate(){
	if(!_wasPointerOver && isPointerOver()){
		_wasPointerOver = true;
		_pointerCaptureTime = ofGetElapsedTimeMillis();
		
	}else if(_wasPointerOver && !isPointerOver() && !isDragging()){
		_wasPointerOver = false;
		_pointerCaptureTime = 0;
		
		setHidden(true);
	}
	if(_pointerCaptureTime > 0){
		
		if(isHidden() && ofGetElapsedTimeMillis() - _pointerCaptureTime > onOverDrawDelay){
			setHidden(false);
		}
	}
}


bool EdgeHandle::isFollowingTarget()
{
	return _followingTarget;
}

} } // ofx::MUI
