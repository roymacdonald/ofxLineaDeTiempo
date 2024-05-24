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
#include "ofxTimecode.h"

namespace ofx {
namespace LineaDeTiempo {


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
		if(_expired || ( _timeout > 0 && currentTime - _creationTime > _timeout))
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
	
	_pointerListeners.push(_self->pointerOver.event(false).newListener(this, &TooltipOwner::onPointerEvent, std::numeric_limits<int>::lowest()));
	_pointerListeners.push(_self->pointerEnter.event(false).newListener(this, &TooltipOwner::onPointerEvent, std::numeric_limits<int>::lowest()));
	_pointerListeners.push(_self->pointerDown.event(false).newListener(this, &TooltipOwner::onPointerEvent, std::numeric_limits<int>::lowest()));
	_overStartTime = ofGetElapsedTimeMillis();
	
}


TooltipOwner::~TooltipOwner()
{

}


void TooltipOwner::onPointerEvent(DOM::PointerUIEventArgs& e)
{
	if(e.type() == PointerEventArgs::POINTER_OVER || e.type() == PointerEventArgs::POINTER_ENTER)
	{
		_bCanShowTooltip = true;
	}
	else
	{
		expireTooltip();
		_bCanShowTooltip = false;
	}
}


void TooltipOwner::expireTooltip()
{
	if(_tooltipModal != nullptr)
	{
		_tooltipModal->expire();
	}
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
		if(bOver)
		{
			if(bMoving){
				
				_overStartTime = ofGetElapsedTimeMillis();
				expireTooltip();
			}
			else
			{
				if(_tooltipModal == nullptr && _bCanShowTooltip)
				{
					if(ofGetElapsedTimeMillis() - _overStartTime  > ConstVars::tooltipDelay)
					{
						auto doc = dynamic_cast<TimelineDocument*>(docu);
						if(doc)
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
		}
		else
		{
			expireTooltip();
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
	_timeout = ConstVars::tooltipTimeout;
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
		_screenPos.x += _margin + 2;
		
		
		
		
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
			bb.x -=  bb.width + _margin + 2;
			setShape(bb);
		}
		
		
		
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


ModalTimeModifier::ModalTimeModifier(DOM::Element* owner, size_t initialMillis)
: Panel<TimeModifier>("TimeModifierPanel", ofRectangle(), initialMillis)
, AbstractModalElement(owner)
{
	_timeout = 0;

	followContainerSize(true);
	setHeaderLabel("Set Total Time");
	setResizable(false);
	updateLayout();
	
}

void ModalTimeModifier::expire()
{
	AbstractModalElement::expire();
	
	container->disableKeys();
	
}


TimeModifier*  ModalTimeModifier::getTimeModifier()
{
	return container;
}


const TimeModifier*  ModalTimeModifier::getTimeModifier() const
{
	return container;
}




	
ModalView::ModalView(const std::string& id, const ofRectangle& shape, TimelineDocument* doc)
: MUI::Widget(id, shape)

,_doc(doc)
{

}


ModalView::~ModalView()
{
	
}

bool ModalView::shouldBeDestroyed()
{
	return _needsToBeDestroyed;
}

void ModalView::onDraw() const
{
	if(_useBackgroundOverlay)
	{
		ofPushStyle();
		ofFill();
		ofSetColor(_backgroundOverlay);
		
		ofDrawRectangle(0,0,getWidth(), getHeight());
		ofPopStyle();
	}
}

void ModalView::useBackgroundOverlay(const ofColor& bg)
{
	_useBackgroundOverlay = true;
	_backgroundOverlay = bg;
}

void ModalView::_onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)
{
	Widget::_onPointerCaptureEvent(e);

    if (e.target() == this && e.type() == PointerEventArgs::GOT_POINTER_CAPTURE)
    {
		// if this gets triggered it means that the pointer was clicked outside any of the modal view's children, thus it need to be destroyed.
//		_needsToBeDestroyed = true;
		for(auto m : _modalElements)
		{
			if(m)
			{
				m->expire();
			}
		}
    }
}



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
	else
	{
		_needsToBeDestroyed = true;
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


void ModalView::_documentShapeChange(DOM::ShapeChangeEventArgs& s)
{
	setShape({0,0, s.shape.getWidth(), s.shape.getHeight()});
}



} } // ofx::LineaDeTiempo

