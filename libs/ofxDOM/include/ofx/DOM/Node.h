//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once

#include <unordered_set>
#include "ofx/DOM/Exceptions.h"
#include "ofx/DOM/Events/NodeEvents.h"

namespace ofx {
namespace DOM {


class Element;


/// \brief A class representing a node object,
/// which can have children that inherit from Node



template<typename NodeType>
class Node
{
public:
	
	Node(const std::string& id, NodeType* parent)
	:_id(id)
	,_parent(parent)
	{
		
	}
	
    Node(const std::string& id)
	:_id(id)
	{
		
	}
    /// \brief Destroy the Node.
	virtual ~Node() = default;

    /// \brief Take ownership of the passed std::unique_ptr<Node>.
    ///
    /// This this is "sink" meaning that any child passed to this will be
    /// owned by this Node.
    ///
    /// \param node the rvalue reference to the child node.
    /// \returns A pointer to the added Node. The parent Node retains
    /// ownership of the pointer via a std::unique_ptr.
    /// \tparam NodeType The Node Type.
    template <typename ChildType>
    ChildType* addChild(std::unique_ptr<ChildType> node);

    /// \brief Create a child using a templated Node type.
    ///
    /// To create a child Node you can use this method like:
    ///
    /// NodeType* node = parentNode->addChild<NodeType>(arguments ...);
    ///
    /// \param args The variable constructor arguments for the NodeType.
    /// \returns A pointer to the added Node. The parent Node retains
    /// ownership of the pointer via a std::unique_ptr.
    /// \tparam NodeType The subclass of Node that will be added.
    /// \tparam Args The variable constructor arguments for the NodeType.
    template <typename ChildType, typename... Args>
    ChildType* addChild(Args&&... args);

    /// \brief Release ownership of a child Node.
    /// \param node The Node to release.
    /// \returns a std::unique_ptr<Node> to the child.
    std::unique_ptr<NodeType> removeChild(Node<NodeType>* node);

    /// \brief Move this Node in front of all of its siblings.
    void moveToFront();

    /// \brief Move this Node in front of its next sibling.
    void moveForward();

    /// \brief Move this Node in back of all of its siblings.
    void moveToBack();

    /// \brief Move this Node in back of its next sibling.
    void moveBackward();

    /// \brief Move the given Node to the the given index.
    ///
    /// If the index value is greater than the number of children, the node
    /// will be moved into the last position.
    ///
    /// \param node The child node to move.
    /// \param index The child index to move to.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildToIndex(Node<NodeType>* node, std::size_t index);

    /// \brief Move the given Node in front of all of its siblings.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildToFront(Node<NodeType>* node);

    /// \brief Move the given Node in front of its next sibling.
    /// \param node The child node to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildForward(Node<NodeType>* node);

    /// \brief Move the given Node in back of all of its siblings.
    /// \param node The child node to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildToBack(Node<NodeType>* node);

    /// \brief Move the given Node in back of its next sibling.
    /// \param node The child node to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildBackward(Node<NodeType>* node);

    /// \brief Determine if the given Node is a child of this Node.
    /// \param node A pointer the the Node to test.
    /// \returns true iff the given node is a child of this Node.
    bool isChild(Node<NodeType>* node) const;

    /// \brief Determine if the given Node is a sibling of this Node.
    /// \param node A pointer the the Node to test.
    /// \returns true iff the given node is a sibling of this Node.
    bool isSibling(Node<NodeType>* node) const;

    /// \returns the number of siblings.
    std::size_t numSiblings() const;

    /// \returns a list of pointers to sibling nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  siblings are found.
    std::vector<NodeType*> siblings();

    /// \returns a list of pointers to sibling nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  siblings are found.
    std::vector<const NodeType*> siblings() const;

    /// \brief Get a list of siblings of a given Node or Node subclass.
    ///
    /// If the there are no siblings of the given type,
    ///
    /// \returns a list of pointers to sibling nodes of a given type.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  siblings are found.
    template <typename SiblingsType>
    std::vector<SiblingsType*> siblings();

    /// \brief Get a list of siblings of a given Node or Node subclass.
    ///
    /// If the there are no siblings of the given type,
    ///
    /// \returns a list of pointers to sibling nodes of a given type.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  siblings are found.
    template <typename SiblingsType>
    std::vector<const SiblingsType*> siblings() const;

    /// \brief Determine if the given Node is the parent of this Node.
    /// \param node A pointer the the Node to test.
    /// \returns true iff the given node is the parent of this Node.
    bool isParent(const Node<NodeType>* node) const;

    /// \returns the number of children.
    std::size_t numChildren() const;

    /// \brief Get a list of pointers to the child nodes.
    ///
    /// The parent Node retains ownership.
    ///
    /// \returns a list of pointers to child nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  children are found.
    std::vector<NodeType*> children();

    /// \brief Get a list of pointers to the child nodes.
    ///
    /// The parent Node retains ownership.
    ///
    /// \returns a list of pointers to child nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  children are found.
    std::vector<const NodeType*> children() const;

    /// \brief Get a list of pointers to the child nodes.
    ///
    /// The parent Node retains ownership.
    ///
    /// \returns a list of pointers to child nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  children are found.
    template <typename ChildrenType>
    std::vector<ChildrenType*> children();

    /// \brief Get a list of pointers to the child nodes.
    ///
    /// The parent Node retains ownership.
    ///
    /// \returns a list of pointers to child nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  children are found.
    template <typename ChildrenType>
    std::vector<const ChildrenType*> children() const;

    /// \brief Determine if this Node has a parent Node.
    /// \returns true if this Node has a parent Node.
    bool hasParent() const;

    /// \brief Find this Node's first child by its id.
    /// \param id The id of the child Node to find.
    /// \returns a pointer to the first child or nullptr if no such child exists.
    NodeType* findFirstChildById(const std::string& id);

    /// \brief Find this Node's first child by its id.
    /// \param id The id of the child Node to find.
    /// \returns a pointer to the first child or nullptr if no such child exists.
    const NodeType* findFirstChildById(const std::string& id) const;

    /// \brief Find all of this Node's matching the given id.
    /// \param id The id of the child Nodes to find.
    /// \returns a vector of pointers to child nodes or an empty vector if none exist.
    std::vector<NodeType*> findChildrenById(const std::string& id);

    /// \brief Find all of this Node's matching the given id.
    /// \param id The id of the child Nodes to find.
    /// \returns a vector of pointers to child nodes or an empty vector if none exist.
    std::vector<const NodeType*> findChildrenById(const std::string& id) const;

    /// \brief Get a pointer to the parent.
    /// \returns a pointer to the parent or a nullptr.
    NodeType* parent();

    /// \brief Get a pointer to the parent.
    /// \returns a pointer to the parent or a nullptr.
    const NodeType* parent() const;

    /// \brief Get this Node's child by its index position.
    /// \param index The index of the child Node to get.
    /// \returns a pointer to the child at index or nullptr if no such child exists.
	NodeType* getChildByIndex( std::size_t index);

    /// \brief Get this Node's child by its index position.
    /// \param index The index of the child Node to get.
    /// \returns a pointer to the child at index or nullptr if no such child exists.
    const NodeType* getChildByIndex( std::size_t index) const;
	
    
	const std::string&  getId() ;
	
    const std::string&  getId() const;

    /// \brief Set the id of the Node.
    /// \param id The new id of the Node.
    void setId(const std::string& id);

    
	typedef NodeEventArgs_<NodeType> NodeEventArgs;
	typedef NodeOrderEventArgs_<NodeType> NodeOrderEventArgs;
	
	
    ofEvent<NodeEventArgs> addedTo;
    ofEvent<NodeEventArgs> removedFrom;
    ofEvent<NodeOrderEventArgs> reordered;

    ofEvent<NodeEventArgs> siblingAdded;
    ofEvent<NodeEventArgs> siblingRemoved;
    ofEvent<NodeOrderEventArgs> siblingReordered;

    ofEvent<NodeEventArgs> childAdded;
    ofEvent<NodeEventArgs> childRemoved;
    ofEvent<NodeOrderEventArgs> childReordered;


    /// \brief Called internally to invalidate the child geometry tree.
    virtual void invalidateChild() const
	{
		_childInvalid = true;

		 if (_parent)
		 {
			 _parent->invalidateChild();
		 }

	}
	
	///\brief return this object downcasted to its inheritor class
	const NodeType* cast() const;
	
	///\brief return this object downcasted to its inheritor class
	NodeType* cast();
	

	void printStructure(std::string prefix = "");
	
protected:
    

    /// \brief Find a child by a raw Node pointer.
    /// \param The pointer to the child.
    /// \returns An iterator pointing to the matching Node or the end.
	typename std::vector<std::unique_ptr<NodeType>>::iterator findChild(Node<NodeType>* node);

    
private:
    /// \brief Not construction-copyable.
    Node(const Node& other) = delete;

    /// \brief Non copyable.
    Node& operator = (const Node&) = delete;

    /// \brief The id for this node.
    std::string _id;

    /// \brief An optional pointer to a parent Node.
    NodeType * _parent = nullptr;

    /// \brief A vector to Nodes.
    std::vector<std::unique_ptr<NodeType>> _children;

	/// \brief True if the child shape is invalid.
    ///
    /// This variable usually set by callbacks from the child elements.
    mutable bool _childInvalid = true;
	
	/// \brief The Element class has access to all private variables.
    friend class Element;
	
	void _notifyNodeReordering(Node<NodeType>* node , const std::size_t& oldIndex, const std::size_t& newIndex );
	
};


template<typename NodeType>
template <typename ChildType, typename... Args>
ChildType* Node<NodeType>::addChild(Args&&... args)
{
    return addChild(std::make_unique<ChildType>(std::forward<Args>(args)...));
}

template<typename NodeType>
template <typename ChildType>
ChildType* Node<NodeType>::addChild(std::unique_ptr<ChildType> node)
{
    static_assert(std::is_base_of<NodeType, ChildType>(), "NodeType must be an Node or derived from Node.");

    if (node)
    {
        // Get a raw pointer to the node for later.
        ChildType* pNode = node.get();

        // Assign the parent to the node via the raw pointer.
        pNode->_parent = cast();

        // Take ownership of the node.
        _children.push_back(std::move(node));

        // Invalidate all cached child shape.
        invalidateChild();

        // Alert the node that its parent was set.
        NodeEventArgs addedEvent(cast());
        ofNotifyEvent(pNode->addedTo, addedEvent, cast());

        NodeEventArgs childAddedEvent(pNode);
        ofNotifyEvent(childAdded, childAddedEvent, cast());

//        // Attach child listeners.
//       ofAddListener(pNode->move, cast(), &Node<NodeType>::_onChildMoved);
//        ofAddListener(pNode->resize, cast(), &Node<NodeType>::_onChildResized);

        /// Alert the node's siblings that they have a new sibling.
        for (auto& child : _children)
        {
            // Don't alert itself.
            if (child.get() != pNode)
            {
//				child->_siblingAdded(pNode);
                NodeEventArgs event(pNode);
                ofNotifyEvent(child->siblingAdded, event, cast());
            }
        }

        return pNode;
    }

    return nullptr;
}

template<typename NodeType>
template <typename SiblingType>
std::vector<SiblingType*> Node<NodeType>::siblings()
{
    static_assert(std::is_base_of<NodeType, SiblingType>(), "SiblingType must be an Node or derived from Node.");

    std::vector<SiblingType*> results;

    if (_parent)
    {
        for (auto& child : _parent->_children)
        {
            SiblingType* pChild = dynamic_cast<SiblingType*>(child.get());

            if (pChild != this)
            {
                results.push_back(pChild);
            }
        }
    }
    
    return results;
}

template<typename NodeType>
template <typename SiblingType>
std::vector<const SiblingType*> Node<NodeType>::siblings() const
{
    static_assert(std::is_base_of<NodeType, SiblingType>(), "SiblingType must be an Node or derived from Node.");

    std::vector<const SiblingType*> results;

    if (_parent)
    {
        for (auto& child : _parent->_children)
        {
            const SiblingType* pChild = dynamic_cast<const SiblingType*>(child.get());

            if (pChild != this)
            {
                results.push_back(pChild);
            }
        }
    }

    return results;
}

template<typename NodeType>
template <typename ChildType>
std::vector<ChildType*> Node<NodeType>::children()
{
    static_assert(std::is_base_of<NodeType, ChildType>(), "ChildType must be a Node or derived from Node.");

    std::vector<ChildType*> results;

    for (auto& child : _children)
    {
        ChildType* pChild = dynamic_cast<ChildType*>(child.get());

        if (pChild)
        {
            results.push_back(pChild);
        }
    }

    return results;
}

template<typename NodeType>
template <typename ChildType>
std::vector<const ChildType*> Node<NodeType>::children() const
{
    static_assert(std::is_base_of<NodeType, ChildType>(), "ChildType must be a Node or derived from Node.");

    std::vector<const ChildType*> results;

    for (const auto& child : _children)
    {
        const ChildType* pChild = dynamic_cast<const ChildType*>(child.get());

        if (pChild)
        {
            results.push_back(pChild);
        }
    }

    return results;
}


template<typename NodeType>
NodeType* Node<NodeType>::parent()
{
    return _parent;
}


template<typename NodeType>
const NodeType* Node<NodeType>::parent() const
{
    return _parent;
}

template<typename NodeType>
const std::string& Node<NodeType>::getId()
{
    return _id;
}


template<typename NodeType>
const std::string& Node<NodeType>::getId() const
{
    return _id;
}


template<typename NodeType>
void Node<NodeType>::setId(const std::string& id)
{
    _id = id;
}



template<typename NodeType>
std::unique_ptr<NodeType> Node<NodeType>::removeChild(Node<NodeType>* element)
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
        NodeEventArgs removedFromEvent(cast());
        ofNotifyEvent(detachedChild->removedFrom, removedFromEvent, cast());

        NodeEventArgs childRemovedEvent(detachedChild.get());
        ofNotifyEvent(childRemoved, childRemovedEvent, cast());

        /// Alert the node's siblings that it no longer has a sibling.
        for (auto& child : _children)
        {
            if (detachedChild.get() != child.get())
            {
                NodeEventArgs e(detachedChild.get());
                ofNotifyEvent(child->siblingRemoved, e, cast());
            }
        }

        
        // Detatch child listeners.
        
//        ofRemoveListener(detachedChild.get()->move, cast(), &Node<NodeType>::_onChildMoved);
//        ofRemoveListener(detachedChild.get()->resize, cast(), &Node<NodeType>::_onChildResized);

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
void Node<NodeType>::_notifyNodeReordering(Node<NodeType>* node , const std::size_t& oldIndex, const std::size_t& newIndex )
{
	NodeOrderEventArgs e(node->cast(), oldIndex, newIndex);
	ofNotifyEvent(reordered, e, node->cast());
	ofNotifyEvent(childReordered, e, cast());
}

template<typename NodeType>
void Node<NodeType>::moveChildToIndex(Node<NodeType>* element, std::size_t index)
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
//        NodeOrderEventArgs e(element->cast(), oldIndex, newIndex);
//        ofNotifyEvent(reordered, e, element->cast());
//        ofNotifyEvent(childReordered, e, cast());
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToFront: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildToFront(Node<NodeType>* element)
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
//        NodeOrderEventArgs e(element->cast(), oldIndex, newIndex);
//        ofNotifyEvent(reordered, e, element->cast());
//        ofNotifyEvent(childReordered, e, cast());
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToFront: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildForward(Node<NodeType>* element)
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
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildForward: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildToBack(Node<NodeType>* element)
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
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToBack: Node does not exist.");
    }
}


template<typename NodeType>
void Node<NodeType>::moveChildBackward(Node<NodeType>* element)
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


template<typename NodeType>
bool Node<NodeType>::isChild(Node<NodeType>* element) const
{
    return element
        && element->_parent == this;
}


template<typename NodeType>
bool Node<NodeType>::isSibling(Node<NodeType>* element) const
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
	return static_cast<const NodeType*>(this);
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
bool Node<NodeType>::isParent(const Node<NodeType>* element) const
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
typename std::vector<std::unique_ptr<NodeType>>::iterator Node<NodeType>::findChild(Node<NodeType>* element)
{
    return std::find_if(_children.begin(),
                        _children.end(),
                        [&](const std::unique_ptr<NodeType>& child) {
                            return element == child.get();
                        });
}
template<typename NodeType>
void Node<NodeType>::printStructure(std::string prefix)
{
	std::cout << prefix << getId() << "\n";
	prefix += "   ";
	
	for(auto c: children())
	{
		c->printStructure(prefix);
	}
	
}

} } // namespace ofx::DOM
