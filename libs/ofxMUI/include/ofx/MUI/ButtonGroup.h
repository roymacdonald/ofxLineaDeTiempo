//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Types.h"
#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Button.h"


namespace ofx {
namespace MUI {


class ButtonGroup;


class ButtonGroupEventArgs: public DOM::EventArgs
{
public:
//    ButtonGroupEventArgs(const std::string& type,
//                         Element* source,
//                         Element* target,
//                         bool bubbles,
//                         bool cancelable,
//                         uint64_t timestamp);


//    static const std::string BUT
//
//
private:
    std::size_t _index;
    Button* _button;
    ButtonGroup* _buttonGroup;

};


class ButtonGroup: public Widget
{
public:
    ButtonGroup(const std::string& id,
                DOM::Orientation orientation);

    ButtonGroup(const std::string& id,
                float x = 0,
                float y = 0,
                float width = Button::DEFAULT_WIDTH,
                float height = Button::DEFAULT_HEIGHT,
                DOM::Orientation orientation = DOM::Orientation::VERTICAL);

    virtual ~ButtonGroup();

    virtual void onDraw() const override;

    template <typename... Args>
    RadioButton* addRadioButton(Args&&... args)
    {
        RadioButton* button = addChild(std::make_unique<RadioButton>(std::forward<Args>(args)...));

        if (button->siblings<Button>().empty())
        {
            button->_value.setWithoutEventNotifications(1);
        }

        return button;
    }

    template <typename... Args>
    ToggleButton* addToggleButton(Args&&... args)
    {
        ToggleButton* button = addChild(std::make_unique<ToggleButton>(std::forward<Args>(args)...));

        return button;
    }

    DOM::DOMEvent<ButtonGroupEventArgs> onButtonGroupEvent;

protected:
    DOM::DOMEvent<ButtonEventArgs> onButtonEvent;
    void _onButtonEvent(ButtonEventArgs& e);

    /// \brief The ButtonGroup orientation.
    DOM::Orientation _orientation = DOM::Orientation::HORIZONTAL;

};


} } // ofx::MUI
