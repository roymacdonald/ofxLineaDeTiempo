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

template<typename T>
Selector<T>::Selector()
: _rect(0,0,0,0)
{
	_drawListener = ofEvents().draw.newListener(this, &Selector<T>::_draw,  std::numeric_limits<int>::max());
}

template<typename T>
void Selector<T>::setLimitingRect(const ofRectangle& r)
{
	_limitingRect = r;
}

template<typename T>
const ofRectangle& Selector<T>::getRect() const
{
	return _rect;
}

template<typename T>
bool Selector<T>::isSelectingRect() const
{
	return _rect.getArea() > 1;
}

template<typename T>
void Selector<T>::onPointerDown(const glm::vec2& screenPosition, DOM::Element* caller)
{
	_selectionRectStart =  screenPosition;
	_rect.set(_selectionRectStart, 0, 0);
	
	
//	std::cout << "Selector<T>::onPointerDown  " << std::boolalpha << _bAddToCurrentSelection << std::endl;
	if(!_bAddToCurrentSelection){
		_bHadSelectedElements = unselectAllElements();
	}
}

template<typename T>
bool Selector<T>::onPointerUp(const glm::vec2& screenPosition, DOM::Element* caller)
{
	if(isSelectingRect()){
		_updateSelectionRect( screenPosition, caller);
		_rect.set(0, 0, 0, 0);
		return true;
	}else {
			if(!_bAddToCurrentSelection){
			auto u = unselectAllElements();
	
//			std::cout << "Selector<T>::onPointerUp  add: " << std::boolalpha << _bAddToCurrentSelection
//				<< "  unsel: " << u << "  hadSel: " << _bHadSelectedElements << std::endl;
				
			u |= _bHadSelectedElements;
		
			_bHadSelectedElements = false;
			return u;
		}
		
	}
}


template<typename T>
void Selector<T>::onPointerDrag(const glm::vec2& screenPosition, DOM::Element* caller)
{
	_updateSelectionRect(screenPosition, caller);
}

template<typename T>
void Selector<T>::_updateSelectionRect(const glm::vec2& screenPosition, DOM::Element* caller)
{
	
	_rect.set(_selectionRectStart, 0, 0);
	_rect.width = screenPosition.x - _selectionRectStart.x;
	_rect.height = screenPosition.y - _selectionRectStart.y;
	_rect.standardize();
	
	
	
	if( !_limitingRect.isEmpty()){
		
		_rect = _rect.getIntersection(_limitingRect);
	}
	
	
	_setSelectedElementsFromRect(_rect);
	
	ofNotifyEvent(selectionRectUpdated, _rect, this);
	
}
template<typename T>
bool Selector<T>::_checkIntersection(const ofRectangle& r, T * k) const
{
	if(_intersectionMode == SELECTOR_USE_CENTER_POSITION)
	{
		return r.inside(k->getScreenCenterPosition());
	}
	else
		if(_intersectionMode == SELECTOR_USE_RECTANGLE)
		{
			return r.intersects(k->getScreenShape());
			//		return r.inside(k->getScreenCenterPosition();
		}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
template<typename T>
void Selector<T>::_setSelectedElementsFromRect(const ofRectangle& r)
{
	for(auto& t: _targetSelectedElementsMap){
		if(t.first){
			for(auto& k: t.first->getCollection()){
				if(!k)continue;
				bool _isSelected = isElementSelected(k, t.first) ;
				if(_checkIntersection(r, k))
					//				if(r.inside(k->getScreenCenterPosition()))
				{
					if(!k->isSelected() && !_isSelected )
					{
						t.second.get()->push_back(k);
						k->setSelectedNoEvents(true);
					}
				}
				else if(!_bAddToCurrentSelection) {
					if(k->isSelected() || _isSelected )
					{
						unselectElement(k, t.first);
					}
				}
			}
		}
	}
}

template<typename T>
void Selector<T>::draw() const{
	_bNeedsDraw = true;
}

template<typename T>
void Selector<T>::_draw(ofEventArgs&)
{
	if(_bNeedsDraw && isSelectingRect()){
		ofPushStyle();
		ofSetColor(0);
		ofSetLineWidth(1);
		ofNoFill();
		ofDrawRectangle(_rect);
		
		ofSetColor(0, 20);
		ofFill();
		ofDrawRectangle(_rect);
		
		ofPopStyle();
		
		_bNeedsDraw = false;
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename T>
void Selector<T>::selectElement(T* element, BaseHasCollection<T>* owner)
{
	if(!element || !owner) return;
	if(_targetSelectedElementsMap.count(owner) == 0) return;
	
	element->setSelectedNoEvents(true);
	
	if(!_bAddToCurrentSelection)
		unselectAllElements();
	
	if(isElementSelected(element, owner)) return;
	
	if(_targetSelectedElementsMap[owner]){
		_targetSelectedElementsMap[owner]->push_back(element);
	}
	
	
}
//---------------------------------------------------------------------------------------------------------------------
template<typename T>
void Selector<T>::unselectElement(T* element, BaseHasCollection<T>* owner)
{
	if(element == nullptr || !owner) return;
	if(_targetSelectedElementsMap.count(owner) == 0) return;
	
	element->setSelectedNoEvents(false);
	
	
	if(_targetSelectedElementsMap[owner]){
		ofRemove(*_targetSelectedElementsMap[owner], [&](T*& key){return key == element;});
	}
	
}
//---------------------------------------------------------------------------------------------------------------------
template<typename T>
bool Selector<T>::unselectAllElements()
{
	bool unselected = false;
	for(auto& t: _targetSelectedElementsMap){
		unselected |= (t.second.get()->size() > 0);
		for(auto& k: *t.second.get())
		{
			k->setSelectedNoEvents(false);
		}
		t.second.get()->clear();
	}
	return unselected;
}
//---------------------------------------------------------------------------------------------------------------------
template<typename T>
void Selector<T>::selectAllElements()
{
	for(auto& t: _targetSelectedElementsMap){
		t.second.get()->clear();
		if(t.first){
			for(auto& k: t.first->getCollection())
			{
				k->setSelectedNoEvents(true);
				t.second.get()->push_back(k);
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
template<typename T>
bool Selector<T>::isElementSelected(T* k, BaseHasCollection<T>* owner)
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
	// TODO: find if a binary search is faster
	//	return binary_search(selectedElements.begin(), selectedElements.end(), k, keyframesort);
}

template<typename T>
std::vector<T*> * Selector<T>::getSelectedElements(BaseHasCollection<T>* target)
{
	if(_targetSelectedElementsMap.count(target))
	{
		return _targetSelectedElementsMap[target].get();
	}
	return nullptr;
}


template<typename T>
bool Selector<T>::addTarget(BaseHasCollection<T>* target)
{
	if(_targetSelectedElementsMap.count(target))
	{
		ofLogWarning("Selector<T>::addTarget") << "Unable to add target as it  already exists.";
		return false;
	}
	
	_targetSelectedElementsMap[target] = std::move(std::make_unique<std::vector<T*>>());
	return true;
}

template<typename T>
bool Selector<T>::removeTarget(BaseHasCollection<T>* target)
{
	auto n = _targetSelectedElementsMap.erase(target);
	if(n) return true;
	
	ofLogWarning("Selector<T>::removeTarget") << "Unable to remove target as it was never added.";
	return false;
	
}

template<typename T>
void Selector<T>::setIntersectionMode(SelectorIntersectionMode mode)
{
	_intersectionMode = mode;
}

template<typename T>
SelectorIntersectionMode Selector<T>::getIntersectionMode() const
{
	return _intersectionMode;
}

template<typename T>
void Selector<T>::onKeyboardEvent(DOM::KeyboardUIEventArgs& evt, DOM::Element* caller)
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
	
//	std::cout << "Selector<T>::onKeyboardEvent  " << std::boolalpha << _bAddToCurrentSelection << std::endl;
	
}


template class Selector<KeyframeView>;


} } // ofx::LineaDeTiempo

