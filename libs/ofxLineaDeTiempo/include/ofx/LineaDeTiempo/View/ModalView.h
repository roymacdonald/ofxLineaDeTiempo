//
//  ModalView.h
//  example-basic
//
//  Created by Roy Macdonald on 8/5/20.
//

#pragma once
#include "DOM/Element.h"




namespace ofx {
namespace LineaDeTiempo {


class ModalView;
class TimelineDocument;

class AbstractModalElement
{
public:
//	AbstractModalElement();
	AbstractModalElement(DOM::Element* owner);
	virtual ~AbstractModalElement();

	
	ofEvent<void> willBeRemovedEvent;
	
	friend class ModalView;
	
	bool needsToBeRemoved() const;
	void update(uint64_t currentTime);
	
	void expire();
protected:
	
	void _willBeRemoved();
	
	
private:
	bool _needsToBeRemoved = false;
	DOM::Element* _owner = nullptr;
	uint64_t _creationTime =0;
	bool _expired = false;
};

class Tooltip;

class TooltipOwner
{
public:
	TooltipOwner(DOM::Element* _self, const std::string& tooltip);
	virtual ~TooltipOwner();
	
	void onPointerEvent(DOM::PointerUIEventArgs& e);
	
protected:

	std::string _tooltip = "";
		
	uint64_t _overStartTime = 0;
		
	void _updateShowTooltip( bool bMoving, bool bOver, const std::map<size_t, PointerEventArgs>& pointersOver, DOM::Document* docu);

	bool _bCanShowTooltip = false;
		
	Tooltip* _tooltipModal = nullptr;

	ofEventListener _modalRemoveListener;
	ofEventListeners _pointerListeners;
	void _removeModalCB();

	DOM::Element* _tooltipOwner = nullptr;
	
	void expireTooltip();
	
	
	
};

class Tooltip
: public DOM::Element
, public AbstractModalElement
{
public:
	Tooltip(DOM::Element* owner, const std::string& label, const DOM::Position& screenPos);
	virtual ~Tooltip();
	
	virtual void onDraw() const override;
	virtual void onUpdate() override;
//protected:
	
	void make();
	
	
	float _margin = 4;
	std::string _label;
	DOM::Position _screenPos;
	
	
	ofVboMesh _textMesh;
	
	
private:
	bool _bNeedsMake = true;
};



class ModalView: public DOM::Element
{
public:
	ModalView(const std::string& id, const ofRectangle& shape, TimelineDocument* _doc);
	virtual ~ModalView();
	
//	bool addTooltip(DOM::Element* owner, const std::string& label, const DOM::Position& screenPosition);
//	void removeTooltip(DOM::Element* owner);
//	bool isShowingTooltip(DOM::Element* owner);
	

	template<typename ModalType, typename... Args>
	ModalType* add(DOM::Element* owner, Args&&... args);
	
	bool remove(AbstractModalElement* modal);
	
	virtual void onUpdate() override;
    
	
//
//	const std::map<DOM::Element* ,Tooltip*>& getTooltipMap(){return _tooltipMap;}
//

	
private:
	ofEventListener _parentShapeListener;
	void _documentShapeChange(DOM::ShapeChangeEventArgs& s);
	
	std::vector<AbstractModalElement*> _modalElements;
	

	
	TimelineDocument* _doc = nullptr;
	
};


template<typename ModalType, typename... Args>
ModalType* ModalView::add(DOM::Element* owner, Args&&... args)
{
    static_assert(std::is_base_of<AbstractModalElement, ModalType>(), "ModalView::add ModalType must be derived from AbstractModalElement.");

	ModalType* e = addChild<ModalType>(owner, std::forward<Args>(args)...);
	_modalElements.push_back(e);
	moveToFront();
	return e;
	
}




} } // ofx::LineaDeTiempo

