////
////  Node.cpp
////  tracksAndTimeTest
////
////  Created by Roy Macdonald on 3/14/20.
////
//
//#include "ofx/DOM/Node.h"
//#include <algorithm>
//
//
//namespace ofx {
//namespace DOM {
//
////template<typename NodeType>
////Node<NodeType>::Node(const std::string& id)
////
////{}
//
////template<typename NodeType>
////Node<NodeType>::~Node()
////{
////}
//
////template<typename NodeType>
////void Node<NodeType>::invalidateChild() const
////{
//// 
////
////}
//
//template<typename NodeType>
//template <typename ChildType, typename... Args>
//ChildType* Node<NodeType>::addChild(Args&&... args)
//{
//    return addChild(std::make_unique<ChildType>(std::forward<Args>(args)...));
//}
//
//template<typename NodeType>
//template <typename ChildType>
//ChildType* Node<NodeType>::addChild(std::unique_ptr<ChildType> node)
//{
//    static_assert(std::is_base_of<NodeType, ChildType>(), "NodeType must be an Node or derived from Node.");
//
//    if (node)
//    {
//        // Get a raw pointer to the node for later.
//        ChildType* pNode = node.get();
//
//        // Assign the parent to the node via the raw pointer.
//        pNode->_parent = cast();
//
//        // Take ownership of the node.
//        _children.push_back(std::move(node));
//
//        // Invalidate all cached child shape.
//        invalidateChild();
//
//        // Alert the node that its parent was set.
//        NodeEventArgs addedEvent(cast());
//        ofNotifyEvent(pNode->addedTo, addedEvent, cast());
//
//        NodeEventArgs childAddedEvent(pNode);
//        ofNotifyEvent(childAdded, childAddedEvent, cast());
//
////        // Attach child listeners.
////       ofAddListener(pNode->move, cast(), &Node<NodeType>::_onChildMoved);
////        ofAddListener(pNode->resize, cast(), &Node<NodeType>::_onChildResized);
//
//        /// Alert the node's siblings that they have a new sibling.
//        for (auto& child : _children)
//        {
//            // Don't alert itself.
//            if (child.get() != pNode)
//            {
////				child->_siblingAdded(pNode);
//                NodeEventArgs event(pNode);
//                ofNotifyEvent(child->siblingAdded, event, cast());
//            }
//        }
//
//        return pNode;
//    }
//
//    return nullptr;
//}
//
//template<typename NodeType>
//template <typename SiblingType>
//std::vector<SiblingType*> Node<NodeType>::siblings()
//{
//    static_assert(std::is_base_of<NodeType, SiblingType>(), "SiblingType must be an Node or derived from Node.");
//
//    std::vector<SiblingType*> results;
//
//    if (_parent)
//    {
//        for (auto& child : _parent->_children)
//        {
//            SiblingType* pChild = dynamic_cast<SiblingType*>(child.get());
//
//            if (pChild != this)
//            {
//                results.push_back(pChild);
//            }
//        }
//    }
//    
//    return results;
//}
//
//template<typename NodeType>
//template <typename SiblingType>
//std::vector<const SiblingType*> Node<NodeType>::siblings() const
//{
//    static_assert(std::is_base_of<NodeType, SiblingType>(), "SiblingType must be an Node or derived from Node.");
//
//    std::vector<const SiblingType*> results;
//
//    if (_parent)
//    {
//        for (auto& child : _parent->_children)
//        {
//            const SiblingType* pChild = dynamic_cast<const SiblingType*>(child.get());
//
//            if (pChild != this)
//            {
//                results.push_back(pChild);
//            }
//        }
//    }
//
//    return results;
//}
//
//template<typename NodeType>
//template <typename ChildType>
//std::vector<ChildType*> Node<NodeType>::children()
//{
//    static_assert(std::is_base_of<NodeType, ChildType>(), "ChildType must be a Node or derived from Node.");
//
//    std::vector<ChildType*> results;
//
//    for (auto& child : _children)
//    {
//        ChildType* pChild = dynamic_cast<ChildType*>(child.get());
//
//        if (pChild)
//        {
//            results.push_back(pChild);
//        }
//    }
//
//    return results;
//}
//
//template<typename NodeType>
//template <typename ChildType>
//std::vector<const ChildType*> Node<NodeType>::children() const
//{
//    static_assert(std::is_base_of<NodeType, ChildType>(), "ChildType must be a Node or derived from Node.");
//
//    std::vector<const ChildType*> results;
//
//    for (const auto& child : _children)
//    {
//        const ChildType* pChild = dynamic_cast<const ChildType*>(child.get());
//
//        if (pChild)
//        {
//            results.push_back(pChild);
//        }
//    }
//
//    return results;
//}
//
//
//template<typename NodeType>
//NodeType* Node<NodeType>::parent()
//{
//    return _parent;
//}
//
//
//template<typename NodeType>
//const NodeType* Node<NodeType>::parent() const
//{
//    return _parent;
//}
//
//template<typename NodeType>
//const std::string& Node<NodeType>::getId()
//{
//    return _id;
//}
//
//
//template<typename NodeType>
//const std::string& Node<NodeType>::getId() const
//{
//    return _id;
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::setId(const std::string& id)
//{
//    _id = id;
//}
//
//
//
//template<typename NodeType>
//std::unique_ptr<NodeType> Node<NodeType>::removeChild(Node<NodeType>* element)
//{
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        // Move the child out of the children array.
//        std::unique_ptr<NodeType> detachedChild = std::move(*iter);
//
//        // Disown the detached child
//        _children.erase(iter);
//
//        // Set the parent to nullptr.
//        detachedChild->_parent = nullptr;
//
//        // Invalidate all cached child geometry.
//        invalidateChild();
//
//        // Alert the node that its parent was set.
//        NodeEventArgs removedFromEvent(cast());
//        ofNotifyEvent(detachedChild->removedFrom, removedFromEvent, cast());
//
//        NodeEventArgs childRemovedEvent(detachedChild.get());
//        ofNotifyEvent(childRemoved, childRemovedEvent, cast());
//
//        /// Alert the node's siblings that it no longer has a sibling.
//        for (auto& child : _children)
//        {
//            if (detachedChild.get() != child.get())
//            {
//                NodeEventArgs e(detachedChild.get());
//                ofNotifyEvent(child->siblingRemoved, e, cast());
//            }
//        }
//
//        
//        // Detatch child listeners.
//        
////        ofRemoveListener(detachedChild.get()->move, cast(), &Node<NodeType>::_onChildMoved);
////        ofRemoveListener(detachedChild.get()->resize, cast(), &Node<NodeType>::_onChildResized);
//
//        // Return the detached child.
//        // If the return value is ignored, it will be deleted.
//
//        return detachedChild;
//    }
//
//    // Return nullptr because we couldn't find anything.
//    return nullptr;
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveToFront()
//{
//    if (_parent)
//    {
//        _parent->moveChildToFront(this);
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveForward()
//{
//    if (_parent)
//    {
//        _parent->moveChildForward(this);
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveToBack()
//{
//    if (_parent)
//    {
//        _parent->moveChildToBack(this);
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveBackward()
//{
//    if (_parent)
//    {
//        _parent->moveChildBackward(this);
//    }
//}
//template<typename NodeType>
//void Node<NodeType>::_notifyNodeReordering(Node<NodeType>* node , const std::size_t& oldIndex, const std::size_t& newIndex )
//{
//	NodeOrderEventArgs e(node->cast(), oldIndex, newIndex);
//	ofNotifyEvent(reordered, e, node->cast());
//	ofNotifyEvent(childReordered, e, cast());
//}
//
//template<typename NodeType>
//void Node<NodeType>::moveChildToIndex(Node<NodeType>* element, std::size_t index)
//{
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        std::size_t oldIndex = iter - _children.begin();
//        std::size_t newIndex = std::min(index, _children.size() - 1);
//
//        auto detachedChild = std::move(*iter);
//
//        _children.erase(iter);
//
//        _children.insert(_children.begin() + newIndex, std::move(detachedChild));
//		_notifyNodeReordering(element, oldIndex, newIndex);
////        NodeOrderEventArgs e(element->cast(), oldIndex, newIndex);
////        ofNotifyEvent(reordered, e, element->cast());
////        ofNotifyEvent(childReordered, e, cast());
//    }
//    else
//    {
//        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToFront: Node does not exist.");
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveChildToFront(Node<NodeType>* element)
//{
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
//		_notifyNodeReordering(element, oldIndex, newIndex);
////        NodeOrderEventArgs e(element->cast(), oldIndex, newIndex);
////        ofNotifyEvent(reordered, e, element->cast());
////        ofNotifyEvent(childReordered, e, cast());
//    }
//    else
//    {
//        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToFront: Node does not exist.");
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveChildForward(Node<NodeType>* element)
//{
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        // Make sure it's not already in the front.
//        if (iter != _children.begin())
//        {
//            std::size_t oldIndex = iter - _children.begin();
//            std::size_t newIndex = oldIndex - 1;
//
//            std::iter_swap(iter, iter - 1);
//_notifyNodeReordering(element, oldIndex, newIndex);
////            NodeOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//    else
//    {
//        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildForward: Node does not exist.");
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveChildToBack(Node<NodeType>* element)
//{
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
//			_notifyNodeReordering(element, oldIndex, newIndex);
////            NodeOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//    else
//    {
//        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::moveChildToBack: Node does not exist.");
//    }
//}
//
//
//template<typename NodeType>
//void Node<NodeType>::moveChildBackward(Node<NodeType>* element)
//{
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        if (iter != _children.end() - 1)
//        {
//            std::size_t oldIndex = iter - _children.begin();
//            std::size_t newIndex = _children.size() + 1;
//
//            std::iter_swap(iter, iter + 1);
//
//			_notifyNodeReordering(element, oldIndex, newIndex);
////            NodeOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//}
//
//
//template<typename NodeType>
//bool Node<NodeType>::isChild(Node<NodeType>* element) const
//{
//    return element
//        && element->_parent == this;
//}
//
//
//template<typename NodeType>
//bool Node<NodeType>::isSibling(Node<NodeType>* element) const
//{
//    return element
//        && element->_parent
//        && element->_parent == _parent;
//}
//
//
//template<typename NodeType>
//std::size_t Node<NodeType>::numSiblings() const
//{
//    // Don't count self.
//    return _parent ? (_parent->numChildren() - 1) : 0;
//}
//
//template<typename NodeType>
//const NodeType* Node<NodeType>::cast() const
//{
//	return static_cast<NodeType*>(this);
//}
//
//template<typename NodeType>
//NodeType* Node<NodeType>::cast()
//{
//	return static_cast<NodeType*>(this);
//}
//template<typename NodeType>
//NodeType* Node<NodeType>::getChildByIndex( std::size_t index)
//{
//	if(_children.size() <= index)return nullptr;
//	return _children[index].get();
//	
//}
//template<typename NodeType>
//const NodeType* Node<NodeType>::getChildByIndex( std::size_t index) const
//{
//	if(_children.size() <= index)return nullptr;
//	return _children[index].get();
//}
//
//template<typename NodeType>
//std::vector<NodeType*> Node<NodeType>::siblings()
//{
//    std::vector<NodeType*> results;
//
//    if (_parent)
//    {
//        results.reserve(_parent->_children.size());
//
//        for (auto& child : _parent->_children)
//        {
//            NodeType* sibling = child.get();
//
//            if (sibling)
//            {
//                if (this != sibling)
//                {
//                    results.push_back(sibling);
//                }
//            }
//            else
//            {
//                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::siblings(): Sibling element is nullptr.");
//            }
//        }
//    }
//
//    return results;
//}
//
//
//template<typename NodeType>
//std::vector<const NodeType*> Node<NodeType>::siblings() const
//{
//    std::vector<const NodeType*> results;
//
//    if (_parent)
//    {
//        results.reserve(_parent->_children.size());
//
//        for (auto& child : _parent->_children)
//        {
//            const NodeType* sibling = child.get();
//
//            if (sibling)
//            {
//                if (this != sibling)
//                {
//                    results.push_back(sibling);
//                }
//            }
//            else
//            {
//                throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::siblings(): Sibling element is nullptr.");
//            }
//        }
//    }
//
//    return results;
//}
//
//
//template<typename NodeType>
//bool Node<NodeType>::isParent(const Node<NodeType>* element) const
//{
//    return element
//        && element == this->_parent;
//}
//
//
//template<typename NodeType>
//std::size_t Node<NodeType>::numChildren() const
//{
//    return _children.size();
//}
//
//
//template<typename NodeType>
//std::vector<NodeType*> Node<NodeType>::children()
//{
//    std::vector<NodeType*> results;
//
//    results.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        NodeType* pChild = child.get();
//
//        if (pChild)
//        {
//            results.push_back(pChild);
//        }
//        else
//        {
//            
//            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::children(): Child element is nullptr.");
//        }
//    }
//
//    return results;
//}
//
//
//template<typename NodeType>
//std::vector<const NodeType*> Node<NodeType>::children() const
//{
//    std::vector<const NodeType*> results;
//
//    results.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        const NodeType* pChild = child.get();
//
//        if (pChild)
//        {
//            results.push_back(pChild);
//        }
//        else
//        {
//            
//            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::children(): Child element is nullptr.");
//        }
//    }
//
//    return results;
//}
//
//
//template<typename NodeType>
//bool Node<NodeType>::hasParent() const
//{
//    return _parent;
//}
//
//
//template<typename NodeType>
//const NodeType* Node<NodeType>::findFirstChildById(const std::string& id) const
//{
//    auto iter = std::find_if(_children.begin(),
//                             _children.end(),
//                             [&](const std::unique_ptr<NodeType>& child) {
//                                 return child->getId() == id;
//                             });
//
//    return (iter != _children.end()) ? iter->get() : nullptr;
//}
//
//
//template<typename NodeType>
//NodeType* Node<NodeType>::findFirstChildById(const std::string& id)
//{
//    auto iter = std::find_if(_children.begin(),
//                             _children.end(),
//                             [&](const std::unique_ptr<NodeType>& child) {
//                                 return child->getId() == id;
//                             });
//
//    return (iter != _children.end()) ? iter->get() : nullptr;
//}
//
//
//template<typename NodeType>
//std::vector<NodeType*> Node<NodeType>::findChildrenById(const std::string& id)
//{
//    std::vector<NodeType*> matches;
//
//    matches.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        NodeType* pChild = child.get();
//
//        if (pChild)
//        {
//            if (child->getId() == id)
//            {
//                matches.push_back(child.get());
//            }
//        }
//        else
//        {
//            
//            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::findChildrenById(): Child element is nullptr.");
//        }
//    }
//
//    return matches;
//}
//
//
//template<typename NodeType>
//std::vector<const NodeType*> Node<NodeType>::findChildrenById(const std::string& id) const
//{
//    std::vector<const NodeType*> matches;
//
//    matches.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        const NodeType* pChild = child.get();
//
//        if (pChild)
//        {
//            if (child->getId() == id)
//            {
//                matches.push_back(child.get());
//            }
//        }
//        else
//        {
//            
//            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Node<NodeType>::findChildrenById(): Child element is nullptr.");
//        }
//    }
//
//    return matches;
//}
//
//
//template<typename NodeType>
//typename std::vector<std::unique_ptr<NodeType>>::iterator Node<NodeType>::findChild(Node<NodeType>* element)
//{
//    return std::find_if(_children.begin(),
//                        _children.end(),
//                        [&](const std::unique_ptr<NodeType>& child) {
//                            return element == child.get();
//                        });
//}
//
//
//} } // namespace ofx::DOM
