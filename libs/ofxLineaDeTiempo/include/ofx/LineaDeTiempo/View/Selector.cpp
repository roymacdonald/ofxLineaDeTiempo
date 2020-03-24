//
//  BaseHasSelectionRect.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/22/20.
//

#include "SelectionRect.h"


namespace ofx {
namespace LineaDeTiempo {

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
}

template<typename ElementType>
bool Selector<ElementType>::_SelectorPointerUp(const glm::vec2& localPosition)
{
	if(isSelectingRect()){
		_updateSelectionRect( localPosition);
		_rect.set(0, 0, 0, 0);
		return true;
	}else {
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
	
	ofNotifyEvent(selectionRectUpdated, _rect, this);
	
	if(_parentElement && _limitingElement){
		auto s = _limitingElement->getScreenShape();
		_rect = _rect.getIntersection(ofRectangle(_parentElement->screenToLocal(s.getMin()), _parentElement->screenToLocal(s.getMax()) ));
	}
	_setSelectedElementsFromRect(_rect, ofGetKeyPressed(OF_KEY_SHIFT));
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
	element->setSelected(true);
	if(isElementSelected(element)) return;
	selectedElements.push_back(element);

}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::unselectElement(ElementType* element)
{
	if(element == nullptr) return;
	
	element->setSelected(false);
	ofRemove(selectedElements, [&](ElementType*& key){return key == element;});

}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::unselectAllElements()
{
	for(auto& k: selectedElements){
		k->setSelected(false);
	}
	selectedElements.clear();
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::selectAllElements()
{
	selectedElements = getCollection();
	for(auto& k: getCollection()){
		k->setSelected(true);
	}
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
bool Selector<ElementType>::isElementSelected(ElementType* k)
{
	if(k == nullptr) return false;
	if(selectedElements.size()==0) return false;
	return binary_search(selectedElements.begin(), selectedElements.end(), k, keyframesort);
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::_setSelectedElementsFromRect(const ofRectangle& r, bool bAddToCurrentSelection)
{
	if(!bAddToCurrentSelection){
		unselectAllElements();
	}
	for(auto& k: getCollection()){
		if(r.inside(k->getCenterPosition())){
			selectElement(k);//Not sure if the overhead that this function adds with the checks it performs is relevant or not
		}
	}
}



} } // ofx::LineaDeTiempo

