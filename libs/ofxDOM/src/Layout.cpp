//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/DOM/Layout.h"
#include "ofx/DOM/Element.h"
#include <iostream>


namespace ofx {
namespace DOM {


Layout::Layout(Element* parent): _parent(parent)
{
}


Layout::~Layout()
{
}


Element* Layout::parent()
{
    return _parent;
}


bool Layout::isDoingLayout() const
{
    return _isDoingLayout;
}


std::vector<Element*> Layout::children()
{
    if (_parent)
    {
        return _parent->children();
    }

    std::vector<Element*> _children;
    return _children;
}


BoxLayout::BoxLayout(Element* parent, Orientation orientation):
    Layout(parent),
    _orientation((orientation == Orientation::DEFAULT) ? Orientation::HORIZONTAL : orientation)
{
}


BoxLayout::~BoxLayout()
{
}


void BoxLayout::doLayout()
{
    if (_parent && !_isDoingLayout)
    {
        // Prevent recursive calls to doLayout.
        _isDoingLayout = true;

        float totalWidth = 0;
        float totalHeight = 0;
        float currentX = 0;
        float currentY = 0;

        for (Element* element : children())
        {
            if (element)
            {
                element->setPosition(currentX, currentY);

                if (_orientation == Orientation::HORIZONTAL)
                {
                    totalHeight = std::max(totalHeight, element->getHeight());
                    currentX += element->getWidth();
                    totalWidth = currentX;
                }
                else
                {
                    totalWidth = std::max(totalWidth, element->getWidth());
                    currentY += element->getHeight();
                    totalHeight = currentY;
                }
            }
        }

        _parent->setSize(totalWidth, totalHeight);

        _isDoingLayout = false;
    }
}


Orientation BoxLayout::orientation() const
{
    return _orientation;
}


} } // namespace ofx::DOM
