//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofTexture.h"
#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Styles.h"


namespace ofx {
namespace MUI {


class Icon: public Widget
{
public:
    Icon();

    Icon(const std::string& textureFilename,
         const ofRectangle& textureSubsection = ofRectangle());

    Icon(const ofTexture& texture,
         const ofRectangle& textureSubsection = ofRectangle());

    virtual ~Icon();

    virtual void onDraw() const override;

    /// \brief Set an icon.
    /// \param iconTexture The icon to set.
    /// \param subsection The icon subsection to use if part of an icon sheet.
    void setTexture(const ofTexture& texture,
                    const ofRectangle& textureSubsection = ofRectangle());

private:
    /// \brief The texture icon.
    ofTexture _texture;

    /// \brief The icon subsection.
    ofRectangle _textureSubsection;

};



} } // ofx::MUI
