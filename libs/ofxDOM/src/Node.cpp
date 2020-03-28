////
////  Node.cpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/14/20.
////

#include "ofx/DOM/Node.h"
#include <algorithm>


namespace ofx {
namespace DOM {


Node* Node::parent()
{
    return _parent;
}



const Node* Node::parent() const
{
    return _parent;
}


const std::string& Node::getId()
{
    return _id;
}



const std::string& Node::getId() const
{
    return _id;
}



void Node::setId(const std::string& id)
{
    _id = id;
}




std::unique_ptr<Node> Node::removeChild(Node* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        // Move the child out of the children array.
        std::unique_ptr<Node> detachedChild = std::move(*iter);

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
        
//        ofRemoveListener(detachedChild.get()->move, this, &Node::_onChildMoved);
//        ofRemoveListener(detachedChild.get()->resize, this, &Node::_onChildResized);

        // Return the detached child.
        // If the return value is ignored, it will be deleted.

        return detachedChild;
    }

    // Return nullptr because we couldn't find anything.
    return nullptr;
}



void Node::moveToFront()
{
    if (_parent)
    {
        _parent->moveChildToFront(this);
    }
}



void Node::moveForward()
{
    if (_parent)
    {
        _parent->moveChildForward(this);
    }
}



void Node::moveToBack()
{
    if (_parent)
    {
        _parent->moveChildToBack(this);
    }
}



void Node::moveBackward()
{
    if (_parent)
    {
        _parent->moveChildBackward(this);
    }
}

void Node::_notifyNodeReordering(Node* node , const std::size_t& oldIndex, const std::size_t& newIndex )
{
	NodeOrderEventArgs e(node, oldIndex, newIndex);
	ofNotifyEvent(reordered, e, node);
	ofNotifyEvent(childReordered, e, this);
}


void Node::moveChildToIndex(Node* element, std::size_t index)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        std::size_t oldIndex = iter - _children.begin();
        std::size_t newIndex = std::min(index, _children.size() - 1);

        auto detachedChild = std::move(*iter);

        _children.erase(iter);

        _children.insert(_children.begin() + newIndex, std::move(detachedChild));
		_notifyNodeReordering(element, oldIndex, newIndex);
//        NodeOrderEventArgs e(element, oldIndex, newIndex);
//        ofNotifyEvent(reordered, e, element);
//        ofNotifyEvent(childReordered, e, this);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::moveChildToFront: Node does not exist.");
    }
}



void Node::moveChildToFront(Node* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        std::size_t oldIndex = iter - _children.begin();
        std::size_t newIndex = 0;

        auto detachedChild = std::move(*iter);
        _children.erase(iter);
        _children.insert(_children.begin(), std::move(detachedChild));

		_notifyNodeReordering(element, oldIndex, newIndex);
//        NodeOrderEventArgs e(element, oldIndex, newIndex);
//        ofNotifyEvent(reordered, e, element);
//        ofNotifyEvent(childReordered, e, this);
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::moveChildToFront: Node does not exist.");
    }
}



void Node::moveChildForward(Node* element)
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
_notifyNodeReordering(element, oldIndex, newIndex);
//            NodeOrderEventArgs e(element, oldIndex, newIndex);
//            ofNotifyEvent(reordered, e, element);
//            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::moveChildForward: Node does not exist.");
    }
}



void Node::moveChildToBack(Node* element)
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

			_notifyNodeReordering(element, oldIndex, newIndex);
//            NodeOrderEventArgs e(element, oldIndex, newIndex);
//            ofNotifyEvent(reordered, e, element);
//            ofNotifyEvent(childReordered, e, this);
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::moveChildToBack: Node does not exist.");
    }
}



void Node::moveChildBackward(Node* element)
{
    auto iter = findChild(element);

    if (iter != _children.end())
    {
        if (iter != _children.end() - 1)
        {
            std::size_t oldIndex = iter - _children.begin();
            std::size_t newIndex = _children.size() + 1;

            std::iter_swap(iter, iter + 1);

			_notifyNodeReordering(element, oldIndex, newIndex);
//            NodeOrderEventArgs e(element, oldIndex, newIndex);
//            ofNotifyEvent(reordered, e, element);
//            ofNotifyEvent(childReordered, e, this);
        }
    }
}



bool Node::isChild(Node* element) const
{
    return element
        && element->_parent == this;
}



bool Node::isSibling(Node* element) const
{
    return element
        && element->_parent
        && element->_parent == _parent;
}



std::size_t Node::numSiblings() const
{
    // Don't count self.
    return _parent ? (_parent->numChildren() - 1) : 0;
}



Node* Node::getChildByIndex( std::size_t index)
{
	if(_children.size() <= index)return nullptr;
	return _children[index].get();
	
}

const Node* Node::getChildByIndex( std::size_t index) const
{
	if(_children.size() <= index)return nullptr;
	return _children[index].get();
}


std::vector<Node*> Node::siblings()
{
    std::vector<Node*> results;

    if (_parent)
    {
        results.reserve(_parent->_children.size());

        for (auto& child : _parent->_children)
        {
            Node* sibling = child.get();

            if (sibling)
            {
                if (this != sibling)
                {
                    results.push_back(sibling);
                }
            }
            else
            {
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::siblings(): Sibling element is nullptr.");
            }
        }
    }

    return results;
}



std::vector<const Node*> Node::siblings() const
{
    std::vector<const Node*> results;

    if (_parent)
    {
        results.reserve(_parent->_children.size());

        for (auto& child : _parent->_children)
        {
            const Node* sibling = child.get();

            if (sibling)
            {
                if (this != sibling)
                {
                    results.push_back(sibling);
                }
            }
            else
            {
                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::siblings(): Sibling element is nullptr.");
            }
        }
    }

    return results;
}



bool Node::isParent(const Node* element) const
{
    return element
        && element == this->_parent;
}



std::size_t Node::numChildren() const
{
    return _children.size();
}



std::vector<Node*> Node::children()
{
    std::vector<Node*> results;

    results.reserve(_children.size());

    for (auto& child : _children)
    {
        Node* pChild = child.get();

        if (pChild)
        {
            results.push_back(pChild);
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::children(): Child element is nullptr.");
        }
    }

    return results;
}



std::vector<const Node*> Node::children() const
{
    std::vector<const Node*> results;

    results.reserve(_children.size());

    for (auto& child : _children)
    {
        const Node* pChild = child.get();

        if (pChild)
        {
            results.push_back(pChild);
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::children(): Child element is nullptr.");
        }
    }

    return results;
}



bool Node::hasParent() const
{
    return _parent;
}



const Node* Node::findFirstChildById(const std::string& id) const
{
    auto iter = std::find_if(_children.begin(),
                             _children.end(),
                             [&](const std::unique_ptr<Node>& child) {
                                 return child->getId() == id;
                             });

    return (iter != _children.end()) ? iter->get() : nullptr;
}



Node* Node::findFirstChildById(const std::string& id)
{
    auto iter = std::find_if(_children.begin(),
                             _children.end(),
                             [&](const std::unique_ptr<Node>& child) {
                                 return child->getId() == id;
                             });

    return (iter != _children.end()) ? iter->get() : nullptr;
}



std::vector<Node*> Node::findChildrenById(const std::string& id)
{
    std::vector<Node*> matches;

    matches.reserve(_children.size());

    for (auto& child : _children)
    {
        Node* pChild = child.get();

        if (pChild)
        {
            if (child->getId() == id)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::findChildrenById(): Child element is nullptr.");
        }
    }

    return matches;
}



std::vector<const Node*> Node::findChildrenById(const std::string& id) const
{
    std::vector<const Node*> matches;

    matches.reserve(_children.size());

    for (auto& child : _children)
    {
        const Node* pChild = child.get();

        if (pChild)
        {
            if (child->getId() == id)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
            
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node::findChildrenById(): Child element is nullptr.");
        }
    }

    return matches;
}



typename std::vector<std::unique_ptr<Node>>::iterator Node::findChild(Node* element)
{
    return std::find_if(_children.begin(),
                        _children.end(),
                        [&](const std::unique_ptr<Node>& child) {
                            return element == child.get();
                        });
}

void Node::printStructure(std::string prefix)
{
	std::cout << prefix << getId() << "\n";
	prefix += "   ";
	
	for(auto& c: _children)
	{
		if(c) c->printStructure(prefix);
	}
	
}

} } // namespace ofx::DOM
