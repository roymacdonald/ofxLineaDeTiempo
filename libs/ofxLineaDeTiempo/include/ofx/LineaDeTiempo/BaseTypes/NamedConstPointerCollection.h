//
//  NamedConstCollection.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#pragma once
#include <vector>
#include <map>
#include <string>
#include "ofx/DOM/Node.h"
#include <type_traits>
namespace ofx {
namespace LineaDeTiempo {
template<typename T>
class NamedConstPointerCollection
{
public:
	
//	static_assert(std::is_base_of<DOM::Node<T>, T>::value,
//				  "NamedConstPointerCollection invalid templated type. It must be or inherit from ofx::DOM::Node");
	
	
	///\brief get the element  specified index using [index] . This function will not check if the index is whitin bounds so you must make sure it is
	const T* operator[] (size_t index) const;
	T* operator[] (size_t index);
	
	
	const T* operator[] (const std::string& name) const;
	T* operator[] (const std::string& name);
	
	
	///\brief get the element at specified index. This function checks if the index is whitin bounds, otherwise returns nullptr/
	const T* at(size_t index) const;
	T* at(size_t index);
	
	
	const T* at(const std::string& id) const;
	T* at(const std::string& id);
	
		
	
	const std::vector<T*> & getCollection();
	const std::vector<const T*> & getCollection() const;
	
	
	
	bool add(T* t);
	
	bool remove(const std::string& id);
	bool remove(T* t);
	bool remove(size_t index);
	
	size_t size() const;
	
	bool has(T* t);
	
	void clear();

	void forceReindexing();
	
	std::string makeUniqueName(std::string name, const std::string& defaultName);
	
protected:
	
	std::vector<T*> _elements;
	std::vector<const T*> _constElements;
	std::map<std::string, T*> _namedElements;
	

};
	



}} //ofx::LineaDeTiempo
