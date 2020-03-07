//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Styles.h"
#ifdef USE_OFX_FONTSTASH2
#include "ofxFontStash.h"
#else
#include "ofTrueTypeFont.h"
#endif

namespace ofx {
namespace MUI {


/// \brief A widget label
class Label: public Widget
{
public:
    enum
    {
        NSLineBreakByWordWrapping = 0,
        NSLineBreakByCharWrapping,
        NSLineBreakByClipping,
        NSLineBreakByTruncatingHead,
        NSLineBreakByTruncatingTail,
        NSLineBreakByTruncatingMiddle
    };
//    typedef NSUInteger NSLineBreakMode


    Label(const std::string& text);

    virtual ~Label();

    virtual void onDraw() const override;

    /// \returns the Label text.
    std::string getText() const;

    /// \brief Set the Label text.
    /// \param text The text to set.
    void setText(const std::string& text);

    /// \returns the displayed text.
    std::string displayText() const;

    /// \returns the vertical alignment of the Label text.
    ofAlignVert getVerticalAlignment() const;

    /// \brief Set the vertical alignment of the Label text.
    /// \param alignment The alignment to set.
    void setVerticalAlignment(ofAlignVert alignment);

    /// \returns the horizontal alignment of the Label text.
    ofAlignHorz getHorizontalAlignment() const;

    /// \brief Set the horizontal alignment of the Label text.
    /// \param alignment The alignment to set.
    void setHorizontalAlignment(ofAlignHorz alignment);

private:
    /// \brief The contents of the label.
    ///
    /// If empty, will default to the DOM::Element's id.
    std::string _text;

    /// \brief The text to be displayed.
    ///
    /// The display text is what will actually be displayed. It may be subject
    /// to content replacement, truncation, etc.
    mutable std::string _displayText;

    /// \brief The label's vertical edge to align to.
    ///
    /// If OF_ALIGN_VERT_IGNORE, OF_ALIGN_VERT_CENTER will be used.
    ofAlignVert _alignmentVertical = OF_ALIGN_VERT_CENTER;

    /// \brief The label's horizontal edge to align to.
    ///
    /// If OF_ALIGN_HORZ_IGNORE, OF_ALIGN_HORZ_LEFT will be used.
    ofAlignHorz _alignmentHorzontal = OF_ALIGN_HORZ_LEFT;

};


} } // ofx::MUI
