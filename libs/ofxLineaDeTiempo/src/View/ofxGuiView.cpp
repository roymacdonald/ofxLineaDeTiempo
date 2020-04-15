//
//  ofxGuiView.cpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/12/20.
//

#include "LineaDeTiempo/View/ofxGuiView.h"


namespace ofx {
namespace LineaDeTiempo {

template<typename T>
ofxGuiView<T>::ofxGuiView(ofParameter<T>& param, float width)
:MUI::Widget(param.getName(), 0,0, width, 18)
{
	_gui.setup("ofxGuiGroup", "", 0,0);
	_gui.setWidthElements(width);
	_gui.add(param);
	_gui.disableHeader();
	_gui.unregisterMouseEvents();
//	std::cout << "ofxGuiView:  " << param.getName() << "\n";
	for(size_t i = 0; i < _gui.getNumControls(); ++i)
	{
		auto g = dynamic_cast<ofxGuiGroup*>(_gui.getControl(i));
		if(g){
//			g->disableHeader();
		}
	}
	setShape(_gui.getShape());
	
	setDraggable(true);
}


template<typename T>
void ofxGuiView<T>::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	
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
		_gui.mousePressed(args);
    }
	else if (e.type() == PointerEventArgs::POINTER_UP)
    {
		args.type = ofMouseEventArgs::Released;
		_gui.mouseReleased(args);
    }
	
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
        if (_isDragging)
        {
            if (!capturedPointers().empty())
            {
				args.type = ofMouseEventArgs::Dragged;
				_gui.mouseDragged(args);
				
            }
            else
            {
                ofLogError("Widget::_onPointerEvent") << "No captured pointers to drag with.";
            }
		}
		else
		{
			args.type = ofMouseEventArgs::Moved;
			_gui.mouseMoved(args);
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
ofxGuiGroup &  ofxGuiView<T>::getOfxGui()
{
	return _gui;
}


template<typename T>
const ofxGuiGroup &  ofxGuiView<T>::getOfxGui() const
{
	return _gui;
}


template<typename T>
void ofxGuiView<T>::onDraw() const
{
	if(parent() && parent()->getHeight() >= getHeight() + getY()){
		_gui.draw();
	}
}



template class ofxGuiView<glm::vec2>;
template class ofxGuiView<glm::vec3>;
template class ofxGuiView<glm::vec4>;

template class ofxGuiView<bool>;
//template class ofxGuiView<void>;


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

template class ofxGuiView<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;





template class ofxGuiView<ofColor>;
template class ofxGuiView<ofShortColor>;
template class ofxGuiView<ofFloatColor>;
template class ofxGuiView<ofRectangle>;




}}
