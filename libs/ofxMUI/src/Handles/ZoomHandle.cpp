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

}


void ZoomHandle::_onMainHandleShapeChanged(DOM::ShapeChangeEventArgs& r)
{
	ResizableHandle::_onMainHandleShapeChanged(r);
		handleValue.min = minPosToNormalizedValue();
		handleValue.max = maxPosToNormalizedValue();

		ofNotifyEvent(handleChangeEvent, handleValue, this);

}


bool ZoomHandle::setValue(const ofRange& val){
	if(handleValue == val) return false;
	handleValue = val;
	auto a = normalizedValueToMinPos(val.min);
	auto b = normalizedValueToMaxPos(val.max);
	if(a || b){
		ofNotifyEvent(handleChangeEvent, handleValue, this);
		return true;
	}
	return false;
	
}
} } // ofx::MUI

