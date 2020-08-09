//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


std::string TrueTypeFontSettings::DEFAULT_FONT = OF_TTF_SANS;


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

void TrueTypeFontSettings::setDefaultFont(const std::string& filepath)
{
	DEFAULT_FONT = filepath;
}

TrueTypeFontSettings TrueTypeFontSettings::defaultFontSettings(FontSize size)
{
    return TrueTypeFontSettings(DEFAULT_FONT, defaultFontSize(size));
}
#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER
std::string Styles::toString(Styles::Role role)
{
    
    if(role == Styles::ROLE_FOREGROUND) return "FOREGROUND";
    if(role == Styles::ROLE_BACKGROUND) return "BACKGROUND";
    if(role == Styles::ROLE_ACCENT) return "ACCENT";
    if(role == Styles::ROLE_BORDER_FOREGROUND) return "BORDER_FOREGROUND";
	if(role == Styles::ROLE_BORDER_BACKGROUND) return "BORDER_BACKGROUND";
    if(role == Styles::ROLE_TEXT) return "TEXT";
    
    return "";

}
 std::string Styles::toString(Styles::State state)
 {
    
    if(state == Styles::STATE_NORMAL) return "NORMAL";
    if(state == Styles::STATE_OVER) return "OVER";
    if(state == Styles::STATE_DOWN) return "DOWN";
    if(state == Styles::STATE_DISABLED) return "DISABLED";
    
    return "";
}
#endif


Styles::Styles(const std::string& name)
:_name(name)
{
    _fonts.assign(EXTRA_LARGE + 1, nullptr);

    // https://color.adobe.com/Neutral-Blue-color-theme-22361/
    ofColor text (255); // text
    ofColor accent  (225); // accent
    ofColor border_foreground (140); // border
	ofColor border_background  (140); // border
    ofColor foreground (200); // foreground
    ofColor background (55); // background

#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER

	parameters.setName(_name );
	_colors.resize(ROLE_TEXT + 1);
	_paramGroups.resize(_colors.size());
	
	for(int r = 0; r < _colors.size(); r++)
	{
		_colors[r].resize(STATE_DISABLED + 1);
		
		auto roleStr = toString(Role(r));
		
		_paramGroups[r].setName(roleStr);
		
		for(int s = 0; s < _colors[r].size(); s++)
		{
			_colors[r][s].set(roleStr + "_" + toString(State(s)), ofColor(255), ofColor(0,0,0,0), ofColor(255,255,255,255));
			_paramGroups[r].add(_colors[r][s]);
		}
		parameters.add(_paramGroups[r]);
	}
#else
	_colors.assign(ROLE_TEXT + 1, std::vector<ofColor>(STATE_DISABLED + 1, ofColor()));
#endif
    setColors(foreground, background, accent, border_foreground, border_background, text);
	
	
}


Styles::~Styles()
{
}

void Styles::print()
{
	
	
	for(int r = 0; r < _colors.size(); r++)
	{
		for(int s = 0; s < _colors[r].size(); s++)
		{
			std::cout << toString(Role(r)) << " " << toString(State(s)) << ": ";
#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER
			std::cout << _colors[r][s].get() << "\n";
#else
			std::cout << _colors[r][s] << "\n";
#endif
		}
	}
}

const std::string& Styles::getName() const
{
	return _name;
}

const ofColor& Styles::getColor(Role role, State state) const
{
#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER
    return _colors[role][state].get();
#else
    return _colors[role][state];
#endif
}

void Styles::setColor(const ofColor& color, Role role, State state)
{
	_colors[role][state] = color;
}

void Styles::setColor(const ofColor& color, Role role)
{
//    std::vector<ofColor> new_colors(STATE_DISABLED + 1, ofColor());

	if(role != ROLE_TEXT ){
	
		_colors[role][STATE_NORMAL] = ofColor(color.r*0.5, color.g*0.5, color.b*0.5);//, 127);
		_colors[role][STATE_OVER] = ofColor(color.r*0.75, color.g*0.75, color.b*0.75);//, 180);
		_colors[role][STATE_DOWN] = color;//, 255);
	}
	else
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
                       const ofColor& border_foreground,
					   const ofColor& border_background,
                       const ofColor& text)
{
    setColor(foreground, ROLE_FOREGROUND);
    setColor(background, ROLE_BACKGROUND);
    setColor(accent, ROLE_ACCENT);
	setColor(border_foreground, ROLE_BORDER_FOREGROUND);
	setColor(border_background, ROLE_BORDER_BACKGROUND);
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
                        (size == FontSize::EXTRA_SMALL ? false: settings.antiAliased()),
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
