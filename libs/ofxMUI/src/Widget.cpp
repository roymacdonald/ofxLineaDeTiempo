//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Widget.h"
#include "ofx/DOM/Exceptions.h"
#include "ofx/MUI/MUI.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


Widget::Widget(float x, float y, float width, float height):
    Widget("", x, y, width, height)
{
}

Widget::Widget(const std::string& id, const ofRectangle& rect):
    Widget(id, rect.x, rect.y, rect.width, rect.height)
{
}
Widget::Widget(const ofRectangle& rect):
    Widget("", rect.x, rect.y, rect.width, rect.height)
{
}


Widget::Widget(const std::string& id, float x, float y, float width, float height):
    DOM::Element(id, x, y, width, height)
{
    addEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(pointerUp, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());

    addEventListener(pointerOver, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(pointerEnter, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(pointerOut, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(pointerLeave, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());

    addEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::lowest());

    setImplicitPointerCapture(true);
}


Widget::~Widget()
{
    removeEventListener(pointerMove, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(pointerDown, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(pointerUp, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());

    removeEventListener(pointerOver, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(pointerEnter, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(pointerOut, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(pointerLeave, &Widget::_onPointerEvent, false, std::numeric_limits<int>::lowest());

    removeEventListener(gotPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(lostPointerCapture, &Widget::_onPointerCaptureEvent, false, std::numeric_limits<int>::lowest());
}


void Widget::onDraw() const
{
    ofPushStyle();
    ofFill();

	if(_drawMode == ShapeDrawMode::ELLIPSE){
		// Translate for circle center.
		  ofPushMatrix();
		  ofTranslate(getWidth() / 2, getHeight() / 2);
	}
	
    auto styles = getStyles();

    if (isPointerDown() || isFocused())
    {
        ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_DOWN));
    }
    else if (isPointerOver() && _highlightOnOver)
    {
        ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_OVER));
    }
    else
    {
        ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
    }

    drawShape(0, 0, getWidth(), getHeight());

    ofNoFill();

    if (isPointerDown())
    {
        ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_DOWN));
    }
    else if (isPointerOver() && _highlightOnOver)
    {
        ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_OVER));
    }
    else
    {
        ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
    }

    drawShape(0, 0, getWidth(), getHeight());
    ofPopStyle();

    if (isFocused())
    {
        ofPushStyle();
        ofNoFill();
        ofSetColor(255, 255, 0, 200);
        int offset = 1;
        drawShape(-offset,
                        -offset,
                        getWidth() + offset * 2,
                        getHeight() + offset * 2);
        ofPopStyle();
    }
	if(_drawMode == ShapeDrawMode::ELLIPSE){
		ofPopMatrix();
	}
}


bool Widget::isPointerOver() const
{
    return _isPointerOver;
}


bool Widget::isPointerDown() const
{
    return !capturedPointers().empty();
}


void Widget::setDropTarget(bool dropTarget)
{
    _isDropTarget = dropTarget;
}


bool Widget::isDropTarget() const
{
    return _isDropTarget;
}


void Widget::setDraggable(bool draggable)
{
    _isDraggable = draggable;
}


bool Widget::isDraggable() const
{
    return _isDraggable;
}


bool Widget::isDragging() const
{
    return _isDragging;
}
    
    
void Widget::setElevation(float elevation)
{
    _elevation = elevation;
}


float Widget::getElevation() const
{
    return _elevation;
}


std::shared_ptr<Styles> Widget::getStyles() const
{
    if (_styles == nullptr)
    {
        const MUI* mui = dynamic_cast<const MUI*>(document());

        if (mui != nullptr)
        {
            _styles = mui->getDocumentStyles();
        }
        else
        {
            ofLogWarning("Widget::getStyles") << "No root document, using default styles.";
            _styles = std::make_shared<Styles>(getId() +"_Styles");
        }
    }

    return _styles;
}


void Widget::setStyles(std::shared_ptr<Styles> styles)
{
    _styles = styles;
}



void Widget::_onDragging(const DOM::CapturedPointer& pointer)
{
	setPosition(screenToParent(pointer.position() - pointer.offset()));
}

void Widget::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
    }
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
        if (_isDragging)
        {
            if (!capturedPointers().empty())
            {
				this->_onDragging(*capturedPointers().begin());
            }
            else
            {
                ofLogError("Widget::_onPointerEvent") << "No captured pointers to drag with.";
            }

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
void Widget::_setIsDragging(bool bDragging){
	if(!_isDraggable){
		_isDragging = false;//just make sure this is always false
		return;
	}
	if(_isDragging != bDragging){
		_isDragging = bDragging;
		ofNotifyEvent(isDraggingEvent, _isDragging, this);
	}
}

void Widget::_onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
    if (e.type() == PointerEventArgs::GOT_POINTER_CAPTURE)
    {
        if (_moveToFrontOnCapture)
        {
            moveToFront();
        }
		
        _setIsDragging(true);
		
    }
    else if (e.type() == PointerEventArgs::LOST_POINTER_CAPTURE)
    {
        _setIsDragging(false);
    }
}

void Widget::drawShape(float x, float y, float width, float height, float radius)const{
	if(_drawMode == ShapeDrawMode::ELLIPSE){
		ofDrawEllipse(x, y, width, height);
	}else if(_drawMode == ShapeDrawMode::RECTANGLE){
		ofDrawRectangle(x, y, width, height);
	}else if(_drawMode == ShapeDrawMode::ROUNDED_RECTANGLE){
		ofDrawRectRounded(x, y, width, height, radius);
	}else if(_drawMode == ShapeDrawMode::TOP_ROUNDED_RECTANGLE){
        ofDrawRectRounded(x, y, 0, width, height, radius, radius, 0, 0);
	}else if(_drawMode == ShapeDrawMode::BOTTOM_ROUNDED_RECTANGLE){
        ofDrawRectRounded(x, y, 0, width, height, 0, 0, radius, radius);
	}else if(_drawMode == ShapeDrawMode::LEFT_ROUNDED_RECTANGLE){
        ofDrawRectRounded(x, y, 0, width, height, radius, 0, 0, radius);
	}else if(_drawMode == ShapeDrawMode::RIGHT_ROUNDED_RECTANGLE){
        ofDrawRectRounded(x, y, 0, width, height, 0, radius, radius, 0);
	}
}

void Widget::setShapeDrawMode(ShapeDrawMode drawMode){
		_drawMode = drawMode;
}

ShapeDrawMode Widget::getShapeDrawMode() const{
		return _drawMode;
}

void Widget::setMoveToFrontOnCapture(bool moveToFront){
	_moveToFrontOnCapture = moveToFront;
}

bool Widget::isMoveToFrontOnCapture(){
	return _moveToFrontOnCapture;
}

void Widget::setHighlightOnOver(bool bHighlight){
	_highlightOnOver = bHighlight;
}

bool Widget::isHighlightingOnOver(){
	return _highlightOnOver;
};

void Widget::printStructure(std::string prefix)
{
	std::cout << prefix << getId() << "  " <<  getShape() << " "<< std::boolalpha << _isDraggable << "\n";
	prefix += "   ";
	
	for(auto c: children())
	{
		c->printStructure(prefix);
	}
	
}


} } // namespace ofx::MUI
