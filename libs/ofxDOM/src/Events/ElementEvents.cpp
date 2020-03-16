//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/DOM/Events/ElementEvents.h"
#include "ofx/DOM/Element.h"


namespace ofx {
namespace DOM {


MoveEventArgs::MoveEventArgs(const Position& position):
    _position(position)
{
}


MoveEventArgs::~MoveEventArgs()
{
}


const Position& MoveEventArgs::position() const
{
    return _position;
}


ResizeEventArgs::ResizeEventArgs(const Shape& shape):
    _shape(shape)
{
}


ResizeEventArgs::~ResizeEventArgs()
{
}


const Shape& ResizeEventArgs::shape() const
{
    return _shape;
}


AttributeEventArgs::AttributeEventArgs(const std::string& key,
                                       const Any& value):
    _key(key),
    _value(value)
{
}


AttributeEventArgs::~AttributeEventArgs()
{
}


const std::string& AttributeEventArgs::key() const
{
    return _key;
}


const Any& AttributeEventArgs::value() const
{
    return _value;
}


EnablerEventArgs::EnablerEventArgs(bool value):
    _value(value)
{
}


EnablerEventArgs::~EnablerEventArgs()
{
}


bool EnablerEventArgs::value() const
{
    return _value;
}


} } // namespace ofx::DOM
