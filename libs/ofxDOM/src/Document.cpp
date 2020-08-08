//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/DOM/Document.h"
#include "ofGraphics.h"
#include "ofAppRunner.h"


namespace ofx {
namespace DOM {


Document::Document(const DocumentSettings& settings)
: Element("Document" , 0,0,1024, 768)
, _settings(settings)
{
		
	_setupListeners();

}


Document::~Document()
{
}


void Document::setup(ofEventArgs& e)
{
    if (_settings.enabledListeners[WINDOW_RESIZED_EVENT])//autoFillScreen
    {
        setSize(ofGetWidth(), ofGetHeight());
    }

    Element::_setup(e);
}


void Document::update(ofEventArgs& e)
{
    Element::_update(e);
}


void Document::draw(ofEventArgs& e)
{
	Element::_draw(e);
}


void Document::exit(ofEventArgs& e)
{
    Element::_exit(e);
}


void Document::windowResized(ofResizeEventArgs& e)
{
	setShape(Shape(0,0,e.width, e.height));
}


bool Document::fileDragEvent(ofDragInfo& e)
{
    return false;
}


bool Document::onKeyEvent(ofKeyEventArgs& e)
{
    if (_focusedElement != nullptr)
    {
        KeyboardUIEventArgs keyboardEvent(e, this, _focusedElement);
        _focusedElement->dispatchEvent(keyboardEvent);
    }

    return false;
}


void Document::setAutoFillScreen(bool autoFillScreen)
{
    if(autoFillScreen)
	{
		enableEventListener(WINDOW_RESIZED_EVENT);
	}
	else
	{
		disableEventListener(WINDOW_RESIZED_EVENT);
	}

    if (autoFillScreen)
    {
        setShape(ofRectangle(0,0,ofGetWidth(), ofGetHeight()));
    }
}


bool Document::getAutoFillScreen() const
{
	return _settings.enabledListeners[WINDOW_RESIZED_EVENT];
}

void Document::focusElement(Element* target)
{
	if(target != nullptr && target->isFocusable() ){
		if (_focusedElement != nullptr && _focusedElement != target)
		{
			Element* _lastFocusedElement = nullptr;
			
			FocusEventArgs focusOut(FocusEventArgs::FOCUS_OUT,
									this,
									_focusedElement,
									target);
			
			_focusedElement->dispatchEvent(focusOut);
			
			FocusEventArgs focusIn(FocusEventArgs::FOCUS_IN,
								   this,
								   target,
								   _focusedElement);
			
			target->dispatchEvent(focusIn);
			
			_focusedElement->_focused = false;
			
			FocusEventArgs blur(FocusEventArgs::BLUR,
								this,
								_focusedElement,
								target);
			
			_focusedElement->dispatchEvent(blur);
			
			_lastFocusedElement = _focusedElement;
			_focusedElement = target;
			
			target->_focused = true;
			
			FocusEventArgs focus(FocusEventArgs::FOCUS,
								 this,
								 _focusedElement,
								 _lastFocusedElement);
			
			_focusedElement->dispatchEvent(focus);
			
		}
		else
		{
			FocusEventArgs focusIn(FocusEventArgs::FOCUS_IN,
								   this,
								   target,
								   nullptr);
			
			target->dispatchEvent(focusIn);
			
			_focusedElement = target;
			
			target->_focused = true;
			
			FocusEventArgs focus(FocusEventArgs::FOCUS,
								 this,
								 _focusedElement,
								 nullptr);
			
			_focusedElement->dispatchEvent(focus);
		}
	}
}




bool Document::onPointerEvent(PointerEventArgs& e)
{
    // Determine if the event was handled.
    bool wasEventHandled = false;

    // Add this pointer to the list of active pointers.
    _activePointers[e.pointerId()] = e;

    // The last element that the current pointer was hitting.
    Element* lastActiveTarget = findElementInMap(e.pointerId(), _activeTargets);

    // The Element that the pointer is currently hitting.
    // Find the current active target.
    // TODO: Use lastActiveTarget to seed target search?
    Element* activeTarget = recursiveHitTest(screenToParent(e.position()));

    // TODO: Quick and dirty.
    if (e.eventType() == PointerEventArgs::POINTER_DOWN && capturedPointers().empty())
    {
		focusElement(activeTarget);
    }

    // The event target is the target that will receive the event.
    //
    // We start off assuming that the event target is the active target.
    // If we determine that the pointer has already been captured, we will
    // correct this.
    Element* eventTarget = findElementInMap(e.pointerId(), _capturedPointerIdToElementMap);

    // If there is no event target but there is an active target, attempt to
    // capture the pointer.
    if (eventTarget == nullptr &&
        activeTarget != nullptr &&
        e.eventType() == PointerEventArgs::POINTER_DOWN &&
        activeTarget->getImplicitPointerCapture())
    {
        eventTarget = activeTarget;
        setPointerCaptureForElement(eventTarget, e.pointerId());
    }

    // If true, we call synthesizePointerOutAndLeave after the pointerup / pointercancel event.
    bool sythesizeUpAndLeaveForEventTarget = false;

    // If activeTarget is not equal to the last active target, then
    /// pointerout, pointerleave, pointerover and pointer enter events will
    // be synthesized as needed. This goes for any event type.
    if (activeTarget != lastActiveTarget)
    {
        // Synthesize pointerout and pointerleave events IF there was a
        // valid target last time.  Also make sure that the last target
        // isn't the current active target.
        if (lastActiveTarget != nullptr)
        {
            // From lastActiveTarget -> activeTarget.
            synthesizePointerOutAndLeave(e, lastActiveTarget, activeTarget);
        }

        // Sytnesize pointerover and pointerenter events if the current
        // active target is valid.
        if (activeTarget != nullptr)
        {
            // From lastActiveTarget -> activeTarget.
            synthesizePointerOverAndEnter(e, activeTarget, lastActiveTarget);
        }
    }


    // Here we handle a special case for non-hover sythesized pointer events.
    if (activeTarget != nullptr &&
        e.deviceType() != PointerEventArgs::TYPE_MOUSE &&
        (e.eventType() == PointerEventArgs::POINTER_UP ||
         e.eventType() == PointerEventArgs::POINTER_CANCEL))
    {
        if (activeTarget == eventTarget)
        {
            // Schedule synthesis, if the active target is the event target.
            sythesizeUpAndLeaveForEventTarget = true;
        }
        else
        {
            // Since lastActiveTarget may be nullptr, we use:
            // activeTarget -> nullptr.
            synthesizePointerOutAndLeave(e, activeTarget, nullptr);
        }
    }

 
    // Now, dispatch the original event if there is a target.
    // If eventTarget != nullptr, that means the current pointer id is captured.
    if (eventTarget != nullptr)
    {
		// Create a DOM pointer event.
		 PointerUIEventArgs event(e, this, eventTarget);

        event.setPhase(EventArgs::Phase::AT_TARGET);

        // Update captured pointer data.
        auto capturedPointer = eventTarget->findCapturedPointerById(e.pointerId());

        if (capturedPointer != eventTarget->capturedPointers().end())
        {
            capturedPointer->update(eventTarget, event);
        }
        else
        {
            throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Document::onPointerEvent");
        }

        // Handle event.
        eventTarget->handleEvent(event);

        // Sythesized events if needed.
        if (sythesizeUpAndLeaveForEventTarget)
        {
            synthesizePointerOutAndLeave(e, eventTarget, nullptr);
        }

        // Release pointer capture if needed.
        if (e.eventType() == PointerEventArgs::POINTER_UP ||
            e.eventType() == PointerEventArgs::POINTER_CANCEL)
        {
            releasePointerCaptureForElement(eventTarget, e.pointerId());
        }

        wasEventHandled = true;

    }
    else
	if (activeTarget != nullptr)
    {
		//Dispatch the event in case that the event was not comming from a captured pointer; mouse move, mouse scroll, etc
			// Create a DOM pointer event.
			 PointerUIEventArgs event(e, this, activeTarget);
			
			if(!activeTarget->dispatchEvent(event)){
				//TODO: (roymacdonald) i am not sure if here something should be done
			}
        // TODO: call default action if there is one.
    }

    // Manage active targets and pointers lists.
    if (e.deviceType() != PointerEventArgs::TYPE_MOUSE
    && (e.eventType() == PointerEventArgs::POINTER_UP ||
        e.eventType() == PointerEventArgs::POINTER_CANCEL))
    {
        _activeTargets.erase(e.pointerId());
        _activePointers.erase(e.pointerId());
    }
    else
    {
        // Active target may be a nullptr if outside of the Document.
        _activeTargets[e.pointerId()] = activeTarget;
    }

    return wasEventHandled;
}


void Document::setPointerCaptureForElement(Element* element, std::size_t id)
{
    // Make sure the element isn't nullptr and the caller is this document.
    if (element != nullptr && this == element->document())
    {
        auto activePointersIter = _activePointers.find(id);

        // If called from within Document, this shouldn't happen, but check anyway.
        if (activePointersIter == _activePointers.end())
        {
            throw DOMException(DOMException::INVALID_POINTER_ID + ": " + "Document::setPointerCapture");
        }
        else if (activePointersIter->second.buttons() > 0 && // Capture only if "button" is pressed.
                 _capturedPointerIdToElementMap.find(id) == _capturedPointerIdToElementMap.end()) // And pointer is not yet captured.
        {
            // Add the pointer to our map.
            _capturedPointerIdToElementMap[id] = element;

            // Add the pointer id to the element's captured pointer list.
            element->_capturedPointers.emplace_back(CapturedPointer(id));

            // Emit a pointer captured event.
            PointerCaptureUIEventArgs e(id, true, this, element);
            element->dispatchEvent(e);
        }
        else
        {
            // Ignore if already captured OR no buttons were pressed.
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Document::setPointerCapture");
    }
}


void Document::releasePointerCaptureForElement(Element* element, std::size_t id)
{
    // TODO: release if the target element is removed from the document.

    if (element != nullptr)
    {
        auto activePointersIter = _activePointers.find(id);

        if (activePointersIter != _activePointers.end())
        {
            auto iter = _capturedPointerIdToElementMap.find(id);

            if (iter != _capturedPointerIdToElementMap.end())
            {
                _capturedPointerIdToElementMap.erase(iter);

                element->_capturedPointers.erase(element->findCapturedPointerById(id));

                PointerCaptureUIEventArgs e(id, false, this, element);
                element->dispatchEvent(e);
            }
        }
        else
        {
            throw DOMException(DOMException::INVALID_POINTER_ID + ": " + "Document::releasePointerCapture");
        }
    }
    else
    {
        throw DOMException(DOMException::INVALID_STATE_ERROR + ": " + "Document::releasePointerCapture");
    }
}


Element* Document::findElementInMap(std::size_t id, PointerElementMap& pem)
{
    // Search the captured pointers for a matching pointer.
    auto iter = pem.find(id);

    if (iter != pem.end())
    {
        return iter->second;
    }

    return nullptr;
}


void Document::synthesizePointerOutAndLeave(const PointerEventArgs& e,
                                            Element* target,
                                            Element* relatedTarget)
{
    PointerEventArgs pointerOut(PointerEventArgs::POINTER_OUT, e);

    // Call pointerout ONLY on old target
    PointerUIEventArgs pointerOutEvent(pointerOut,
                                       this,
                                       target,
                                       relatedTarget);

    pointerOutEvent.setPhase(EventArgs::Phase::AT_TARGET);

    target->handleEvent(pointerOutEvent);

    PointerEventArgs pointerLeave(PointerEventArgs::POINTER_LEAVE, e);

    // Call pointerleave on old target AND ancestors.
    PointerUIEventArgs pointerLeaveEvent(pointerLeave,
                                         this,
                                         target,
                                         relatedTarget);

    target->dispatchEvent(pointerLeaveEvent);
}


void Document::synthesizePointerOverAndEnter(const PointerEventArgs& e,
                                             Element* target,
                                             Element* relatedTarget)
{
    PointerEventArgs pointerOver(PointerEventArgs::POINTER_OVER, e);

    // Call pointerout ONLY on old target
    PointerUIEventArgs pointerOverEvent(pointerOver,
                                        this,
                                        target,
                                        relatedTarget);

    pointerOverEvent.setPhase(EventArgs::Phase::AT_TARGET);

    target->handleEvent(pointerOverEvent);

    PointerEventArgs pointerEnter(PointerEventArgs::POINTER_ENTER, e);

    // Call pointerover ONLY on the target.
    // Call pointerenter on target and ancestors.
    // Call pointerleave on old target and ancestors
    PointerUIEventArgs pointerEnterEvent(pointerEnter,
                                         this,
                                         target,
                                         relatedTarget);

    target->dispatchEvent(pointerEnterEvent);
}

// std::string toString(DocumentEvent d)
// {
// 	if(d == SETUP_EVENT) return "SETUP_EVENT";
// 	if(d == UPDATE_EVENT) return "UPDATE_EVENT";
// 	if(d == DRAW_EVENT) return "DRAW_EVENT";
// 	if(d == EXIT_EVENT) return "EXIT_EVENT";
// 	if(d == WINDOW_RESIZED_EVENT) return "WINDOW_RESIZED_EVENT";
// 	if(d == FILE_DROPPED_EVENT) return "FILE_DROPPED_EVENT";
// 	if(d == KEY_PRESSED_EVENT) return "KEY_PRESSED_EVENT";
// 	if(d == KEY_RELEASED_EVENT) return "KEY_RELEASED_EVENT";
// 	return "";
// }

void Document::enableEventListener(DocumentEvent event)
{
	ofCoreEvents& events = _settings.window ? _settings.window->events() : ofEvents();
	
    if( event == SETUP_EVENT)
    {
        _setupListener = events.setup.newListener(this, &Document::setup);
    }
	else 
    if( event == UPDATE_EVENT)
    {
        _updateListener = events.update.newListener(this, &Document::update);
    }
	else 
    if( event == DRAW_EVENT)
    {
        _drawListener = events.draw.newListener(this, &Document::draw, std::numeric_limits<int>::max());
    }
	else
    if( event == EXIT_EVENT)
    {
        _exitListener = events.exit.newListener(this, &Document::exit);
    }
	else 
    if( event == WINDOW_RESIZED_EVENT)
    {
        _windowResizedListener = events.windowResized.newListener(this, &Document::windowResized, std::numeric_limits<int>::lowest());
    }
	else 
    if( event == FILE_DROPPED_EVENT)
    {
        _fileDroppedListener = events.fileDragEvent.newListener(this, &Document::fileDragEvent, std::numeric_limits<int>::lowest());
    }
	else 
    if( event == KEY_PRESSED_EVENT)
    {
        _keyPressedListener = events.keyPressed.newListener(this, &Document::onKeyEvent, std::numeric_limits<int>::lowest());
    }
	else 
    if( event == KEY_RELEASED_EVENT)
    {
        _keyReleasedListener = events.keyReleased.newListener(this, &Document::onKeyEvent, std::numeric_limits<int>::lowest());
    }

    _settings.enabledListeners[event] = true;

}

void Document::disableEventListener(DocumentEvent event)
{

      	 if(event == SETUP_EVENT )          {         _setupListener.unsubscribe(); }
    else if(event == UPDATE_EVENT )         {        _updateListener.unsubscribe(); }
    else if(event == DRAW_EVENT )           {          _drawListener.unsubscribe(); }
    else if(event == EXIT_EVENT )           {          _exitListener.unsubscribe(); }
    else if(event == WINDOW_RESIZED_EVENT ) { _windowResizedListener.unsubscribe(); }
    else if(event == FILE_DROPPED_EVENT )   {   _fileDroppedListener.unsubscribe(); }
    else if(event == KEY_PRESSED_EVENT )    {    _keyPressedListener.unsubscribe(); }
	else if(event == KEY_RELEASED_EVENT )   {   _keyReleasedListener.unsubscribe(); }
 
	_settings.enabledListeners[event] = false;

}
bool Document::isListeningEvent(DocumentEvent event)
{
	return _settings.enabledListeners[event];
}

void Document::_setupListeners()
{
	
    if (_settings.window)
    {
        _pointerEventListener = PointerEventsManager::instance().eventsForWindow(_settings.window)->pointerEvent.newListener(this, &Document::onPointerEvent, _settings.pointerEventPriority);
    }
    else
    {
        _pointerEventListener = PointerEventsManager::instance().events()->pointerEvent.newListener(this, &Document::onPointerEvent, _settings.pointerEventPriority);
    }
	
	
	for(int i = 0; i < _settings.enabledListeners.size(); ++i)
	{
		if(_settings.enabledListeners[i])
		{
			enableEventListener((DocumentEvent)i);
		}
	}
}
void Document::_disableAllListeners()
{
	for(int i = 0; i < _settings.enabledListeners.size(); ++i)
	{
		disableEventListener((DocumentEvent)i);
	}
}
void Document::setWindow(ofAppBaseWindow* window)
{
	_disableAllListeners();
	_settings.window = window;
	
	_setupListeners();
	
}


std::shared_ptr<MUI::Styles> Document::getDocumentStyles() const
{
    if (_documentStyles == nullptr)
    {
        _documentStyles = std::make_shared<MUI::Styles>("Document Styles");
    }

    return _documentStyles;
}


void Document::setDocumentStyles(std::shared_ptr<MUI::Styles> documentStyles)
{
    _documentStyles = documentStyles;
}



} } // namespace ofx::DOM
