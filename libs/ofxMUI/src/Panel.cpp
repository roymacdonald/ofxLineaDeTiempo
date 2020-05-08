//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Panel.h"
#include "ofGraphics.h"
#include "ConstVars.h"
#include "LineaDeTiempo/View/TracksPanel.h"


namespace ofx {
namespace MUI {





template<typename T>
void Panel<T>::updateLayout()
{
	_setHeaderHandleShape();
	_setCornerHandleViewRect();
}



template<typename T>
void Panel<T>::setEnableHeaderHandle(bool enable)
{
	if(enable)
	{
		_addHeaderHandle();
	}
	else
	{
		_removeHeaderHandle();
	}
}


template<typename T>
bool Panel<T>::hasHeaderHandle() const
{
	return (bool) _headerHandle;
}


template<typename T>
void Panel<T>::_setHeaderHandleShape()
{
	if(_headerHandle)
	{
		_headerHandle->setShape({0,0, getWidth(), LineaDeTiempo::ConstVars::ViewTopHeaderHeight});
	}
}


template<typename T>
void Panel<T>::_cornerHandleChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_ignoreCornerHandleChange && e.moved())
	{
		_ignoreCornerHandleChange = true;
		
//		auto ps = getScreenPosition();
		auto c = _cornerHandle->getShape().getMax();
		
		
		setSize(c.x , c.y);
		
		_ignoreCornerHandleChange = false;
	}
}


template<typename T>
void Panel<T>::_headerHandleChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_ignoreHeaderHandleChange && e.moved())
	{
		_ignoreHeaderHandleChange = true;
		setPosition( getPosition() + _headerHandle->getPosition());
		_headerHandle->setPosition(0, 0);
		_ignoreHeaderHandleChange = false;
	}
}

template<typename T>
void Panel<T>::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	updateLayout();
	_updateContainerShape();
}

template<typename T>
void Panel<T>::_updateContainerShape()
{
	if(container)
	{
		float h  = ((bool)_headerHandle)?_headerHandle->getHeight():0;
		container->setShape(ofRectangle(0, h, getWidth(), getHeight()-h));
	}
}

template<typename T>
void Panel<T>::_addHeaderHandle()
{
	if(_headerHandle == nullptr)
	{
		_headerHandle = addChild<Label>("ofxLineaDeTiempo");
		_headerHandle->setDraggable(true);
		
		if(_headerLabel.empty())
		{
			_headerLabel = getId();
		}
		
		_headerHandle->setText(_headerLabel);
		
		_setHeaderHandleShape();

		_updateContainerShape();
		
		_headerHandleListener = _headerHandle->shapeChanged.newListener(this, &Panel::_headerHandleChanged);
	}
}


template<typename T>
void Panel<T>::_removeHeaderHandle()
{
	if(_headerHandle && container)
	{
		container->setPosition(0, 0);
		setHeight(getHeight() - _headerHandle->getHeight() );
		
		removeChild(_headerHandle);
		_headerHandleListener.unsubscribe();
		_headerHandle = nullptr;
		
		_updateContainerShape();
		
	}
}

template<typename T>
void Panel<T>::setHeaderLabel(const std::string& label)
{
	_headerLabel = label;
	_headerHandle->setText(_headerLabel);
}


template<typename T>
const std::string& Panel<T>::getHeaderLabel() const
{
	return _headerLabel;
}

template<typename T>
void Panel<T>::_addCornerHandle()
{
	if(_cornerHandle == nullptr)
	{
		_cornerHandle = addChild<Widget>("Corner Handle", ofRectangle());
		_setCornerHandleViewRect();
		_cornerHandle->setDraggable(true);
		
		_cornerHandleListener = _cornerHandle->shapeChanged.newListener(this, &Panel::_cornerHandleChanged);
	}
}


template<typename T>
void Panel<T>::_removeCornerHandle()
{
	if(_cornerHandle)
	{
		removeChild(_cornerHandle);
		_cornerHandleListener.unsubscribe();
		_cornerHandle = nullptr;
	}
}


template<typename T>
void Panel<T>::_setCornerHandleViewRect()
{
	
	if(_cornerHandle)
	{
		_cornerHandle->setShape({getWidth() - _cornerHandleSize, getHeight() - _cornerHandleSize, _cornerHandleSize, _cornerHandleSize});
		_cornerHandle->moveToFront();
	}
}

template<typename T>
void Panel<T>::setCornerHandleSize(float cornerHandleSize )
{
	_cornerHandleSize = cornerHandleSize;
	updateLayout();
}


template<typename T>
float Panel<T>::getCornerHandleSize() const
{
	return _cornerHandleSize;
}


template<typename T>
void Panel<T>::setResizable(bool resizable)
{
	
	if(_resizeable != resizable)
	{
		_resizeable = resizable;
		if(_resizeable)
		{
			_addCornerHandle();
		}
		else
		{
			_removeCornerHandle();
		}
		updateLayout();
	}
}


template<typename T>
bool Panel<T>::isResizable() const
{
	return _resizeable;
}

template class Panel<LineaDeTiempo::TracksPanel>;

} } // namespace ofx::MUI

