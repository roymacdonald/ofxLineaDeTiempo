//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <type_traits>
#include <utility>
#include <typeinfo>
#include <string>
#include <cassert>
#include "json.hpp"
#include "ofRectangle.h"
#include "ofTypes.h"


namespace ofx {
namespace DOM {


class Element;
class PointerEvent;


typedef glm::vec2 Position;
typedef glm::vec2 Size;
typedef ofRectangle Shape;

/// \brief The orientation of a Widget.
/// \todo Replace this with ofOrientation.

//    OF_ORIENTATION_DEFAULT = 1,
//    OF_ORIENTATION_180 = 2,
//    OF_ORIENTATION_90_LEFT = 3,
//    OF_ORIENTATION_90_RIGHT = 4,
//    OF_ORIENTATION_UNKNOWN = 5

enum Orientation
{
    /// \brief Locks the Orientation to landscape.
    HORIZONTAL = 0,
    /// \brief Locks the Orientation to portrait.
    VERTICAL = 1,
    /// \brief Sets the Orientation based on the aspect ratio.
    DEFAULT
};


NLOHMANN_JSON_SERIALIZE_ENUM( Orientation, {
    { Orientation::HORIZONTAL, "HORIZONTAL" },
    { Orientation::VERTICAL, "VERTICAL"},
    { Orientation::DEFAULT, "DEFAULT"}
})


template <class T>
using StorageType = typename std::decay<T>::type;

/// \brief C++11 Any class.
/// \sa https://codereview.stackexchange.com/questions/20058/c11-any-class
/// \note This class may change in the near future.
struct Any
{
    bool is_null() const { return !ptr; }
    bool not_null() const { return ptr; }

    template <typename U> Any(U&& value)
    : ptr(new Derived<StorageType<U>>(std::forward<U>(value)))
    {
    }

    template <class U> bool is() const
    {
        typedef StorageType<U> T;

        auto derived = dynamic_cast<Derived<T>*>(ptr);

        return derived;
    }

    template <class U>
    StorageType<U>& as()
    {
        typedef StorageType<U> T;

        auto derived = dynamic_cast<Derived<T>*>(ptr);

        if (!derived)
            throw std::bad_cast();

        return derived->value;
    }

    template <class U>
    operator U()
    {
        return as<StorageType<U>>();
    }

    Any(): ptr(nullptr)
    {
    }

    Any(Any& that): ptr(that.clone())
    {

    }

    Any(Any&& that): ptr(that.ptr)
    {
        that.ptr = nullptr;
    }

    Any(const Any& that): ptr(that.clone())
    {
    }


    Any(const Any&& that): ptr(that.clone())
    {
    }


    Any& operator=(const Any& a)
    {
        if (ptr == a.ptr)
            return *this;

        auto old_ptr = ptr;

        ptr = a.clone();

        if (old_ptr)
            delete old_ptr;

        return *this;
    }

    Any& operator=(Any&& a)
    {
        if (ptr == a.ptr)
            return *this;

        std::swap(ptr, a.ptr);

        return *this;
    }

    ~Any()
    {
        if (ptr)
            delete ptr;
    }

private:
    struct Base
    {
        virtual ~Base() {}

        virtual Base* clone() const = 0;
    };

    template <typename T>
    struct Derived: Base
    {
        template <typename U> Derived(U&& value) : value(std::forward<U>(value)) { }

        T value;

        Base* clone() const { return new Derived<T>(value); }
    };

    Base* clone() const
    {
        if (ptr)
            return ptr->clone();

        return nullptr;
    }

    Base* ptr;
};


} } // namespace ofx::DOM
