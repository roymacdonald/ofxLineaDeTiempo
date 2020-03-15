//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//

//
#pragma once
//
//
#include <string>
//#include <type_traits>
//#include <utility>
//#include <ctime>
//#include "ofEvents.h"
//#include "ofx/PointerEvents.h"
//#include "ofx/DOM/Exceptions.h"
#include "ofx/DOM/Types.h"
//

namespace ofx {
namespace DOM {


class MoveEventArgs
{
public:
    MoveEventArgs(const Position& position);
    virtual ~MoveEventArgs();

    const Position& position() const;

protected:
    Position _position;

};


class ResizeEventArgs
{
public:
    /// \brief Construct a ResizeEventArgs with the given shape.
    /// \param shape The new shape.
    ResizeEventArgs(const Shape& shape);

    /// \brief Destroy the ResizeEventArgs.
    virtual ~ResizeEventArgs();

    const Shape& shape() const;

protected:
    Shape _shape;

};


class AttributeEventArgs
{
public:
    /// \brief Create an AttributeEventArgs with the given parameters.
    /// \param key The key associated with this event.
    /// \param value The value associated with this event.
    AttributeEventArgs(const std::string& key, const Any& value = Any());

    /// \brief Destroy the AttributeEventArgs.
    virtual ~AttributeEventArgs();

    /// \returns the key associated with this event.
    const std::string& key() const;

    /// \returns the value associated with this event.
    const Any& value() const;

protected:
    /// \brief The key associated with this event.
    std::string _key;

    /// \brief The value associated with this event.
    Any _value;

};


class EnablerEventArgs
{
public:
    EnablerEventArgs(bool value);
    virtual ~EnablerEventArgs();

    bool value() const;

protected:
    bool _value = false;

};
} } // namespace ofx::DOM
