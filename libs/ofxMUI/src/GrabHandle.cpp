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


void GrabHandle::onDraw() const
{
    // ofPushStyle();
    // ofFill();

    // // Translate for circle center.
    // ofPushMatrix();
    // ofTranslate(getWidth() / 2, getHeight() / 2);

    // auto styles = getStyles();

    // if (isPointerDown())
    // {
    //     ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_DOWN));
    // }
    // else if (isPointerOver())
    // {
    //     ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_OVER));
    // }
    // else
    // {
    //     ofSetColor(styles->getColor(Styles::ROLE_BACKGROUND, Styles::STATE_NORMAL));
    // }

    // ofDrawEllipse(0, 0, getWidth(), getHeight());

    // ofNoFill();

    // if (isPointerDown())
    // {
    //     ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_DOWN));
    // }
    // else if (isPointerOver())
    // {
    //     ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_OVER));
    // }
    // else
    // {
    //     ofSetColor(styles->getColor(Styles::ROLE_BORDER, Styles::STATE_NORMAL));
    // }

    // ofDrawEllipse(0, 0, getWidth() - 1, getHeight() - 1);
    // ofPopStyle();

    // if (isFocused())
    // {
    //     ofPushStyle();
    //     ofNoFill();
    //     ofSetColor(255, 255, 0, 200);
    //     int offset = 1;
    //     ofDrawEllipse(-offset,
    //                   -offset,
    //                   getWidth() + offset * 2,
    //                   getHeight() + offset * 2);
    //     ofPopStyle();
    // }

    // ofPopMatrix();

    Widget::onDraw();
	
	
//    for (const auto& child: children<GrabHandle>())
//    {
//        glm::vec3 a = getShape().getCenter() - getShape().getPosition();
//        glm::vec3 b = child->getShape().getCenter();
//        glm::vec3 d = (a - b);
//        glm::vec3 m = (a + b) / 2.0;
//        glm::vec3 n = glm::normalize(d);
//        glm::vec3::value_type l = glm::distance(a, b);
//        glm::vec3::value_type h1 = l * 0.5f - getShape().getWidth() / 2 * 1.5;
//        glm::vec3::value_type h2 = l * 0.5f - child->getShape().getWidth() / 2 * 1.5;
//
//        glm::vec3 aa = m + n * h1;
//        glm::vec3 bb = m - n * h2;
//
//        if (h1 + h2 > 0 )
//        {
//            ofDrawLine(aa, bb);
//        }
//    }
}


void GrabHandle::onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt)
{
    if (this == evt.target())
    {
        ofLogNotice("GrabHandle::onKeyboardDownEvent") << evt.toString();
    }
}

} } // namespace ofx::MUI
