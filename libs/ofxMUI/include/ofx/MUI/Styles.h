//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "json.hpp"
#include "ofColor.h"
#include "ofTrueTypeFont.h"


#define LINEA_DE_TIEMPO_USE_OF_PARAMETER
#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER
#include "ofParameter.h"
#endif
namespace ofx {
namespace MUI {


enum FontSize
{
    EXTRA_SMALL = 0,
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 3,
    EXTRA_LARGE = 4
};


NLOHMANN_JSON_SERIALIZE_ENUM( FontSize, {
    { EXTRA_SMALL, "EXTRA_SMALL" },
    { SMALL, "SMALL"},
    { MEDIUM, "MEDIUM"},
    { LARGE, "LARGE"},
    { EXTRA_LARGE, "EXTRA_LARGE"}
})

    
class TrueTypeFontSettings
{
public:
    TrueTypeFontSettings(const std::string& filename = DEFAULT_FONT,
                         int fontsize = defaultFontSize(FontSize::MEDIUM),
                         bool antiAliased = true,
                         bool fullCharacterSet = true,
                         bool makeContours = false,
                         float simplifyAmt = 0.3f,
                         int dpi = 0);

    const std::string& filename() const;
    int fontSize() const;
    bool antiAliased() const;
    bool fullCharacterSet() const;
    bool makeContours() const;
    float simplifyAmount() const;
    int dpi() const;

    /// \brief The default font name.
    static std::string DEFAULT_FONT;

	
	static void setDefaultFont(const std::string& filepath);
	
	
    /// \brief Get the font size in pixels for the given FontSize.
    /// \param size The named FontSize.
    /// \returns the size in pixels.
    static int defaultFontSize(FontSize size = FontSize::MEDIUM);

    static TrueTypeFontSettings defaultFontSettings(FontSize size = FontSize::MEDIUM);

private:
    std::string _filename;
    int _fontsize = defaultFontSize(FontSize::MEDIUM);
    bool _antiAliased = true;
    bool _fullCharacterSet = true;
    bool _makeContours = false;
    float _simplifyAmt = 0.3f;
    int _dpi = 0;

};


inline void to_json(nlohmann::json& j, const TrueTypeFontSettings& v)
{
    j["filename"] = v.filename();
    j["font_size"] = v.fontSize();
    j["anti_aliased"] = v.antiAliased();
    j["full_character_set"] = v.fullCharacterSet();
    j["make_contours"] = v.makeContours();
    j["simplify_amount"] = v.simplifyAmount();
    j["dpi"] = v.dpi();
}


inline void from_json(const nlohmann::json& j, TrueTypeFontSettings& v)
{
    v = TrueTypeFontSettings(j["filename"],
                             j["font_size"],
                             j["anti_aliased"] ,
                             j["full_character_set"],
                             j["make_contours"],
                             j["simplify_amount"] ,
                             j["dpi"]);
}


/// \brief A common class for setting shared Widget styles.
class Styles
{
public:
    /// \brief Each Style has a role.
    enum Role
    {
        /// \brief Styles applied to the foreground.
        ROLE_FOREGROUND = 0,
        /// \brief Styles applied to the background.
        ROLE_BACKGROUND,
        /// \brief Styles applied to the accent areas.
        ROLE_ACCENT,
        /// \brief Styles applied to the foreground's borders.
        ROLE_BORDER_FOREGROUND,
		/// \brief Styles applied to the background's borders.
        ROLE_BORDER_BACKGROUND,
        /// \brief Styles applied to the text.
        ROLE_TEXT
    };

    /// \brief Each style can also be applied to an interaction state.
    enum State
    {
        /// \brief The normal target is idle.
        STATE_NORMAL = 0,
        /// \brief The state when a pointer is over the target.
        STATE_OVER,
        /// \brief The state when a target is down.
        STATE_DOWN,
        /// \brief The state when a target is disabled.
        STATE_DISABLED
    };

    /// \brief Create a default styles.
    Styles(const std::string& name);
	
    /// \brief Destroy these styles.
    virtual ~Styles();

    /// \brief Set colors for each role in the Style.
    /// \param foreground The foreground color.
    /// \param background The background color.
    /// \param accent The accent color.
	/// \param border_foreground The foreground's border color.
	/// \param border_background The background's border color.
    /// \param text The text color.
    void setColors(const ofColor& foreground,
                   const ofColor& background,
                   const ofColor& accent,
                   const ofColor& border_foreground,
				   const ofColor& border_background,
                   const ofColor& text);

    /// \brief Get the ofColor for a given Role and State.
    /// \param role The Role desired.
    /// \param state The State desired.
    /// \returns an ofColor for the given role and state.
    const ofColor& getColor(Role role, State state) const;

    /// \brief Set the ofColor for a given Role and State.
    /// \param color The color to set.
    /// \param role The Role desired.
    /// \param state The State desired.
    void setColor(const ofColor& color, Role role, State state);

    /// \brief Set all the ofColor s for a given Role, using the default states
	/// each state will get the same color but with different opacity.
    /// \param color The color to set.
    /// \param role The Role desired.
	
    void setColor(const ofColor& color, Role role);

	
	
    /// \brief Get the font for a given FontSize.
    /// \param size The font size to get.
    /// \returns a reference to the requested font.
    const ofTrueTypeFont& getFont(FontSize size = FontSize::MEDIUM) const;

    /// \brief Set the font for a given FontSize.
    /// \param size The FontSize for the font.
    /// \param font The cached font to use.
    void setFont(FontSize size, std::shared_ptr<ofTrueTypeFont> font);

	
	///\brief get the name
	///\returns std::string with the name
	const std::string& getName() const;
#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER
	ofParameterGroup parameters;
#endif
	void print();
protected:
    /// \brief A collection of colors for this Style.
#ifdef LINEA_DE_TIEMPO_USE_OF_PARAMETER
	std::vector<std::vector<ofParameter<ofColor>>> _colors;
	
	std::vector<ofParameterGroup> _paramGroups;
#else
	std::vector<std::vector<ofColor>> _colors;
#endif
    /// \brief A font cache for this Style.
    mutable std::vector<std::shared_ptr<ofTrueTypeFont>> _fonts;

	std::string _name = "";
	
	
public:
	static std::string toString(State s);
	
	static std::string toString(Role r);
	
	
	
	
};


NLOHMANN_JSON_SERIALIZE_ENUM( Styles::Role, {
    { Styles::Role::ROLE_FOREGROUND, "ROLE_FOREGROUND" },
    { Styles::Role::ROLE_BACKGROUND, "ROLE_BACKGROUND"},
    { Styles::Role::ROLE_ACCENT, "ROLE_ACCENT"},
    { Styles::Role::ROLE_BORDER_FOREGROUND, "ROLE_BORDER_FOREGROUND"},
    { Styles::Role::ROLE_BORDER_BACKGROUND, "ROLE_BORDER_BACKGROUND"},
    { Styles::Role::ROLE_TEXT, "ROLE_TEXT"}
})


NLOHMANN_JSON_SERIALIZE_ENUM( Styles::State, {
    { Styles::State::STATE_NORMAL, "STATE_NORMAL" },
    { Styles::State::STATE_OVER, "STATE_OVER"},
    { Styles::State::STATE_DOWN, "STATE_DOWN"},
    { Styles::State::STATE_DISABLED, "STATE_DISABLED"}
})


} } // ofx::MUI
