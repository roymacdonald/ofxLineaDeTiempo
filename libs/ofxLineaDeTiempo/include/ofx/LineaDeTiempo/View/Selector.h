//
//  BaseHasSelectionRect.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/22/20.
//


#pragma once

#include "LineaDeTiempo/BaseTypes/BaseSelectable.h"
#include "LineaDeTiempo/BaseTypes/BaseHasCollection.h"
//#include "ofEvent.h"
#include "DOM/Element.h"
#include "ofMain.h"

#include <map>

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
	
	
	Selector();
	
	void setLimitingElement(DOM::Element * limitingElement);
	
	bool isSelectingRect() const;
	
	
	ofEvent<ofRectangle> selectionRectUpdated;
	
	const ofRectangle& getRect() const;
	
	void draw() const;
	
	void selectElement(ElementType* e, BaseHasCollection<ElementType>* owner);
	
	void unselectElement(ElementType* e, BaseHasCollection<ElementType>* owner);
	
	bool isElementSelected(ElementType* e, BaseHasCollection<ElementType>* owner);
	
	///\brief returns true if any element got unselected
	bool unselectAllElements();
	
	void selectAllElements();

	
	bool addTarget(BaseHasCollection<ElementType>* target);
	bool removeTarget(BaseHasCollection<ElementType>* target);
	
	
//	///\brief this function needs to be implemented on the derived class and pass the collection of elements that can be selected.
//	/// these elements must inherit form ofx::LineaDeTiempo::BaseSelectable
//	virtual std::vector<ElementType*> & getCollection() = 0;
//	virtual const std::vector<ElementType*> & getCollection() const= 0;

	std::vector<ElementType*> * getSelectedElements(BaseHasCollection<ElementType>* target);
	
	
	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt, DOM::Element* caller);
	
	void onPointerDown(const glm::vec2& localPosition, DOM::Element* caller);
	
	bool onPointerUp(const glm::vec2& localPosition, DOM::Element* caller);
	
	void onPointerDrag(const glm::vec2& localPosition, DOM::Element* caller);
	

	
	
	
	
protected:

//	virtual void _removeSelectedElements() = 0;
	
	// implement the keyboard listener function in the derived class and pass it to the selector
	//	void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt) ;
	
	
	
	void _setSelectedElementsFromRect(const ofRectangle& r);
	void _updateSelectionRect(const glm::vec2& args, DOM::Element* caller);
	
	
//	std::vector<ElementType*> selectedElements;

	std::map<BaseHasCollection<ElementType>*, std::unique_ptr<std::vector<ElementType*>> > _targetSelectedElementsMap;
	
private:
	
	bool _bAddToCurrentSelection = false;
	
    ofRectangle _rect;
	glm::vec2 _selectionRectStart;
	
	DOM::Element * _limitingElement = nullptr;
	
	
};
} } // ofx::LineaDeTiempo

