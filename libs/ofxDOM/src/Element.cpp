//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/DOM/Element.h"
#include "ofx/DOM/Document.h"
#include "ofGraphics.h"
#include <algorithm>


namespace ofx {
namespace DOM {

Element::Element(const ofRectangle& rect):
Element("", rect.x, rect.y, rect.width, rect.height)
{
	
}
Element::Element(const std::string& id, const ofRectangle& rect):
Element(id, rect.x, rect.y, rect.width, rect.height)
{
	
}
Element::Element(float x, float y, float width, float height):
    Element("", x, y, width, height)
{
}


Element::Element(const std::string& id,
                 float x,
                 float y,
                 float width,
                 float height):
    _id(id),
    _shape(x, y, width, height)
{
}


Element::~Element()
{
}


std::unique_ptr<Element> Element::removeChild(Element* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        // Move the child out of the children array.
        std::unique_ptr<Element> detachedChild = std::move(*iter);

        // Disown the detached child
        _children.erase(iter);

        // Set the parent to nullptr.
        detachedChild->_parent = nullptr;

        // Invalidate all cached child geometry.
        invalidateChildShape();

        // Alert the node that its parent was set.
        ElementEventArgs removedFromEvent(this);
        ofNotifyEvent(detachedChild->removedFrom, removedFromEvent, this);

        ElementEventArgs childRemovedEvent(detachedChild.get());
        ofNotifyEvent(childRemoved, childRemovedEvent, this);

        /// Alert the node's siblings that it no longer has a sibling.
        for (auto& child : _children)
        {
            if (detachedChild.get() != child.get())
            {
                ElementEventArgs e(detachedChild.get());
                ofNotifyEvent(child->siblingRemoved, e, this);
            }
        }

        // Detatch child listeners.
        ofRemoveListener(detachedChild.get()->move, this, &Element::_onChildMoved);
        ofRemoveListener(detachedChild.get()->resize, this, &Element::_onChildResized);

        // Return the detached child.
        // If the return value is ignored, it will be deleted.

        return detachedChild;
    }

    // Return nullptr because we couldn't find anything.
    return nullptr;
}


void Element::moveToFront()
{
    if (_parent)
    {
        _parent->moveChildToFront(this);
    }
}


void Element::moveForward()
{
    if (_parent)
    {
        _parent->moveChildForward(this);
    }
}


void Element::moveToBack()
{
    if (_parent)
    {
        _parent->moveChildToBack(this);
    }
}


void Element::moveBackward()
{
    if (_parent)
    {
        _parent->moveChildBackward(this);
    }
}


void Element::moveChildToIndex(Element* element, std::size_t index)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        std::size_t oldIndex = iter - _children.begin();
        std::size_t newIndex = std::min(index, _children.size() - 1);

        auto detachedChild = std::move(*iter);

        _children.erase(iter);

        _children.insert(_children.begin() + newIndex, std::move(detachedChild));

        ElementOrderEventArgs e(element, oldIndex, newIndex);
        ofNotifyEvent(reordered, e, element);
        ofNotifyEvent(childReordered, e, this);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToFront: Element does not exist.");
    }
}


void Element::moveChildToFront(Element* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        std::size_t oldIndex = iter - _children.begin();
        std::size_t newIndex = 0;

        auto detachedChild = std::move(*iter);
        _children.erase(iter);
        _children.insert(_children.begin(), std::move(detachedChild));

        ElementOrderEventArgs e(element, oldIndex, newIndex);
        ofNotifyEvent(reordered, e, element);
        ofNotifyEvent(childReordered, e, this);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToFront: Element does not exist.");
    }
}


void Element::moveChildForward(Element* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        // Make sure it's not already in the front.
        if (iter != _children.begin())
        {
            std::size_t oldIndex = iter - _children.begin();
            std::size_t newIndex = oldIndex - 1;

            std::iter_swap(iter, iter - 1);

            ElementOrderEventArgs e(element, oldIndex, newIndex);
            ofNotifyEvent(reordered, e, element);
            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildForward: Element does not exist.");
    }
}


void Element::moveChildToBack(Element* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        // Make sure it's not already in the back.
        if (iter != _children.end() - 1)
        {
            std::size_t oldIndex = iter - _children.begin();
            std::size_t newIndex = _children.size() - 1;

            auto detachedChild = std::move(*iter);
            _children.erase(iter);
            _children.push_back(std::move(detachedChild));

            ElementOrderEventArgs e(element, oldIndex, newIndex);
            ofNotifyEvent(reordered, e, element);
            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToBack: Element does not exist.");
    }
}


void Element::moveChildBackward(Element* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        if (iter != _children.end() - 1)
        {
            std::size_t oldIndex = iter - _children.begin();
            std::size_t newIndex = _children.size() + 1;

            std::iter_swap(iter, iter + 1);

            ElementOrderEventArgs e(element, oldIndex, newIndex);
            ofNotifyEvent(reordered, e, element);
            ofNotifyEvent(childReordered, e, this);
        }
    }
}


bool Element::isChild(Element* element) const
{
    return element
        && element->_parent == this;
}


bool Element::isSibling(Element* element) const
{
    return element
        && element->_parent
        && element->_parent == _parent;
}


std::size_t Element::numSiblings() const
{
    // Don't count self.
    return _parent ? (_parent->numChildren() - 1) : 0;
}


std::vector<Element*> Element::siblings()
{
    std::vector<Element*> results;

    if (_parent)
    {
        results.reserve(_parent->_children.size());

        for (auto& child : _parent->_children)
        {
            Element* sibling = child.get();

            if (sibling)
            {
                if (this != sibling)
                {
                    results.push_back(sibling);
                }
            }
            else
            {
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::siblings(): Child element is nullptr.");
            }
        }
    }

    return results;
}


bool Element::isParent(Element* element) const
{
    return element
        && element == this->_parent;
}


std::size_t Element::numChildren() const
{
    return _children.size();
}


std::vector<Element*> Element::children()
{
    std::vector<Element*> results;

    results.reserve(_children.size());

    for (auto& child : _children)
    {
        Element* pChild = child.get();

        if (pChild)
        {
            results.push_back(pChild);
        }
        else
        {
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::children(): Child element is nullptr.");
        }
    }

    return results;
}


bool Element::hasParent() const
{
    return _parent;
}


Element* Element::findFirstChildById(const std::string& id)
{
    auto iter = std::find_if(_children.begin(),
                             _children.end(),
                             [&](const std::unique_ptr<Element>& child) {
                                 return child->getId() == id;
                             });

    return (iter != _children.end()) ? iter->get() : nullptr;
}


std::vector<Element*> Element::findChildrenById(const std::string& id)
{
    std::vector<Element*> matches;

    matches.reserve(_children.size());

    for (auto& child : _children)
    {
        Element* pChild = child.get();

        if (pChild)
        {
            if (child->getId() == id)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::findChildrenById(): Child element is nullptr.");
        }
    }

    return matches;
}


std::vector<std::unique_ptr<Element>>::iterator Element::findChild(Element* element)
{
    return std::find_if(_children.begin(),
                        _children.end(),
                        [&](const std::unique_ptr<Element>& child) {
                            return element == child.get();
                        });
}


Element* Element::parent()
{
    return _parent;
}


const Element* Element::parent() const
{
    return _parent;
}

void Element::setParent(Element* parent)
{
	_parent = parent;
}


Document* Element::document()
{
    if (_parent)
    {
        // If a parent exists, return it recursively.
        return _parent->document();
    }

    // Return self if a Document, otherwise, will return nullptr.
    return dynamic_cast<Document*>(this);

}


const Document* Element::document() const
{
    if (_parent)
    {
        // If a parent exists, return it recursively.
        return _parent->document();
    }

    // Return self if a Document, otherwise, will return nullptr.
    return dynamic_cast<const Document*>(this);
}


bool Element::hitTest(const Position& parentPosition) const
{
    return getShape().inside(parentPosition);
}


bool Element::childHitTest(const Position& localPosition) const
{
    return getChildShape().inside(localPosition);
}


Position Element::localToScreen(const Position& localPosition) const
{
    return localPosition + getScreenPosition();;
}


Position Element::screenToLocal(const Position& screenPosition) const
{
    return screenPosition - getScreenPosition();
}


Position Element::parentToScreen(const Position& parentPosition) const
{
    if (_parent)
    {
        return parentPosition + _parent->getScreenPosition();
    }

    return parentPosition;
}


Position Element::screenToParent(const Position& screenPosition) const
{
    if (_parent)
    {
        return screenPosition - _parent->getScreenPosition();
    }

    return screenPosition;
}


void Element::setPosition(float x, float y)
{
    _shape.setPosition(x, y);
    MoveEventArgs e(getPosition());
    ofNotifyEvent(move, e, this);
}


void Element::setPosition(const Position& position)
{
    setPosition(position.x, position.y);
}


Position Element::getPosition() const
{
    return _shape.getPosition();
}


float Element::getX() const
{
    return _shape.getX();
}


float Element::getY() const
{
    return _shape.getY();
}


void Element::setCenterPosition(float centerX, float centerY)
{
    setPosition(centerX - _shape.width * 0.5f,
                centerY - _shape.height * 0.5f);
}


void Element::setCenterPosition(const Position& center)
{
    setCenterPosition(center.x, center.y);
}


Position Element::getCenterPosition() const
{
    return _shape.getCenter();
}


Position Element::getScreenPosition() const
{
    if (_parent)
    {
        return getPosition() + _parent->getScreenPosition();
    }

    return getPosition();
}

Shape Element::getScreenShape() const{
	return Shape(getScreenPosition(), getWidth(), getHeight() );
}


float Element::getScreenX() const
{
    return getScreenPosition().x;
}


float Element::getScreenY() const
{
    return getScreenPosition().y;
}


Position Element::getScreenCenterPosition() const
{
    if (_parent)
    {
        return getCenterPosition() + _parent->getScreenPosition();
    }

    return getCenterPosition();
}


void Element::setSize(float width, float height)
{
    _shape.setWidth(width);
    _shape.setHeight(height);
    _shape.standardize();
    ResizeEventArgs e(_shape);
    ofNotifyEvent(resize, e, this);
}


Size Element::getSize() const
{
    return Size(_shape.width, _shape.height);
}


float Element::getWidth() const
{
    return _shape.getWidth();
}


float Element::getHeight() const
{
    return _shape.getHeight();
}


Shape Element::getShape() const
{
    return _shape;
}


void Element::setShape(const Shape& shape)
{
    setPosition(shape.x, shape.y);
    setSize(shape.width, shape.height);
}


Shape Element::getChildShape() const
{
    if (_childShapeInvalid)
    {
        _childShape = Shape(); // Clear.

        auto iter = _children.begin();

        while (iter != _children.end())
        {
            const Element* child = iter->get();

            if (child)
            {
                if (iter == _children.begin())
                {
                    _childShape = child->getTotalShape();
                }
                else
                {
                    _childShape.growToInclude(child->getTotalShape());
                }
            }
            else
            {
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::getChildGeometry(): Child element is nullptr.");
            }

            ++iter;
        }

        _childShapeInvalid = false;
    }

    return _childShape;
}

Shape Element::getTotalShape() const
{
    Shape totalShape(_shape);

    if (!_children.empty())
    {
        totalShape.growToInclude(getChildShape() + getPosition());
    }

    return totalShape;
}


std::string Element::getId() const
{
    return _id;
}


void Element::setId(const std::string& id)
{
    _id = id;
}


bool Element::hasAttribute(const std::string& key) const
{
    return _attributes.find(key) != _attributes.end();
}


void Element::setAttribute(const std::string& key, const Any& value)
{
    _attributes[key] = value;

    AttributeEventArgs e(key, value);
    ofNotifyEvent(attributeSet, e, this);
}


void Element::clearAttribute(const std::string& key)
{
    _attributes.erase(key);
    AttributeEventArgs e(key);
    ofNotifyEvent(attributeCleared, e, this);
}



void Element::_setup(ofEventArgs& e)
{
    for (auto& child : _children)
    {
        child->_setup(e);
    }

    onSetup();
}


void Element::_update(ofEventArgs& e)
{
    if (_enabled)
    {
        for (auto& child : _children)
        {
            child->_update(e);
        }

        onUpdate();
    }
}

void Element::_applyTransform(){
	if(_drawAsViewport){
		ofPushView();
		ofViewport({getScreenX(), getScreenY(), _shape.width,_shape.height});
		ofSetupScreen();
	}else{
		ofPushMatrix();
		ofTranslate(_shape.getPosition());
	}
}

void Element::_restoreTransform(){
	if(_drawAsViewport){
		ofPopView();
	}else{
		ofPopMatrix();
	}
}

void Element::_draw(ofEventArgs& e)
{
    if (!_hidden)
    {
		
        ofPushStyle();
		_applyTransform();
		if(!_drawChildrenOnly){
        // Draw parent behind children.
        onDraw();
		}
        // Now draw in reverse order.
        auto iter = _children.rbegin();

        while (iter != _children.rend())
        {
            (*iter)->_draw(e);
            ++iter;
        }

		_restoreTransform();
	
        ofPopStyle();
    }
}


void Element::_exit(ofEventArgs& e)
{
    for (auto& child : _children)
    {
        child->_exit(e);
    }

    onExit();
}


Element* Element::recursiveHitTest(const Position& parentPosition)
{
    if (_enabled)
    {
        Position childLocal = parentPosition - this->getPosition();

        if (!_children.empty() && childHitTest(childLocal))
        {
            for (auto& child : _children)
            {
                Element* target = child->recursiveHitTest(childLocal);

                if (target)
                {
                    return target;
                }
            }
        }

        // If there is no child target, is this a viable target?
        if (hitTest(parentPosition))
        {
            return this;
        }

            return nullptr;
        }

    return nullptr;
}


void Element::setPointerCapture(std::size_t id)
{
    Document* _document = document();

    if (_document)
    {
        _document->setPointerCaptureForElement(this, id);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::setPointerCapture");
    }
}


void Element::releasePointerCapture(std::size_t id)
{
    Document* _document = document();

    if (_document)
    {
        _document->releasePointerCaptureForElement(this, id);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": Element::releasePointerCapture");
    }
}


bool Element::isEnabled() const
{
    return _enabled;
}


void Element::setEnabled(bool enabled_)
{
	if(_enabled != enabled_){
    _enabled = enabled_;
    EnablerEventArgs e(_enabled);
    ofNotifyEvent(enabled, e, this);
}
}


bool Element::isHidden() const
{
    return _hidden;
}


void Element::setHidden(bool hidden_)
{
	if(_hidden != hidden_){
    _hidden = hidden_;
    EnablerEventArgs e(_hidden);
    ofNotifyEvent(hidden, e, this);
}
}


bool Element::isLocked() const
{
    return _locked;
}


void Element::setLocked(bool locked_)
{
	if(_locked != locked_){
    _locked = locked_;
    EnablerEventArgs e(_locked);
    ofNotifyEvent(locked, e, this);
}
}


void Element::setFocusable(bool focusable)
{
    _focusable = focusable;
}


bool Element::isFocusable() const
{
    return _focusable;
}


bool Element::isFocused() const
{
    return _focused;
}


void Element::invalidateChildShape() const
{
    _childShapeInvalid = true;

    if (_parent)
    {
        _parent->invalidateChildShape();
    }

    if (_layout)
    {
        _layout->doLayout();
    }
}


bool Element::isPointerCaptured(std::size_t pointerId) const
{
    return findCapturedPointerById(pointerId) != _capturedPointers.end();
}


std::vector<CapturedPointer>::iterator Element::findCapturedPointerById(std::size_t pointerId)
{
    return std::find_if(_capturedPointers.begin(),
                        _capturedPointers.end(),
                        [pointerId](const CapturedPointer& pointer)
                        {
                            return pointerId == pointer.pointerId();
                        });
}



std::vector<CapturedPointer>::const_iterator Element::findCapturedPointerById(std::size_t pointerId) const
{
     return std::find_if(_capturedPointers.cbegin(),
                         _capturedPointers.cend(),
                         [pointerId](const CapturedPointer& pointer)
                         {
                             return pointerId == pointer.pointerId();
                         });
}


std::vector<CapturedPointer>& Element::capturedPointers()
{
    return _capturedPointers;
}


const std::vector<CapturedPointer>& Element::capturedPointers() const
{
    return _capturedPointers;
}


void Element::setImplicitPointerCapture(bool implicitPointerCapture)
{
    _implicitPointerCapture = implicitPointerCapture;
}


bool Element::getImplicitPointerCapture() const
{
    return _implicitPointerCapture;
}

void Element::_onChildMoved(MoveEventArgs&)
{
    invalidateChildShape();
}


void Element::_onChildResized(ResizeEventArgs&)
{
    invalidateChildShape();
}

void Element::setDrawAsViewport(bool bViewport)
{
	_drawAsViewport = bViewport;
}

bool Element::isDrawingAsViewport()const
{
	return _drawAsViewport;
}

void Element::setDrawChildrenOnly(bool drawChildrenOnly)
{
	_drawChildrenOnly = drawChildrenOnly;
}

bool Element::isDrawingChildrenOnly() const
{
	return _drawChildrenOnly;
}

void Element::printStructure(std::string prefix)
{
	std::cout << prefix << getId() << "  " <<  getShape() <<"\n";
	prefix += "   ";
	
	for(auto c: children())
	{
		c->printStructure(prefix);
	}
	
}


} } // namespace ofx::DOM
