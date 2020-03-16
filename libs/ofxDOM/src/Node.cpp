//
//  Node.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/14/20.
//


#include "ofx/DOM/Node.h"
#include "ofx/DOM/Element.h"
#include <algorithm>


namespace ofx {
namespace DOM {

//template<typename NodeType>
//Node<NodeType>::Node(const std::string& id)
//
//{}

//template<typename NodeType>
//Node<NodeType>::~Node()
//{
//}

//template<typename NodeType>
//void Node<NodeType>::invalidateChild() const
//{
// 
//
//}


template<typename NodeType>
std::unique_ptr<NodeType> Node<NodeType>::removeChild(NodeType* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        // Move the child out of the children array.
        std::unique_ptr<NodeType> detachedChild = std::move(*iter);

        // Disown the detached child
        _children.erase(iter);

        // Set the parent to nullptr.
        detachedChild->_parent = nullptr;

        // Invalidate all cached child geometry.
        invalidateChild();

        // Alert the node that its parent was set.
        NodeEventArgs removedFromEvent(this);
        ofNotifyEvent(detachedChild->removedFrom, removedFromEvent, this);

        NodeEventArgs childRemovedEvent(detachedChild.get());
        ofNotifyEvent(childRemoved, childRemovedEvent, this);

        /// Alert the node's siblings that it no longer has a sibling.
        for (auto& child : _children)
        {
            if (detachedChild.get() != child.get())
            {
                NodeEventArgs e(detachedChild.get());
                ofNotifyEvent(child->siblingRemoved, e, this);
            }
        }

        
        // Detatch child listeners.
        
//        ofRemoveListener(detachedChild.get()->move, this, &Node<NodeType>::_onChildMoved);
//        ofRemoveListener(detachedChild.get()->resize, this, &Node<NodeType>::_onChildResized);

        // Return the detached child.
        // If the return value is ignored, it will be deleted.

        return detachedChild;
    }

    // Return nullptr because we couldn't find anything.
    return nullptr;
}


template<typename NodeType>
void Node<NodeType>::moveToFront()
{
    if (_parent)
    {
        _parent->moveChildToFront(this);
    }
}


template<typename NodeType>
void Node<NodeType>::moveForward()
{
    if (_parent)
    {
        _parent->moveChildForward(this);
    }
}


template<typename NodeType>
void Node<NodeType>::moveToBack()
{
    if (_parent)
    {
        _parent->moveChildToBack(this);
    }
}


template<typename NodeType>
void Node<NodeType>::moveBackward()
{
    if (_parent)
    {
        _parent->moveChildBackward(this);
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildToIndex(NodeType* element, std::size_t index)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        std::size_t oldIndex = iter - _children.begin();
        std::size_t newIndex = std::min(index, _children.size() - 1);

        auto detachedChild = std::move(*iter);

        _children.erase(iter);

        _children.insert(_children.begin() + newIndex, std::move(detachedChild));

        NodeOrderEventArgs e(element, oldIndex, newIndex);
        ofNotifyEvent(reordered, e, element);
        ofNotifyEvent(childReordered, e, this);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToFront: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildToFront(NodeType* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        std::size_t oldIndex = iter - _children.begin();
        std::size_t newIndex = 0;

        auto detachedChild = std::move(*iter);
        _children.erase(iter);
        _children.insert(_children.begin(), std::move(detachedChild));

        NodeOrderEventArgs e(element, oldIndex, newIndex);
        ofNotifyEvent(reordered, e, element);
        ofNotifyEvent(childReordered, e, this);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToFront: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildForward(NodeType* element)
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

            NodeOrderEventArgs e(element, oldIndex, newIndex);
            ofNotifyEvent(reordered, e, element);
            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildForward: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildToBack(NodeType* element)
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

            NodeOrderEventArgs e(element, oldIndex, newIndex);
            ofNotifyEvent(reordered, e, element);
            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToBack: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildBackward(NodeType* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        if (iter != _children.end() - 1)
        {
            std::size_t oldIndex = iter - _children.begin();
            std::size_t newIndex = _children.size() + 1;

            std::iter_swap(iter, iter + 1);

            NodeOrderEventArgs e(element, oldIndex, newIndex);
            ofNotifyEvent(reordered, e, element);
            ofNotifyEvent(childReordered, e, this);
        }
    }
}


template<typename NodeType>
bool Node<NodeType>::isChild(NodeType* element) const
{
    return element
        && element->_parent == this;
}


template<typename NodeType>
bool Node<NodeType>::isSibling(NodeType* element) const
{
    return element
        && element->_parent
        && element->_parent == _parent;
}


template<typename NodeType>
std::size_t Node<NodeType>::numSiblings() const
{
    // Don't count self.
    return _parent ? (_parent->numChildren() - 1) : 0;
}

template<typename NodeType>
const NodeType* Node<NodeType>::cast() const
{
	return static_cast<NodeType*>(this);
}

template<typename NodeType>
NodeType* Node<NodeType>::cast()
{
	return static_cast<NodeType*>(this);
}
template<typename NodeType>
NodeType* Node<NodeType>::getChildByIndex( std::size_t index)
{
	if(_children.size() <= index)return nullptr;
	return _children[index].get();
	
}
template<typename NodeType>
const NodeType* Node<NodeType>::getChildByIndex( std::size_t index) const
{
	if(_children.size() <= index)return nullptr;
	return _children[index].get();
}

template<typename NodeType>
std::vector<NodeType*> Node<NodeType>::siblings()
{
    std::vector<NodeType*> results;

    if (_parent)
    {
        results.reserve(_parent->_children.size());

        for (auto& child : _parent->_children)
        {
            NodeType* sibling = child.get();

            if (sibling)
            {
                if (this != sibling)
                {
                    results.push_back(sibling);
                }
            }
            else
            {
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::siblings(): Sibling element is nullptr.");
            }
        }
    }

    return results;
}


template<typename NodeType>
std::vector<const NodeType*> Node<NodeType>::siblings() const
{
    std::vector<const NodeType*> results;

    if (_parent)
    {
        results.reserve(_parent->_children.size());

        for (auto& child : _parent->_children)
        {
            const NodeType* sibling = child.get();

            if (sibling)
            {
                if (this != sibling)
                {
                    results.push_back(sibling);
                }
            }
            else
            {
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::siblings(): Sibling element is nullptr.");
            }
        }
    }

    return results;
}


template<typename NodeType>
bool Node<NodeType>::isParent(const NodeType* element) const
{
    return element
        && element == this->_parent;
}


template<typename NodeType>
std::size_t Node<NodeType>::numChildren() const
{
    return _children.size();
}


template<typename NodeType>
std::vector<NodeType*> Node<NodeType>::children()
{
    std::vector<NodeType*> results;

    results.reserve(_children.size());

    for (auto& child : _children)
    {
        NodeType* pChild = child.get();

        if (pChild)
        {
            results.push_back(pChild);
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::children(): Child element is nullptr.");
        }
    }

    return results;
}


template<typename NodeType>
std::vector<const NodeType*> Node<NodeType>::children() const
{
    std::vector<const NodeType*> results;

    results.reserve(_children.size());

    for (auto& child : _children)
    {
        const NodeType* pChild = child.get();

        if (pChild)
        {
            results.push_back(pChild);
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::children(): Child element is nullptr.");
        }
    }

    return results;
}


template<typename NodeType>
bool Node<NodeType>::hasParent() const
{
    return _parent;
}


template<typename NodeType>
const NodeType* Node<NodeType>::findFirstChildById(const std::string& id) const
{
    auto iter = std::find_if(_children.begin(),
                             _children.end(),
                             [&](const std::unique_ptr<NodeType>& child) {
                                 return child->getId() == id;
                             });

    return (iter != _children.end()) ? iter->get() : nullptr;
}


template<typename NodeType>
NodeType* Node<NodeType>::findFirstChildById(const std::string& id)
{
    auto iter = std::find_if(_children.begin(),
                             _children.end(),
                             [&](const std::unique_ptr<NodeType>& child) {
                                 return child->getId() == id;
                             });

    return (iter != _children.end()) ? iter->get() : nullptr;
}


template<typename NodeType>
std::vector<NodeType*> Node<NodeType>::findChildrenById(const std::string& id)
{
    std::vector<NodeType*> matches;

    matches.reserve(_children.size());

    for (auto& child : _children)
    {
        NodeType* pChild = child.get();

        if (pChild)
        {
            if (child->getId() == id)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::findChildrenById(): Child element is nullptr.");
        }
    }

    return matches;
}


template<typename NodeType>
std::vector<const NodeType*> Node<NodeType>::findChildrenById(const std::string& id) const
{
    std::vector<const NodeType*> matches;

    matches.reserve(_children.size());

    for (auto& child : _children)
    {
        const NodeType* pChild = child.get();

        if (pChild)
        {
            if (child->getId() == id)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::findChildrenById(): Child element is nullptr.");
        }
    }

    return matches;
}


template<typename NodeType>
typename std::vector<std::unique_ptr<NodeType>>::iterator Node<NodeType>::findChild(NodeType* element)
{
    return std::find_if(_children.begin(),
                        _children.end(),
                        [&](const std::unique_ptr<NodeType>& child) {
                            return element == child.get();
                        });
}





} } // namespace ofx::DOM
