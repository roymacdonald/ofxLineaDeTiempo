//
//  BaseHasSelectionRect.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/22/20.
//


#pragma once
#include "LineaDeTiempo/View/KeyFrameView.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/BaseTypes/BaseSelectable.h"
#include "ofEvent.h"



namespace ofx {
namespace LineaDeTiempo {


template<typename ElementType>
class Selector
{
public:
	
	static_assert(std::is_base_of<BaseSelectable, ElementType>::value,
	"Selector<ElementType> instantiation failed. ElementType has to to be derived from ofx::LineaDeTiempo::BaseSelectable.");
	
	static_assert(std::is_base_of<BaseSelectable, ElementType>::value,
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
	virtual bool elementSort(ElementType* a, ElementType* b) = 0;

protected:
	
	void _SelectorPointerDown(const glm::vec2& localPosition);

	bool _SelectorPointerUp(const glm::vec2& localPosition);
	
	void _SelectorDragging(const glm::vec2& localPosition);

	
	void _setSelectedElementsFromRect(const ofRectangle& r, bool bAddToCurrentSelection);
	void _updateSelectionRect(const glm::vec2& args);
	
	
	std::vector<ElementType*> selectedElements;

	
private:
	
    ofRectangle _rect;
	glm::vec2 _selectionRectStart;
	
	DOM::Element * _limitingElement = nullptr;
	DOM::Element * _parentElement = nullptr;
	
};


} } // ofx::LineaDeTiempo

