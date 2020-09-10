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
#ifdef ENABLE_NODE_BASE
	NodeBase(id),
#endif
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

        // Invalidate all cached child geometry.
        invalidateChildShape();

//		element->releaseAllCapturedPointers();
		
		
//		auto removedChild = (*iter).get();
		
		_removeChild((*iter).get());
		
		
//        // Alert the node that its parent was set.
//        ElementEventArgs removedFromEvent(this);
//        ofNotifyEvent(removedChild->removedFrom, removedFromEvent, this);
//
//        ElementEventArgs childRemovedEvent(removedChild);
//        ofNotifyEvent(childRemoved, childRemovedEvent, this);
//
//        /// Alert the node's siblings that it no longer has a sibling.
//        for (auto& child : _children)
//        {
//            if (removedChild != child.get())
//            {
//                ElementEventArgs e(removedChild);
//                ofNotifyEvent(child->siblingRemoved, e, this);
//            }
//        }
//
//		auto doc = document();
//		if(doc)
//		{
//
//			ofNotifyEvent(doc->elementRemovedEvent, childRemovedEvent, this);
//		}
//		else
//		{
//			ofLogWarning("Element::removeChild") << "no document found. This should not happen!";
//		}
//
//		ofRemoveListener(removedChild->shapeChanged, this, &Element::_childShapeChange);
//
//
//
        // Return the detached child.
        // If the return value is ignored, it will be deleted.

		std::unique_ptr<Element> detachedChild = std::move(*iter);

		detachedChild->_parent = nullptr;
		
		// Disown the detached child
		_children.erase(iter);
		
		
        return detachedChild;
    }

    // Return nullptr because we couldn't find anything.
    return nullptr;
}

void Element::_removeChild(Element* child)
{
	
	child->releaseAllCapturedPointers();
	
	
	ElementEventArgs removedFromEvent(this);
	ofNotifyEvent(child->removedFrom, removedFromEvent, this);
	
	ElementEventArgs childRemovedEvent(child);
	ofNotifyEvent(childRemoved, childRemovedEvent, this);
	
	
	auto doc = document();
	if(doc)
	{
		ofNotifyEvent(doc->elementRemovedEvent, childRemovedEvent, this);
	}
	
	
	ofRemoveListener(child->shapeChanged, this, &Element::_childShapeChange);
	// Set the parent to nullptr.
	child->_parent = nullptr;
	
}
void Element::removeAllChildren()
{
//	std::cout << "Element::removeAllChildren()  " << getId() << "\n";
	invalidateChildShape();
	for(auto& child: _children)
	{
		_removeChild(child.get());
//
//			child->releaseAllCapturedPointers();
//
//
//			// Alert the node that its parent was set.
//			ElementEventArgs removedFromEvent(this);
//			ofNotifyEvent(child->removedFrom, removedFromEvent, this);
//
//			ElementEventArgs childRemovedEvent(child.get());
//			ofNotifyEvent(childRemoved, childRemovedEvent, this);
//
//
//			auto doc = document();
//			if(doc)
//			{
//
//				ofNotifyEvent(doc->elementRemovedEvent, childRemovedEvent, this);
//			}
//
//			// Detatch child listeners.
//			  ofRemoveListener(child.get()->shapeChanged, this, &Element::_childShapeChange);
//	//        ofRemoveListener(detachedChild.get()->move, this, &Element::_onChildMoved);
//	//        ofRemoveListener(detachedChild.get()->resize, this, &Element::_onChildResized);
//
//			// Return the detached child.
//			// If the return value is ignored, it will be deleted.
//		// Set the parent to nullptr.
//		child->_parent = nullptr;
//
//			return detachedChild;
	}
	_children.clear();
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
//	if(element!= nullptr && index < _children.size() && _children[index].get() != element)
//	{
		auto iter = findChild(element);
		
		if (iter != _children.end())
		{
			std::size_t oldIndex = iter - _children.begin();
			std::size_t newIndex = index;//std::min(index, _children.size() - 1);
			
			//		if(oldIndex != newIndex)
			//		{
			auto detachedChild = std::move(*iter);
			
			_children.erase(iter);
			
			_children.insert(_children.begin() + newIndex, std::move(detachedChild));
			
			_notifyChildReordered(element, oldIndex, newIndex);
			//        ElementOrderEventArgs e(element, oldIndex, newIndex);
			//        ofNotifyEvent(reordered, e, element);
			//        ofNotifyEvent(childReordered, e, this);
			//		}
			
		}
		else
		{
			throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToIndex: Element does not exist.");
		}
//	}
//	else
//	{
//		throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToIndex: Element is already in the passed index or the index is out of bounds");
////		ofLogNotice("ofxDOM::Element::moveChildToIndex") << "Failed moving as the element
//	}
}


void Element::moveChildToFront(Element* element)
{
	moveChildToIndex(element, 0);
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        std::size_t oldIndex = iter - _children.begin();
//        std::size_t newIndex = 0;
//
//        auto detachedChild = std::move(*iter);
//        _children.erase(iter);
//        _children.insert(_children.begin(), std::move(detachedChild));
//
//		_notifyChildReordered(element, oldIndex, newIndex);
////        ElementOrderEventArgs e(element, oldIndex, newIndex);
////        ofNotifyEvent(reordered, e, element);
////        ofNotifyEvent(childReordered, e, this);
//    }
//    else
//    {
//        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToFront: Element does not exist.");
//    }
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

			_notifyChildReordered(element, oldIndex, newIndex);
//            ElementOrderEventArgs e(element, oldIndex, newIndex);
//            ofNotifyEvent(reordered, e, element);
//            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildForward: Element does not exist.");
    }
}


void Element::moveChildToBack(Element* element)
{
	moveChildToIndex(element, _children.size() - 1);
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        // Make sure it's not already in the back.
//        if (iter != _children.end() - 1)
//        {
//            std::size_t oldIndex = iter - _children.begin();
//            std::size_t newIndex = _children.size() - 1;
//
//            auto detachedChild = std::move(*iter);
//            _children.erase(iter);
//            _children.push_back(std::move(detachedChild));
//
//			_notifyChildReordered(element, oldIndex, newIndex);
////            ElementOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//    else
//    {
//        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Element::moveChildToBack: Element does not exist.");
//    }
}


void Element::moveChildBackward(Element* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
		// Make sure the element is not already at the back
        if (iter != _children.end() - 1)
        {
            std::size_t oldIndex = iter - _children.begin();
			std::size_t newIndex = oldIndex + 1;//_children.size() + 1;

            std::iter_swap(iter, iter + 1);

			_notifyChildReordered(element, oldIndex, newIndex);
//            ElementOrderEventArgs e(element, oldIndex, newIndex);
//            ofNotifyEvent(reordered, e, element);
//            ofNotifyEvent(childReordered, e, this);
        }
    }
}

void Element::_notifyChildReordered(Element* child,  std::size_t oldIndex, std::size_t newIndex)
{
	if(child){
		ElementOrderEventArgs e(child, oldIndex, newIndex);
		ofNotifyEvent(reordered, e, child);
		ofNotifyEvent(childReordered, e, this);
		for(auto& c: _children)
		{
			if(c && c.get() != child)
			{
				ofNotifyEvent(siblingReordered, e, child);
			}
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


float Element::localToScreenX(const float& localX) const
{
    return localX + getScreenX();
}


float Element::localToScreenY(const float& localY) const
{
    return localY + getScreenY();
}


float Element::screenToLocalX(const float& screenX) const
{
    return screenX - getScreenX();   
}


float Element::screenToLocalY(const float& screenY) const
{
    return screenY - getScreenY();
}


float Element::parentToScreenX(const float& parentX) const
{
    if (_parent)
    {
        return parentX + _parent->getScreenX();
    }

    return parentX;
}


float Element::parentToScreenY(const float& parentY) const
{
if (_parent)
    {
        return parentY + _parent->getScreenY();
    }

    return parentY;
}


float Element::screenToParentX(const float& screenX) const
{
    if (_parent)
    {
        return screenX - _parent->getScreenX();
    }

    return screenX;
}


float Element::screenToParentY(const float& screenY) const
{
    if (_parent)
    {
        return screenY - _parent->getScreenY();
    }

    return screenY;
}


void Element::setPosition(float x, float y)
{
	
	ShapeChangeEventArgs e(this);
	e.prevShape = _shape;
    _shape.setPosition(x, y);
	
	e.shape = _shape;
	
	e.findChanges();
	_onShapeChange(e);
	
	ofNotifyEvent(shapeChanged, e, this);
	
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
    if (_parent)
    {
        return getX() + _parent->getScreenX();
    }

    return getX();
}


float Element::getScreenY() const
{
    if (_parent)
    {
        return getY() + _parent->getScreenY();
    }

    return getY();
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
	ShapeChangeEventArgs e(this);
	e.prevShape = _shape;
	
    _shape.setWidth(width);
    _shape.setHeight(height);
    _shape.standardize();

	e.shape = _shape;
	
	e.findChanges();
	_onShapeChange(e);
	
	ofNotifyEvent(shapeChanged, e, this);
	
	
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


void Element::setWidth(float width)
{
    setSize(width, _shape.height);
}


void Element::setHeight(float height)
{
    setSize(_shape.width, height);
}


Shape Element::getShape() const
{
    return _shape;
}


void Element::setShape(const Shape& shape)
{
	
	ShapeChangeEventArgs e(this);
	e.prevShape = _shape;
	
	_shape = shape;
    _shape.standardize();

	e.shape = _shape;
	
	e.findChanges();
	_onShapeChange(e);
	
	ofNotifyEvent(shapeChanged, e, this);
	
	
	//this triggers two event which ends up being redundat.
//    setPosition(shape.x, shape.y);
//    setSize(shape.width, shape.height);
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
		bool bHit = hitTest(parentPosition);
	 	if ((_drawAsViewport && bHit) || !_drawAsViewport) //only allow hits that are inside the parent element.
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
			if(bHit)
				return this;
		}
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


void Element::releaseAllCapturedPointers()
{
	Document* _document = document();

	if (_document)
	{
		for(auto& c: _capturedPointers)
		{
			_document->releasePointerCaptureForElement(this, c.pointerId());
//			releasePointerCapture(c.pointerId());
		}
	}
	else
	{
		throw DOMException(DOMException::INVALID_STATE_ERROR + ": Element::releasePointerCapture");
	}
	_capturedPointers.clear();
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

bool Element::isChildShapeInvalidated() const
{
	return _childShapeInvalid;
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


void Element::_childShapeChange(ShapeChangeEventArgs& a)
{
    invalidateChildShape();
	_onChildShapeChanged(a);
	
}


//void Element::_onChildMoved(MoveEventArgs&)
//{
//    invalidateChildShape();
//}
//
//
//void Element::_onChildResized(ResizeEventArgs&)
//{
//    invalidateChildShape();
//}

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
	std::cout << prefix << getId() << "  " <<  getShape() << "\n";
	prefix += "   ";
	
	for(auto c: children())
	{
		c->printStructure(prefix);
	}
	
}


std::shared_ptr<MUI::Styles> Element::getStyles() const
{
    if (_styles == nullptr)
    {
        auto doc = document();

        if (doc != nullptr)
        {
            _styles = doc->getDocumentStyles();
        }
        else
        {
            ofLogWarning("Widget::getStyles") << "No root document, using default styles.";
            _styles = std::make_shared<MUI::Styles>(getId() +"_Styles");
        }
    }

    return _styles;
}


void Element::setStyles(std::shared_ptr<MUI::Styles> styles)
{
    _styles = styles;
}

void Element::recursiveUpdateLayout()
{
	updateLayout();
	for(auto& c: _children)
	{
		c->recursiveUpdateLayout();
	}
}


void Element::_notifyToDocumentElementAdded(ElementEventArgs& e){
	
	auto doc = document();
	if(doc)
	{
		ofNotifyEvent(doc->elementAddedEvent, e, this);
	}
}

} } // namespace ofx::DOM
