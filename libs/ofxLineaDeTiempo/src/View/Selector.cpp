//
//  BaseHasSelectionRect.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/22/20.
//

#include "LineaDeTiempo/View/Selector.h"
#include "LineaDeTiempo/View/KeyframeView.h"
#include "ofGraphics.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename ElementType>
Selector<ElementType>::Selector()
: _rect(0,0,0,0)
{
	
}

template<typename ElementType>
void Selector<ElementType>::setLimitingElement(DOM::Element * limitingElement)
{
	_limitingElement = limitingElement;
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
void Selector<ElementType>::onPointerDown(const glm::vec2& localPosition, DOM::Element* caller)
{
	_selectionRectStart =  localPosition;
	_rect.set(_selectionRectStart, 0, 0);
	
	
	if(!_bAddToCurrentSelection){
		unselectAllElements();
	}
}

template<typename ElementType>
bool Selector<ElementType>::onPointerUp(const glm::vec2& localPosition, DOM::Element* caller)
{
	if(isSelectingRect()){
		_updateSelectionRect( localPosition, caller);
		_rect.set(0, 0, 0, 0);
		return true;
	}else {
		return unselectAllElements();
	}
}


template<typename ElementType>
void Selector<ElementType>::onPointerDrag(const glm::vec2& localPosition, DOM::Element* caller)
{
	_updateSelectionRect(localPosition, caller);
}

template<typename ElementType>
void Selector<ElementType>::_updateSelectionRect(const glm::vec2& localPosition, DOM::Element* caller)
{
	
	_rect.set(_selectionRectStart, 0, 0);
	_rect.width = localPosition.x - _selectionRectStart.x;
	_rect.height = localPosition.y - _selectionRectStart.y;
	_rect.standardize();
	
	
	
	if( caller && _limitingElement){
		auto s = _limitingElement->getScreenShape();
		_rect = _rect.getIntersection(ofRectangle(caller->screenToLocal(s.getMin()), caller->screenToLocal(s.getMax()) ));
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
void Selector<ElementType>::selectElement(ElementType* element, BaseHasCollection<ElementType>* owner)
{
	if(!element || !owner) return;
	if(_targetSelectedElementsMap.count(owner) == 0) return;
	
	element->_isSelected = true;
	
	if(!_bAddToCurrentSelection)
		unselectAllElements();
	
	if(isElementSelected(element, owner)) return;
	
	if(_targetSelectedElementsMap[owner]){
		_targetSelectedElementsMap[owner]->push_back(element);
	}
	

}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::unselectElement(ElementType* element, BaseHasCollection<ElementType>* owner)
{
	if(element == nullptr || !owner) return;
	if(_targetSelectedElementsMap.count(owner) == 0) return;
	
	element->_isSelected = false;

	
	if(_targetSelectedElementsMap[owner]){
		ofRemove(*_targetSelectedElementsMap[owner], [&](ElementType*& key){return key == element;});
	}

}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
bool Selector<ElementType>::unselectAllElements()
{
	bool unselected = false;
	for(auto& t: _targetSelectedElementsMap){
		unselected |= (t.second.get()->size() > 0);
		for(auto& k: *t.second.get())
		{
			k->_isSelected = false;
		}
		t.second.get()->clear();
	}
	return unselected;
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
void Selector<ElementType>::selectAllElements()
{
	for(auto& t: _targetSelectedElementsMap){
		t.second.get()->clear();
		if(t.first){
			for(auto& k: t.first->getCollection())
			{
				k->_isSelected = true;
				t.second.get()->push_back(k);
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
template<typename ElementType>
bool Selector<ElementType>::isElementSelected(ElementType* k, BaseHasCollection<ElementType>* owner)
{
	if(k == nullptr || !owner) return false;
	if(_targetSelectedElementsMap.count(owner) == 0) return false;
	for(auto e : *_targetSelectedElementsMap[owner].get())
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
	for(auto& t: _targetSelectedElementsMap){
		if(t.first){
			for(auto& k: t.first->getCollection()){
				if(!k)continue;
				bool _isSelected = isElementSelected(k, t.first) ;
				if(r.inside(k->getCenterPosition()))
				{
					if(!k->isSelected() && !_isSelected )
					{
						t.second.get()->push_back(k);
						k->_isSelected = true;
					}
				}
				else
				if(k->isSelected() || _isSelected )
				{
					unselectElement(k, t.first);
				}
			}
		}
	}
}

template<typename ElementType>
std::vector<ElementType*> * Selector<ElementType>::getSelectedElements(BaseHasCollection<ElementType>* target)
{
	if(_targetSelectedElementsMap.count(target))
	{
		return _targetSelectedElementsMap[target].get();
	}
	return nullptr;
}


template<typename ElementType>
bool Selector<ElementType>::addTarget(BaseHasCollection<ElementType>* target)
{
	if(_targetSelectedElementsMap.count(target))
	{
		ofLogWarning("Selector<ElementType>::addTarget") << "Unable to add target as it  already exists.";
		return false;
	}
	
	_targetSelectedElementsMap[target] = std::move(std::make_unique<std::vector<ElementType*>>());
	return true;
}

template<typename ElementType>
bool Selector<ElementType>::removeTarget(BaseHasCollection<ElementType>* target)
{
	auto n = _targetSelectedElementsMap.erase(target);
	if(n) return true;
	
	ofLogWarning("Selector<ElementType>::removeTarget") << "Unable to remove target as it was never added.";
	return false;

}



template<typename ElementType>
void Selector<ElementType>::onKeyboardEvent(DOM::KeyboardUIEventArgs& evt, DOM::Element* caller)
{
	if(evt.type() == DOM::KeyboardUIEventArgs::KEY_DOWN){
		if(evt.shiftKey()){
			_bAddToCurrentSelection = true;
		}
		else
		if(evt.key().key == OF_KEY_BACKSPACE)
		{
			for(auto& t: _targetSelectedElementsMap){
				if(t.first){
					t.first->removeElements(*t.second.get());
				}
			}
			
		}
	}
	else
	{
		_bAddToCurrentSelection = false;
	}
}


template class Selector<KeyframeView>;


} } // ofx::LineaDeTiempo

