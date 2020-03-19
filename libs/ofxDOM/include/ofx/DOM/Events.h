//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <type_traits>
#include <utility>
#include <ctime>
#include "ofEvents.h"
#include "ofx/PointerEvents.h"
#include "ofx/DOM/Exceptions.h"
#include "ofx/DOM/Types.h"


namespace ofx {
namespace DOM {


class Element;


/// \brief The base type describing a named Element Event.
///
/// \sa http://www.w3.org/TR/DOM-Level-3-Events/
class EventArgs
{
public:
    /// \brief Create EventArgs with a type.
    /// \param type The event type string (case-insensitive).
    /// \param source The source Element.
    /// \param target The target Element.
    /// \param bubbles True iff the argument bubbles after AT_TARGET phase.
    /// \param cancelable True iff the event can be cancelled by a listener.
    /// \param timestamp The timestamp of the event.
    EventArgs(const std::string& type,
              Element* source,
              Element* target,
              bool bubbles,
              bool cancelable,
              uint64_t timestamp);

    /// \brief Create EventArgs with a type.
    /// \param type The event type string (case-insensitive).
    /// \param source The source Element.
    /// \param target The target Element.
    /// \param bubbles True iff the argument bubbles after AT_TARGET phase.
    /// \param cancelable True iff the event can be cancelled by a listener.
    /// \param timestamp The timestamp of the event.
    EventArgs(const std::string& type,
              Element* source,
              Element* target,
              Element* relatedTarget,
              bool bubbles,
              bool cancelable,
              uint64_t timestamp);

    /// \brief Destroy the EventArgs.
    virtual ~EventArgs();

    /// \brief Get the event type.
    /// \returns the event type string.
    const std::string& type() const;

    enum class Phase
    {
        /// \brief Events not currently dispatched are in this phase.
        NONE = 0,
        /// \brief When an event is dispatched to an object that participates in a tree it will be in this phase before it reaches its target attribute value.
        CAPTURING_PHASE = 1,
        /// \brief When an event is dispatched it will be in this phase on its target attribute value.
        AT_TARGET = 2,
        /// \brief When an event is dispatched to an object that participates in a tree it will be in this phase after it reaches its target attribute value.
        BUBBLING_PHASE = 3
    };


    /// \brief Stop the propagation of the event.
    ///
    /// The stopPropagation method is used prevent further propagation of an
    /// event during event flow. If this method is called by any EventListener
    /// the event will cease propagating through the tree. The event will
    /// complete dispatch to all listeners on the current EventTarget before
    /// event flow stops. This method may be used during any stage of event
    /// flow.
    void stopPropagation();

    // \brief Stop the propagation of the event, including all other events at the target.
    //
    // If successful this event throws ofEventAttendedException(). This exception
    // should be handled gracefully by the ofEvent dispatching this event.
    //
    // The same effect can be achieved by returning "true" from any event
    // callback with a boolean return type.
    //
    // \throws ofEventAttendedException if the event is cancelable.
    void stopImmediatePropagation();

    /// \brief Prevent any default actions associated with the event.
    ///
    /// For some events, there are default actions.  Calling preventDefault will
    /// tell the event dispatcher that it should not call the default action
    /// after the event has been dispatched.  This is different from
    /// stopPropagation.  Calling stopPropagation does not prevent the default
    /// action from taking place.  To stop propagation and prevent the default,
    /// both methods must be called.
    void preventDefault();

    /// \returns true iff the event was cancelled.
    bool isCancelled() const;

    /// \returns true iff the default activity was prevented.
    bool isDefaultPrevented() const;

    /// \brief Set the Phase of the event.
    /// \param phase The phase to set.
    void setPhase(Phase phase);

    /// \returns the Phase of the event.
    Phase getPhase() const;

    /// \brief Determine if the event has a bubbling phase.
    /// \returns true iff the event should bubble.
    bool bubbles() const;

    /// \returns true iff the Event can be cancelled.
    bool isCancelable() const;

    /// \returns the source Element.
    Element* source();

    /// \returns the target Element.
    Element* target();

    /// \returns the related target Element.
    Element* relatedTarget();

    /// \returns a pointer to the current target Element.
    Element* getCurrentTarget();

    /// \returns a pointer to the current target Element.
    const Element* getCurrentTarget() const;

    /// \brief Set the current target Element.
    /// \param target The current target Element.
    void setCurrentTarget(Element* target);

    /// \returns the timestamp (in milliseconds relative to the epoch).
    uint64_t timestamp() const;

    /// \brief A utility method to print get the Event as a std::string.
    /// \returns The Event as a std::string.
    /// \note Not for serialization.
    virtual std::string toString() const;

protected:
    /// \brief The name of the event (case-insensitive).
    std::string _type;

    /// \brief The source of the event.
    Element* _source = nullptr;

    /// \brief The event's target.
    Element* _target = nullptr;

    /// \brief The event's related target.
    Element* _relatedTarget = nullptr;

    /// \brief Used to indicate whether or not an event is a bubbling event.
    /// If the event can bubble the value is true, else the value is false.
    bool _bubbles = true;

    /// \brief Used to indicate whether propgation was stopped.  The currentTarget
    /// will indicate which target stopped propagation.
    bool _cancelable = true;

    /// \brief Used to indicated
    bool _defaultPrevented = false;

    /// \brief Used to indicate the EventTarget whose EventListeners are currently being processed.
    /// This is particularly useful during capturing and bubbling.
    Element* _currentTaget = nullptr;

    /// \brief Used to indicate which phase of event flow is currently being evaluated.
    Phase _phase = Phase::NONE;

    /// \brief Used to indicate if an event is canceled.
    bool _canceled = false;

    /// \brief Used to specify the time (in milliseconds relative to the epoch)
    /// at which the event was created.
    ///
    /// Due to the fact that some systems may not provide this information the
    /// value of timeStamp may be not available for all events. When not
    /// available, a value of 0 will be returned. Examples of epoch time are
    /// the time of the system start or 0:0:0 UTC 1st January 1970.
    uint64_t _timestamp = 0;

    /// \brief The Document class has access to Event data.
    friend class Document;
};


/// can we handle this named ui event at this coordinate?
class UIEventArgs: public EventArgs
{
public:
    using EventArgs::EventArgs;

    virtual ~UIEventArgs()
    {
    }

};


class PointerCaptureUIEventArgs: public UIEventArgs
{
public:
    /// \param source The source Element.
    /// \param target The target Element.
    PointerCaptureUIEventArgs(std::size_t id,
                              bool wasCaptured,
                              Element* source,
                              Element* target);

    virtual ~PointerCaptureUIEventArgs();

    /// \returns the pointer id.
    std::size_t id() const;

private:
    /// \brief The pointer id.
    std::size_t _id = 0;

};


class PointerUIEventArgs: public UIEventArgs
{
public:
    /// \param source The source Element.
    /// \param target The target Element.
    PointerUIEventArgs(const PointerEventArgs& args,
                       Element* source,
                       Element* target,
                       Element* relatedTarget = nullptr);

    virtual ~PointerUIEventArgs();

    const PointerEventArgs& pointer() const;

    Position screenPosition() const;

    Position localPosition() const;

protected:
    static bool eventBubbles(const std::string& event);
    static bool eventCancelable(const std::string& event);

    PointerEventArgs _pointer;

};


class KeyboardUIEventArgs: public UIEventArgs
{
public:
    /// \param source The source Element.
    /// \param target The target Element.
    KeyboardUIEventArgs(const ofKeyEventArgs& args,
                        Element* source,
                        Element* target);

    virtual ~KeyboardUIEventArgs();

    const ofKeyEventArgs& key() const;

    /// \returns true if the alt key was active when this event was generated.
    bool altKey() const;

    /// \returns true if the meta key was active when this event was generated.
    bool metaKey() const;

    /// \returns true if the shift key was active when this event was generated.
    bool shiftKey() const;
    
    /// \returns true if the control key was active when this event was generated.
    bool ctrlKey() const;
    
    std::string toString() const override;
    
    static const std::string KEY_DOWN;
    static const std::string KEY_UP;

protected:
    ofKeyEventArgs _key;

};


/// \sa http://www.w3.org/TR/DOM-Level-3-Events/#event-type-focus
class FocusEventArgs: public EventArgs
{
public:
    /// \param source The source Element.
    /// \param target The target Element.
    FocusEventArgs(const std::string& type,
                   Element* source,
                   Element* target,
                   Element* relatedTarget = nullptr);

    virtual ~FocusEventArgs();

    static const std::string FOCUS_IN;
    static const std::string FOCUS;
    static const std::string FOCUS_OUT;
    static const std::string BLUR;

};


class DragDropEventArgs: public EventArgs
{
public:

};


class AbstractDOMEvent
{
public:
    virtual ~AbstractDOMEvent()
    {
    }
};



class BaseDOMEvent
{
public:
    virtual ~BaseDOMEvent()
    {
    }

    //virtual std::string type() const = 0;

    /// \returns true if the event has bubble phase listeners.
    virtual bool hasBubblePhaseListeners() const = 0;

    /// \returns true if the event has capture phase listeners.
    virtual bool hasCapturePhaseListeners() const = 0;

    /// \returns true if the event has bubble or capture phase listeners.
    bool hasListeners() const
    {
        return hasBubblePhaseListeners() || hasCapturePhaseListeners();
    }

};


/// \brief DOM Events follow the DOM capture, target, bubble propagation scheme.
/// \tparam EventArgsType The Event argument type wrapped this DOMEvent.
template <typename EventArgsType>
class DOMEvent: public BaseDOMEvent
{
public:
    virtual ~DOMEvent()
    {
    }

    bool hasBubblePhaseListeners() const override
    {
        return _bubbleEvent.size() > 0;
    }

    bool hasCapturePhaseListeners() const override
    {
        return _captureEvent.size() > 0;
    }

    ofEvent<EventArgsType>& event(bool useCapture = false)
    {
        return useCapture ? _captureEvent : _bubbleEvent;
    }

    void notify(EventArgsType& e)
    {
        switch (e.getPhase())
        {
            case EventArgs::Phase::NONE:
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "DOMEvent::notify");
            case EventArgs::Phase::CAPTURING_PHASE:
                _captureEvent.notify(e.source(), e);
                return;
            case EventArgs::Phase::AT_TARGET:
                _captureEvent.notify(e.source(), e);
                _bubbleEvent.notify(e.source(), e);
                return;
            case EventArgs::Phase::BUBBLING_PHASE:
                _bubbleEvent.notify(e.source(), e);
                return;
        }
    }

private:
    ofEvent<EventArgsType> _bubbleEvent;
    ofEvent<EventArgsType> _captureEvent;

};


class MoveEventArgs
{
public:
    MoveEventArgs(const Position& position);
    virtual ~MoveEventArgs();

    const Position& position() const;

protected:
    Position _position;

};


class ResizeEventArgs
{
public:
    /// \brief Construct a ResizeEventArgs with the given shape.
    /// \param shape The new shape.
    ResizeEventArgs(const Shape& shape);

    /// \brief Destroy the ResizeEventArgs.
    virtual ~ResizeEventArgs();

    const Shape& shape() const;

protected:
    Shape _shape;

};


class AttributeEventArgs
{
public:
    /// \brief Create an AttributeEventArgs with the given parameters.
    /// \param key The key associated with this event.
    /// \param value The value associated with this event.
    AttributeEventArgs(const std::string& key, const Any& value = Any());

    /// \brief Destroy the AttributeEventArgs.
    virtual ~AttributeEventArgs();

    /// \returns the key associated with this event.
    const std::string& key() const;

    /// \returns the value associated with this event.
    const Any& value() const;

protected:
    /// \brief The key associated with this event.
    std::string _key;

    /// \brief The value associated with this event.
    Any _value;

};


class EnablerEventArgs
{
public:
    EnablerEventArgs(bool value);
    virtual ~EnablerEventArgs();

    bool value() const;

protected:
    bool _value = false;

};


class ElementEventArgs
{
public:
    /// \brief Construct the ElementEventArgs.
    /// \param element The element associated with this Element event.
    ElementEventArgs(Element* element);

    /// \brief Destroy the ElementEventArgs.
    virtual ~ElementEventArgs();

    /// \returns a pointer to the element or nullptr if not available.
    Element* element();
    
    /// \returns a pointer to the element or nullptr if not available.
    const Element* element() const;

protected:
    /// \brief A pointer to the element or nullptr if not available.
    Element* _element = nullptr;

};


class ElementOrderEventArgs: public ElementEventArgs
{
public:
    /// \brief Create an ElementOrderEventArgs.
    /// \param element The element associated with this Element order event.
    /// \param oldIndex old index before the Element order event.
    /// \param newIndex The new index after the Element order event.
    ElementOrderEventArgs(Element* element,
                          std::size_t oldIndex,
                          std::size_t newIndex);

    /// \brief Destroys the ElementOrderEventArgs.
    virtual ~ElementOrderEventArgs();

    /// \returns the old index before the Element order event.
    std::size_t oldIndex() const;

    /// \returns the new index after the Element order event.
    std::size_t newIndex() const;

    /// \returns true if the Element was moved forward.
    bool wasMovedForward() const;

    /// \returns true if the Element was moved backward.
    bool wasMovedBackward() const;

    /// \returns true if the Element is at the front.
    bool isAtFront() const;

    /// \returns true if the Element is at the back.
    bool isAtBack() const;

protected:
    /// \brief The old index before the Element order event.
    std::size_t _oldIndex = 0;

    /// \brief The new index after the Element order event.
    std::size_t _newIndex = 0;

};


} } // namespace ofx::DOM
