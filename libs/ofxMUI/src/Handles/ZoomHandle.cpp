//
//  ScrollbarHandle.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#include "ZoomHandle.h"

#include "ofRectangleHelper.h"
#include "Constants.h"
#include "Utils.h"

namespace ofx {
namespace MUI {

//---------------------------------------------------------------------------------------------------------------------
ZoomHandle::ZoomHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect):
	ResizableHandle(id, orientation, rect),
	BaseScrollHandle<ofRange>()
{
//	std::cout <<  "ZoomHandle::ZoomHandle  " << getId() << "  " << rect << "\n";
//	setValue({0,1});
}
//---------------------------------------------------------------------------------------------------------------------
void ZoomHandle::_onMainHandleMoved(DOM::MoveEventArgs& m){
	ResizableHandle::_onMainHandleMoved(m);
	_mainHandleChanged();
}

//---------------------------------------------------------------------------------------------------------------------
void ZoomHandle::_onMainHandleResize(DOM::ResizeEventArgs& m){
	ResizableHandle::_onMainHandleResize(m);
	_mainHandleChanged();
}
//---------------------------------------------------------------------------------------------------------------------
void ZoomHandle::_mainHandleChanged(){
	handleValue.min = minPosToNormalizedValue();
	handleValue.max = maxPosToNormalizedValue();
//	setValue({a, b});
//	if(a || b){
		ofNotifyEvent(handleChangeEvent, handleValue, this);
//	}
}
//---------------------------------------------------------------------------------------------------------------------
//void ZoomHandle::setZoomMin(float mn){
//	handleValue.min = mn;
//	_valueToMinPos();
//}
////---------------------------------------------------------------------------------------------------------------------
//void ZoomHandle::setZoomMax(float mx){
//	handleValue.max = mx;
//	_valueToMaxPos();
//}
////---------------------------------------------------------------------------------------------------------------------
//const ofRange& ZoomHandle::getZoom()const{
//	return handleValue;
//}
//---------------------------------------------------------------------------------------------------------------------
bool ZoomHandle::setValue(const ofRange& val){
	if(handleValue == val)return false;
	handleValue = val;
	auto a = normalizedValueToMinPos(val.min);
	auto b = normalizedValueToMaxPos(val.max);
	if(a || b){
		ofNotifyEvent(handleChangeEvent, handleValue, this);
		return true;
	}
	return false;
	
	//	handleValue = zoom;
	
//	if(a || b){
//		ofNotifyEvent(handleChangeEvent, handleValue, this);
//	}
}
////---------------------------------------------------------------------------------------------------------------------
//float ZoomHandle::_minPosToValue(){
//	return ofMap(mainHandle->getPosition()[dimIndex()], 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE , 0,1, true);
////	if(setFloatIfNonEqual(handleValue.min, mn)){
//////		if(bNotify)ofNotifyEvent(handleChangeEvent, handleValue, this);
////		return true;
////	}
////	return false;
//}
////---------------------------------------------------------------------------------------------------------------------
//float ZoomHandle::_maxPosToValue(){
//	return ofMap(mainHandle->getShape().getMax()[dimIndex()], HANDLE_MIN_SIZE, getSize()[dimIndex()] , 0,1, true);
////	if(setFloatIfNonEqual(handleValue.max, mx)){
//////		if(bNotify)ofNotifyEvent(handleChangeEvent, handleValue, this);
////		return true;
////	}
////	return false;
//}
//---------------------------------------------------------------------------------------------------------------------
//bool ZoomHandle::_valueToMinPos(float val){
//	auto p = mainHandle->getPosition();
//	p[dimIndex()] = ofMap(val, 0, 1, 0, getSize()[dimIndex()] - HANDLE_MIN_SIZE ,  true);
//	if(setPosIfNonEqual(mainHandle, p)){
//		_updateInHandle();
//		return true;
//	}
//	return false;
//}
////---------------------------------------------------------------------------------------------------------------------
//bool ZoomHandle::_valueToMaxPos(float val){
//
//	auto p = mainHandle->getShape().getMax();
//
//	p[dimIndex()] = ofMap(handleValue.max, HANDLE_MIN_SIZE, getSize()[dimIndex()], 0, 1,  true);
//	if(setShapeIfNonEqual(mainHandle, {mainHandle->getPosition(), p})){
//		_updateOutHandle();
//		return true;
//	}
//	return false;
//}
////---------------------------------------------------------------------------------------------------------------------
} } // ofx::MUI

