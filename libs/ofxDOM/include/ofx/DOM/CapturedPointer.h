//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/DOM/Events/DOMEvents.h"


namespace ofx {
namespace DOM {


class Element;

/// \brief A class for keeping track of captured pointers.
class CapturedPointer
{
public:
    /// \brief Create a CapturedPointer with the given id.
    /// \param pointerId The id of the captured pointer.
    CapturedPointer(std::size_t pointerId);

    /// \brief Destroy the captured pointer.
    ~CapturedPointer();

    /// \brief Update a given Captured Pointer from an Element and PointerEvent.
    ///
    /// This method updates offset, position, velocity, lastUpdate and other
    /// parameters of the CapturedPointer.
    ///
    /// \param element The element that is currently handling the Pointer.
    /// \param e The PointerUIEventArgs used to update the CapturedPointer's data.
    void update(Element* element, const PointerUIEventArgs& e);

    /// \returns the captured pointer's id.
    std::size_t pointerId() const;

    OF_DEPRECATED_MSG("Use pointerId().", std::size_t id() const);

    /// \returns the start position of the captured pointer.
    Position start() const;

    /// \returns the start() - position() of the captured pointer.
    Position offset() const;

    /// \returns the current position of the captured pointer.
    Position position() const;

    /// \returns the velocity of the captured pointer (lastPosition() - position()).
    Position velocity() const;

    /// \returns the last update time in milliseconds.
    uint64_t lastUpdateMillis() const;

    OF_DEPRECATED_MSG("Use lastUpdateMillis().", uint64_t lastUpdate() const);

    /// \returns the initial timestamp when the pointer was captured in millisecons.
    uint64_t timestampMillis() const;

    OF_DEPRECATED_MSG("Use timestampMillis().", uint64_t timestamp() const);

    friend std::ostream& operator << (std::ostream& os,
                                      const CapturedPointer& pointer);

private:
    /// \brief The captured pointer's id.
    std::size_t _pointerId = 0;

    /// \brief The captured pointer's start position.
    Position _start;

    /// \brief The captured pointer's current offset from its start position.
    Position _offset;

    /// \brief The captured pointer's current position.
    Position _position;

    /// \brief The captured pointer's current velocity.
    Position _velocity;

    /// \brief The timestamp of the last update in milliseconds.
    uint64_t _lastUpdateMillis;

    /// \brief The timestamp when the pointer was captured in milliseconds.
    uint64_t _timestampMillis;

};


inline std::ostream& operator << (std::ostream& os,
                                  const CapturedPointer& pointer)
{
//    os << pointer.pointerId() << " " << pointer.lastUpdateMillis();
    
	
	os << "pointerId : " << pointer.pointerId()
	<< "\nstart : " << pointer.start()
	<< "\noffset : " << pointer.offset()
	<< "\nposition : " << pointer.position()
	<< "\nvelocity : " << pointer.velocity()
	<< "\nlastUpdateMillis : " << pointer.lastUpdateMillis()
	<< "\ntimestampMillis : " << pointer.timestampMillis() ;
	
	return os;
	
}


} } // namespace ofx::DOM
