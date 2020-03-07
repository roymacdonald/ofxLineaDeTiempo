//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Label.h"


namespace ofx {
namespace MUI {


Label::Label(const std::string& text):
    Widget(0, 0, 0, 0),
    _text(text)
{
}


Label::~Label()
{
}


void Label::onDraw() const
{
    // TODO
    
}


std::string Label::getText() const
{
    return _text;
}


void Label::setText(const std::string& text)
{
    _text = text;
}


std::string Label::displayText() const
{
    return _displayText;
}


ofAlignVert Label::getVerticalAlignment() const
{
    return _alignmentVertical;
}


void Label::setVerticalAlignment(ofAlignVert alignment)
{
    _alignmentVertical = alignment;
}


ofAlignHorz Label::getHorizontalAlignment() const
{
    return _alignmentHorzontal;
}


void Label::setHorizontalAlignment(ofAlignHorz alignment)
{
    _alignmentHorzontal = alignment;
}


} } // namespace ofx::MUI
