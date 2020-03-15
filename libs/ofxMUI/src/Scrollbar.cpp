//
//  Scrollbar.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/5/20.
//

#include "Scrollbar.h"

#include "ScrollablePanel.h"
#include "Constants.h"
#include "Utils.h"
namespace ofx {
namespace MUI {
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
float Scrollbar_<HandleType, ScrollData>::scrollSpeed = 0.02;
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
Scrollbar_<HandleType, ScrollData>::Scrollbar_(const std::string& id,
					 DOM::Orientation orientation):
Widget(id, 0, 0, SCROLL_BAR_SIZE,SCROLL_BAR_SIZE)
//_orientation(orientation)
{
//	FUNC_NAME_TO_DEBUG_STRING
	this->setFocusable(false);
	ofRectangle handleRect (0,0, SCROLL_BAR_SIZE, SCROLL_BAR_SIZE);
	
	if(orientation == DOM::Orientation::HORIZONTAL){
		handleRect.width = HANDLE_MIN_SIZE;
	}else{
		handleRect.height = HANDLE_MIN_SIZE;
	}
	
	_handle = this->addChild<HandleType>(id+"_handle", orientation, handleRect);
	
	scrollListener = ofEvents().mouseScrolled.newListener(this, &Scrollbar_<HandleType, ScrollData>::_onScrollEvent,std::numeric_limits<int>::lowest());

	shapeChangeListeners.push(Widget::move.newListener(this, &Scrollbar_<HandleType, ScrollData>::_onMove, std::numeric_limits<int>::lowest()));
	shapeChangeListeners.push(Widget::resize.newListener(this, &Scrollbar_<HandleType, ScrollData>::_onResize, std::numeric_limits<int>::lowest()));
	
	setHighlightOnOver(false);
	
}

//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
void Scrollbar_<HandleType, ScrollData>::updateLayout(const ofRectangle& rect){
	
	if(rect != this->getShape()){
//	std::cout << "Scrollbar_::updateLayout   " << rect << "\n";
	
		this->setShape(rect);
		if(_handle) _handle->updateLayout();
	}
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
void Scrollbar_<HandleType, ScrollData>::onUpdate(){
//	FUNC_NAME_TO_DEBUG_STRING
		if(bUpdateLayout){
			invalidateChild();
			bUpdateLayout = false;
		}
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
DOM::Orientation Scrollbar_<HandleType, ScrollData>::getOrientation() const{
//	FUNC_NAME_TO_DEBUG_STRING
	if(_handle){
		return _handle->getOrientation();
	}
	return DOM::Orientation::HORIZONTAL;
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
void Scrollbar_<HandleType, ScrollData>::setOrientation(DOM::Orientation orientation){
//	FUNC_NAME_TO_DEBUG_STRING
	if(_handle){
		_handle->setOrientation(orientation);
	}
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
void Scrollbar_<HandleType, ScrollData>::_onResize(DOM::ResizeEventArgs&){
//	FUNC_NAME_TO_DEBUG_STRING
	if(_handle){
		_handle->updateLayout();
	}
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
void Scrollbar_<HandleType, ScrollData>::_onMove(DOM::MoveEventArgs&){
//	FUNC_NAME_TO_DEBUG_STRING
	if(_handle){
		_handle->updateLayout();
	}
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
bool Scrollbar_<HandleType, ScrollData>::_onScrollEvent(ofMouseEventArgs & e){
	auto shape = getScreenShape();
//	std::cout << "scroll event " << glm::vec2(e) << " " << e.scrollX << " - " << e.scrollY;
	if(shape.inside(e)){
//		std::cout << "   inside\n";
		
//		int index = (getOrientation() == DOM::HORIZONTAL)?0:1;
//		auto pos = _handle->getPosition();
//		auto val = _handle->getValue();
//		float val = 0.05* ((_handle->getOrientation() == DOM::HORIZONTAL)? e.scrollX: e.scrollY);
//		pos[index] = ofClamp(pos[index] + (, 0, getSize()[index]);
//		return _handle->addToValue(val);
		return scroll((_handle->getOrientation() == DOM::HORIZONTAL)? e.scrollX: e.scrollY);
//		return true;
	}
//	std::cout << "\n";
	return false;
}
template<typename HandleType, typename ScrollData>
bool Scrollbar_<HandleType, ScrollData>::scroll(float amt){
	
		float val = scrollSpeed * amt;
		return _handle->addToValue(val);
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
void Scrollbar_<HandleType, ScrollData>:: setValue(const ScrollData& val ){
	if(_handle) _handle->setValue(val);
}
//---------------------------------------------------------------------------------------------------
template<typename HandleType, typename ScrollData>
const ScrollData& Scrollbar_<HandleType, ScrollData>::getValue() const {
	if(_handle)return _handle->getValue();
}

template class Scrollbar_<ScrollHandle, float>;
template class Scrollbar_<ZoomHandle, ofRange>;


} } // ofx::MUI
//
