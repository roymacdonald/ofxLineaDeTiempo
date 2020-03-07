//
//  ConstrainedGrabHandle.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/5/20.
//

#include "ConstrainedGrabHandle.h"
#include "ofRectangleHelper.h"
#include "Utils.h"
namespace ofx {
namespace MUI {
//---------------------------------------------------------------------------------------------------
ConstrainedGrabHandle::ConstrainedGrabHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect):
	GrabHandle(id, rect),
	DOM::OrientedElement(orientation)
{
	setDraggable(true);

	setShapeDrawMode(ShapeDrawMode::ROUNDED_RECTANGLE);
	constrainTo(parent());
}
//---------------------------------------------------------------------------------------------------
ConstrainedGrabHandle::~ConstrainedGrabHandle()
{
}
//---------------------------------------------------------------------------------------------------
void ConstrainedGrabHandle::_onDragging(const DOM::CapturedPointer& pointer)
{
	if(bConstrainToParent && _constraint != parent() && hasParent()){
		setConstrainedToParent(true);
	}
	
	glm::vec2 newPos = getScreenPosition();
	newPos[dimIndex()] = (pointer.position()-pointer.offset())[dimIndex()];
	

	ofRectangle r (newPos, getWidth(), getHeight());
	
	
	
	if(_constraint){
			ofRectangle c = _constraint->getScreenShape();
			if(getOrientation() == DOM::HORIZONTAL)
			{
				if(DOM::ofRectangleHelper::keepInsideX(r, c)){
					newPos = r.getPosition();
				}
			}
			else
			{
				if(DOM::ofRectangleHelper::keepInsideY(r, c)){
					newPos = r.getPosition();
				}
			}
	}
	setPosition(screenToParent(newPos));
}
//---------------------------------------------------------------------------------------------------
void ConstrainedGrabHandle::constrainTo(DOM::Element* constraint)
{
	bConstrainToParent = parent() == constraint;
	_constraint = constraint;
}
//---------------------------------------------------------------------------------------------------
DOM::Element* ConstrainedGrabHandle::getConstraint()
{
	return _constraint;
}
//---------------------------------------------------------------------------------------------------
void ConstrainedGrabHandle::removeConstraint()
{
	_constraint = nullptr;
}
//---------------------------------------------------------------------------------------------------
void ConstrainedGrabHandle::setConstrainedToParent(bool bConstrained)
{
	bConstrainToParent = bConstrained;
	if(bConstrainToParent){
		constrainTo(parent());
	}else{
		removeConstraint();
	}
}
//---------------------------------------------------------------------------------------------------
bool ConstrainedGrabHandle::isConstrainedToParent()
{
	return bConstrainToParent;
}
//---------------------------------------------------------------------------------------------------

} } // ofx::MUI
