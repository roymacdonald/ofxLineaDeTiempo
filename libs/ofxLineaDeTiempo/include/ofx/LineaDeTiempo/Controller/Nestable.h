//
//  Nestable.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/7/20.
//
// This class was extracted from ofxDOM::Element written by Christopher Baker
//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT



//#pragma once

//#define USE_NESTABLE
//#ifdef USE_NESTABLE
//#include <string>
//#include <memory>
//#include <vector>
//#include "ofEvent.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
////
////class NestableEventArgs
////{
////public:
////    /// \brief Construct the ElementEventArgs.
////    /// \param element The element associated with this Element event.
////    NestableEventArgs(Nestable* element);
////
////    /// \brief Destroy the ElementEventArgs.
////    virtual ~NestableEventArgs();
////
////    /// \returns a pointer to the element or nullptr if not available.
////    Nestable* element();
////
////    /// \returns a pointer to the element or nullptr if not available.
////    const Nestable* element() const;
////
////protected:
////    /// \brief A pointer to the element or nullptr if not available.
////    Nestable _element = nullptr;
////
////};
////
////
////class NestableOrderEventArgs
////{
////public:
////    /// \brief Create an ElementOrderEventArgs.
////    /// \param element The element associated with this Element order event.
////    /// \param oldIndex old index before the Element order event.
////    /// \param newIndex The new index after the Element order event.
////    NestableOrderEventArgs(std::size_t oldIndex,
////                          std::size_t newIndex);
////
////    /// \brief Destroys the ElementOrderEventArgs.
////    virtual ~NestableOrderEventArgs();
////
////    /// \returns the old index before the Element order event.
////    std::size_t oldIndex() const;
////
////    /// \returns the new index after the Element order event.
////    std::size_t newIndex() const;
////
////    /// \returns true if the Element was moved forward.
////    bool wasMovedForward() const;
////
////    /// \returns true if the Element was moved backward.
////    bool wasMovedBackward() const;
////
////    /// \returns true if the Element is at the front.
////    bool isAtFront() const;
////
////    /// \returns true if the Element is at the back.
////    bool isAtBack() const;
////
////protected:
////    /// \brief The old index before the Element order event.
////    std::size_t _oldIndex = 0;
////
////    /// \brief The new index after the Element order event.
////    std::size_t _newIndex = 0;
////
////};
////
//
//
//template<typename ChildType, typename ParentType>
//class Nestable_
//{
//public:
//    /// \brief Construct a new Nestable with the given parameters.
//    ///
//    /// The Nestable will take the default id, an empty string.
//	Nestable_()
//	{
//
//	}
//
//	/// \brief Construct a new Nestable with the given parameters.
//    /// \param id The id of the Nestable.
//    Nestable_(const std::string& id):
//	_id(id)
//	{
//
//	}
//
//    /// \brief Destroy the Nestable.
//    virtual ~Nestable_()
//	{
//
//	}
//
//    /// \brief Take ownership of the passed std::unique_ptr<Nestable>.
//    ///
//    /// This this is "sink" meaning that any child passed to this will be
//    /// owned by this Node.
//    ///
//    /// \param element the rvalue reference to the child node.
//    /// \returns A pointer to the added Nestable. The parent Nestable retains
//    /// ownership of the pointer via a std::unique_ptr.
//    /// \tparam NestableType The Nestable Type.
//    template <typename NestableType>
//    NestableType* addChild(std::unique_ptr<NestableType> child);
//
//    /// \brief Create a child using a templated Nestable type.
//    ///
//    /// To create a child Nestable you can use this method like:
//    ///
//    /// NestableType* element = parentNestable->addChild<NestableType>(arguments ...);
//    ///
//    /// \param args The variable constructor arguments for the NestableType.
//    /// \returns A pointer to the added Nestable. The parent Nestable retains
//    /// ownership of the pointer via a std::unique_ptr.
//    /// \tparam NestableType The subclass of Nestable that will be added.
//    /// \tparam Args The variable constructor arguments for the NestableType.
//    template <typename NestableType, typename... Args>
//    NestableType* addChild(Args&&... args);
//
//    /// \brief Release ownership of a child Nestable.
//    /// \param element The Nestable to release.
//    /// \returns a std::unique_ptr<Nestable> to the child.
//    std::unique_ptr<ChildType> removeChild(ChildType* element);
//
//    /// \brief Move this Nestable in front of all of its siblings.
//    void moveToFront();
//
//    /// \brief Move this Nestable in front of its next sibling.
//    void moveForward();
//
//    /// \brief Move this Nestable in back of all of its siblings.
//    void moveToBack();
//
//    /// \brief Move this Nestable in back of its next sibling.
//    void moveBackward();
//
//    /// \brief Move the given Nestable to the the given index.
//    ///
//    /// If the index value is greater than the number of children, the element
//    /// will be moved into the last position.
//    ///
//    /// \param element The child element to move.
//    /// \param index The child index to move to.
//    void moveChildToIndex(ChildType* element, std::size_t index);
//
//    /// \brief Move the given Nestable in front of all of its siblings.
//
//    void moveChildToFront(ChildType* element);
//
//    /// \brief Move the given Nestable in front of its next sibling.
//    /// \param element The child element to move.
//    void moveChildForward(ChildType* element);
//
//    /// \brief Move the given Nestable in back of all of its siblings.
//    /// \param element The child element to move.
//    void moveChildToBack(ChildType* element);
//
//    /// \brief Move the given Nestable in back of its next sibling.
//    /// \param element The child element to move.
//    void moveChildBackward(ChildType* element);
//
//    /// \brief Determine if the given Nestable is a child of this Nestable.
//    /// \param element A pointer the the Nestable to test.
//    /// \returns true iff the given element is a child of this Nestable.
//    bool isChild(ChildType* element) const;
//
//    /// \brief Determine if the given Nestable is a sibling of this Nestable.
//    /// \param element A pointer the the Nestable to test.
//    /// \returns true iff the given element is a sibling of this Nestable.
//    bool isSibling(Nestable_<ChildType, ParentType>* element) const;
//
//    /// \returns the number of siblings.
//    std::size_t numSiblings() const;
//
//    /// \returns a list of pointers to sibling elements.
//
//    ///  siblings are found.
//    const std::vector<Nestable_<ChildType, ParentType> *>& siblings();
//
//    /// \returns a list of pointers to sibling elements.
//
//    ///  siblings are found.
//    const std::vector<const Nestable_<ChildType, ParentType> *>& siblings() const;
//
//    /// \brief Determine if the given Nestable is the parent of this Nestable.
//    /// \param element A pointer the the Nestable to test.
//    /// \returns true iff the given element is the parent of this Nestable.
//    bool isParent(const ParentType* element) const;
//
//    /// \returns the number of children.
//    std::size_t numChildren() const;
//
//    /// \brief Get a list of pointers to the child elements.
//    ///
//    /// The parent Nestable retains ownership.
//    ///
//    /// \returns a list of pointers to child elements.
//    const std::vector<ChildType*>& children();
//
//    /// \brief Get a list of pointers to the child elements.
//    ///
//    /// The parent Nestable retains ownership.
//    ///
//    /// \returns a list of pointers to child elements.
//    const std::vector<const ChildType*>& children() const;
//
//
//    /// \brief Determine if this Nestable has a parent Nestable.
//    /// \returns true if this Nestable has a parent Nestable.
//    bool hasParent() const;
//
//    /// \brief Find this Nestable's first child by its id.
//    /// \param id The id of the child Nestable to find.
//    /// \returns a pointer to the first child or nullptr if no such child exists.
//   ChildType* findFirstChildById(const std::string& id);
//
//    /// \brief Find this Nestable's first child by its id.
//    /// \param id The id of the child Nestable to find.
//    /// \returns a pointer to the first child or nullptr if no such child exists.
//    const ChildType* findFirstChildById(const std::string& id) const;
//
//    /// \brief Find all of this Nestable's matching the given id.
//    /// \param id The id of the child Nestables to find.
//    /// \returns a vector of pointers to child elements or an empty vector if none exist.
//    std::vector<ChildType*> findChildrenById(const std::string& id);
//
//    /// \brief Find all of this Nestable's matching the given id.
//    /// \param id The id of the child Nestables to find.
//    /// \returns a vector of pointers to child elements or an empty vector if none exist.
//    std::vector<const ChildType*> findChildrenById(const std::string& id) const;
//
//    /// \brief Get a pointer to the parent.
//    /// \returns a pointer to the parent or a nullptr.
//    ParentType* parent();
//
//    /// \brief Get a pointer to the parent.
//    /// \returns a pointer to the parent or a nullptr.
//    const ParentType* parent() const;
//
//
//    /// \brief Get the id of this Nestable.
//    ///
//    /// The id is optional and an empty std::string by default.
//    ///
//    /// \returns the id of the Nestable.
//    std::string getId() const;
//
//    /// \brief Set the id of the Nestable.
//    /// \param id The new id of the Nestable.
//    void setId(const std::string& id);
//
////
////
////	ofEvent<NestableEventArgs> addedTo;
////    ofEvent<NestableEventArgs> removedFrom;
////    ofEvent<NestableOrderEventArgs> reordered;
////
////    ofEvent<NestableEventArgs> siblingAdded;
////    ofEvent<NestableEventArgs> siblingRemoved;
////    ofEvent<NestableOrderEventArgs> siblingReordered;
////
////    ofEvent<NestableEventArgs> childAdded;
////    ofEvent<NestableEventArgs> childRemoved;
////    ofEvent<NestableOrderEventArgs> childReordered;
////
//
//protected:
//
//    /// \brief Find a child by a raw Nestable pointer.
//    /// \param The pointer to the child.
//    /// \returns An iterator pointing to the matching Nestable or the end.
//	typename std::vector<std::unique_ptr<ChildType>>::iterator findChild(ChildType* element);
//
//	void _notifyChildReorder(ChildType * child, std::size_t oldIndex, std::size_t newIndex);
//
//	void _flagChildrenCacheDirty();
//	void _flagSiblingsCacheDirty();
//
//private:
//    /// \brief Not construction-copyable.
//    Nestable_(const Nestable_& other) = delete;
//
//    /// \brief Non copyable.
//    Nestable_& operator = (const Nestable_&) = delete;
//
//    /// \brief The id for this element.
//    std::string _id;
//
//    /// \brief An optional pointer to a parent Node.
//    ParentType* _parent = nullptr;
//
//    /// \brief A vector to Nestables.
//    std::vector<std::unique_ptr<ChildType>> _children;
//
//	std::vector<ChildType*> _childrenCache;
//	std::vector<const ChildType*> _childrenConstCache;
//	bool _bChildrenCacheDirty = false;
//	bool _bChildrenConstCacheDirty = false;
//
//	std::vector<Nestable_<ChildType, ParentType>*> _siblingsCache;
//	std::vector<const Nestable_<ChildType, ParentType>*> _siblingsConstCache;
//	bool _bSiblingsCacheDirty = false;
//	bool _bSiblingsConstCacheDirty = false;
//
//};
//
//template<typename ChildType, typename ParentType>
//template <typename NestableType, typename... Args>
//NestableType* Nestable_<ChildType, ParentType>::addChild(Args&&... args)
//{
//	static_assert(std::is_base_of<ChildType, NestableType>(), "NestableType must be an Nestable or derived from Nestable.");
//    return addChild(std::make_unique<NestableType>(std::forward<Args>(args)...));
//}
//
//template<typename ChildType, typename ParentType>
//template <typename NestableType>
//NestableType* Nestable_<ChildType, ParentType>::addChild(std::unique_ptr<NestableType> element)
//{
//    static_assert(std::is_base_of<ChildType, NestableType>(), "NestableType must be an Nestable or derived from Nestable.");
//
//    if (element)
//    {
//        // Get a raw pointer to the node for later.
//        NestableType* pNode = element.get();
//
//        // Assign the parent to the node via the raw pointer.
//        pNode->_parent = this;
//
//        // Take ownership of the node.
//        _children.push_back(std::move(element));
//
//		_flagChildrenCacheDirty();
//
//        // Alert the node that its parent was set.
////        NestableEventArgs addedEvent(this);
////        ofNotifyEvent(pNode->addedTo, addedEvent, this);
////
////        NestableEventArgs childAddedEvent(pNode);
////        ofNotifyEvent(childAdded, childAddedEvent, this);
//
//        /// Alert the node's siblings that they have a new sibling.
//        for (auto& child : _children)
//        {
//            // Don't alert itself.
//            if (child.get() != pNode)
//            {
//				child->_flagSiblingsCacheDirty();
////                NestableEventArgs event(pNode);
////                ofNotifyEvent(child->siblingAdded, event, this);
//            }
//        }
//
//        return pNode;
//    }
//
//    return nullptr;
//}
//
//
////template <typename NestableType>
////std::vector<NestableType*> Nestable::siblings()
////{
////    static_assert(std::is_base_of<Nestable, NestableType>(), "NestableType must be an Nestable or derived from Nestable.");
////
////    std::vector<NestableType*> results;
////
////    if (_parent)
////    {
////        for (auto& child : _parent->_children)
////        {
////            NestableType* pChild = dynamic_cast<NestableType*>(child.get());
////
////            if (pChild != this)
////            {
////                results.push_back(pChild);
////            }
////        }
////    }
////
////    return results;
////}
////
////
////template <typename NestableType>
////std::vector<const NestableType*> Nestable::siblings() const
////{
////    static_assert(std::is_base_of<Nestable, NestableType>(), "NestableType must be an Nestable or derived from Nestable.");
////
////    std::vector<const NestableType*> results;
////
////    if (_parent)
////    {
////        for (auto& child : _parent->_children)
////        {
////            const NestableType* pChild = dynamic_cast<const NestableType*>(child.get());
////
////            if (pChild != this)
////            {
////                results.push_back(pChild);
////            }
////        }
////    }
////
////    return results;
////}
////
////
////template <typename NestableType>
////std::vector<NestableType*> Nestable::children()
////{
////    static_assert(std::is_base_of<Nestable, NestableType>(), "NestableType must be an Nestable or derived from Nestable.");
////
////    std::vector<NestableType*> results;
////
////    for (auto& child : _children)
////    {
////        NestableType* pChild = dynamic_cast<NestableType*>(child.get());
////
////        if (pChild)
////        {
////            results.push_back(pChild);
////        }
////    }
////
////    return results;
////}
////
////
////template <typename NestableType>
////std::vector<const NestableType*> Nestable::children() const
////{
////    static_assert(std::is_base_of<Nestable, NestableType>(), "NestableType must be an Nestable or derived from Nestable.");
////
////    std::vector<const NestableType*> results;
////
////    for (const auto& child : _children)
////    {
////        const NestableType* pChild = dynamic_cast<const NestableType*>(child.get());
////
////        if (pChild)
////        {
////            results.push_back(pChild);
////        }
////    }
////
////    return results;
////}
//
//
//
//
//} } // namespace ofx::DOM
//
//#endif
