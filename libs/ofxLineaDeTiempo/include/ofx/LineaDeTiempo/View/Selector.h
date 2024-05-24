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


///\brief Defines the different methods for finding if an element is intersecting the Selector's rectangle.
enum SelectorIntersectionMode{
	
	/// The element will be selected only when its center is inside the selector's rectangle
	SELECTOR_USE_CENTER_POSITION =0,
	/// The element will be selected when its rectangle intersects the selector's rectangle
	SELECTOR_USE_RECTANGLE
};



template<typename ElementType>
class Selector
{
public:
	
	static_assert(std::is_base_of<BaseSelectable, ElementType>::value,
	"Selector<ElementType> instantiation failed. ElementType has to to be derived from ofx::LineaDeTiempo::BaseSelectable.");
	
	static_assert(std::is_base_of<DOM::Element, ElementType>::value,
	"Selector<ElementType> instantiation failed. ElementType has to to be derived from ofx::DOM::Element.");
	
	
	Selector();
	
	
	///\brief Rectangle that limits the selectors area. Must be in screen coordinates
	void setLimitingRect(const ofRectangle& r);
	
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
	
	
	std::vector<ElementType*> * getSelectedElements(BaseHasCollection<ElementType>* target);
	
	
	void onKeyboardEvent(DOM::KeyboardUIEventArgs& evt, DOM::Element* caller);
	
	void onPointerDown(const glm::vec2& screenPosition, DOM::Element* caller);
	
	bool onPointerUp(const glm::vec2& screenPosition, DOM::Element* caller);
	
	void onPointerDrag(const glm::vec2& screenPosition, DOM::Element* caller);
	
	
	
	
	void setIntersectionMode(SelectorIntersectionMode mode);
	
	SelectorIntersectionMode getIntersectionMode() const;
	
	
protected:
	
	
	void _setSelectedElementsFromRect(const ofRectangle& r);
	void _updateSelectionRect(const glm::vec2& args, DOM::Element* caller);
	

	bool _checkIntersection(const ofRectangle& r,  ElementType * k ) const;
	
	std::map<BaseHasCollection<ElementType>*, std::unique_ptr<std::vector<ElementType*>> > _targetSelectedElementsMap;
	
	void _draw(ofEventArgs&);
	
private:
	
	SelectorIntersectionMode _intersectionMode = SELECTOR_USE_CENTER_POSITION;
	
	bool _bAddToCurrentSelection = false;
	
    ofRectangle _rect;
	ofRectangle _localRect;
	glm::vec2 _selectionRectStart;
	
	ofRectangle _limitingRect;
	
	
	ofEventListener _drawListener;
	mutable bool _bNeedsDraw = false;

	bool _bHadSelectedElements = false;
};
} } // ofx::LineaDeTiempo

