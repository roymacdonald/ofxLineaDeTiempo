//
//  NestableContainer.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/7/20.
//

//#include "ofx/LineaDeTiempo/Controller/Nestable.h"
//#ifdef USE_NESTABLE
//#include <algorithm>
//#include "ofLog.h"
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//
////
////NestableEventArgs::NestableEventArgs(Nestable* element):
////    _element(element)
////{
////}
////
////NestableEventArgs::~NestableEventArgs()
////{
////}
////
////
////Nestable* NestableEventArgs::element()
////{
////    return _element;
////}
////
////const Nestable* ElementEventArgs::element() const
////{
////    return _element;
////}
////
////
////NestableOrderEventArgs::NestableOrderEventArgs(Nestable* element,
////                                             std::size_t oldIndex,
////                                             std::size_t newIndex):
////    NestableEventArgs(element),
////    _oldIndex(oldIndex),
////    _newIndex(newIndex)
////{
////}
////
////
////NestableOrderEventArgs::~NestableOrderEventArgs()
////{
////}
////
////
////std::size_t NestableOrderEventArgs::oldIndex() const
////{
////    return _oldIndex;
////}
////
////
////std::size_t NestableOrderEventArgs::newIndex() const
////{
////    return _newIndex;
////}
////
////
////bool NestableOrderEventArgs::wasMovedForward() const
////{
////    return _oldIndex > _newIndex;
////}
////
////
////bool NestableOrderEventArgs::wasMovedBackward() const
////{
////    return _newIndex > _oldIndex;
////}
////
////
////bool NestableOrderEventArgs::isAtFront() const
////{
////    return _newIndex == 0;
////}
////
////
////bool NestableOrderEventArgs::isAtBack() const
////{
////    return _element->numSiblings() == _newIndex;
////}
//
//
////template<typename C, typename P>
////Nestable_<C, P>::Nestable_()
////{
////
////}
////template<typename C, typename P>
////Nestable_<C, P>::Nestable_(const std::string& id):_id(id)
////{
////}
////
////template<typename C, typename P>
////Nestable_<C, P>::~Nestable_()
////{
////}
//
//template<typename C, typename P>
//std::unique_ptr<C> Nestable_<C, P>::removeChild(C* element)
//{
//    auto iter = findChild(element);
//
//    if (iter != _children.end())
//    {
//        // Move the child out of the children array.
//        std::unique_ptr<C> detachedChild = std::move(*iter);
//
//        // Disown the detached child
//        _children.erase(iter);
//
//        // Set the parent to nullptr.
//        detachedChild->_parent = nullptr;
//
////		_onChildRemoved(detachedChild);
////        // Invalidate all cached child geometry.
////        invalidateChildShape();
////
//		_flagChildrenCacheDirty();
//        // Alert the node that its parent was set.
////        NestableEventArgs removedFromEvent(this);
////        ofNotifyEvent(detachedChild->removedFrom, removedFromEvent, this);
////
////        NestableEventArgs childRemovedEvent(detachedChild.get());
////        ofNotifyEvent(childRemoved, childRemovedEvent, this);
//
//        /// Alert the node's siblings that it no longer has a sibling.
//        for (auto& child : _children)
//        {
//            if (detachedChild.get() != child.get())
//            {
//				child->_flagSiblingsCacheDirty();
//
////                NestableEventArgs e(detachedChild.get());
////                ofNotifyEvent(child->siblingRemoved, e, this);
//            }
//        }
//
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
//template<typename C, typename P>
//void Nestable_<C, P>::moveToFront()
//{
//    if (_parent)
//    {
//        _parent->moveChildToFront(this);
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveForward()
//{
//    if (_parent)
//    {
//        _parent->moveChildForward(this);
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveToBack()
//{
//    if (_parent)
//    {
//        _parent->moveChildToBack(this);
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveBackward()
//{
//    if (_parent)
//    {
//        _parent->moveChildBackward(this);
//    }
//}
//template<typename C, typename P>
//void void Nestable_<C, P>::_notifyChildReorder(C * child, std::size_t oldIndex, std::size_t newIndex)
//{
////	NestableOrderEventArgs e(child, oldIndex, newIndex);
////	ofNotifyEvent(reordered, e, element);
////	ofNotifyEvent(childReordered, e, this);
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveChildToIndex(C* element, std::size_t index)
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
//
//		_notifyChildReorder(element, oldIndex, newIndex);
////        NestableOrderEventArgs e(element, oldIndex, newIndex);
////        ofNotifyEvent(reordered, e, element);
////        ofNotifyEvent(childReordered, e, this);
//    }
//    else
//    {
//        ofLogError("Nestable_<C, P>::moveChildToFront: Nestable does not exist.");
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveChildToFront(C* element)
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
//		_notifyChildReorder(element, oldIndex, newIndex);
////        ElementOrderEventArgs e(element, oldIndex, newIndex);
////        ofNotifyEvent(reordered, e, element);
////        ofNotifyEvent(childReordered, e, this);
//    }
//    else
//    {
//        ofLogError("Nestable_<C, P>::moveChildToFront: Nestable does not exist.");
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveChildForward(C* element)
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
//
//			_notifyChildReorder(element, oldIndex, newIndex);
////            NestableOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//    else
//    {
//        ofLogError("Nestable_<C, P>::moveChildForward : Nestable does not exist.");
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveChildToBack(C* element)
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
//			_notifyChildReorder(element, oldIndex, newIndex);
////            NestableOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//    else
//    {
//         ofLogError("Nestable_<C, P>::moveChildToBack") << "Nestable does not exist.";
//    }
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::moveChildBackward(C* element)
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
//			_notifyChildReorder(element, oldIndex, newIndex);
////            NestableOrderEventArgs e(element, oldIndex, newIndex);
////            ofNotifyEvent(reordered, e, element);
////            ofNotifyEvent(childReordered, e, this);
//        }
//    }
//}
//
//template<typename C, typename P>
//bool Nestable_<C, P>::isChild(C* element) const
//{
//    return element
//        && element->_parent == this;
//}
//
//template<typename C, typename P>
//bool Nestable_<C, P>::isSibling(Nestable_<C, P>* element) const
//{
//    return element
//        && element->_parent
//        && element->_parent == _parent;
//}
//
//template<typename C, typename P>
//std::size_t Nestable_<C, P>::numSiblings() const
//{
//    // Don't count self.
//    return _parent ? (_parent->numChildren() - 1) : 0;
//}
//
//template<typename C, typename P>
//const std::vector<Nestable_<C,P>*>& Nestable_<C, P>::siblings()
//{
////    std::vector<Nestable*> results;
//
//	if (_bSiblingsCacheDirty && _parent)
//    {
//		_siblingsCache.clear();
//        _siblingsCache.reserve(_parent->_children.size() - 1 );
//
//        for (auto& child : _parent->_children)
//        {
//            Nestable* sibling = child.get();
//
//            if (sibling)
//            {
//                if (this != sibling)
//                {
//                    _siblingsCache.push_back(sibling);
//                }
//            }
//            else
//            {template<typename C, typename P>
//                ofLogError("Nestable_<C, P>::siblings(): Sibling element is nullptr.");
//            }
//        }
//		_bSiblingsCacheDirty = false;
//    }
//
//    return _siblingsCache;
//}
//
//template<typename C, typename P>
//const std::vector<const Nestable*>& Nestable_<C, P>::siblings() const
//{
////    std::vector<const Nestable*> results;
////	_siblingsConstCache
//
//    if (_bSiblingsConstCacheDirty && _parent)
//    {
//		_siblingsConstCache.clear();
//        _siblingsConstCache.reserve(_parent->_children.size() - 1);
//
//        for (auto& child : _parent->_children)
//        {
//            const Nestable* sibling = child.get();
//
//            if (sibling)
//            {
//                if (this != sibling)
//                {
//                    _siblingsConstCache.push_back(sibling);
//                }
//            }
//            else
//            {template<typename C, typename P>
//                ofLogError("Nestable_<C, P>::siblings() const: Sibling element is nullptr.");
//            }
//        }
//		_bSiblingsConstCacheDirty = false;
//    }
//
//	return _siblingsConstCache;
//}
//
//template<typename C, typename P>
//bool Nestable_<C, P>::isParent(const Nestable* element) const
//{
//    return element
//        && element == this->_parent;
//}
//
//template<typename C, typename P>
//std::size_t Nestable_<C, P>::numChildren() const
//{
//    return _children.size();
//}
//
//
//template<typename C, typename P>
//const std::vector<Nestable*>& Nestable_<C, P>::children()
//{
////    std::vector<Nestable*> results;
//	if(_bChildrenCacheDirty)
//	{
//		_childrenCache.reserve(_children.size());
//
//		for (auto& child : _children)
//		{
//			Nestable* pChild = child.get();
//
//			if (pChild)
//			{
//				_childrenCache.push_back(pChild);
//			}
//			else
//			{template<typename C, typename P>
//				ofLogError("Nestable_<C, P>::children(): Child element is nullptr.");
//			}
//		}
//		_bChildrenCacheDirty = false;
//	}
//	return _childrenCache;
//}
//
////std::vector<Nestable*> _childrenCache;
////std::vector<const Nestable*> _childrenConstCache;
////bool _bChildrenCacheDirty = false;
////bool _bChildrenConstCacheDirty = false;
//template<typename C, typename P>
//const std::vector<const Nestable*>& Nestable_<C, P>::children() const
//{
//	if(_bChildrenConstCacheDirty)
//	{
////    std::vector<const Nestable*> results;
//
//    _childrenConstCache.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        const Nestable* pChild = child.get();
//
//        if (pChild)
//        {
//            _childrenConstCache.push_back(pChild);
//        }
//        else
//        {template<typename C, typename P>
//            ofLogError("Nestable_<C, P>::children(): Child element is nullptr.");
//        }
//    }
//		_bChildrenConstCacheDirty = false;
//	}
//    return _childrenConstCache;
//}
//
//template<typename C, typename P>
//bool Nestable_<C, P>::hasParent() const
//{
//    return _parent;
//}
//
//template<typename C, typename P>
//const Nestable* Nestable_<C, P>::findFirstChildById(const std::string& id) const
//{
//    auto iter = std::find_if(_children.begin(),
//                             _children.end(),
//                             [&](const std::unique_ptr<Nestable>& child) {
//                                 return child->getId() == id;
//                             });
//
//    return (iter != _children.end()) ? iter->get() : nullptr;
//}
//
//template<typename C, typename P>
//Nestable* Nestable_<C, P>::findFirstChildById(const std::string& id)
//{
//    auto iter = std::find_if(_children.begin(),
//                             _children.end(),
//                             [&](const std::unique_ptr<Nestable>& child) {
//                                 return child->getId() == id;
//                             });
//
//    return (iter != _children.end()) ? iter->get() : nullptr;
//}
//
//template<typename C, typename P>
//std::vector<Nestable*> Nestable_<C, P>::findChildrenById(const std::string& id)
//{
//    std::vector<Nestable*> matches;
//
//    matches.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        Nestable* pChild = child.get();
//
//        if (pChild)
//        {
//            if (child->getId() == id)
//            {
//                matches.push_back(child.get());
//            }
//        }
//        else
//        {template<typename C, typename P>
//            ofLogError("Nestable_<C, P>::findChildrenById(): Child element is nullptr.");
//        }
//    }
//
//    return matches;
//}
//
//template<typename C, typename P>
//std::vector<const Nestable*> Nestable_<C, P>::findChildrenById(const std::string& id) const
//{
//    std::vector<const Nestable*> matches;
//
//    matches.reserve(_children.size());
//
//    for (auto& child : _children)
//    {
//        const Nestable* pChild = child.get();
//
//        if (pChild)
//        {
//            if (child->getId() == id)
//            {
//                matches.push_back(child.get());
//            }
//        }
//        else
//        {template<typename C, typename P>
//            ofLogError("Nestable_<C, P>::findChildrenById(): Child element is nullptr.");
//        }
//    }
//
//    return matches;
//}
//
//template<typename C, typename P>
//std::vector<std::unique_ptr<Nestable>>::iterator Nestable_<C, P>::findChild(Nestable* element)
//{
//    return std::find_if(_children.begin(),
//                        _children.end(),
//                        [&](const std::unique_ptr<Nestable>& child) {
//                            return element == child.get();
//                        });
//}
//
//template<typename C, typename P>
//Nestable* Nestable_<C, P>::parent()
//{
//    return _parent;
//}
//
//template<typename C, typename P>
//const Nestable* Nestable_<C, P>::parent() const
//{
//    return _parent;
//}
//
//template<typename C, typename P>
//std::string Nestable_<C, P>::getId() const
//{
//    return _id;
//}
//
//template<typename C, typename P>
//void Nestable_<C, P>::setId(const std::string& id)
//{
//    _id = id;
//}
//template<typename C, typename P>
//void Nestable_<C, P>::_flagChildrenCacheDirty()
//{
//	_bChildrenCacheDirty = true;
//	_bChildrenConstCacheDirty = true;
//}template<typename C, typename P>
//void Nestable_<C, P>::_flagSiblingsCacheDirty()
//{
//	_bSiblingsCacheDirty = true;
//	_bSiblingsConstCacheDirty = true;
//}
//
//
//
//
//} } // namespace ofx::DOM
//#endif
