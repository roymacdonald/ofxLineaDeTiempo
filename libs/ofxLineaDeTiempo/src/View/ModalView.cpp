//
//  ModalView.cpp
//  example-basic
//
//  Created by Roy Macdonald on 8/5/20.
//
#include "ofGraphics.h"
#include "LineaDeTiempo/View/ModalView.h"
#include "LineaDeTiempo/View/TimelineDocument.h"
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {


//AbstractModalElement::AbstractModalElement()
//{
//	
//}


AbstractModalElement::AbstractModalElement(DOM::Element* owner):
_owner(owner)
{
	_creationTime = ofGetElapsedTimeMillis();
}


AbstractModalElement::~AbstractModalElement()
{
	
}

void AbstractModalElement::update(uint64_t currentTime)
{
	if(!_needsToBeRemoved)
	{
		if(_expired || currentTime - _creationTime > ConstVars::tooltipTimeout)
		{
			_willBeRemoved();
		}
	}
}

void AbstractModalElement::_willBeRemoved()
{
	ofNotifyEvent(willBeRemovedEvent, this);
	_needsToBeRemoved = true;
}


bool AbstractModalElement::needsToBeRemoved() const
{
	return _needsToBeRemoved;
}


void AbstractModalElement::expire()
{
	_expired = true;
}

TooltipOwner::TooltipOwner(DOM::Element* _self, const std::string& tooltip)
:_tooltipOwner(_self)
,_tooltip(tooltip)
{
	
	_pointerListeners.push(_self->pointerOver.event(false).newListener(this, &TooltipOwner::onPointerOver, std::numeric_limits<int>::lowest()));
	_pointerListeners.push(_self->pointerEnter.event(false).newListener(this, &TooltipOwner::onPointerOver, std::numeric_limits<int>::lowest()));
	_overStartTime = ofGetElapsedTimeMillis();
	
}


TooltipOwner::~TooltipOwner()
{

}


void TooltipOwner::onPointerOver(DOM::PointerUIEventArgs& e)
{
	_bCanShowTooltip = true;
}

void TooltipOwner::_updateShowTooltip( bool bMoving, bool bOver, const std::map<size_t, PointerEventArgs>& pointersOver, DOM::Document* docu)
{
	
	if(!ConstVars::showTooltips) return;
	
	if(_tooltipOwner == nullptr)
	{
		std::cout << "TooltipOwner::_updateShowTooltip: tooltop Owner is null\n";
		return;
	}
	if(_tooltip != "")
	{
		auto doc = dynamic_cast<TimelineDocument*>(docu);
		if(doc)
		{
			if(doc->getModal()){
				
				if(bOver)
				{
					if(bMoving){
						
						_overStartTime = ofGetElapsedTimeMillis();
						if(_tooltipModal != nullptr)
						{
							_tooltipModal->expire();
						}
					}
					else
					{
						if(_tooltipModal == nullptr && _bCanShowTooltip)
						{
							if(ofGetElapsedTimeMillis() - _overStartTime  > ConstVars::tooltipDelay)
							{
								for(auto& p: pointersOver)
								{
									
									_tooltipModal = doc->getModal()->add<Tooltip>(_tooltipOwner, _tooltip, p.second.position());
									_modalRemoveListener = _tooltipModal->willBeRemovedEvent.newListener(this, &::ofx::LineaDeTiempo::TooltipOwner::_removeModalCB);
								}
							}
						}
					}
				}
				else if(_tooltipModal != nullptr)
				{
					_tooltipModal->expire();
				}
			}
		}
	}
}
void TooltipOwner::_removeModalCB()
{
	_tooltipModal = nullptr;
	_modalRemoveListener.unsubscribe();
	_bCanShowTooltip = false;
}







Tooltip::Tooltip(DOM::Element* owner, const std::string& label, const DOM::Position& screenPos)
:AbstractModalElement(owner)
,_label(label)
,_screenPos(screenPos)
, DOM::Element(label, screenPos.x, screenPos.y, 0,0)
{

}


Tooltip::~Tooltip()
{
	
}



void Tooltip::make()
{
	auto s = document()->getDocumentStyles();
	if(s){
		auto f = s->getFont(MUI::EXTRA_SMALL);
		
		_screenPos.y -= _margin;
		
		auto pos = screenToParent(_screenPos);
		
		
		
		
		auto bb = f.getStringBoundingBox(_label, pos.x, pos.y);
		
		bb.standardize();
		bb.x -=  _margin;
		bb.y -= _margin;
		bb.height += _margin*2;
		bb.width += _margin*2;
		
		setShape(bb);
		
		auto localPos = screenToLocal(_screenPos);
		
		if(bb.width + _screenPos.x  > ofGetWidth())
		{
			bb.x -=  bb.width;
			setShape(bb);
			localPos.x -=  bb.width - _margin;
		}
		
		
//		std::cout << "Tooltip::make() localPos: " << localPos << "\n";
		_textMesh = f.getStringMesh(_label, localPos.x, localPos.y);
		_bNeedsMake = false;
	}
}

void Tooltip::onUpdate()
{
	if(_bNeedsMake) make();
}

void Tooltip::onDraw() const
{
	
	auto s = document()->getDocumentStyles();
	if(s){
		
		ofFill();
		ofSetColor(ConstVars::TooltipBackgroundColor.get());
		ofDrawRectangle(0,0,getWidth(), getHeight());
		
		ofNoFill();
		ofSetColor(ConstVars::TooltipBorderColor.get());
		ofDrawRectangle(0,0,getWidth(), getHeight());
		
		ofSetColor(ConstVars::TooltipTextColor.get());
		
		auto f = s->getFont(MUI::EXTRA_SMALL);
		f.getFontTexture().bind();
		_textMesh.draw();
		f.getFontTexture().unbind();
		
	}
}




ModalView::ModalView(const std::string& id, const ofRectangle& shape, TimelineDocument* doc)
:DOM::Element(id, shape)
,_doc(doc)
{
	setDrawChildrenOnly(true);
//	if(_doc)
//	{
////		_parentShapeListener = _doc->shapeChanged.newListener(this, &ModalView::_documentShapeChange);
//	}
}


ModalView::~ModalView()
{
	
}


//bool ModalView::addTooltip(DOM::Element* owner, const std::string& label, const DOM::Position& screenPosition)
//{
//	if(_tooltipMap.count(owner) == 0)
//	{
//		_tooltipMap[owner] = addChild<Tooltip>(owner, label, screenPosition);
//		moveToFront();
//		return true;
//	}
//	else
//	{
//		std::cout << "there is already a tooltip from this owner\n";
//	}
//	return false;
//}


void ModalView::onUpdate()
{
	if(_modalElements.size())
	{
		auto t = ofGetElapsedTimeMillis();
		for(auto& e: _modalElements)
		{
			e->update(t);
		}
		
		ofRemove(_modalElements, [this](AbstractModalElement* e){
			return this->remove(e);
		});
	}
}


bool ModalView::remove(AbstractModalElement* e)
{
	
	if(e->needsToBeRemoved())
	{
		auto c = dynamic_cast<DOM::Element*>(e);
		if(c)
		{
			removeChild(c);
		}
		return true;
	}
	return false;
}

//bool ModalView::isShowingTooltip(DOM::Element* owner)
//{
//	return _tooltipMap.count(owner) > 0;
//}


void ModalView::_documentShapeChange(DOM::ShapeChangeEventArgs& s)
{
	setShape({0,0, s.shape.getWidth(), s.shape.getHeight()});
}



} } // ofx::LineaDeTiempo

