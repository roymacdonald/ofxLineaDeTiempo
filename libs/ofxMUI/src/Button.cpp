//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Button.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


const std::string ButtonEventArgs::BUTTON_UP = "buttonup";
const std::string ButtonEventArgs::BUTTON_DOWN = "buttondown";
const std::string ButtonEventArgs::BUTTON_PRESSED = "buttonpressed";


ButtonEventArgs::~ButtonEventArgs()
{
}


bool ButtonEventArgs::isButtonUp() const
{
    return type() == BUTTON_UP;
}


bool ButtonEventArgs::isButtonDown() const
{
    return type() == BUTTON_DOWN;
}


bool ButtonEventArgs::isButtonPressed() const
{
    return type() == BUTTON_PRESSED;
}


Button::Button(const std::string& id,
               float x,
               float y,
               float width,
               float height,
               bool autoExclusive,
               bool triggersOnRelease,
               bool requirePointerOverOnRelease,
               std::size_t stateCount):
    Widget(id, x, y, width, height),
    _autoExclusive(autoExclusive),
    _triggersOnRelease(triggersOnRelease),
    _requirePointerOverOnRelease(requirePointerOverOnRelease),
    _stateCount(stateCount),
    _value(id, 0, 0, _stateCount)
{
    registerEventType(ButtonEventArgs::BUTTON_DOWN, &buttonDown);
    registerEventType(ButtonEventArgs::BUTTON_UP, &buttonUp);
    registerEventType(ButtonEventArgs::BUTTON_PRESSED, &buttonPressed);

    _value.addListener(this,
                       &Button::_onValueChanged,
                       std::numeric_limits<int>::lowest());

    addEventListener(pointerDown, &Button::onPointerEvent, false, std::numeric_limits<int>::lowest());
    addEventListener(pointerUp, &Button::onPointerEvent, false, std::numeric_limits<int>::lowest());

    addEventListener(gotPointerCapture, &Button::onPointerCaptureEvent);
    addEventListener(lostPointerCapture, &Button::onPointerCaptureEvent);

    setImplicitPointerCapture(true);
}


Button::~Button()
{
    // Remove the listener from the local or bound parameters.
    _value.removeListener(this,
                          &Button::_onValueChanged,
                          std::numeric_limits<int>::lowest());

    removeEventListener(pointerDown, &Button::onPointerEvent, false, std::numeric_limits<int>::lowest());
    removeEventListener(pointerUp, &Button::onPointerEvent, false, std::numeric_limits<int>::lowest());

    removeEventListener(gotPointerCapture, &Button::onPointerCaptureEvent);
    removeEventListener(lostPointerCapture, &Button::onPointerCaptureEvent);
}


bool Button::triggersOnRelease() const
{
    return _triggersOnRelease;
}


bool Button::requirePointerOverOnRelease() const
{
    return _requirePointerOverOnRelease;
}


bool Button::autoExclusive() const
{
    return _autoExclusive;
}


std::size_t Button::stateCount() const
{
    return _stateCount;
}


void Button::onDraw() const
{
    Widget::onDraw();

    auto styles = getStyles();

    ofFill();

    if (isPointerDown())
    {
        ofSetColor(styles->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_DOWN));
    }
    else if (isPointerOver())
    {
        ofSetColor(styles->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_OVER));
    }
    else
    {
        ofSetColor(styles->getColor(Styles::ROLE_FOREGROUND, Styles::STATE_NORMAL));
    }

    ofRectangle targetRectangle(5, 5, getWidth() - 10, getHeight() - 10);
    ofRectangle fullRectangle(0, 0, getWidth(), getHeight());

    ofDrawRectangle(targetRectangle);

    ofNoFill();
    ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
    ofDrawRectangle(fullRectangle);
}


void Button::onPointerEvent(DOM::PointerUIEventArgs& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
        ButtonEventArgs buttonDown(ButtonEventArgs::BUTTON_DOWN,
                                   this,
                                   this,
                                   nullptr,
                                   true,
                                   true,
                                   e.timestamp());

        this->dispatchEvent(buttonDown);

        if (!_triggersOnRelease)
        {
            _incrementState();
        }
    }
    else if (e.type() == PointerEventArgs::POINTER_UP)
    {

        if (_triggersOnRelease &&
            (!_requirePointerOverOnRelease ||
             (_requirePointerOverOnRelease && isPointerOver())))
        {
            _incrementState();
        }

        ButtonEventArgs buttonUp(ButtonEventArgs::BUTTON_UP,
                                 this,
                                 this,
                                 nullptr,
                                 true,
                                 true,
                                 e.timestamp());
        this->dispatchEvent(buttonUp);

        ButtonEventArgs buttonPressed(ButtonEventArgs::BUTTON_PRESSED,
                                      this,
                                      this,
                                      nullptr,
                                      true,
                                      true,
                                      e.timestamp());

        this->dispatchEvent(buttonPressed);
    }
}


void Button::onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
    if (PointerEventArgs::GOT_POINTER_CAPTURE == e.type() && _primaryPointerId == 0)
    {
        _primaryPointerId = e.id();
    }
    else if (PointerEventArgs::LOST_POINTER_CAPTURE == e.type() && _primaryPointerId == e.id())
    {
        _primaryPointerId = 0;
    }
}


void Button::_onValueChanged(const void* sender, int& value)
{
    // We forward the event changes as sent by the slider.
    ofNotifyEvent(valueChanged, value, this);
}


int Button::operator = (int v)
{
    _value = v;
    return v;
}


Button::operator const int& ()
{
    return _value;
}


void Button::_incrementState()
{
    if (_autoExclusive)
    {
        for (auto& sibling : siblings<Button>())
        {
            if (sibling->autoExclusive())
            {
                sibling->_value.setWithoutEventNotifications(0);
            }
        }

        _value = 1;
    }
    else
    {
        _value = (_value + 1) % _stateCount;
    }
}


ToggleButton::ToggleButton(const std::string& id,
                           float x,
                           float y,
                           float width,
                           float height,
                           bool autoExclusive,
                           bool triggersOnRelease,
                           bool requirePointerOverOnRelease):
    Button(id,
           x,
           y,
           width,
           height,
           autoExclusive,
           triggersOnRelease,
           requirePointerOverOnRelease,
           2)
{
}


ToggleButton::~ToggleButton()
{
}


void ToggleButton::onDraw() const
{
    Button::onDraw();

    if (_value)
    {
        ofFill();
        ofSetColor(getStyles()->getColor(Styles::ROLE_ACCENT, Styles::STATE_DOWN));
        ofDrawRectangle(10, 10, getWidth() - 20, getHeight() - 20);
    }
}



RadioButton::RadioButton(const std::string& id,
                         float x,
                         float y,
                         float width,
                         float height):
    Button(id, x, y, width, height, true, false, true)
{
}


RadioButton::~RadioButton()
{
}


void RadioButton::onDraw() const
{
    if (_value)
    {
        ofFill();
    }
    else
    {
        ofNoFill();
    }

    ofSetColor(getStyles()->getColor(Styles::ROLE_ACCENT, Styles::STATE_DOWN));
    ofDrawEllipse(getWidth() / 2, getHeight() / 2, getWidth() - 10, getHeight() - 10);
}


bool RadioButton::hitTest(const DOM::Position& parentPosition) const
{
    auto center = getShape().getCenter();

    return glm::distance(glm::vec2(center.x, center.y),
                         parentPosition) < (getWidth() - 10) / 2.0;
}


} } // namespace ofx::MUI
