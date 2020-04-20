//
//  ScrollHandle.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/9/20.
//

#include "ScrollHandle.h"
#include "Utils.h"
namespace ofx {
namespace MUI {
//---------------------------------------------------------------------------------------------------------------------
ScrollHandle::ScrollHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect)
:ConstrainedGrabHandle(id, orientation, rect)
,BaseScrollHandle<float>()
{
}
//---------------------------------------------------------------------------------------------------------------------
void ScrollHandle::_onDragging(const DOM::CapturedPointer& pointer){
	ConstrainedGrabHandle::_onDragging(pointer);
	_updateValueFromScroll();
}
//---------------------------------------------------------------------------------------------------------------------
bool ScrollHandle::_updateValueFromScroll(){
	if(!hasParent())return false;
	auto p_size = parent()->getSize();
	if(setFloatIfNonEqual(handleValue, ofMap(getPosition()[dimIndex()], 0, p_size[dimIndex()] - getSize()[dimIndex()], 0, 1, true ))){
		ofNotifyEvent(handleChangeEvent, handleValue, this);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
bool ScrollHandle::_updateScrollFromValue(){
	if(!hasParent())return  false;
	auto p_size = parent()->getSize();
	
	glm::vec2 pos(0,0);
	
	pos[dimIndex()] = ofMap(handleValue, 0, 1, 0, p_size[dimIndex()] - getSize()[dimIndex()], true );
	return setPosIfNonEqual(this, pos);
}
//---------------------------------------------------------------------------------------------------------------------
void ScrollHandle::updateLayout(){
	if(this->isDragging())return;
	_updateScrollFromValue();
}
bool ScrollHandle::setValue(const float& val ){
	if(setFloatIfNonEqual(handleValue, val)){
		ofNotifyEvent(handleChangeEvent, handleValue, this);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
} } // ofx::MUI
