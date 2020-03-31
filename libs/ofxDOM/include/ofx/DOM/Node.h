//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once

#include <unordered_set>
#include "ofx/DOM/Exceptions.h"
#include "ofx/DOM/NodeEvents.h"

namespace ofx {
namespace DOM {


/// \brief A class representing a node object,
/// which can have children that inherit from Node




class Node
{
public:
	
	Node(const std::string& id, Node* parent)
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
    /// \tparam Node The Node Type.
    template <typename ChildType>
    ChildType* addChild(std::unique_ptr<ChildType> node);

    /// \brief Create a child using a templated Node type.
    ///
    /// To create a child Node you can use this method like:
    ///
    /// Node* node = parentNode->addChild<Node>(arguments ...);
    ///
    /// \param args The variable constructor arguments for the Node.
    /// \returns A pointer to the added Node. The parent Node retains
    /// ownership of the pointer via a std::unique_ptr.
    /// \tparam Node The subclass of Node that will be added.
    /// \tparam Args The variable constructor arguments for the Node.
    template <typename ChildType, typename... Args>
    ChildType* addChild(Args&&... args);

    /// \brief Release ownership of a child Node.
    /// \param node The Node to release.
    /// \returns a std::unique_ptr<Node> to the child.
    std::unique_ptr<Node> removeChild(Node* node);

	/// \brief remove and release ownership of a all children Nodes.
	void removeAllChildren();
	
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
    void moveChildToIndex(Node* node, std::size_t index);

    /// \brief Move the given Node in front of all of its siblings.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildToFront(Node* node);

    /// \brief Move the given Node in front of its next sibling.
    /// \param node The child node to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildForward(Node* node);

    /// \brief Move the given Node in back of all of its siblings.
    /// \param node The child node to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildToBack(Node* node);

    /// \brief Move the given Node in back of its next sibling.
    /// \param node The child node to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child node exists.
    void moveChildBackward(Node* node);

    /// \brief Determine if the given Node is a child of this Node.
    /// \param node A pointer the the Node to test.
    /// \returns true iff the given node is a child of this Node.
    bool isChild(Node* node) const;

    /// \brief Determine if the given Node is a sibling of this Node.
    /// \param node A pointer the the Node to test.
    /// \returns true iff the given node is a sibling of this Node.
    bool isSibling(Node* node) const;

    /// \returns the number of siblings.
    std::size_t numSiblings() const;

    /// \returns a list of pointers to sibling nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  siblings are found.
    std::vector<Node*> siblings();

    /// \returns a list of pointers to sibling nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  siblings are found.
    std::vector<const Node*> siblings() const;

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
    bool isParent(const Node* node) const;

    /// \returns the number of children.
    std::size_t numChildren() const;

    /// \brief Get a list of pointers to the child nodes.
    ///
    /// The parent Node retains ownership.
    ///
    /// \returns a list of pointers to child nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  children are found.
    std::vector<Node*> children();

    /// \brief Get a list of pointers to the child nodes.
    ///
    /// The parent Node retains ownership.
    ///
    /// \returns a list of pointers to child nodes.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if invalid
    ///  children are found.
    std::vector<const Node*> children() const;

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
    Node* findFirstChildById(const std::string& id);

    /// \brief Find this Node's first child by its id.
    /// \param id The id of the child Node to find.
    /// \returns a pointer to the first child or nullptr if no such child exists.
    const Node* findFirstChildById(const std::string& id) const;

    /// \brief Find all of this Node's matching the given id.
    /// \param id The id of the child Nodes to find.
    /// \returns a vector of pointers to child nodes or an empty vector if none exist.
    std::vector<Node*> findChildrenById(const std::string& id);

    /// \brief Find all of this Node's matching the given id.
    /// \param id The id of the child Nodes to find.
    /// \returns a vector of pointers to child nodes or an empty vector if none exist.
    std::vector<const Node*> findChildrenById(const std::string& id) const;

    /// \brief Get a pointer to the parent.
    /// \returns a pointer to the parent or a nullptr.
    Node* parent();

    /// \brief Get a pointer to the parent.
    /// \returns a pointer to the parent or a nullptr.
    const Node* parent() const;

    /// \brief Get this Node's child by its index position.
    /// \param index The index of the child Node to get.
    /// \returns a pointer to the child at index or nullptr if no such child exists.
	Node* getChildByIndex( std::size_t index);

    /// \brief Get this Node's child by its index position.
    /// \param index The index of the child Node to get.
    /// \returns a pointer to the child at index or nullptr if no such child exists.
    const Node* getChildByIndex( std::size_t index) const;
	
    
	const std::string&  getId() ;
	
    const std::string&  getId() const;

    /// \brief Set the id of the Node.
    /// \param id The new id of the Node.
    void setId(const std::string& id);

    
	
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
	
	

	void printStructure(std::string prefix = "");
	
protected:
    

    /// \brief Find a child by a raw Node pointer.
    /// \param The pointer to the child.
    /// \returns An iterator pointing to the matching Node or the end.
	typename std::vector<std::unique_ptr<Node>>::iterator findChild(Node* node);

    
private:
    /// \brief Not construction-copyable.
    Node(const Node& other) = delete;

    /// \brief Non copyable.
    Node& operator = (const Node&) = delete;

    /// \brief The id for this node.
    std::string _id;

    /// \brief An optional pointer to a parent Node.
    Node * _parent = nullptr;

    /// \brief A vector to Nodes.
    std::vector<std::unique_ptr<Node>> _children;

	/// \brief True if the child shape is invalid.
    ///
    /// This variable usually set by callbacks from the child elements.
    mutable bool _childInvalid = true;
	
	
	void _notifyNodeReordering(Node* node , const std::size_t& oldIndex, const std::size_t& newIndex );
	
};



template <typename ChildType, typename... Args>
ChildType* Node::addChild(Args&&... args)
{
    return addChild(std::make_unique<ChildType>(std::forward<Args>(args)...));
}


template <typename ChildType>
ChildType* Node::addChild(std::unique_ptr<ChildType> node)
{
    static_assert(std::is_base_of<Node, ChildType>(), "Node must be an Node or derived from Node.");

    if (node)
    {
        // Get a raw pointer to the node for later.
        ChildType* pNode = node.get();

        // Assign the parent to the node via the raw pointer.
        pNode->_parent = this;

        // Take ownership of the node.
        _children.push_back(std::move(node));

        // Invalidate all cached child shape.
        invalidateChild();

        // Alert the node that its parent was set.
        NodeEventArgs addedEvent(this);
        ofNotifyEvent(pNode->addedTo, addedEvent, this);

        NodeEventArgs childAddedEvent(pNode);
        ofNotifyEvent(childAdded, childAddedEvent, this);

//        // Attach child listeners.
//       ofAddListener(pNode->move, this, &Node::_onChildMoved);
//        ofAddListener(pNode->resize, this, &Node::_onChildResized);

        /// Alert the node's siblings that they have a new sibling.
        for (auto& child : _children)
        {
            // Don't alert itself.
            if (child.get() != pNode)
            {
//				child->_siblingAdded(pNode);
                NodeEventArgs event(pNode);
                ofNotifyEvent(child->siblingAdded, event, this);
            }
        }

        return pNode;
    }

    return nullptr;
}


template <typename SiblingType>
std::vector<SiblingType*> Node::siblings()
{
    static_assert(std::is_base_of<Node, SiblingType>(), "SiblingType must be an Node or derived from Node.");

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


template <typename SiblingType>
std::vector<const SiblingType*> Node::siblings() const
{
    static_assert(std::is_base_of<Node, SiblingType>(), "SiblingType must be an Node or derived from Node.");

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


template <typename ChildType>
std::vector<ChildType*> Node::children()
{
    static_assert(std::is_base_of<Node, ChildType>(), "ChildType must be a Node or derived from Node.");

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


template <typename ChildType>
std::vector<const ChildType*> Node::children() const
{
    static_assert(std::is_base_of<Node, ChildType>(), "ChildType must be a Node or derived from Node.");

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





} } // namespace ofx::DOM
