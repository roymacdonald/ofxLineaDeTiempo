//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofAppBaseWindow.h"
#include "ofx/DOM/Element.h"


namespace ofx {
namespace DOM {


/// \brief The Document represents the root DOM Element in an DOM tree.
class Document: public Element
{
public:
    /// \brief Create a default Document.
    ///
    /// The Document will have the default id of "document" and will fill
    /// the entire screen.
    ///
    /// \param window The window that is the source of the UI events.
    Document(ofAppBaseWindow* window = ofGetWindowPtr());

    /// \brief Destroy the Document.
    virtual ~Document();

    /// \brief Callback for the setup event.
    /// \param e the event data.
    void setup(ofEventArgs& e);

    /// \brief Callback for the update event.
    /// \param e the event data.
    void update(ofEventArgs& e);

    /// \brief Callback for the draw event.
    /// \param e the event data.
    void draw(ofEventArgs& e);

    /// \brief Callback for the exit event.
    /// \param e the event data.
    void exit(ofEventArgs& e);

    /// \brief Callback for the window resized event.
    /// \param e the event data.
    void windowResized(ofResizeEventArgs& e);

    /// \brief Callback for file drag events.
    /// \param e the event data.
    /// \returns true iff the event was handled.
    bool fileDragEvent(ofDragInfo& e);

    /// \brief Callback for key events events.
    /// \param e the event data.
    /// \returns true iff the event was handled.
    bool onKeyEvent(ofKeyEventArgs& e);

    /// \brief Determine if the Document size should always match the screen size.
    /// \param true if if the Document size should always match the screen size.
    void setAutoFillScreen(bool autoFillScreen);

    /// \returns true if the Document size will always match the screen size.
    bool getAutoFillScreen() const;

    /// \brief Callback for pointer events.
    /// \param e The PointerEventArgs.
    /// \returns true if the event was handled.
    /// \todo Implement way to call default action if the event is not handled.
    bool onPointerEvent(PointerEventArgs& e);

    /// \brief Set a pointer capture on a given Element.
    /// \param element A pointer to the capturing Element.
    /// \param id The pointer id to capture.
    /// \throws DOMException on invalid DOM state or pointer id.
    void setPointerCaptureForElement(Element* element, std::size_t id);

    /// \brief Release a pointer capture on a given Element.
    /// \param element A pointer to the capturing Element.
    /// \param id The pointer id to release.
    /// \throws DOMException on invalid DOM state or pointer id.
    void releasePointerCaptureForElement(Element* element, std::size_t id);

protected:
    /// \brief Map pointer ids to Elements.
    typedef std::unordered_map<std::size_t, Element*> PointerElementMap;

    /// \brief True if the Document size should always match the screen size.
    bool _autoFillScreen = true;

    /// \brief Captured pointer and their capture target.
    PointerElementMap _capturedPointerIdToElementMap;

    /// \brief Currently active targets for given pointer ids.
    ///
    /// It is not required that these targets are captured, only that they
    /// passed a hit test. This is used for doing pointer in / pointer out, etc
    /// when the pointer isn't captured (e.g. mouse over, etc).
    ///
    /// In some cases, an active target may be a nullptr, meaning that the
    /// last pointer event could not be handled by any Element in the Document
    /// tree. This may happen, for instance, if the root Document does not cover
    /// the entire screen and we receive an event that falls outside.
    ///
    /// We still keep track of these events in order to correctly generate
    /// various synthesized events and gestures.
    PointerElementMap _activeTargets;

    /// \brief Currently active pointers and their last associated event.
    ///
    /// This map is a basic list of the pointers that we know about.
    ///
    /// For pointers that support hovering (e.g. mouse, trackball, etc) the
    /// pointer's id will always be active. For pointers that do not support
    /// hovering (e.g. multi-touch surfaces) the pointer ids will only be
    /// recorded until they leave the surface via a pointerup or pointercancel
    /// event.
    std::unordered_map<std::size_t, PointerEventArgs> _activePointers;

    /// \brief The Element that currently has focus.
    Element* _focusedElement = nullptr;

private:
    /// \brief Utility method to find an Element mapped to a pointer id.
    /// \param id The pointer id to search for.
    /// \param pem The pointer element map to search.
    /// \returns the matching element or nullptr if no match is found.
    static Element* findElementInMap(std::size_t id, PointerElementMap& pem);

    /// \brief Synthesize pointerout and pointerleave events on the target.
    /// \param e The PointerEventArgs that caused the events.
    /// \param target The target to receive the events.
    /// \param relatedTarget The target that this is transitioning from.
    void synthesizePointerOutAndLeave(const PointerEventArgs& e,
                                      Element* target,
                                      Element* relatedTarget);

    /// \brief Synthesize pointerover and pointerenter events on the target.
    /// \param e The PointerEventArgs that caused the events.
    /// \param target The target to receive the events.
    /// \param relatedTarget The target that this is transitioning from.
    void synthesizePointerOverAndEnter(const PointerEventArgs& e,
                                       Element* target,
                                       Element* relatedTarget);


    /// \brief Setup event listener.
    ofEventListener _setupListener;

    /// \brief Update event listener.
    ofEventListener _updateListener;

    /// \brief Draw event listener.
    ofEventListener _drawListener;

    /// \brief Exit event listener.
    ofEventListener _exitListener;

    /// \brief Window resized event listener.
    ofEventListener _windowResizedListener;

    /// \brief File drop event listener.
    ofEventListener _fileDroppedListener;

    /// \brief Key pressed event listener.
    ofEventListener _keyPressedListener;

    /// \brief Key released event listener.
    ofEventListener _keyReleasedListener;

    /// \brief Pointer down event listener.
    ofEventListener _pointerEventListener;

    /// \brief The event source window.
    ofAppBaseWindow* _window = nullptr;
};


} } // namespace ofx::DOM
