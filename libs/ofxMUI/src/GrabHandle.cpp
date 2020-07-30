//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/GrabHandle.h"
#include "ofx/MUI/Styles.h"
#include "ofGraphics.h"


namespace ofx {
namespace MUI {


GrabHandle::GrabHandle(float x, float y, float radius):
    GrabHandle(x, y, radius * 2, radius * 2)
{

}
GrabHandle::GrabHandle(const std::string& id, const ofRectangle& rect):
    GrabHandle(id, rect.x, rect.y, rect.width, rect.height)
{
	
}

GrabHandle::GrabHandle(float x, float y, float width, float height):
    GrabHandle("", x, y, width, height)
{
}

GrabHandle::GrabHandle(const std::string& id, float x, float y, float radius):
    GrabHandle(id, x, y, radius * 2, radius * 2)
{
}


GrabHandle::GrabHandle(const std::string& id, float x, float y, float width, float height):
    Widget(id, x, y, width, height)
{
    addEventListener(keyDown,
                     &GrabHandle::onKeyboardDownEvent,
                     false,
                     std::numeric_limits<int>::lowest());
	setShapeDrawMode(ShapeDrawMode::ELLIPSE);//so it behaves as the original implementation
    setDraggable(true);
}


GrabHandle::~GrabHandle()
{
}


void GrabHandle::onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt)
{
    if (this == evt.target())
    {
        ofLogNotice("GrabHandle::onKeyboardDownEvent") << evt.toString();
    }
}

} } // namespace ofx::MUI
