//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Label.h"


namespace ofx {
namespace MUI {


Label::Label(const std::string& text):
    Widget(0, 0, 0, 0)
{
	setText(text);
}


Label::~Label()
{
}


void Label::onDraw() const
{
	Widget::onDraw();
	
	ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
	auto & font = getStyles()->getFont(MUI::SMALL);
	
	DOM::Position pos;
	float margin  = 6;
	switch (_alignmentHorzontal)
	{
		case OF_ALIGN_HORZ_IGNORE:
		case OF_ALIGN_HORZ_LEFT: 
			pos.x = margin;
		break;
		case OF_ALIGN_HORZ_RIGHT: 
			pos.x = getWidth() - font.stringWidth(_displayText) - margin;
		break;
		case OF_ALIGN_HORZ_CENTER:
			pos.x = (getWidth() - font.stringWidth(_displayText))*0.5;
		break;
	}

	switch(_alignmentVertical)
	{
		case OF_ALIGN_VERT_IGNORE :
		case OF_ALIGN_VERT_TOP :
			pos.y = font.getAscenderHeight() + margin;
		break;
		case OF_ALIGN_VERT_BOTTOM :
			pos.y = getHeight() - font.getDescenderHeight() - margin;
		break;
		case OF_ALIGN_VERT_CENTER :
			pos.y = LineaDeTiempo::getTextVCenteredPos({0,0,0, getHeight()}, font);
		break;
	}
	
	
	font.drawString(_displayText, pos.x, pos.y);
		
		
    
}


std::string Label::getText() const
{
    return _text;
}


void Label::setText(const std::string& text)
{
    _text = text;
	_displayText = _text;
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
