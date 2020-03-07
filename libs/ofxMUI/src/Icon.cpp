//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/MUI/Icon.h"
#include "ofImage.h"


namespace ofx {
namespace MUI {


Icon::Icon():
    Widget(0, 0, 0, 0)
{
}

Icon::Icon(const std::string& textureFilename,
           const ofRectangle& textureSubsection):
    Widget(0, 0, 0, 0)
{
    ofTexture texture;
    ofLoadImage(texture, textureFilename);
    setTexture(texture, textureSubsection);
}


Icon::Icon(const ofTexture& texture,
           const ofRectangle& textureSubsection):
    Widget(0, 0, 0, 0)
{
    setTexture(texture, textureSubsection);
}


Icon::~Icon()
{
}


void Icon::onDraw() const
{
    if (_texture.isAllocated())
    {
        DOM::Shape parentShape = hasParent() ? parent()->getShape() : DOM::Shape();

        ofRectangle targetRectangle(5, 5, parentShape.getWidth() - 10, parentShape.getHeight() - 10);
        ofRectangle textureRectangle(0, 0, _texture.getWidth(), _texture.getHeight());

        textureRectangle.scaleTo(targetRectangle, OF_SCALEMODE_FIT);

        auto styles = getStyles();

        if (isPointerDown())
        {
            ofSetColor(styles->getColor(Styles::ROLE_TEXT, Styles::STATE_DOWN));
        }
        else if (isPointerOver())
        {
            ofSetColor(styles->getColor(Styles::ROLE_TEXT, Styles::STATE_OVER));
        }
        else
        {
            ofSetColor(styles->getColor(Styles::ROLE_TEXT, Styles::STATE_NORMAL));
        }

        _texture.drawSubsection(targetRectangle, _textureSubsection);
    }
}


void Icon::setTexture(const ofTexture& texture,
                      const ofRectangle& textureSubsection)
{
    _texture = texture;

    if (textureSubsection.isEmpty())
    {
        _textureSubsection = ofRectangle(0,
                                         0,
                                         _texture.getWidth(),
                                         _texture.getHeight());
    }
    else _textureSubsection = textureSubsection;
}


} } // namespace ofx::MUI
