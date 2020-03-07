//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <vector>
#include "ofx/DOM/Types.h"


namespace ofx {
namespace DOM {


class Element;


/// \brief A base class for laying out Elements.
///
/// Generally this class and its subclasses should not be instantiated directly
/// but instead should be created using Element::createLayout<LayoutType>(...).
/// This pattern preserves the ownership of the Layout.
class Layout
{
public:
    /// \brief Create a Layout with a given Element parent.
    /// \param parent The parent Element.
    Layout(Element* parent);

    /// \brief Destroy the layout.
    virtual ~Layout();

    /// \returns a pointer to the parent Element or nullptr if none.
    Element* parent();

    /// \returns true iff this layout is currently being done.
    bool isDoingLayout() const;

    /// \brief Get all of the children for this element.
    std::vector<Element*> children();

    /// \brief Do
    virtual void doLayout() = 0;

protected:
    /// \brief The owning Widget class.
    Element* _parent = nullptr;

    /// \brief True if in doLayout(). Used to prevent recusive calls.
    bool _isDoingLayout = false;

    friend class Element;

};


class BoxLayout: public Layout
{
public:
    /// If the Orientation::DEFAULT is chosen, the default will be set to
    /// Orientation::HORIZONTAL.
    BoxLayout(Element* parent, Orientation orientation = Orientation::VERTICAL);

    virtual ~BoxLayout();

    virtual void doLayout() override;

    Orientation orientation() const;

protected:
    Orientation _orientation = Orientation::HORIZONTAL;

};


} } // ofx::DOM
