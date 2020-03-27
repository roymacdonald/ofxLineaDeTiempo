//
//  BaseHasSelectionRect.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/22/20.
//


#pragma once

#include "LineaDeTiempo/BaseTypes/BaseSelectable.h"
//#include "ofEvent.h"
#include "DOM/Element.h"
#include "ofMain.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename ElementType>
class Selector
{
public:
	
	static_assert(std::is_base_of<BaseSelectable, ElementType>::value,
	"Selector<ElementType> instantiation failed. ElementType has to to be derived from ofx::LineaDeTiempo::BaseSelectable.");
	
	static_assert(std::is_base_of<DOM::Element, ElementType>::value,
	"Selector<ElementType> instantiation failed. ElementType has to to be derived from ofx::DOM::Element.");
	
	
	Selector(DOM::Element * parentElement, DOM::Element * limitingElement);
	
	bool isSelectingRect() const;
	
	
	ofEvent<ofRectangle> selectionRectUpdated;
	
	const ofRectangle& getRect() const;
	
	void draw() const;
	
	void selectElement(ElementType* e);
	void unselectElement(ElementType* e);
	bool isElementSelected(ElementType* e);
	void unselectAllElements();
	void selectAllElements();

	
	
	///\brief this function needs to be implemented on the derived class and pass the collection of elements that can be selected.
	/// these elements must inherit form ofx::LineaDeTiempo::BaseSelectable
	virtual std::vector<ElementType*> & getCollection() = 0;
	virtual const std::vector<ElementType*> & getCollection() const= 0;

	std::vector<ElementType*> & getSelectedElements();
	const std::vector<ElementType*> & getSelectedElements() const;
	
	
	
	
protected:

	virtual void _removeSelectedElements() = 0;
	
	// implement the keyboard listener function in the derived class and pass it to the selector
	//	void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	void _SelectorKeyboardEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	void _SelectorPointerDown(const glm::vec2& localPosition);

	bool _SelectorPointerUp(const glm::vec2& localPosition);
	
	void _SelectorDragging(const glm::vec2& localPosition);

	
	void _setSelectedElementsFromRect(const ofRectangle& r);
	void _updateSelectionRect(const glm::vec2& args);
	
	
	std::vector<ElementType*> selectedElements;

	
private:
	
	bool _bAddToCurrentSelection = false;
	
    ofRectangle _rect;
	glm::vec2 _selectionRectStart;
	
	DOM::Element * _limitingElement = nullptr;
	DOM::Element * _parentElement = nullptr;
	
};

template<typename ElementType>
Selector<ElementType>::Selector(DOM::Element * parentElement, DOM::Element * limitingElement)
: _rect(0,0,0,0)
, _limitingElement(limitingElement)
, _parentElement(parentElement)
{
	
}

template<typename ElementType>
const ofRectangle& Selector<ElementType>::getRect() const
{
	return _rect;
}

template<typename ElementType>
bool Selector<ElementType>::isSelectingRect() const
{
	return _rect.getArea() > 0.5;
}

template<typename ElementType>
void Selector<ElementType>::_SelectorPointerDown(const glm::vec2& localPosition)
{
	_selectionRectStart =  localPosition;
	_rect.set(_selectionRectStart, 0, 0);
	
	
	if(!_bAddToCurrentSelection){
		unselectAllElements();
	}
}

template<typename ElementType>
bool Selector<ElementType>::_SelectorPointerUp(const glm::vec2& localPosition)
{
	if(isSelectingRect()){
		_updateSelectionRect( localPosition);
		_rect.set(0, 0, 0, 0);
		return true;
	}else {
		if(selectedElements.size()){
			unselectAllElements();
			return true;
		}
		return  false;
	}
}

template<typename ElementType>
void Selector<ElementType>::_SelectorDragging(const glm::vec2& localPosition)
{
	_updateSelectionRect(localPosition);
}

template<typename ElementType>
void Selector<ElementType>::_updateSelectionRect(const glm::vec2& args)
{
	
	_rect.set(_selectionRectStart, 0, 0);
	_rect.width = args.x - _selectionRectStart.x;
	_rect.height = args.y - _selectionRectStart.y;
	_rect.standardize();
	
	
	
	if(_parentElement && _limitingElement){
		auto s = _limitingElement->getScreenShape();
		_rect = _rect.getIntersection(ofRectangle(_parentElement->screenToLocal(s.getMin()), _parentElement->screenToLocal(s.getMax()) ));
	}
	
	
	_setSelectedElementsFromRect(_rect);
	
	ofNotifyEvent(selectionRectUpdated, _rect, this);
	
}

template<typename ElementType>
void Selector<ElementType>::draw() const
{
	if(isSelectingRect()){
		ofPushStyle();
		ofSetColor(0);
		ofSetLineWidth(1);
		ofNoFill();
		ofDrawRectangle(_rect);
		
		ofSetColor(0, 20);
		ofFill();
		ofDrawRectangle(_rect);
		
		ofPopStyle();
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::selectElement(ElementType* element)
{
	if(!element) return;
//	element->setSelected(true); // this generates a sort of weird loop
	element->_isSelected = true;
	if(!_bAddToCurrentSelection)
		unselectAllElements();
	
	if(isElementSelected(element)) return;
	
	selectedElements.push_back(element);

}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::unselectElement(ElementType* element)
{
	if(element == nullptr) return;
	element->_isSelected = false;
//	element->setSelected(false);
	ofRemove(selectedElements, [&](ElementType*& key){return key == element;});

}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::unselectAllElements()
{
	for(auto& k: selectedElements)
	{
		k->_isSelected = false;
	}
	selectedElements.clear();
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::selectAllElements()
{
	selectedElements = getCollection();
	for(auto& k: getCollection())
	{
		k->_isSelected = true;
	}
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
bool Selector<ElementType>::isElementSelected(ElementType* k)
{
	if(k == nullptr) return false;
	for(auto e : selectedElements)
	{
		if(e && k == e)
		{
			return true;
		}
	}
	return false;
//	return binary_search(selectedElements.begin(), selectedElements.end(), k, keyframesort);
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::_setSelectedElementsFromRect(const ofRectangle& r)
{

	for(auto& k: getCollection()){
		if(!k)continue;
		if(r.inside(k->getCenterPosition())){

			if(k->isSelected() == false )
			{
				if(isElementSelected(k) == false){
					selectedElements.push_back(k);
					k->_isSelected = true;
				}
			}
		}
	}
}

template<typename ElementType>
std::vector<ElementType*> & Selector<ElementType>::getSelectedElements()
{
	return selectedElements;
}

template<typename ElementType>
const std::vector<ElementType*> & Selector<ElementType>::getSelectedElements() const
{
	return selectedElements;
}

template<typename ElementType>
void Selector<ElementType>::_SelectorKeyboardEvent(DOM::KeyboardUIEventArgs& evt)
{
	if(evt.type() == DOM::KeyboardUIEventArgs::KEY_DOWN){
		if(evt.shiftKey()){
			_bAddToCurrentSelection = true;
		}
		else
		if(evt.key().key == OF_KEY_BACKSPACE)
		{
			_removeSelectedElements();
		}
	}
	else
	{
		_bAddToCurrentSelection = false;
	}
}


} } // ofx::LineaDeTiempo

