//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofTexture.h"
#include "ofx/DOM/Events.h"
#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


class Button;


/// \brief A set of event arguments for Button events.
class ButtonEventArgs: public DOM::EventArgs
{
public:
    using DOM::EventArgs::EventArgs;

    /// \brief Destroy the ButtonEventArgs.
    virtual ~ButtonEventArgs();

    /// \returns true if event type is BUTTON_UP.
    bool isButtonUp() const;

    /// \returns true if event type is BUTTON_DOWN.
    bool isButtonDown() const;

    /// \returns true if event type is BUTTON_PRESSED.
    bool isButtonPressed() const;

    /// \brief The button up event type.
    static const std::string BUTTON_UP;

    /// \brief The button down event type.
    static const std::string BUTTON_DOWN;

    /// \brief The button pressed event type.
    static const std::string BUTTON_PRESSED;

};



/// \brief A simple one state push button.
///
/// In addition to the standard Pointer events, the following button events are
/// triggered when a button is pressed:
///
///     onButtonDown // When the button is pressed.
///     onButtonUp // When the button is released.
///
///     onButtonPressed // If the button is pressed and released according to
///         the `PointerOverOnRelease` policy.
///
///     onButtonStateChanged // Called
///     if
//    ofEvent<void> onButtonPressed;
//
//    /// \brief Event called when the button switches state.
//    ///
//    /// The event data represents the current state of the button.
//    ofEvent<const int> onButtonStateChanged;
//
//    /// \brief The event called when the button goes from an up to down state.
//    ofEvent<void> onButtonDown;
//
//    /// \brief The event called when the button goes from down to up state.
//    ofEvent<void> onButtonUp;
///
class Button: public Widget
{
public:
    /// \brief Create a Button with the given parameters.
    /// \param id The Widget's id string.
    /// \param x x-position in parent coordinates.
    /// \param y y-position in parent coordinates.
    /// \param width The width (x-dimension) of Widget.
    /// \param height The height (y-dimension) of Widget.
    /// \param autoExclusive If true, behaves like an exclusive radio button.
    /// \param triggersOnRelease If true, the button is toggled only on release.
    /// \param requirePointerOverOnRelease Require a pointer to be over the
    ///        button to trigger to change states.
    /// \param stateCount The number of values for multi-state buttons.
    Button(const std::string& id = "",
           float x = 0,
           float y = 0,
           float width = DEFAULT_WIDTH,
           float height = DEFAULT_HEIGHT,
           bool autoExclusive = false,
           bool triggersOnRelease = false,
           bool requirePointerOverOnRelease = true,
           std::size_t stateCount = 1);

    /// \brief Destroy the Button.
    virtual ~Button();

    /// \returns true iff the value should be changed on Button release.
    bool triggersOnRelease() const;

    bool requirePointerOverOnRelease() const;

    /// \returns true iff the button has auto-exclusive mode enabled.
    bool autoExclusive() const;

    /// \returns the number of Button states.
    std::size_t stateCount() const;

    virtual void onDraw() const override;

    /// \brief Default callback for built-in events, including dragging.
    /// \param e The event data.
    void onPointerEvent(DOM::PointerUIEventArgs& e);

    /// \brief Default callback for built-in events, including dragging.
    /// \param e The event data.
    void onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e);

    /// \brief Add listeners to this onValueChanged event.
    /// \tparam ListenerClass The class type of the listener.
    /// \tparam ListenerMethod The name of the listener method.
    /// \param listener A pointer to the listener instance.
    /// \param method A pointer to the listener method.
    /// \param prioirty The order priority of this listener.
    template <class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass* listener, ListenerMethod method, int priority = OF_EVENT_ORDER_AFTER_APP)
    {
        ofAddListener(valueChanged, listener, method, priority);
    }

    /// \brief Remove listeners to this onValueChanged event.
    /// \tparam ListenerClass The class type of the listener.
    /// \tparam ListenerMethod The name of the listener method.
    /// \param listener A pointer to the listener instance.
    /// \param method A pointer to the listener method.
    /// \param prioirty The order priority of this listener.
    template <class ListenerClass, typename ListenerMethod>
    void removeListener(ListenerClass* listener, ListenerMethod method, int priority = OF_EVENT_ORDER_AFTER_APP)
    {
        ofRemoveListener(valueChanged, listener, method, priority);
    }

    /// \brief Event called when button is pressed and released.
    ///
    /// This event follows the require release over policy.
    DOM::DOMEvent<ButtonEventArgs> buttonPressed;

    /// \brief The event called when the button goes from an up to down state.
    DOM::DOMEvent<ButtonEventArgs> buttonDown;

    /// \brief The event called when the button goes from down to up state.
    DOM::DOMEvent<ButtonEventArgs> buttonUp;

    /// \brief The event that is set when the value of a button changes.
    ofEvent<int> valueChanged;

    /// \brief The assignment operator.
    /// \param v Value to assign.
    /// \returns the assigned value.
    int operator = (int v);

    /// \brief Dereference operator.
    operator const int& ();

    enum
    {
        DEFAULT_WIDTH = 40,
        DEFAULT_HEIGHT = 40,
    };

protected:
    /// \brief A callback for the ParameterWidget's value.
    /// \param value The the updated value.
    void _onValueChanged(const void* sender, int& value);

    /// \brief Increment the current button state.
    void _incrementState();

    /// \brief If true, will act as a radio button.
    ///
    /// It will disable all sibling autoExlusive buttons on press.
    bool _autoExclusive = true;

    /// \brief Update the value immediately on press.
    bool _triggersOnRelease = false;

    /// \brief Require that release is over the button.
    bool _requirePointerOverOnRelease = true;

    /// \brief How many states can this button represent?
    std::size_t _stateCount = 1;

    /// \brief The "primary" pointer id.
    ///
    /// This is the first pointer that was captured when dragging.
    std::size_t _primaryPointerId = 0;

    /// \brief The parameter to watch.
    ofParameter<int> _value;

    friend class ButtonGroup;

};


/// \brief A two state button.
class ToggleButton: public Button
{
public:
    /// \brief Create a ToggleButton with the given parameters.
    /// \param id The Widget's id string.
    /// \param x x-position in parent coordinates.
    /// \param y y-position in parent coordinates.
    /// \param width The width (x-dimension) of Widget.
    /// \param height The height (y-dimension) of Widget.
    /// \param autoExclusive If true, behaves like an exclusive radio button.
    /// \param triggersOnRelease If true, the button is toggled only on release.
    /// \param requirePointerOverOnRelease Require a pointer to be over the
    ///        button to trigger to change states.
    ToggleButton(const std::string& id = "",
                 float x = 0,
                 float y = 0,
                 float width = DEFAULT_WIDTH,
                 float height = DEFAULT_HEIGHT,
                 bool autoExclusive = false,
                 bool triggersOnRelease = false,
                 bool requirePointerOverOnRelease = true);

    /// \brief Destroy the ToggleButton
    virtual ~ToggleButton();

    virtual void onDraw() const override;

};


/// \brief A two state Radio style button.
class RadioButton: public Button
{
public:
    /// \brief Create a RadioButton with the given parameters.
    /// \param id The Widget's id string.
    /// \param x x-position in parent coordinates.
    /// \param y y-position in parent coordinates.
    /// \param width The width (x-dimension) of Widget.
    /// \param height The height (y-dimension) of Widget.
    RadioButton(const std::string& id = "",
                float x = 0,
                float y = 0,
                float width = DEFAULT_WIDTH,
                float height = DEFAULT_HEIGHT);

    /// \brief Destroy the ToggleButton
    virtual ~RadioButton();
    
    virtual void onDraw() const override;

    virtual bool hitTest(const DOM::Position& parentPosition) const override;

};


} } // ofx::MUI
