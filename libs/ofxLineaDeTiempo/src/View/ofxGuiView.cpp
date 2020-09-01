//
//  ofxGuiView.cpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/12/20.
//

#include "LineaDeTiempo/View/ofxGuiView.h"
#include "LineaDeTiempo/View/TrackHeader.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "LineaDeTiempo/Utils/ofxTypeTraits.h"

#include "ofxSliderGroup.h"


namespace ofx {
namespace LineaDeTiempo {

template<typename T>
ofxGuiView<T>::ofxGuiView(ofParameter<T>& param, float width, TrackHeader* trackHeader)
: MUI::Widget(param.getName(), 0,0, width, 18)
, _trackHeader(trackHeader)
{
	
	_makeGui(param, width);
	if(_gui)
	{
		_gui->setPosition(0,0);

		_gui->unregisterMouseEvents();
	
		_bOfxGuiIsMinimizable = (bool)(dynamic_cast<ofxGuiGroup*>(_gui.get()));
		if(_bOfxGuiIsMinimizable)
		{
			_gui->setBackgroundColor(ofColor::red);
		}
	}
	
	
	_ofxGuiShape = _gui->getShape();
	_ignoreOfxGuiShapeChange = true;
	setHeight(std::max(getHeight(), _gui->getHeight()));
	_ignoreOfxGuiShapeChange = false;
	
	setDraggable(true);
}

template<typename T>
void ofxGuiView<T>::_makeGui(ofParameter<T>& param, float width)
{
	_gui = std::make_unique<ofxSlider<T>>(param, width);
}
template<>
void ofxGuiView<ofColor>::_makeGui(ofParameter<ofColor>& param, float width){
	_gui = std::make_unique<ofxColorSlider>(param, width);
} 
template<>
void ofxGuiView<ofShortColor>::_makeGui(ofParameter<ofShortColor>& param, float width){
	_gui = std::make_unique<ofxShortColorSlider>(param, width);
} 
template<>
void ofxGuiView<ofFloatColor>::_makeGui(ofParameter<ofFloatColor>& param, float width){
	_gui = std::make_unique<ofxFloatColorSlider>(param, width);
} 
template<>
void ofxGuiView<ofDefaultVec3>::_makeGui(ofParameter<ofDefaultVec3>& param, float width){
	_gui = std::make_unique<ofxVec3Slider>(param, width);	
} 
template<>
void ofxGuiView<ofDefaultVec2>::_makeGui(ofParameter<ofDefaultVec2>& param, float width){
	_gui = std::make_unique<ofxVec2Slider>(param, width);	
} 
template<>
void ofxGuiView<ofDefaultVec4>::_makeGui(ofParameter<ofDefaultVec4>& param, float width){
	_gui = std::make_unique<ofxVec4Slider>(param, width);	
} 
template<>
void ofxGuiView<ofRectangle>::_makeGui(ofParameter<ofRectangle>& param, float width){
	_gui = std::make_unique<ofxRectangleSlider>(param, width);
}
template<>
void ofxGuiView<bool>::_makeGui(ofParameter<bool>& param, float width){
	_gui = std::make_unique<ofxToggle>(param, width);
}

template<>
void ofxGuiView<void>::_makeGui(ofParameter<void>& param, float width){
	_gui = std::make_unique<ofxButton>(param, width);		
}



template<typename T>
void ofxGuiView<T>::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	if(!_gui) return;
	
	ofMouseEventArgs args;
	auto p = screenToLocal(e.screenPosition());
	args.x =p.x;
	args.y =p.y;
	args.button = 0;
	
	auto buttons = e.pointer().buttons();
	for(int i = 0; i < 7; i++)
	{
		if((buttons >> i) & 1)
		{
			args.button = i ;
			
			break;
		}
	}
	
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
		args.type = ofMouseEventArgs::Pressed;
		_gui->mousePressed(args);
    }
	else if (e.type() == PointerEventArgs::POINTER_UP)
    {
		args.type = ofMouseEventArgs::Released;
		_gui->mouseReleased(args);
    }
	
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
        if (_isDragging)
        {
            if (!capturedPointers().empty())
            {
				args.type = ofMouseEventArgs::Dragged;
				_gui->mouseDragged(args);
				
            }
            else
            {
                ofLogError("Widget::_onPointerEvent") << "No captured pointers to drag with.";
            }
		}
		else
		{
			args.type = ofMouseEventArgs::Moved;
			_gui->mouseMoved(args);
		}
			
    }
    else if (e.type() == PointerEventArgs::POINTER_OVER)
    {
        _isPointerOver = true;
    }
    else if (e.type() == PointerEventArgs::POINTER_OUT)
    {
        _isPointerOver = false;
    }
    else
    {
        // unhandled.
    }
	
}


template<typename T>
void ofxGuiView<T>::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	if(_gui && !_ignoreOfxGuiShapeChange)
	{
		if(e.widthChanged())
		{
			_gui->setSize(getWidth(), _gui->getHeight());
		}
	}
}


template<typename T>
void ofxGuiView<T>::_updateShapeFromOfxGui()
{
	auto s = _gui->getShape();
	if( _ofxGuiShape != s)
	{
		_ofxGuiShape = s;
		_ignoreOfxGuiShapeChange =true;
		setHeight(_gui->getHeight());
		_ignoreOfxGuiShapeChange = false;
	}
	
}


template<typename T>
void ofxGuiView<T>::onUpdate()
{
	MUI::Widget::onUpdate();
	if(_bOfxGuiIsMinimizable){
		_updateShapeFromOfxGui();
	}
}

template<typename T>
void ofxGuiView<T>::onDraw() const
{
//	if(parent() && parent()->getHeight() >= getHeight() + getY()){
	if(_gui)// && getHeight() >= _gui->getHeight())
	{
		_gui->draw();
	}
}

template<typename T>
ofxBaseGui* ofxGuiView<T>::getOfxGui()
{
	return _gui.get();
}




template class ofxGuiView<glm::vec2>;
template class ofxGuiView<glm::vec3>;
template class ofxGuiView<glm::vec4>;

template class ofxGuiView<bool>;
template class ofxGuiView<void>;


template class ofxGuiView<int8_t>;
template class ofxGuiView<uint8_t>;
template class ofxGuiView<int16_t>;
template class ofxGuiView<uint16_t>;
template class ofxGuiView<int32_t>;
template class ofxGuiView<uint32_t>;
template class ofxGuiView<int64_t>;
template class ofxGuiView<uint64_t>;
template class ofxGuiView<float>;
template class ofxGuiView<double>;
#ifndef TARGET_LINUX
template class ofxGuiView<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;
#endif





template class ofxGuiView<ofColor>;
template class ofxGuiView<ofShortColor>;
template class ofxGuiView<ofFloatColor>;
template class ofxGuiView<ofRectangle>;




}}
