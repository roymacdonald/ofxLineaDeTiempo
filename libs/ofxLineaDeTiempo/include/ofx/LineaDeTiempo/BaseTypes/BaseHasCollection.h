//
//  BaseHasCollection.hpp
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#pragma once
#include "LineaDeTiempo/BaseTypes/BaseHasName.h"
#include "ofConstants.h"
#include <memory>
#include <map>
#include <vector>
#include "LineaDeTiempo/BaseTypes/BaseHasParent.h"
#include "DOM/Element.h"

#include "ofLog.h"
#include "ofUtils.h"

namespace ofx {
namespace LineaDeTiempo {



template<typename ElementType, typename useUniquePtr>
class BaseHasCollection
//: public BaseHasName
{
public:
	
//	static_assert(std::is_base_of<BaseHasParent<BaseHasCollection<ElementType, useUniquePtr>>, ElementType>::value, "ElementType must be an Element or derived from Element.");
		static_assert(std::is_base_of<std::true_type, useUniquePtr>::value or
					  std::is_base_of<std::false_type, useUniquePtr>::value
					  , "useUniquePtr must be std::true_type or std::false_type.");
	
	
	typedef typename std::conditional<useUniquePtr::value, std::unique_ptr<ElementType>, ElementType*>::type collectionStoreType;
	typedef typename std::vector<collectionStoreType>::iterator iterType;
	
	//	BaseHasCollection(const std::string& name);
	
	BaseHasCollection() = default;
	virtual ~BaseHasCollection() = default;
	
	
	template <typename NewElementType>
	typename std::enable_if<not useUniquePtr::value, NewElementType*>::type
	addElement( NewElementType* element)
	{
		
		static_assert(std::is_base_of<ElementType, NewElementType>::value, "ElementType must be an Element or derived from Element.");
		
		if (element)
		{
			
			_collection.push_back(element);
			
			
			sortData();
			
			ofNotifyEvent(addElementEvent, element, this);
			
			return element;
		}
		
		return nullptr;
		
	}
	
	template <typename NewElementType, typename... Args>
	typename std::enable_if<useUniquePtr::value, NewElementType*>::type addElement(Args&&... args)
	{
		static_assert(std::is_base_of<ElementType, NewElementType>::value, "ElementType must be an Element or derived from Element.");
		auto element =std::make_unique<NewElementType>(std::forward<Args>(args)...);
		
		// Get a raw pointer to the node for later.
		auto nElem = element.get();
		
		// Assign the parent to the node via the raw pointer.
		
		nElem->_parent = this;
		
		_collection.push_back(std::move(element));
		
		
		sortData();
		
		ofNotifyEvent(addElementEvent, element, this);
		
		return nElem;
		
	}
	
	
	
	size_t getNumElements()
	{
		return _collection.size();
	}
	
	
	void clear();
	
	
	/// \brief Find this Element's first child by its id.
	/// \param id The id of the child Element to find.
	/// \returns a pointer to the first child or nullptr if no such child exists.
	ElementType* findFirstElementByName(const std::string& name);
	
	/// \brief Find this Element's first child by its id.
	/// \param id The id of the child Element to find.
	/// \returns a pointer to the first child or nullptr if no such child exists.
	const ElementType* findFirstElementByName(const std::string& name) const;
	
	/// \brief Find all of this Element's matching the given id.
	/// \param id The id of the child Elements to find.
	/// \returns a vector of pointers to child elements or an empty vector if none exist.
	std::vector<ElementType*> findElementsByName(const std::string& name);
	
	/// \brief Find all of this Element's matching the given id.
	/// \param id The id of the child Elements to find.
	/// \returns a vector of pointers to child elements or an empty vector if none exist.
	std::vector<const ElementType*> findElementsByName(const std::string& name) const;
	
	
	ElementType* getElementByIndex(const size_t& index);
	
	const ElementType* getElementByIndex(const size_t& index) const;
	
	
	
	collectionStoreType removeElement(ElementType* element)
	{
	
		collectionStoreType detachedElement = nullptr;
		
		_removeElement(element, detachedElement);
		
		if(detachedElement != nullptr)
		{
			_flagRawPtrCollectionUpdate();
			
			ofNotifyEvent(removeElementEvent, detachedElement, this);
		}
		
		
		
//		auto iter = findElement(element);
//
//		if (iter != _collection.end())
//		{
//			// Move the child out of the children array.
//			collectionStoreType detachedChild;
//			if(useUniquePtr){
//				detachedChild= std::move(*iter);
//			}else{
//				detachedChild = *iter;
//			}
//			// Disown the detached child
//			_collection.erase(iter);
//
//			// Set the parent to nullptr.
//			detachedChild->_parent = nullptr;
//
//			// flag update for raw ptr collections
//			_flagRawPtrCollectionUpdate();
//
//			return detachedChild;
//		}
//
		return detachedElement;
	}

	
	void sortData()
	{
		_customSortData(_collection);
		_flagRawPtrCollectionUpdate();
	}
	
	
	std::string getUniqueName(const std::string& name, const std::string& defaultName);
	
	const std::vector<ElementType*>& getCollection();
	
	const std::vector<const ElementType*>& getCollection() const;
	
	ofEvent<collectionStoreType> addElementEvent;
	ofEvent<collectionStoreType> removeElementEvent;
	
	
protected:
	
	
	
	///\brief sort the collection's elements.
	/// by default it will not sort.
	/// if you want to sort you need to override this function and implement sorting yourself.
	/// A possible implementation of this functionn is commented inside of it below
	virtual void _customSortData(std::vector<collectionStoreType>& collection)
	{
		//		ofSort(_collection,
		//			   [](const std::unique_ptr<ElementType> & a, std::unique_ptr<ElementType> & b )
		//			   {
		//					//this is a lambda function
		//					// return true if you want a to go before b. otherwise return false
		//				}
		//			   );
		
	}
	
	void _flagRawPtrCollectionUpdate();
	
// std::unique_ptr<ElementType>, ElementType*>
	void _removeElement(ElementType* element, std::unique_ptr<ElementType>& ptr)
	{
		
		auto iter = findElement(element);
		
		if (iter != _collection.end())
		{
			// Move the child out of the children array.
			ptr = std::move(*iter);
			
			// Disown the detached child
			_collection.erase(iter);
			
			// Set the parent to nullptr.
			ptr->setParent(nullptr);
		}
	}
	
	void _removeElement(ElementType* element, ElementType* ptr)
	{
		
		auto iter = findElement(element);
		
		if (iter != _collection.end())
		{
			// Move the child out of the children array.
			ptr = *iter;
			
			// Disown the detached child
			_collection.erase(iter);
		}
	}
	
	
private:
	
	iterType findElement(ElementType* element);
	
	std::vector<collectionStoreType> _collection;
	
	
	std::vector< ElementType* >_rawPtrCollection;
	
	void _updateRawPtrCollections();
	
	void _updateConstRawPtrCollection();
	void _updateRawPtrCollection();
	
	std::vector<const ElementType* > _constRawPtrCollection;
	bool _bRawPtrCollectionsNeedUpdate = false;
	
	bool compPtr(ElementType*a , const std::unique_ptr<ElementType>&b)
	{
		return a == b.get();
	}
	bool compPtr(ElementType* a , ElementType* b)
	{
		return a == b;
	}
	
};
template<typename ElementType, typename useUniquePtr>
typename BaseHasCollection<ElementType, useUniquePtr>::iterType BaseHasCollection<ElementType, useUniquePtr>::findElement(ElementType* element)
{
	return std::find_if(_collection.begin(),
						_collection.end(),
						[&](const collectionStoreType& child) {
		return compPtr(element, child);
	});
}


//
//template<typename ElementType, typename useUniquePtr>
//size_t BaseHasCollection<ElementType, useUniquePtr>::getNumElements()
//{
//
//}



template<typename ElementType, typename useUniquePtr>
void BaseHasCollection<ElementType, useUniquePtr>::clear()
{
	_collection.clear();
	_rawPtrCollection.clear();
	_constRawPtrCollection.clear();
	
}



template<typename ElementType, typename useUniquePtr>
ElementType* BaseHasCollection<ElementType, useUniquePtr>::findFirstElementByName(const std::string& name)
{
	
    auto iter = std::find_if(_collection.begin(),
                             _collection.end(),
                             [&](const std::unique_ptr<ElementType>& child) {
                                 return child->getName() == name;
                             });

    return (iter != _collection.end()) ? iter->get() : nullptr;
	
}

template<typename ElementType, typename useUniquePtr>
const ElementType*  BaseHasCollection<ElementType, useUniquePtr>::findFirstElementByName(const std::string& name) const
{
	auto iter = std::find_if(_collection.begin(),
                             _collection.end(),
                             [&](const std::unique_ptr<ElementType>& child) {
                                 return child->getName() == name;
                             });

    return (iter != _collection.end()) ? iter->get() : nullptr;
}

template<typename ElementType, typename useUniquePtr>
std::vector<ElementType*>  BaseHasCollection<ElementType, useUniquePtr>::findElementsByName(const std::string& name)
{
    std::vector<ElementType*> matches;

    matches.reserve(_collection.size());

    for (auto& child : _collection)
    {
        auto pChild = child.get();

        if (pChild)
        {
            if (child->getName() == name)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
			ofLogError("BaseHasCollection<ElementType, useUniquePtr>::findChildrensByName") << "an element was nullptr. This should not happen.";
        }
    }

    return matches;
}

template<typename ElementType, typename useUniquePtr>
std::vector<const ElementType*>  BaseHasCollection<ElementType, useUniquePtr>::findElementsByName(const std::string& name) const
{
    std::vector<const ElementType*> matches;

    matches.reserve(_collection.size());

    for (auto& child : _collection)
    {
        auto pChild = child.get();

        if (pChild)
        {
            if (child->getName() == name)
            {
                matches.push_back(child.get());
            }
        }
        else
        {
			ofLogError("BaseHasCollection<ElementType, useUniquePtr>::findChildrensByName") << "an element was nullptr. This should not happen.";
        }
    }

    return matches;

}

template<typename ElementType, typename useUniquePtr>
ElementType* BaseHasCollection<ElementType, useUniquePtr>::getElementByIndex(const size_t& index)
{
	if(_collection[index].size() <= index) return nullptr;
	return _collection[index];
}

template<typename ElementType, typename useUniquePtr>
const ElementType* BaseHasCollection<ElementType, useUniquePtr>::getElementByIndex(const size_t& index) const
{
	if(_collection[index].size() <= index) return nullptr;
	return _collection[index];
}


//
//template<typename ElementType, typename useUniquePtr>
//void BaseHasCollection<ElementType, useUniquePtr>::sortData()
//{
//	_customSortData();
//	_flagRawPtrCollectionUpdate();
//}

template<typename ElementType, typename useUniquePtr>
std::string BaseHasCollection<ElementType, useUniquePtr>::getUniqueName(const std::string& name, const std::string& defaultName)
{
	std::string uniqueName = name;
	if(name.empty()) uniqueName = defaultName;
	
	//TODO: IMPLEMENT THIS PROPERLY
	
	auto e = findElementsByName(uniqueName);
	if(e.size()){
		uniqueName += " " + ofToString(e.size());
		/// recursivelly call this function until getting a unique name.
		/// I guess this is probably not the best way for doing this.
		/// TODO: Find a better way for handling this
		uniqueName =  getUniqueName(uniqueName, defaultName);
	}
	
	
	
	return uniqueName;
	
	
	
	
}

template<typename ElementType, typename useUniquePtr>
const std::vector<ElementType*>& BaseHasCollection<ElementType, useUniquePtr>::getCollection()
{
	if(useUniquePtr::value){
	_updateRawPtrCollections();
	
	return _rawPtrCollection;
	}
	return _collection;
}

template<typename ElementType, typename useUniquePtr>
const std::vector<const ElementType*>& BaseHasCollection<ElementType, useUniquePtr>::getCollection() const
{
	_updateRawPtrCollections();
	return _constRawPtrCollection;
}


template<typename ElementType, typename useUniquePtr>
void BaseHasCollection<ElementType, useUniquePtr>::_updateConstRawPtrCollection()
{
	_constRawPtrCollection.clear();
	
	_constRawPtrCollection.reserve(_collection.size());
	
	for(auto element: getCollection())
	{
		const ElementType* cE = element;
		if (cE)
		{
			_constRawPtrCollection.push_back(cE);
		}
		else
		{
			ofLogError("BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollections()") << "the collection has an invalid pointer. This should never happen";
		}
	}
}

template<typename ElementType, typename useUniquePtr>
void BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollection()
{
	if(useUniquePtr::value){
		_rawPtrCollection.clear();
		
		_rawPtrCollection.reserve(_collection.size());
		
		for(auto& element: _collection)
		{
			ElementType* e = element;
			if (e)
			{
				_rawPtrCollection.push_back(e);
			}
			else
			{
				ofLogError("BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollections()") << "the collection has an invalid pointer. This should never happen";
			}
		}
	}
}


template<typename ElementType, typename useUniquePtr>
void BaseHasCollection<ElementType, useUniquePtr>::_updateRawPtrCollections()
{

	if(_bRawPtrCollectionsNeedUpdate)
	{
	
		_updateConstRawPtrCollection();
		_updateRawPtrCollection();
		_bRawPtrCollectionsNeedUpdate = false;
		
		
		
		
	}
}



template<typename ElementType, typename useUniquePtr>
void BaseHasCollection<ElementType, useUniquePtr>::_flagRawPtrCollectionUpdate()
{
	_bRawPtrCollectionsNeedUpdate = true;
}


} } // ofx::LineaDeTiempo

