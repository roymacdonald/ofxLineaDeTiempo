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
#include "ofLog.h"
#include "LineaDeTiempo/BaseTypes/AbstractSerializable.h"
namespace ofx {
namespace LineaDeTiempo {
template<typename T>
class NamedConstPointerCollection
: public AbstractSerializable
{
public:
	
	//	static_assert(std::is_base_of<DOM::Node<T>, T>::value,
	//				  "NamedConstPointerCollection invalid templated type. It must be or inherit from ofx::DOM::Node");
	
	
	///\brief get the element  specified index using [index] . This function will not check if the index is whitin bounds so you must make sure it is
	NamedConstPointerCollection();
	
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
	
	virtual void fromJson(const ofJson& j) override{}
	virtual ofJson toJson() override;
	
	bool checkJson(const ofJson& j);
//	void fromJson(const ofJson& j,  T* newElement (const std::string&));
	
protected:

	
	
	std::vector<T*> _elements;
	std::vector<const T*> _constElements;
	std::map<std::string, T*> _namedElements;
	
	
};

template<typename T>
NamedConstPointerCollection<T>::NamedConstPointerCollection()
{
	clear();
}

template<typename T>
const T* NamedConstPointerCollection<T>::operator[] (size_t index) const
{
	return _constElements[index];
}

template<typename T>
T* NamedConstPointerCollection<T>::operator[] (size_t index)
{
	return _elements[index];
}


template<typename T>
const T* NamedConstPointerCollection<T>::operator[] (const std::string& name) const
{
	return this->at(name);
}

template<typename T>
T* NamedConstPointerCollection<T>::operator[] (const std::string& name)
{
	return this->at(name);
}
template<typename T>
const T* NamedConstPointerCollection<T>::at(size_t index) const
{
	if(index < _elements.size()) return _elements[index];
	
	return nullptr;
}
template<typename T>
T* NamedConstPointerCollection<T>::at(size_t index)
{
	if(index < _elements.size()) return _elements[index];
	
	return nullptr;
}

template<typename T>
const T* NamedConstPointerCollection<T>::at(const std::string& id) const
{
	if(_namedElements.count(id) == 0) return nullptr;
	return _namedElements.at(id);
}
template<typename T>
T* NamedConstPointerCollection<T>::at(const std::string& id)
{
	if(_namedElements.count(id) == 0) return nullptr;
	return _namedElements[id];
}

template<typename T>
const std::vector<T*> & NamedConstPointerCollection<T>::getCollection()
{
	return _elements;
}

template<typename T>
const std::vector<const T*> & NamedConstPointerCollection<T>::getCollection() const
{
	return _constElements;
}


template<typename T>
bool NamedConstPointerCollection<T>::add(T* t)
{
	if(_namedElements.count(t->getId())){
		ofLogError("NamedConstPointerCollection<T>::add") << "fail. There is already another item with the same name. Not adding it";
		return false;
	}
	
	if(this->has(t))
	{
		ofLogError("NamedConstPointerCollection<T>::add") << "fail. This item is already part of the collection. Not adding it " << t->getId();
		return false;
	}
	
	_namedElements[t->getId()] = t;
	_elements.push_back(t);
	_constElements.push_back(t);
	return true;
}


template<typename T>
bool NamedConstPointerCollection<T>::remove(const std::string& id)
{
	return remove(at(id));
}

template<typename T>
bool NamedConstPointerCollection<T>::remove(T* t)
{
	if(t == nullptr) return  false;
	
	for(size_t i = 0; i < _elements.size(); i++)
	{
		if(_elements[i] == t)
		{
			
			return remove(i);
			
		}
	}
	return false;
	
}

template<typename T>
bool NamedConstPointerCollection<T>::remove(size_t index)
{
	if(index < _elements.size())
	{
		
		if(_elements[index] == nullptr)
		{
			ofLogError("NamedConstPointerCollection<T>::remove(T* t)") << "Something went wrong. The element at the specified index is nullptr. Try force rebuilding";
			return false;
		}
		
		const T* ct = _elements[index];
		
		if(_constElements[index] != ct)
		{
			ofLogError("NamedConstPointerCollection<T>::remove(T* t)") << "Something went wrong. The internal collections dont match. Try force rebuilding";
			return false;
		}
		
		if( _namedElements.count(_elements[index]->getId()) == 0)
		{
			ofLogError("NamedConstPointerCollection<T>::remove(T* t)") << "Something went wrong. The internal collections dont match. Try force rebuilding";
			return false;
		}
		_namedElements.erase(_elements[index]->getId());
		_elements.erase(_elements.begin() + index);
		_constElements.erase(_constElements.begin() + index);
		return true;
	}
	return false;
}


template<typename T>
size_t NamedConstPointerCollection<T>::size() const
{
	return _elements.size();
}


template<typename T>
bool NamedConstPointerCollection<T>::has(T* t)
{
	return (std::find_if(_elements.begin(),
						 _elements.end(),
						 [&](T* element)
						 {
		return t == element;
	}
						 ) != _elements.end());
}


template<typename T>
void NamedConstPointerCollection<T>::clear()
{
	
	_elements.clear();
	_constElements.clear();
	_namedElements.clear();
}

template<typename T>
void NamedConstPointerCollection<T>::forceReindexing()
{
	
	
	// remove any pointer that is invalid
	ofRemove(_elements, [](T* e){return !e;});
	
	auto elements = _elements;
	clear();
	
	for(auto e: elements)
	{
		add(e);
	}
}


template<typename T>
std::string  NamedConstPointerCollection<T>::makeUniqueName(std::string name, const std::string& defaultName)
{
	if(name.empty()) name = defaultName;
	
	if(_namedElements.count(name) == 0) return name;
	
	name += ofToString(_namedElements.size());
	
	return makeUniqueName(name, defaultName);
	
	// TODO: IMPLEMENT A NICER WAY TO GET UNIQUE NAMES
}

//template<typename T>
//void NamedConstPointerCollection<T>::checkJson(const ofJson& j,  void newElement (const ofJson&))
//{
//
//	auto dt = j["classType"].get<std::string>();
//	auto tt = typeid( T ).name();
//	if(dt != tt )
//	{
//		ofLogError("NamedConstPointerCollection<DataType>::fromJson") << "DataType is different from what was saved. " << dt << " != " << tt;
//		return;
//	}
//	if(j.count("elements") && j["elements"].is_array())
//	{
//		for(auto e: j["elements"])
//		{
//			if(j.count("name"))
//			{
//				newElement(e);
//			}
//		}
//	}
//}

template<typename T>
bool NamedConstPointerCollection<T>::checkJson(const ofJson& j)
{
//	j["class"] = "NamedConstPointerCollection";
	auto dt = j["classType"].get<std::string>();
	auto tt = typeid( T ).name();
	if(dt != tt )
	{
		ofLogError("NamedConstPointerCollection<DataType>::checkJson") << "DataType is different from what was saved. " << dt << " != " << tt;
		return false;
	}
	if(j.count("elements") && j["elements"].is_array())
	{
		return true;
	}
		ofLogError("NamedConstPointerCollection<DataType>::checkJson") <<  "no elements array";
	return false;
//	if(j.count("elements") && j["elements"].is_array())
//	{
//		for(auto e: j["elements"])
//		{
//			if(j.count("name"))
//			{
//				cout << j["name"].get<std::string>();
//			}
//
//		}
//	}
//	for(auto e: _elements)
//	{
//		auto a = dynamic_cast<AbstractSerializable*>(e);
//		if(a)
//		{
//			jsonElements.push_back(a->toJson());
//		}
//		else
//		{
//			std::cout << "not serializable\n";
//		}
//	}
//	j["num_elements"] = _elements.size();
//	j["elements"] = jsonElements;


//
	
}

template<typename T>
ofJson NamedConstPointerCollection<T>::toJson()
{

	ofJson j;
	j["class"] = "NamedConstPointerCollection";
	j["classType"] = typeid( T ).name();
	auto jsonElements = ofJson::array();
	
	for(auto e: _elements)
	{
		auto a = dynamic_cast<AbstractSerializable*>(e);
		if(a)
		{
			jsonElements.push_back(a->toJson());
		}
		else
		{
			std::cout << "not serializable\n";
		}
	}
	j["num_elements"] = _elements.size();
	j["elements"] = jsonElements;
	
	return j;
}




}} //ofx::LineaDeTiempo
