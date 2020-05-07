//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Panel.h"
#include "ofGraphics.h"
#include "ConstVars.h"

namespace ofx {
namespace MUI {



Panel::Panel(const std::string& id, const ofRectangle& rect):
DOM::Element(id, rect)
{
	container = addChild<AutoReziseContainer>(id+ "_container", ofRectangle(0, 0, rect.width, rect.height));
	
}




void Panel::updateLayout()
{
	_setHeaderHandleShape();
	_setCornerHandleViewRect();
}



void Panel::setEnableHeaderHandle(bool enable)
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


bool Panel::hasHeaderHandle() const
{
	return (bool) _headerHandle;
}


void Panel::_setHeaderHandleShape()
{
	if(_headerHandle)
	{
		_headerHandle->setShape({0,0, getWidth(), LineaDeTiempo::ConstVars::ViewTopHeaderHeight});
	}
}


void Panel::_cornerHandleChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_ignoreCornerHandleChange && e.moved() && parent())
	{
		_ignoreCornerHandleChange = true;
		
		auto ps = parent()->getScreenPosition();
		auto c = _cornerHandle->getScreenShape().getMax();
		
		
		setSize(c.x -ps.x, c.y -ps.y);
		
		_ignoreCornerHandleChange = false;
	}
}


void Panel::_headerHandleChanged(DOM::ShapeChangeEventArgs& e)
{
	if(!_ignoreHeaderHandleChange && e.moved() && parent())
	{
		_ignoreHeaderHandleChange = true;
		parent()->setPosition( _headerHandle->getScreenPosition());
		_headerHandle->setPosition(0, 0);
		_ignoreHeaderHandleChange = false;
	}
}

void Panel::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	updateLayout();
	if(container)
	{
		float h  = ((bool)_headerHandle)?_headerHandle->getHeight():0;
		container->setShape(ofRectangle(0, h, getWidth(), getHeight()-h));
	}
}


void Panel::_addHeaderHandle()
{
	if(_headerHandle == nullptr)
	{
		std::cout << "Panel::_addHeaderHandle()\n";
		_headerHandle = addChild<Label>("ofxLineaDeTiempo");
		_headerHandle->setDraggable(true);
		
		if(_headerLabel.empty())
		{
			_headerLabel = getId();
		}
		
		_headerHandle->setText(_headerLabel);
		
		_setHeaderHandleShape();
//		container->setPosition(0, _headerHandle->getHeight());
		setHeight(getHeight() + _headerHandle->getHeight() );
		
		_headerHandleListener = _headerHandle->shapeChanged.newListener(this, &Panel::_headerHandleChanged);
	}
}


void Panel::_removeHeaderHandle()
{
	if(_headerHandle)
	{
		container->setPosition(0, 0);
		setHeight(getHeight() - _headerHandle->getHeight() );
		
		removeChild(_headerHandle);
		_headerHandleListener.unsubscribe();
		_headerHandle = nullptr;
		
	}
}

void Panel::setHeaderLabel(const std::string& label)
{
	_headerLabel = label;
	_headerHandle->setText(_headerLabel);
}


const std::string& Panel::getHeaderLabel() const
{
	return _headerLabel;
}

void Panel::_addCornerHandle()
{
	if(_cornerHandle == nullptr)
	{
		_cornerHandle = addChild<Widget>("Corner Handle", ofRectangle(getWidth() - _cornerHandleSize, getHeight() - _cornerHandleSize, _cornerHandleSize, _cornerHandleSize));
		_setCornerHandleViewRect();
		_cornerHandle->setDraggable(true);
		
		_cornerHandleListener = _cornerHandle->shapeChanged.newListener(this, &Panel::_cornerHandleChanged);
	}
}


void Panel::_removeCornerHandle()
{
	if(_cornerHandle)
	{
		removeChild(_cornerHandle);
		_cornerHandleListener.unsubscribe();
		_cornerHandle = nullptr;
	}
}


void Panel::_setCornerHandleViewRect()
{
	
	if(_cornerHandle)
	{
		_cornerHandle->setShape({getWidth() - _cornerHandleSize, getHeight() - _cornerHandleSize, _cornerHandleSize, _cornerHandleSize});
		_cornerHandle->moveToFront();
	}
}

void Panel::setCornerHandleSize(float cornerHandleSize )
{
	_cornerHandleSize = cornerHandleSize;
	updateLayout();
}


float Panel::getCornerHandleSize() const
{
	return _cornerHandleSize;
}


void Panel::setResizable(bool resizable)
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


bool Panel::isResizable() const
{
	return _resizeable;
}


} } // namespace ofx::MUI
