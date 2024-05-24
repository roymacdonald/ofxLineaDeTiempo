//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/SliderGroup.h"


namespace ofx {
namespace MUI {


SliderGroup::SliderGroup(const std::string& id,
                         DOM::Orientation orientation):
    SliderGroup(id, 0, 0, 0, 0, orientation)
{
}


SliderGroup::SliderGroup(const std::string& id,
                         float x,
                         float y,
                         float width,
                         float height,
                         DOM::Orientation orientation):
    Widget(id, x, y, width, height),
    _orientation(orientation)
{
    createLayout<DOM::BoxLayout>(this, orientation);
}


SliderGroup::~SliderGroup()
{
}


void SliderGroup::onDraw() const
{
    ofSetColor(255, 127);
    ofFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());
}


} } // namespace ofx::MUI
