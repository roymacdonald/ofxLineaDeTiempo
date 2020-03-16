//
//  NamedConstCollection.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/16/20.
//

#include "LineaDeTiempo/BaseTypes/NamedConstCollection.h"

#include "ofLog.h"

namespace ofx {
namespace LineaDeTiempo {
		
	

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
		if(_namedElements.count(name) == 0) return nullptr;
		return _namedElements[name];
	}

template<typename T>
	T* NamedConstPointerCollection<T>::operator[] (const std::string& name)
	{
		
	}
template<typename T>
const T* NamedConstPointerCollection<T>::at(size_t index) const
{
	
}
template<typename T>
T* NamedConstPointerCollection<T>::at(size_t index)
{
	
}

template<typename T>
const T* NamedConstPointerCollection<T>::at(const std::string& id) const
{
	if(_namedElements.count(id) == 0) return nullptr;
	return _namedElements[id];
}
template<typename T>
T* NamedConstPointerCollection<T>::at(const std::string& id)
{
	
}

template<typename T>
	const std::vector<T*> & NamedConstPointerCollection<T>::get()
	{
		return _elements;
	}

template<typename T>
	const std::vector<const T*> & NamedConstPointerCollection<T>::get() const
	{
		return _constElements;
	}
	

template<typename T>
	bool NamedConstPointerCollection<T>::add(T* t)
	{
		if(_namedElements.count(t->getId())){
			ofLogError("NamedConstPointerCollection<T>::add") << "fail. There is already another item with the same name. not adding it";
			return false;
		}
		_namedElements[t->getId()] = t;
		_elements.push_back(t);
		_constElements.push_back(t);
	}
	

template<typename T>
	bool NamedConstPointerCollection<T>::remove(const std::string& t)
	{
		return 
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
		_elements.size();
	}
	

template<typename T>
	bool NamedConstPointerCollection<T>::has(T* t)
	{
		return (std::find_if(_elements.begin(),
							_elements.end(),
							[&](T* element)
								{
									return t, element;
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





}} //ofx::LineaDeTiempo
