//
//  BaseHasCollection.cpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

//#include "BaseHasCollection.h"
//#include "ofLog.h"
//#include "ofUtils.h"

//namespace ofx {
//namespace LineaDeTiempo {


//
//
//template<typename ElementType>
//BaseHasCollection<ElementType, useUniquePtr>::BaseHasCollection(const std::string& name):
//BaseHasCollection(name, nullptr)
//{
//
//}
//template<>


//template<typename ElementType, bool useUniquePtr>
//typename BaseHasCollection<ElementType, useUniquePtr>::iterType BaseHasCollection<ElementType, useUniquePtr>::findElement(ElementType* element)
//{
//	return std::find_if(_collection.begin(),
//						_collection.end(),
//						[&](const collectionStoreType& child) {
//		return compPtr(element, child);
//	});
//}
//
//
//
//template<typename ElementType, bool useUniquePtr>
//size_t BaseHasCollection<ElementType, useUniquePtr>::getNumElements()
//{
//	return _collection.size();
//}
//
//template<typename ElementType, bool useUniquePtr>
//typename BaseHasCollection<ElementType, useUniquePtr>::collectionStoreType	BaseHasCollection<ElementType, useUniquePtr>::removeElement(ElementType* element)
//{
//
//	auto iter = findElement(element);
//
//	if (iter != _collection.end())
//	{
//		// Move the child out of the children array.
//		typename BaseHasCollection<ElementType, useUniquePtr>::collectionStoreType detachedChild;
//		if(useUniquePtr){
//			detachedChild= std::move(*iter);
//		}else{
//			detachedChild = *iter;
//		}
//		// Disown the detached child
//		_collection.erase(iter);
//
//		// Set the parent to nullptr.
//		detachedChild->_parent = nullptr;
//
//		// flag update for raw ptr collections
//		_flagRawPtrCollectionUpdate();
//
//		return detachedChild;
//	}
//
//	// Return nullptr because we couldn't find anything.
//	return nullptr;
//}
//
//
//template<typename ElementType, bool useUniquePtr>
//void BaseHasCollection<ElementType, useUniquePtr>::clear()
//{
//	_collection.clear();
//	_rawPtrCollection.clear();
//	_constRawPtrCollection.clear();
//
//}
//
//
//
//template<typename ElementType, bool useUniquePtr>
//ElementType* BaseHasCollection<ElementType, useUniquePtr>::findFirstElementByName(const std::string& name)
//{
//
//    auto iter = std::find_if(_collection.begin(),
//                             _collection.end(),
//                             [&](const std::unique_ptr<ElementType>& child) {
//                                 return child->getName() == name;
//                             });
//
//    return (iter != _collection.end()) ? iter->get() : nullptr;
//
//}
//
//template<typename ElementType, bool useUniquePtr>
//const ElementType*  BaseHasCollection<ElementType, useUniquePtr>::findFirstElementByName(const std::string& name) const
//{
//	auto iter = std::find_if(_collection.begin(),
//                             _collection.end(),
//                             [&](const std::unique_ptr<ElementType>& child) {
//                                 return child->getName() == name;
//                             });
//
//    return (iter != _collection.end()) ? iter->get() : nullptr;
//}
//
//template<typename ElementType, bool useUniquePtr>
//std::vector<ElementType*>  BaseHasCollection<ElementType, useUniquePtr>::findElementsByName(const std::string& name)
//{
//    std::vector<ElementType*> matches;
//
//    matches.reserve(_collection.size());
//
//    for (auto& child : _collection)
//    {
//        auto pChild = child.get();
//
//        if (pChild)
//        {
//            if (child->getName() == name)
//            {
//                matches.push_back(child.get());
//            }
//        }
//        else
//        {
//			ofLogError("BaseHasCollection<ElementType, useUniquePtr>::findChildrensByName") << "an element was nullptr. This should not happen.";
//        }
//    }
//
//    return matches;
//
//}
//
//template<typename ElementType, bool useUniquePtr>
//std::vector<const ElementType*>  BaseHasCollection<ElementType, useUniquePtr>::findElementsByName(const std::string& name) const
//{
//    std::vector<const ElementType*> matches;
//
//    matches.reserve(_collection.size());
//
//    for (auto& child : _collection)
//    {
//        auto pChild = child.get();
//
//        if (pChild)
//        {
//            if (child->getName() == name)
//            {
//                matches.push_back(child.get());
//            }
//        }
//        else
//        {
//			ofLogError("BaseHasCollection<ElementType, useUniquePtr>::findChildrensByName") << "an element was nullptr. This should not happen.";
//        }
//    }
//
//    return matches;
//
//}
//
//template<typename ElementType, bool useUniquePtr>
//ElementType* BaseHasCollection<ElementType, useUniquePtr>::getElementByIndex(const size_t& index)
//{
//	if(_collection[index].size() <= index) return nullptr;
//	return _collection[index];
//}
//
//template<typename ElementType, bool useUniquePtr>
//const ElementType* BaseHasCollection<ElementType, useUniquePtr>::getElementByIndex(const size_t& index) const
//{
//	if(_collection[index].size() <= index) return nullptr;
//	return _collection[index];
//}
//
//
////
////template<typename ElementType, bool useUniquePtr>
////void BaseHasCollection<ElementType, useUniquePtr>::sortData()
////{
////	_customSortData();
////	_flagRawPtrCollectionUpdate();
////}
//
//template<typename ElementType, bool useUniquePtr>
//std::string BaseHasCollection<ElementType, useUniquePtr>::getUniqueName(const std::string& name, const std::string& defaultName)
//{
//	std::string uniqueName = name;
//	if(name.empty()) uniqueName = defaultName;
//
//	//TODO: IMPLEMENT THIS PROPERLY
//
//	auto e = findElementsByName(uniqueName);
//	if(e.size()){
//		uniqueName += " " + ofToString(e.size());
//		/// recursivelly call this function until getting a unique name.
//		/// I guess this is probably not the best way for doing this.
//		/// TODO: Find a better way for handling this
//		uniqueName =  getUniqueName(uniqueName, defaultName);
//	}
//
//
//
//	return uniqueName;
//
//
//
//
//}
//
//template<typename ElementType, bool useUniquePtr>
//const std::vector<ElementType*>& BaseHasCollection<ElementType, useUniquePtr>::getCollection()
//{
//	if(useUniquePtr){
//	_updateRawPtrCollections();
//
//	return _rawPtrCollection;
//	}
//	return _collection;
//}
//
//template<typename ElementType, bool useUniquePtr>
//const std::vector<const ElementType*>& BaseHasCollection<ElementType, useUniquePtr>::getCollection() const
//{
//	_updateRawPtrCollections();
//	return _constRawPtrCollection;
//}
//
//
//template<typename ElementType, bool useUniquePtr>
//void BaseHasCollection<ElementType, useUniquePtr>::_updateConstRawPtrCollection()
//{
//	_constRawPtrCollection.clear();
//
//	_constRawPtrCollection.reserve(_collection.size());
//
//	for(auto element: getCollection())
//	{
//		const ElementType* cE = element;
//		if (cE)
//		{
//			_constRawPtrCollection.push_back(cE);
//		}
//		else
//		{
//			ofLogError("BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollections()") << "the collection has an invalid pointer. This should never happen";
//		}
//	}
//}
//
//template<typename ElementType, bool useUniquePtr>
//void BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollection()
//{
//	if(useUniquePtr){
//		_rawPtrCollection.clear();
//
//		_rawPtrCollection.reserve(_collection.size());
//
//		for(auto& element: _collection)
//		{
//			ElementType* e = element;
//			if (e)
//			{
//				_rawPtrCollection.push_back(e);
//			}
//			else
//			{
//				ofLogError("BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollections()") << "the collection has an invalid pointer. This should never happen";
//			}
//		}
//	}
//}
//
//
//template<typename ElementType, bool useUniquePtr>
//void BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollections()
//{
//
//	if(_bRawPtrCollectionsNeedUpdate)
//	{
//
//		_updateConstRawPtrCollection();
//		_updateRawPtrCollection();
//		_bRawPtrCollectionsNeedUpdate = false;
//
//
//
//
//	}
//}
//
//
//
//template<typename ElementType, bool useUniquePtr>
//void BaseHasCollection<ElementType, useUniquePtr>::_flagRawPtrCollectionUpdate()
//{
//	_bRawPtrCollectionsNeedUpdate = true;
//}

//} } // ofx::LineaDeTiempo


