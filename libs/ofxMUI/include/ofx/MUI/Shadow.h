//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofShader.h"
#include "ofRectangle.h"
#include "ofColor.h"


namespace ofx {
namespace MUI {


class Shadow
{
public:
//    static void draw(float elevation,
//                     const ofFloatColor& color,
//                     float cornerRadius = 0,
//                     bool inset = false);

    static void draw(const ofRectangle& rect,
                     float windowWidth,
                     float windowHeight,
                     float angleDeg,
                     float distancePx,
                     float spreadPct,
                     float sizePx,
                     const ofFloatColor& color,
                     float cornerRadius = 0,
                     bool inset = false);
    
    // https://www.w3schools.com/cssref/css3_pr_box-shadow.asp
    /// \brief horizontalOffset The horizontal offset of the shadow.
    ///
    /// A positive value puts the shadow on the right side of the box, a
    /// negative value puts the shadow on the left side of the box
    ///
    /// The vertical offset of the shadow.
    ///
    /// A positive value puts the shadow below the box, a negative value puts
    /// the shadow above the box.
    ///
    ///
    static void draw(const ofRectangle& rect,
                     float windowWidth,
                     float windowHeight,
                     float horizontalOffset,
                     float verticalOffset,
                     float blurRadius,
                     float spreadRadius,
                     const ofColor& color,
                     float cornerRadius = 0,
                     bool inset = false);

    
    static Shadow& instance();

//    static const std::unordered_map<std::pair<Param, Param>> shadows;

    void reload()
    {
        shaderBoxShadow.load("boxShadow");
        shaderRoundedBoxShadow.load("roundedBoxShadow");
    }
    
private:
    Shadow();
    ~Shadow();
    
    ofShader shaderBoxShadow;
    ofShader shaderRoundedBoxShadow;
};
    

} } // ofx::MUI
