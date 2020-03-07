//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <stdexcept>
#include <string>


namespace ofx {
namespace DOM {


/// \brief A generic DOM exception.
class DOMException: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;

    /// \brief Invalid pointer id exception.
    static const std::string INVALID_POINTER_ID;

    /// \brief Invalid state exception.
    static const std::string INVALID_STATE_ERROR;

    /// \brief Unregistered event exception.
    static const std::string UNREGISTERED_EVENT;

    /// \brief Invalid attribute key exception.
    static const std::string INVALID_ATTRIBUTE_KEY;

};


} } // namespace ofx::DOM
