//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Types.h"
#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Slider.h"


namespace ofx {
namespace MUI {


class SliderGroup: public Widget
{
public:
    SliderGroup(const std::string& id,
                DOM::Orientation orientation);

    SliderGroup(const std::string& id,
                float x = 0,
                float y = 0,
                float width = DEFAULT_WIDTH,
                float height = DEFAULT_HEIGHT,
                DOM::Orientation orientation = DOM::Orientation::HORIZONTAL);

    virtual ~SliderGroup();

    virtual void onDraw() const override;

    ///
    enum
    {
        DEFAULT_WIDTH = 10,
        DEFAULT_HEIGHT = 200
    };

protected:
    /// \brief The ButtonGroup orientation.
    DOM::Orientation _orientation = DOM::Orientation::HORIZONTAL;

};



} } // ofx::MUI
