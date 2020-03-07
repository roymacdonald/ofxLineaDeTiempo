//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


const std::string TrueTypeFontSettings::DEFAULT_FONT = OF_TTF_SANS;


TrueTypeFontSettings::TrueTypeFontSettings(const std::string& filename,
                                           int fontsize,
                                           bool antiAliased,
                                           bool fullCharacterSet,
                                           bool makeContours,
                                           float simplifyAmt,
                                           int dpi):
    _filename(filename),
    _fontsize(fontsize),
    _antiAliased(antiAliased),
    _fullCharacterSet(fullCharacterSet),
    _makeContours(makeContours),
    _simplifyAmt(simplifyAmt),
    _dpi(dpi)
{
}


const std::string& TrueTypeFontSettings::filename() const
{
    return _filename;
}


int TrueTypeFontSettings::fontSize() const
{
    return _fontsize;
}


bool TrueTypeFontSettings::antiAliased() const
{
    return _antiAliased;
}


bool TrueTypeFontSettings::fullCharacterSet() const
{
    return _fullCharacterSet;
}


bool TrueTypeFontSettings::makeContours() const
{
    return _makeContours;
}


float TrueTypeFontSettings::simplifyAmount() const
{
    return _simplifyAmt;
}


int TrueTypeFontSettings::dpi() const
{
    return _dpi;
}


int TrueTypeFontSettings::defaultFontSize(FontSize size)
{
    switch (size)
    {
        case FontSize::EXTRA_SMALL:
            return 8;
        case FontSize::SMALL:
            return 10;
        case FontSize::MEDIUM:
            return 12;
        case FontSize::LARGE:
            return 20;
        case FontSize::EXTRA_LARGE:
            return 32;
        default:
            return 12;
    }
}


TrueTypeFontSettings TrueTypeFontSettings::defaultFontSettings(FontSize size)
{
    return TrueTypeFontSettings(DEFAULT_FONT, defaultFontSize(size));
}


Styles::Styles()
{
    _fonts.assign(EXTRA_LARGE + 1, nullptr);

    // https://color.adobe.com/Neutral-Blue-color-theme-22361/
    ofColor text = ofColor::fromHex(0xFCFFF5); // text
    ofColor accent = ofColor::fromHex(0xD1DBBD); // accent
    ofColor border = ofColor::fromHex(0x91AA9D); // border
    ofColor foreground = ofColor::fromHex(0x3E606F); // foreground
    ofColor background = ofColor::fromHex(0x193441); // background

	_colors.assign(ROLE_TEXT + 1, std::vector<ofColor>(STATE_DISABLED + 1, ofColor()));

    setColors(foreground, background, accent, border, text);
	
	
}


Styles::~Styles()
{
}


const ofColor& Styles::getColor(Role role, State state) const
{
    return _colors[role][state];
}

void Styles::setColor(const ofColor& color, Role role, State state)
{
	_colors[role][state] = color;
}

void Styles::setColor(const ofColor& color, Role role)
{
//    std::vector<ofColor> new_colors(STATE_DISABLED + 1, ofColor());

	if(role == ROLE_FOREGROUND || role == ROLE_BACKGROUND){
	
		_colors[role][STATE_NORMAL] = ofColor(color.r*0.5, color.g*0.5, color.b*0.5);//, 127);
		_colors[role][STATE_OVER] = ofColor(color.r*0.75, color.g*0.75, color.b*0.75);//, 180);
		_colors[role][STATE_DOWN] = color;//, 255);
	}else
	{
		_colors[role][STATE_NORMAL] = color;
		_colors[role][STATE_OVER] = color;
		_colors[role][STATE_DOWN] = color;
	}
    _colors[role][STATE_DISABLED] = ofColor(color, 20);

	
}


void Styles::setColors(const ofColor& foreground,
                       const ofColor& background,
                       const ofColor& accent,
                       const ofColor& border,
                       const ofColor& text)
{
//    std::vector<ofColor> _foreground(STATE_DISABLED + 1, ofColor());
//
//    _foreground[STATE_NORMAL] = ofColor(foreground, 127);
//    _foreground[STATE_OVER] = ofColor(foreground, 180);
//    _foreground[STATE_DOWN] = ofColor(foreground, 255);
//    _foreground[STATE_DISABLED] = ofColor(foreground, 20);
//
//    std::vector<ofColor> _background(STATE_DISABLED + 1, ofColor());
//
//    _background[STATE_NORMAL] = ofColor(background, 127);
//    _background[STATE_OVER] = ofColor(background, 180);
//    _background[STATE_DOWN] = ofColor(background, 255);
//    _background[STATE_DISABLED] = ofColor(background, 20);
//
//    std::vector<ofColor> _accent(STATE_DISABLED + 1, ofColor());
//
//    _accent[STATE_NORMAL] = accent;
//    _accent[STATE_OVER] = accent;
//    _accent[STATE_DOWN] = accent;
//    _accent[STATE_DISABLED] = ofColor(accent, 20);
//
//    std::vector<ofColor> _border(STATE_DISABLED + 1, ofColor());
//
//    _border[STATE_NORMAL] = border;
//    _border[STATE_OVER] = border;
//    _border[STATE_DOWN] = border;
//    _border[STATE_DISABLED] = ofColor(border, 20);
//
//    std::vector<ofColor> _text(STATE_DISABLED + 1, ofColor());
//
//    _text[STATE_NORMAL] = text;
//    _text[STATE_OVER] = text;
//    _text[STATE_DOWN] = text;
//    _text[STATE_DISABLED] = ofColor(text, 20);
//
//    _colors.assign(ROLE_TEXT + 1, std::vector<ofColor>());

    setColor(foreground, ROLE_FOREGROUND);
    setColor(background, ROLE_BACKGROUND);
    setColor(accent, ROLE_ACCENT);
    setColor(border, ROLE_BORDER);
    setColor(text, ROLE_TEXT);
}

const ofTrueTypeFont& Styles::getFont(FontSize size) const
{
    std::shared_ptr<ofTrueTypeFont> font = _fonts[size];

    if (font == nullptr)
    {
        TrueTypeFontSettings settings = TrueTypeFontSettings::defaultFontSettings(size);

        font = std::make_shared<ofTrueTypeFont>();

        if (!font->load(settings.filename(),
                        settings.fontSize(),
                        settings.antiAliased(),
                        settings.fullCharacterSet(),
                        settings.makeContours(),
                        settings.simplifyAmount(),
                        settings.dpi()))
        {
            ofLogError("Styles::getFont") << "Unable to load font: " << settings.filename();
        }

        _fonts[size] = font;
    }

    return *font;
}


void Styles::setFont(FontSize size, std::shared_ptr<ofTrueTypeFont> font)
{
    _fonts[size] = font;
}


} } // namespace ofx::MUI
