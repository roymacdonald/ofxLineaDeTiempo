//
//  EdgeHandle.cpp
//  edgeHandle
//
//  Created by Roy Macdonald on 2/21/20.
//

#include "EdgeHandle.h"


namespace ofx {
namespace MUI {

const uint64_t EdgeHandle::onOverDrawDelay = 100;

//---------------------------------------------------------------------------------------
EdgeHandle::EdgeHandle(const std::string& id, DOM::RectEdge edge, DOM::Element* target, EdgeHandleAlignment edgeAlignment, bool bAutoHide)
: ConstrainedGrabHandle(id, DOM::ofRectangleHelper::getOrientationFromEdge(edge), ofRectangle(0,0, EDGE_HANDLE_SIZE, EDGE_HANDLE_SIZE))
, _target(target)
, _edge(edge)
, _edgeAlignment(edgeAlignment)
{
	
//	for(auto&s: siblings())
//	{
//		if(s == _target)
//		{
//			_targetIsSibling = true;
//			break;
//		}
//	}
	
	auto t = dynamic_cast<ConstrainedGrabHandle*>(_target);
	if(t)
	{
		_targetConstraint = t->getConstraint();
	}
	setConstrainedToParent(false);
	_targetListener = target->shapeChanged.newListener(this, &EdgeHandle::_targetShapeChanged);
	setAutoHide(bAutoHide);
	setAnchors();
	updateLayout();
}

void EdgeHandle::setAnchors()
{	
	if (_edge == DOM::RECT_TOP)
	{
		vTargetAnchor = OF_ALIGN_VERT_TOP;
		hTargetAnchor = OF_ALIGN_HORZ_IGNORE;
		hThisAnchor = OF_ALIGN_HORZ_IGNORE;

		switch (_edgeAlignment)
		{
			case ALIGN_INSIDE: vThisAnchor = vTargetAnchor; break;
			case ALIGN_CENTER: vThisAnchor = OF_ALIGN_VERT_CENTER; break;
			case ALIGN_OUTSIDE: vThisAnchor = OF_ALIGN_VERT_BOTTOM; break;
		}		

	}
	else if (_edge == DOM::RECT_BOTTOM)
	{
		vTargetAnchor = OF_ALIGN_VERT_BOTTOM;
		hTargetAnchor = OF_ALIGN_HORZ_IGNORE;
		hThisAnchor = OF_ALIGN_HORZ_IGNORE;

		switch (_edgeAlignment)
		{
			case ALIGN_INSIDE: vThisAnchor = vTargetAnchor; break;
			case ALIGN_CENTER: vThisAnchor = OF_ALIGN_VERT_CENTER; break;
			case ALIGN_OUTSIDE: vThisAnchor = OF_ALIGN_VERT_TOP; break;
		}

		// vThisAnchor
	}
	else if (_edge == DOM::RECT_RIGHT)
	{
		hTargetAnchor = OF_ALIGN_HORZ_RIGHT;
		vTargetAnchor = OF_ALIGN_VERT_IGNORE;
		vThisAnchor = OF_ALIGN_VERT_IGNORE;

		switch (_edgeAlignment)
		{
			case ALIGN_INSIDE: hThisAnchor = hTargetAnchor; break;
			case ALIGN_CENTER: hThisAnchor = OF_ALIGN_HORZ_CENTER; break;
			case ALIGN_OUTSIDE: hThisAnchor = OF_ALIGN_HORZ_LEFT; break;
		}

		
	}
	else if (_edge == DOM::RECT_LEFT)
	{
		hTargetAnchor = OF_ALIGN_HORZ_LEFT;
		vTargetAnchor = OF_ALIGN_VERT_IGNORE;
		vThisAnchor = OF_ALIGN_VERT_IGNORE;

	switch (_edgeAlignment)
		{
			case ALIGN_INSIDE: hThisAnchor = hTargetAnchor; break;
			case ALIGN_CENTER: hThisAnchor = OF_ALIGN_HORZ_CENTER; break;
			case ALIGN_OUTSIDE: hThisAnchor = OF_ALIGN_HORZ_RIGHT; break;
		}

	}
}

void EdgeHandle::_targetShapeChanged(DOM::ShapeChangeEventArgs&)
{
	if(isDragging()) return;
	if(_target)
	{
		_followingTarget = true;
		updateLayout();
		_followingTarget = false;
	}
}


void EdgeHandle::_onDragging(const DOM::CapturedPointer& pointer)
{
	ConstrainedGrabHandle::_onDragging(pointer);
	if(_target)
	{
		float val = 0;
		
		DOM::Position p;
		
		auto s = getShape();
		
		
		if(_edgeAlignment == ALIGN_CENTER)
		{
			p =  getCenterPosition();
		}
		
		else if(_edgeAlignment == ALIGN_OUTSIDE)
		{
			if(_edge == DOM::RECT_TOP || _edge == DOM::RECT_LEFT)
			{
				p = s.getMax();
			}else
			{
				p= s.getMin();
			}
		}
		else if(_edgeAlignment == ALIGN_INSIDE)
		{
			if(_edge == DOM::RECT_TOP || _edge == DOM::RECT_LEFT)
			{
				p = s.getMin();
			}else
			{
				p= s.getMax();
			}
		}
		auto screenPos =  parentToScreen(p);

		bool needsUpdateLayout = false;
		
		if(_targetConstraint){
			auto ts = _targetConstraint->getScreenShape();
			auto sp = ofClamp(screenPos[dimIndex()], ts.getMin()[dimIndex()], ts.getMax()[dimIndex()]);
			if(!ofIsFloatEqual(screenPos[dimIndex()] , sp))
			{
				needsUpdateLayout = true;
				screenPos[dimIndex()] = sp;
			}
			
		}
		p = _target->screenToParent( screenPos);
		
		auto result = DOM::ofRectangleHelper::setEdge(_target, p[dimIndex()] , _edge, _targetMinSizeEnabled, _targetMinSize);
		
		if(needsUpdateLayout || result == DOM::SET_EDGE_MIN) updateLayout();
		
	}
}


void EdgeHandle::updateLayout()
{
	if(_target){
		auto s = _target->getShape();
		ofRectangle r = s;
		
		if(_target == parent())
		{
			s.setPosition(0, 0);
		}
		else
		{
			auto p = _target->parentToScreen(r.getPosition());
			p = this->screenToParent(p);
			s.setPosition(p.x, p.y);
		}
		
		if (_edge == DOM::RECT_TOP || _edge == DOM::RECT_BOTTOM)
		{
			r.height = _handleSize;
			r.alignToVert(s, vTargetAnchor, vThisAnchor );
		}else{
			r.width = _handleSize;
			r.alignToHorz(s, hTargetAnchor, hThisAnchor );
		}
		
		setShape(r);
	}
}


void EdgeHandle::setHandleSize(float handleSize)
{
	_handleSize = handleSize;
	updateLayout();
}


float EdgeHandle::getHandleSize() const
{
	return _handleSize;
}



void EdgeHandle::_onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
	Widget::_onPointerCaptureEvent(e);
	if(_bAutoHide){
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
}


void EdgeHandle::onUpdate(){
	if(_bAutoHide){
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
}


void EdgeHandle::setAutoHide(bool autoHide)
{
	_bAutoHide = autoHide;
	setHidden(_bAutoHide);
	
}

void EdgeHandle::enableAutoHide()
{
	setAutoHide(true);
}


void EdgeHandle::disableAutoHide()
{
	setAutoHide(false);
}


bool EdgeHandle::isAutoHidding()
{
	return _bAutoHide;
}


bool EdgeHandle::isFollowingTarget()
{
	return _followingTarget;
}


void EdgeHandle::setAlignment( EdgeHandleAlignment edgeAlignment)
{
	_edgeAlignment = edgeAlignment;
	setAnchors();
	updateLayout();
}


EdgeHandleAlignment EdgeHandle::getAlignment() const
{
	return _edgeAlignment;
}


void EdgeHandle::setTargetMinSize(float minSize)
{
	_targetMinSizeEnabled = true;
	_targetMinSize = minSize;
}


float EdgeHandle::getTargetMinSize() const
{
	return _targetMinSize;
}


bool EdgeHandle::hasTargetMinSize() const
{
	return _targetMinSizeEnabled;
}


void EdgeHandle::removeTargetMinSize()
{
	_targetMinSizeEnabled = false;
}


void EdgeHandle::setTargetConstraint(DOM::Element* constraint)
{
	_targetConstraint = constraint;
}


DOM::Element* EdgeHandle::getTargetConstraint()
{
	return _targetConstraint;
}


} } // ofx::MUI
