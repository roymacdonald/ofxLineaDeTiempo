//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/DOM/CapturedPointer.h"
#include "ofx/DOM/Element.h"


namespace ofx {
namespace DOM {


CapturedPointer::CapturedPointer(std::size_t pointerId):
    _pointerId(pointerId),
    _start(0, 0),
    _offset(0, 0),
    _position(0, 0),
    _velocity(0, 0),
    _lastUpdateMillis(std::numeric_limits<uint64_t>::lowest()),
    _timestampMillis(std::numeric_limits<uint64_t>::lowest())
{
}


CapturedPointer::~CapturedPointer()
{
}


void CapturedPointer::update(Element* element, const PointerUIEventArgs& e)
{
    uint64_t now = ofGetElapsedTimeMillis();

    if (_timestampMillis != std::numeric_limits<uint64_t>::lowest())
    {
        uint64_t dt = now - _lastUpdateMillis;
        Point ds = _position - e.pointer().point().position();

        _velocity = ds.position() / float(dt);
        _position = e.pointer().point().position();
        _lastUpdateMillis = now;
    }
    else
    {
        _pointerId = e.pointer().pointerId();
        _start = e.pointer().point().position();
        _offset = _start - element->getScreenPosition();
        _position = e.pointer().point().position();
        _velocity = Position(0);
        _lastUpdateMillis = now;
        _timestampMillis = now;
    }
}


std::size_t CapturedPointer::pointerId() const
{
    return _pointerId;
}


std::size_t CapturedPointer::id() const
{
    return _pointerId;
}


Position CapturedPointer::start() const
{
    return _start;
}


Position CapturedPointer::offset() const
{
    return _offset;
}


Position CapturedPointer::position() const
{
    return _position;
}


Position CapturedPointer::velocity() const
{
    return _velocity;
}


uint64_t CapturedPointer::lastUpdateMillis() const
{
    return _lastUpdateMillis;
}


uint64_t CapturedPointer::lastUpdate() const
{
    return lastUpdateMillis();
}


uint64_t CapturedPointer::timestampMillis() const
{
    return _timestampMillis;
}


uint64_t CapturedPointer::timestamp() const
{
    return timestampMillis();
}


} } // namespace ofx::DOM
