//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once
	

#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Types.h"

namespace ofx {
namespace MUI {


class GrabHandle: public Widget
{
public:
	
    GrabHandle(float x, float y, float radius);
    GrabHandle(float x, float y, float width, float height);
    GrabHandle(const std::string& id, float x, float y, float radius);
    GrabHandle(const std::string& id, float x, float y, float width, float height);
    GrabHandle(const std::string& id, const ofRectangle& rect);
	
    /// \brief Destroy the GrabHandle.
    virtual ~GrabHandle();


    void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt);

protected:
    /// \brief True if the Panel can be resized.
    bool _resizeable = false;

};


} } // ofx::MUI
