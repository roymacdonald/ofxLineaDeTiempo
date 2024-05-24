//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/ButtonGroup.h"


namespace ofx {
namespace MUI {

ButtonGroup::ButtonGroup(const std::string& id,
                         DOM::Orientation orientation):
    ButtonGroup(id, 0, 0, 0, 0, orientation)
{
}


ButtonGroup::ButtonGroup(const std::string& id,
                         float x,
                         float y,
                         float width,
                         float height,
                         DOM::Orientation orientation):
    Widget(id, x, y, width, height),
    _orientation(orientation)
{
    createLayout<DOM::BoxLayout>(this, orientation);

    registerEventType(ButtonEventArgs::BUTTON_PRESSED, &onButtonEvent);
    registerEventType(ButtonEventArgs::BUTTON_DOWN, &onButtonEvent);
    registerEventType(ButtonEventArgs::BUTTON_UP, &onButtonEvent);

    addEventListener(onButtonEvent,
                     &ButtonGroup::_onButtonEvent,
                     true,
                     std::numeric_limits<int>::lowest());


}


ButtonGroup::~ButtonGroup()
{
    removeEventListener(onButtonEvent,
                        &ButtonGroup::_onButtonEvent,
                        true,
                        std::numeric_limits<int>::lowest());

}


void ButtonGroup::onDraw() const
{
    ofSetColor(255, 127);
    ofFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}


void ButtonGroup::_onButtonEvent(ButtonEventArgs& e)
{
//    if (e.type() == ButtonEventArgs::BUTTON_DOWN)
//    {
//        if (_exclusive)
//        {
//            for (auto& child : _children)
//            {
//                Button* button = dynamic_cast<Button*>(child.get());
//
//                if (button && button != e.source())
//                {
//                    button->_value.setWithoutEventNotifications(0);
//                }
//                else
//                {
////                    button->_value.setWithoutEventNotifications(1);
//                }
//            }
//        }
//    }
}


    
//Button* ButtonGroup::addButton(const std::string& name)
//{
//    return nullptr;
//}


} } // namespace ofx::MUI



