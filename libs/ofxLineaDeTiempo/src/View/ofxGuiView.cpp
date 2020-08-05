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
namespace ofx {
namespace LineaDeTiempo {

template<typename T>
ofxGuiView<T>::ofxGuiView(ofParameter<T>& param, float width, TrackHeader* trackHeader)
: MUI::Widget(param.getName(), 0,0, width, 18)
, _trackHeader(trackHeader)
{
	_gui.setup("ofxGuiGroup", "", 0,0);
	_gui.setWidthElements(width);
	_gui.add(param);
	_gui.disableHeader();
	_gui.unregisterMouseEvents();
	
	_bGuiWasMinimized = _gui.isMinimized();
	
	
//	for(size_t i = 0; i < _gui.getNumControls(); ++i)
//	{
//		auto g = dynamic_cast<ofxGuiGroup*>(_gui.getControl(i));
//		if(g){
//			g->disableHeader();
//		}
//	}
	setShape(_gui.getShape());
	
	_guiShape = getShape();
	
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
void ofxGuiView<T>::onUpdate()
{
	MUI::Widget::onUpdate();
	auto s = _gui.getShape();

	if(!ofIsFloatEqual(_guiShape.height, s.height) )
	{
		auto tempShape = getShape();
		tempShape.height = s.height;
		setShape(tempShape);

		_guiShape = s;


		if( _trackHeader)
		{
			auto t = dynamic_cast<TrackView*>(_trackHeader->getTrack());
			if(t)
			{

//				hacer las matematicas y logica de esto correctamente.

				bool bHeaderTallerThanGui =  _trackHeader->getHeight() >= getHeight() + getY();
				if(!_gui.isMinimized() && _bGuiWasMinimized )
				{
					if(!bHeaderTallerThanGui)
					{
						 if( _bGuiWasMinimized && !_gui.isMinimized())
							 _minimizedHeightFactor = t->getHeightFactor();

						t->setMinHeight(getHeight() + getY());
					}
				}
				else if( !_bGuiWasMinimized && _gui.isMinimized())
				{
					t->setHeightFactor(_minimizedHeightFactor);
				}
				
				_bGuiWasMinimized = _gui.isMinimized();
			}
		}
	}
}
template<typename T>
void ofxGuiView<T>::onDraw() const
{
//	if(parent() && parent()->getHeight() >= getHeight() + getY()){
		_gui.draw();
//	}
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
