//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/DOM/Events.h"
#include "ofx/DOM/Element.h"


namespace ofx {
namespace DOM {


EventArgs::EventArgs(const std::string& type,
                     Element* source,
                     Element* target,
                     bool bubbles,
                     bool cancelable,
                     uint64_t timestamp):
    EventArgs(type, source, target, nullptr, bubbles, cancelable, timestamp)
{
}


EventArgs::EventArgs(const std::string& type,
                     Element* source,
                     Element* target,
                     Element* relatedTarget,
                     bool bubbles,
                     bool cancelable,
                     uint64_t timestamp):
    _type(type),
    _source(source),
    _target(target),
    _relatedTarget(relatedTarget),
    _bubbles(bubbles),
    _cancelable(cancelable),
    _timestamp(timestamp)
{
}


EventArgs::~EventArgs()
{
}


const std::string& EventArgs::type() const
{
    return _type;
}


void EventArgs::stopPropagation()
{
    if (_cancelable)
    {
        _canceled = true;
    }
}


void EventArgs::stopImmediatePropagation()
{
    if (_cancelable)
    {
        _canceled = true;
        // TODO: this is no longer in 0.10.0
        // throw ofEventAttendedException();
    }
}


void EventArgs::preventDefault()
{
    _defaultPrevented = true;
}


bool EventArgs::isCancelled() const
{
    return _canceled;
}


bool EventArgs::isDefaultPrevented() const
{
    return _defaultPrevented;
}


void EventArgs::setPhase(Phase phase)
{
    _phase = phase;
}


EventArgs::Phase EventArgs::getPhase() const
{
    return _phase;
}


bool EventArgs::bubbles() const
{
    return _bubbles;
}


bool EventArgs::isCancelable() const
{
    return _cancelable;
}


Element* EventArgs::source()
{
    return _source;
}


Element* EventArgs::target()
{
    return _target;
}


Element* EventArgs::relatedTarget()
{
    return _relatedTarget;
}


Element* EventArgs::getCurrentTarget()
{
    return _currentTaget;
}


const Element* EventArgs::getCurrentTarget() const
{
    return _currentTaget;
}


void EventArgs::setCurrentTarget(Element* target)
{
    _currentTaget = target;
}


uint64_t EventArgs::timestamp() const
{
    return _timestamp;
}


std::string EventArgs::toString() const
{
    std::stringstream ss;

    std::string phaseString = "";

    switch (_phase)
    {
        case Phase::NONE:
            phaseString = "NONE";
            break;
        case Phase::CAPTURING_PHASE:
            phaseString = "CAPTURING_PHASE";
            break;
        case Phase::AT_TARGET:
            phaseString = "AT_TARGET";
            break;
        case Phase::BUBBLING_PHASE:
            phaseString = "BUBBLING_PHASE";
            break;
    }


    ss << "Event Type: " << _type << std::endl;
    ss << "     Phase: " << phaseString << std::endl;
    ss << "    Source: " << (_source != nullptr ? _source->getId() : "nullptr") << std::endl;
    ss << "    Target: " << (_target != nullptr ? _target->getId() : "nullptr") << std::endl;
    ss << "Rel-Target: " << (_relatedTarget != nullptr ? _relatedTarget->getId() : "nullptr") << std::endl;
    ss << "Cur-Target: " << (_currentTaget != nullptr ? _currentTaget->getId() : "nullptr") << std::endl;
    ss << " Bubs/Canc: " << _bubbles << "/" << _cancelable << std::endl;
    ss << " DP/Canc'd: " << _defaultPrevented << "/" << _canceled << std::endl;
    ss << " timestamp: " << _timestamp << std::endl;

    return ss.str();
}


PointerCaptureUIEventArgs::PointerCaptureUIEventArgs(std::size_t id,
                                                     bool wasCaptured,
                                                     Element* source,
                                                     Element* target):
    UIEventArgs((wasCaptured ? PointerEventArgs::GOT_POINTER_CAPTURE : PointerEventArgs::LOST_POINTER_CAPTURE),
            source,
            target,
            true,
            false,
            ofGetElapsedTimeMillis()),
    _id(id)
{
}



PointerCaptureUIEventArgs::~PointerCaptureUIEventArgs()
{
}


std::size_t PointerCaptureUIEventArgs::id() const
{
    return _id;
}


PointerUIEventArgs::PointerUIEventArgs(const PointerEventArgs& pointer,
                                       Element* source,
                                       Element* target,
                                       Element* relatedTarget):
    UIEventArgs(pointer.eventType(),
                source,
                target,
                relatedTarget,
            	eventBubbles(pointer.eventType()),
                eventCancelable(pointer.eventType()),
                pointer.timestampMillis()),
    _pointer(pointer)
{
}


PointerUIEventArgs::~PointerUIEventArgs()
{
}


const PointerEventArgs& PointerUIEventArgs::pointer() const
{
    return _pointer;
}


Position PointerUIEventArgs::screenPosition() const
{
    return pointer().position();
}


Position PointerUIEventArgs::localPosition() const
{
    if (_currentTaget)
    {
        return _currentTaget->screenToLocal(pointer().point().position());
    }

    return pointer().point().position();
}


bool PointerUIEventArgs::eventBubbles(const std::string& event)
{
    return !(event == PointerEventArgs::POINTER_ENTER
          || event == PointerEventArgs::POINTER_LEAVE);
}


bool PointerUIEventArgs::eventCancelable(const std::string& event)
{
    return !(event == PointerEventArgs::POINTER_ENTER
          || event == PointerEventArgs::POINTER_CANCEL
          || event == PointerEventArgs::POINTER_LEAVE
          || event == PointerEventArgs::GOT_POINTER_CAPTURE
          || event == PointerEventArgs::LOST_POINTER_CAPTURE);
}


const std::string KeyboardUIEventArgs::KEY_DOWN = "keydown";
const std::string KeyboardUIEventArgs::KEY_UP = "keyup";


KeyboardUIEventArgs::KeyboardUIEventArgs(const ofKeyEventArgs& args,
                                         Element* source,
                                         Element* target):
    UIEventArgs(args.type == ofKeyEventArgs::Pressed ? KEY_DOWN : KEY_UP,
                source,
                target,
                true,
                true,
                ofGetElapsedTimeMillis()),
    _key(args)
{
}


KeyboardUIEventArgs::~KeyboardUIEventArgs()
{
}


const ofKeyEventArgs& KeyboardUIEventArgs::key() const
{
    return _key;
}


bool KeyboardUIEventArgs::altKey() const
{
    return _key.hasModifier(OF_KEY_ALT);
}

    
bool KeyboardUIEventArgs::metaKey() const
{
    return _key.hasModifier(OF_KEY_SUPER);
}

    
bool KeyboardUIEventArgs::shiftKey() const
{
    return _key.hasModifier(OF_KEY_SHIFT);
}

    
bool KeyboardUIEventArgs::ctrlKey() const
{
    return _key.hasModifier(OF_KEY_CONTROL);
}

    
std::string KeyboardUIEventArgs::toString() const
{
    std::stringstream ss;
    ss << UIEventArgs::toString();
    
    ss << "========" << std::endl;
    ss << " codepoint: " << _key.codepoint << " (" << ofUTF8ToString(_key.codepoint) << ")" << std::endl;
    ss << "  isRepeat: " << _key.isRepeat << std::endl;
    ss << "       key: " << _key.key << " (" << ofUTF8ToString(_key.key) << ")" << std::endl;
    ss << "   keycode: " << _key.keycode << " (" << ofUTF8ToString(_key.keycode) << ")" << std::endl;
    ss << "  scancode: " << _key.scancode  << " (" << ofUTF8ToString(_key.scancode) << ")" << std::endl;
    ss << "      type: " << _key.type << std::endl;
    ss << " modifiers: " << _key.modifiers << std::endl;
    ss << "      meta: " << metaKey() << std::endl;
    ss << "      ctrl: " << ctrlKey() << std::endl;
    ss << "     shift: " << shiftKey() << std::endl;
    ss << "       alt: " << altKey() << std::endl;

    return ss.str();
}

    
const std::string FocusEventArgs::FOCUS_IN = "focusin";
const std::string FocusEventArgs::FOCUS = "focus";
const std::string FocusEventArgs::FOCUS_OUT = "focusout";
const std::string FocusEventArgs::BLUR = "blur";


FocusEventArgs::FocusEventArgs(const std::string& type,
                               Element* source,
                               Element* target,
                               Element* relatedTarget):
    EventArgs(type,
              source,
              target,
              (type != FOCUS), // In the spec.
              false,
              ofGetElapsedTimeMillis())
{
    // TODO: better Event constructor.
    _relatedTarget = relatedTarget;
}


FocusEventArgs::~FocusEventArgs()
{
}


MoveEventArgs::MoveEventArgs(const Position& position):
    _position(position)
{
}


MoveEventArgs::~MoveEventArgs()
{
}


const Position& MoveEventArgs::position() const
{
    return _position;
}


ResizeEventArgs::ResizeEventArgs(const Shape& shape):
    _shape(shape)
{
}


ResizeEventArgs::~ResizeEventArgs()
{
}


const Shape& ResizeEventArgs::shape() const
{
    return _shape;
}


AttributeEventArgs::AttributeEventArgs(const std::string& key,
                                       const Any& value):
    _key(key),
    _value(value)
{
}


AttributeEventArgs::~AttributeEventArgs()
{
}


const std::string& AttributeEventArgs::key() const
{
    return _key;
}


const Any& AttributeEventArgs::value() const
{
    return _value;
}


EnablerEventArgs::EnablerEventArgs(bool value):
    _value(value)
{
}


EnablerEventArgs::~EnablerEventArgs()
{
}


bool EnablerEventArgs::value() const
{
    return _value;
}


ElementEventArgs::ElementEventArgs(Element* element):
    _element(element)
{
}


ElementEventArgs::~ElementEventArgs()
{
}


Element* ElementEventArgs::element()
{
    return _element;
}


const Element* ElementEventArgs::element() const
{
    return _element;
}


ElementOrderEventArgs::ElementOrderEventArgs(Element* element,
                                             std::size_t oldIndex,
                                             std::size_t newIndex):
    ElementEventArgs(element),
    _oldIndex(oldIndex),
    _newIndex(newIndex)
{
}


ElementOrderEventArgs::~ElementOrderEventArgs()
{
}


std::size_t ElementOrderEventArgs::oldIndex() const
{
    return _oldIndex;
}
    
    
std::size_t ElementOrderEventArgs::newIndex() const
{
    return _newIndex;
}


bool ElementOrderEventArgs::wasMovedForward() const
{
    return _oldIndex > _newIndex;
}


bool ElementOrderEventArgs::wasMovedBackward() const
{
    return _newIndex > _oldIndex;
}


bool ElementOrderEventArgs::isAtFront() const
{
    return _newIndex == 0;
}


bool ElementOrderEventArgs::isAtBack() const
{
    return _element->numSiblings() == _newIndex;
}


} } // namespace ofx::DOM
