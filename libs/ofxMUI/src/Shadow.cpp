//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Shadow.h"
#include "ofGraphics.h"
#include "ofVectorMath.h"


namespace ofx {
namespace MUI {



//const std::vector<ShadowParam> shadows = {
//    {
//        { 0.24, 90, 2, 6, 3 }, // 1 dp
//        { 0.16, 90, 1, 2, 4 },
//
//        { 0.24, 90, 3, 6, 5 }, // 2 dp
//        { 0.16, 90, 1, 2, 7 },
//
//        { 0.24, 90, 5, 6, 7 }, // 3 dp
//        { 0.16, 90, 2, 2, 10 },
//
//        { 0.24, 90, 7, 6, 10 }, // 4 dp
//        { 0.16, 90, 3, 2, 13 },
//
//        { 0.24, 90, 10, 6, 15 }, // 6 dp
//        { 0.16, 90, 4,  2, 20 },
//
//        { 0.24, 90, 13, 6, 20 }, // 8 dp
//        { 0.16, 90, 5,  2, 27 },
//
//        { 0.24, 90, 18, 6, 27 }, // 9 dp
//        { 0.16, 90, 9,  2, 36 },
//
//        { 0.24, 90, 20, 6, 30 }, // 12 dp
//        { 0.16, 90, 8,  2, 41 },
//
//        { 0.24, 90, 28, 6, 40 }, // 16 dp
//        { 0.16, 90, 11, 2, 53 },
//
//        { 0.24, 90, 39, 6, 60 }, // 24 dp
//        { 0.16, 90, 15, 2, 81 },
//    }
//};
//

void Shadow::draw(const ofRectangle& rect,
                  float windowWidth,
                  float windowHeight,
                  float angleDeg,
                  float distancePx,
                  float spreadPct,
                  float sizePx,
                  const ofFloatColor& color,
                  float cornerRadius,
                  bool inset)
{
//    (180 - $angle) * pi() / 180;
    
    float angleRad = (180 - angleDeg) * glm::pi<float>() / 180;// / 180; glm::radians<float>(angleDeg);
    
    float offsetX = distancePx * std::cos(angleRad);
    float offsetY = distancePx * std::sin(angleRad);

    float spreadRadius = sizePx * spreadPct / 100.0;
    float blurRadius = sizePx - spreadRadius;

    
//    std::cout << "offsetX: " << offsetX << std::endl;
//    std::cout << "offsetY: " << offsetY << std::endl;
//    std::cout << "angleRad: " << angleRad << std::endl;
//    std::cout << "distancePx: " << distancePx << std::endl;
//    std::cout << "spreadPct: " << spreadPct << std::endl;
//    std::cout << "sizePx: " << sizePx << std::endl;

//    blurRadius *= 100;
    
    Shadow::draw(rect,
                 windowWidth,
                 windowHeight,
                 offsetX,
                 offsetY,
                 blurRadius,
                 spreadRadius,
                 ofColor(color),
                 cornerRadius,
                 inset);
}


void Shadow::draw(const ofRectangle& rect,
                  float windowWidth,
                  float windowHeight,
                  float horizontalOffset,
                  float verticalOffset,
                  float blurRadius,
                  float spreadRadius,
                  const ofColor& color,
                  float cornerRadius,
                  bool inset)
{
    ofFloatColor c(color);
    
    ofRectangle _rect = rect;
    _rect.setFromCenter(_rect.getCenter().x + horizontalOffset,
                        _rect.getCenter().y + verticalOffset,
                        _rect.getWidth()    + spreadRadius,
                        _rect.getHeight()   + spreadRadius);
    
    ofShader* shader = cornerRadius > 0 ? &instance().shaderRoundedBoxShadow : &instance().shaderBoxShadow;
    
    shader->begin();
    shader->setUniform4f("box", _rect.getMinX(), _rect.getMinY(), _rect.getMaxX(), _rect.getMaxY());
    shader->setUniform4f("color", c.r, c.g, c.b, c.a);
    shader->setUniform1f("blurRadius", blurRadius);
    shader->setUniform2f("window", windowWidth, windowHeight);
    
    shader->setUniform1f("corner", cornerRadius);
    
    ofFill();
    ofDrawRectangle(0, 0, 1, 1);
    shader->end();
}

Shadow& Shadow::instance()
{
    static Shadow shadow;
    return shadow;
}

    
Shadow::Shadow()
{
    shaderBoxShadow.load("boxShadow");
    shaderRoundedBoxShadow.load("roundedBoxShadow");
}

Shadow::~Shadow()
{
}

    
} } // namespace ofx::MUI



