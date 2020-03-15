//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <unordered_set>
#include "ofx/PointerEvents.h"
#include "ofx/DOM/CapturedPointer.h"
#include "ofx/DOM/ElementEvents.h"

#include "ofx/DOM/Exceptions.h"
#include "ofx/DOM/Layout.h"
#include "ofx/DOM/Types.h"

#include "ofx/DOM/Events/DOMEventTarget.h"
#include "ofx/DOM/Node.h"

namespace ofx {
namespace DOM {


class Document;
class AbstractLayout;


/// \brief A class representing a DOM Element.
///
/// There are several DOM coordiante systems with respect to an Element.
///
/// 1. Local Coordinates: The origin of the local coordiantes are at 0, 0 of the
/// Element Shape.  The coordiantes of the local shape range from (0, 0)
/// - the upper left corner to (width, height) - the lower right corner of the
/// Element.
///
/// 2. Parent Coordinates: The (x, y) position of the Element shape are in
/// "Parent" Coordinates, meaning they are oriented with respect to the
/// parent's Local Coordinates.
///
/// 3. Screen Coordinates: The screen coordinates are the coordinates (x, y)
/// in terms of the global screen coordiantes where (0, 0) is the upper left
/// corner of the screen / window, and (ofGetWidth(), ofGetHeight()) are the
/// coordiantes of the lower right corner.
class Element
: public Node<Element>
, public DOMEventTarget<Element>
{
public:
    /// \brief Construct a new Element with the given parameters.
    ///
    /// The Element will take the default id, an empty string.
    ///
    /// \param x the X position of the Element in its parent coordinates.
    /// \param y the Y position of the Element in its parent coordinates.
    /// \param width the width of the Element.
    /// \param height the height of the Element.
    Element(float x, float y, float width, float height);

	/// \brief Construct a new Element with the given parameters.
    ///
    /// The Element will take the default id, an empty string.
    ///
    /// \param rect the rectangle that defines the element
	Element(const ofRectangle& rect);
	
    /// \brief Construct a new Element with the given parameters.
    /// \param id The id of the Element.
    /// \param x the X position of the Element in its parent coordinates.
    /// \param y the Y position of the Element in its parent coordinates.
    /// \param width the width of the Element.
    /// \param height the height of the Element.
    Element(const std::string& id, float x, float y, float width, float height);

	/// \brief Construct a new Element with the given parameters.
    /// \param id The id of the Element.
    /// \param rect the rectangle that defines the element
    Element(const std::string& id, const ofRectangle& rect);
	
    /// \brief Destroy the Element.
    virtual ~Element();


    /// \brief Get a pointer to the parent Document.
    /// \returns a pointer to the parent Document, self if a Document or a nullptr.
    Document* document();

    /// \brief Get a pointer to the parent Document.
    /// \returns a pointer to the parent Document, self if a Document or a nullptr.
    const Document* document() const;

    /// \brief Create a Layout using a templated Layout type.
    ///
    /// To create a Layout you can use this method like:
    ///
    /// LayoutType* layout = parentElement->createLayout<LayoutType>(arguments ...);
    ///
    /// \param args The variable constructor arguments for the ElementType.
    /// \returns A pointer to the added Element. The parent Element retains
    ///          ownership of the pointer via a std::unique_ptr.
    /// \tparam ElementType The subclass of Element that will be added.
    /// \tparam Args The variable constructor arguments for the ElementType.
    template <typename LayoutType, typename... Args>
    LayoutType* createLayout(Args&&... args);

    /// \brief Take ownership of the passed std::unique_ptr<Layout>.
    ///
    /// This this is "sink" meaning that any Layout passed to this will be
    /// owned by this Element.
    ///
    /// \param layout the rvalue reference to the Layout.
    /// \returns A pointer to the set Layout. The parent Element retains
    /// ownership of the pointer via a std::unique_ptr.
    /// \tparam LayoutType The Layout Type.
    template <typename LayoutType>
    LayoutType* setLayout(std::unique_ptr<LayoutType> layout);

    /// \brief Release ownership of the Layout.
    /// \returns a std::unique_ptr<Layout> to the Layout or nullptr if none.
    std::unique_ptr<Layout> removeLayout();

    /// \brief Get a pointer to the associated Layout.
    ///
    /// The Element retains ownership of the pointer via a std::unique_ptr.
    ///
    /// \returns a pointer to the associated Layout or nullptr if there is none.
    Layout* layout();

    /// \brief Perform a hit test on the Element.
    ///
    /// For a normal Element, the hit test will test the rectangular shape
    /// of the Element. Subclasses can override this method for custom hit test
    /// geometry.
    ///
    /// Parent coordinates are used because the shape / position of the
    /// Element are in parent coordinates.
    ///
    /// \param parentPosition The Position to test in parent coordinates.
    /// \returns true iff the local position is within the hit test region.
    virtual bool hitTest(const Position& parentPosition) const;

    /// \brief Perform a hit test on a child Element.
    /// \param localPosition The Position to test in local coordinates.
    /// \returns true iff the local position is within the hit test region.
    virtual bool childHitTest(const Position& localPosition) const;

    /// \brief Convert the local coordinates to screen coordinates.
    ///
    /// Local coordinates are defined with reference to the position of the box.
    /// The Position of this element will be in its parent's local coordinates.
    ///
    /// \param localPosition The local coordinates to convert.
    /// \returns the position converted from local to screen coordinates.
    Position localToScreen(const Position& localPosition) const;

    /// \brief Convert the screen coordinates to local coordinates.
    ///
    /// Local coordinates are defined with reference to the position of the box.
    /// The Position of this element will be in its parent's local coordinates.
    ///
    /// \param screenPosition The screen coordinates to convert.
    /// \returns the position converted from screen to local coordinates.
    Position screenToLocal(const Position& screenPosition) const;

    /// \brief Convert the parent coordinates to screen coordinates.
    /// \param parentPosition The parent coordinates to convert.
    /// \returns the position converted from parent to screen coordinates.
    Position parentToScreen(const Position& parentPosition) const;

    /// \brief Convert the screen coordinates to parent coordinates.
    /// \param screenPosition The screen coordinates to convert.
    /// \returns the position converted from screen to parent coordinates.
    Position screenToParent(const Position& screenPosition) const;

    /// \brief Set the position of the Element in its parent coordinates.
    /// \param x The new x position.
    /// \param y The new y position.
    void setPosition(float x, float y);

    /// \brief Set the position of the Element in its parent coordinates.
    /// \param position The new position.
    void setPosition(const Position& position);

    /// \brief Get the position of the Element in its parent coordinates.
    ///
    /// Local coordinates are defined with reference to the position of the box.
    /// The Position of this element will be in its parent's local coordinates.
    ///
    /// \returns The position in parent coordinates.
    Position getPosition() const;

    /// \brief Get the X position of the Element in its parent coordinates.
    /// \returns the X position of the Element in its parent coordinates.
    float getX() const;

    /// \brief Get the Y position of the Element in its parent coordinates.
    /// \returns the Y position of the Element in its parent coordinates.
    float getY() const;

    /// \brief Set the center position of the Element in its parent coordinates.
    ///
    /// This will set the position from the center based on the size of the
    /// element shape.
    ///
    /// \param centerX The new center x position in parent coordiantes.
    /// \param centerY The new center y position in parent coordinates.
    void setCenterPosition(float centerX, float centerY);

    /// \brief Set the center position of the Element in its parent coordinates.
    ///
    /// This will set the position from the center based on the size of the
    /// element shape.
    ///
    /// \param position The new center position in parent coordiantes.
    void setCenterPosition(const Position& center);

    /// \returns the center of the shape in parent coordinates.
    Position getCenterPosition() const;

    /// \brief Get the Position of the Element in screen coordinates.
    /// \returns the Position of the Element in screen coordinates.
    /// \todo Cache screen position w/ shape.
    Position getScreenPosition() const;

	/// \brief Get the Shape of the Element in screen coordinates.
    /// \returns the Shape of the Element in screen coordinates.
    /// \todo Cache screen shape w/ shape.
    Shape getScreenShape() const;
	
    /// \brief Get the X position of the Element in screen coordinates.
    /// \returns the X position of the Element in screen coordinates.
    float getScreenX() const;

    /// \brief Get the Y position of the Element in screen coordinates.
    /// \returns the Y position of the Element in screen coordinates.
    float getScreenY() const;

    /// \brief Get the center position of the Element in screen coordinates.
    /// \returns the center position of the Element in screen coordinates.
    Position getScreenCenterPosition() const;

    /// \brief Set the size of the Element.
    /// \param width The new width of the Element.
    /// \param height The new height of the Element.
    void setSize(float width, float height);

    /// \brief Get the Size of the Element.
    /// \returns the Size of the Element.
    Size getSize() const;

    /// \brief Get the width of the Element.
    /// \returns The width of the Element.
    float getWidth() const;

    /// \brief Get the height of the Element.
    /// \returns The height of the Element.
    float getHeight() const;

    /// \brief Get the shape of the Element in its parent coordinates.
    /// \returns the shape of the Element in its parent coordinates.
    Shape getShape() const;

    /// \brief Set the shape of the Element in its parent coordinates.
    /// \param shape The new shape of the Element in its parent coordinates.
    void setShape(const Shape& shape);

    /// \brief Get the bounding box representing all child elements.
    /// \returns the bounding box representing all child elements, or
    /// a rectangle of zero width and height at the origin if no children.
    Shape getChildShape() const;

    /// \brief Get the bounding box representing the union of the child shape and the element shape.
    /// \returns the bounding box representing the union of the child shape and the element shape.
    Shape getTotalShape() const;

    /// \brief Determine of the Element has an attribute with the given name.
    /// \param name The name of the Attribute to query.
    /// \returns true iff the Element has an attribute with the given name.
    bool hasAttribute(const std::string& name) const;

    /// \brief Get a named attribute via its key.
    ///
    /// Users should check to see if the attribute exists using hasAttribute or
    /// catch the DOMException.
    ///
    /// \throws DOMException if no such key.
    /// \throws Poco::BadCastException if the types do not match.
    /// \param key The name of the attribute.
    /// \param inherit True if the Element should query its ancestors for the attribute.
    /// \returns The value corresponding to the key, or throws an exception.
    template <typename AnyType>
    AnyType getAttribute(const std::string& key, bool inherit = false) const;

    /// \brief Set a value for a named attribute.
    ///
    /// If the given attribute exists, it will be overwritten with the given
    /// value.
    ///
    /// \param name The name of the attribute.
    /// \param value The new value of the attribute called name.
    void setAttribute(const std::string& name, const Any& value);

    /// \brief Clear a named attribute.
    /// \param The name of the attribute to clear.
    void clearAttribute(const std::string& name);

    /// \brief Request that the parent Document capture the given pointer id.
    ///
    /// Captured pointers send all of their revents to the capturing Element.
    ///
    /// \param id The pointer id to capture.
    void setPointerCapture(std::size_t id);

    /// \brief Release a captured pointer with the given id.
    ///
    /// Usually this call is not required as the parent Document's pointer
    /// dispatching system will automatically release a pointer on the next
    /// POINTER_UP event.  In some cases, the user may want to explicity release
    /// the event to fire the associated lostPointerCapture events.
    ///
    /// \param id The pointer id to release.
    void releasePointerCapture(std::size_t id);

    /// \returns true iff the Element is enabled.
    bool isEnabled() const;

    /// \brief Enable or disable this Element's interaction with the pointer (mouse) events.
    /// \param enabled The enabled state to set. True to enable, false to disable.
	/// When enabled this element will receive these events and will not when disabled.
	/// The element will draw regardless of its enabled state.
	/// Use setHidden to enable or disable drawing the element.
    void setEnabled(bool enabled);

    /// \returns true iff the Element is hidden.
    bool isHidden() const;

    /// \brief Hide or show this Element.
    /// \param hidden The visible state to set. True to hide, false to show.
	/// When an element is hidden, the pointer (mouse) events will still be passed to it and its children.
	/// Use setEnabled to enable or disable the mouse pointer events.
    void setHidden(bool hidden);

    /// \returns true iff the Element is locked.
    bool isLocked() const;

    /// \brief Lock or unlock a this Element.
    /// \param locked The locked state to set. True to lock, false to unlock.
    void setLocked(bool locked);

    /// \brief Determine if this element has focus.
    bool isFocused() const;

    /// \brief Set whether this Element can achieve focus.
    /// \param focusable True if the Element can achieve focus.
    void setFocusable(bool focusable);

    /// \returns true if this Element can achieve focus.
    bool isFocusable() const;

    // void setTabIndex(int index);
    // int getTabIndex() const;
	
	/// \brief sets if this element will get drawn or not but always draw its children
	/// \param drawChildrenOnly if true will not draw this element but it will draw its children
	void setDrawChildrenOnly(bool drawChildrenOnly);
	
	/// \brief gets if this element will get drawn or not, but always draw its children
	/// \returns true this element will not get drawn but its children will.
	bool isDrawingChildrenOnly() const;
	
	///\brief sets if to draw children by translating  or applying a viewport.
	///\param bViewport when set to true it will draw children clipped by parent.
	void setDrawAsViewport(bool bViewport);
	///\brief get if is drawing children by translating  or applying a viewport.
	bool isDrawingAsViewport() const;
	
	
	///EVENTS
	
	///\brief Move event
	/// Event dispatched when the element has changed it's position.
	ofEvent<MoveEventArgs> move;
	
	///\brief Resize event
	/// Event dispatched when the element has changed it's size (width or height).
	ofEvent<ResizeEventArgs> resize;

	///\brief Set Attribute
	/// Event dispatched when an attribute has been set for this Element instance.
	ofEvent<AttributeEventArgs> attributeSet;
	
	///\brief Cleared Attribute
	/// Event dispatched when an attribute has been removed from this Element instance.
	ofEvent<AttributeEventArgs> attributeCleared;

	///\brief Enable event
	/// Event dispatched when this Element instance has been enabled or disabled
	ofEvent<EnablerEventArgs> enabled;
	
	///\brief Locked event
	/// Event dispatched when this Element instance has been locked or unlocked
	ofEvent<EnablerEventArgs> locked;
	
	///\brief Locked event
	/// Event dispatched when this Element instance has been hideen or unhidden.
	ofEvent<EnablerEventArgs> hidden;
	
	
	///\brief onSetup
	/// Called internally once the Element has been setup.
	/// override it on a derived class if you want something specific to happen during setup.
	/// The Element automatically listens to setup. No need to call it manually.
	virtual void onSetup()
	{
		
	}
	///\brief onUpdate
	/// Called internally once the Element has been updated within the update loop.
	/// override it on a derived class if you want something specific to happen during setup.
	/// The Element automatically listens to update. No need to call it manually.
	virtual void onUpdate()
	{
		
	}
	///\brief onDraw
	/// Called internally once the Element has been drawn on each new frame.
	/// override it on a derived class if you want customize how the element gets drawn
	/// The Element automatically listens to draw. No need to call it manually.
	virtual void onDraw()
	{
		
	}
	///\brief onExit
	/// Called internally when the application ends
	/// override it on a derived class if you want customize how the element manages its resources.
	/// The Element automatically listens to ofExit. No need to call it manually.
	virtual void onExit()
	{
		
	}
	
	
protected:
    /// \brief Setup method called by parent Element.
    /// \param e The event data.
    void _setup(ofEventArgs& e);

    /// \brief Update method called by parent Element.
    /// \param e The event data.
    void _update(ofEventArgs& e);

    /// \brief Draw method called by parent Element.
    /// \param e The event data.
	void _draw(ofEventArgs& e);

    /// \brief Exit method called by parent Element.
    /// \param e The event data.
    void _exit(ofEventArgs& e);

    /// \brief A recursive hit test to find a target element.
    /// \param parentPosition The parent coordinates to test.
    /// \returns A pointer to the target Element or a nullptr if none found.
    /// \todo Provide a seed position to speed up search?
    Element* recursiveHitTest(const Position& parentPosition);

    /// \brief Find a child by a raw Element pointer.
    /// \param The pointer to the child.
    /// \returns An iterator pointing to the matching Element or the end.
    std::vector<std::unique_ptr<Element>>::iterator findChild(Element* element);

    /// \brief Determine if a given pointer id is captured.
    /// \param pointerId The pointer id to test.
    /// \returns true if the given pointer id is captured.
    bool isPointerCaptured(std::size_t pointerId) const;

    /// \brief Find the given CapturePointer info by id.
    /// \param pointerId The pointer id to find.
    /// \returns An const iterator to the CapturedPointer info if found.
    std::vector<CapturedPointer>::iterator findCapturedPointerById(std::size_t pointerId);

    /// \brief Find the given CapturePointer info by id.
    /// \param pointerId The pointer id to find.
    /// \returns An const iterator to the CapturedPointer info if found.
    std::vector<CapturedPointer>::const_iterator findCapturedPointerById(std::size_t pointerId) const;

    /// \brief Get a reference to the captured pointer vector.
    /// \returns a reference to all pointers captured by this Element.
    std::vector<CapturedPointer>& capturedPointers();

    /// \brief Get a reference to the captured pointer vector.
    /// \returns a reference to all pointers captured by this Element.
    const std::vector<CapturedPointer>& capturedPointers() const;

    /// \brief Set if the pointer is implicitly captured on pointer down.
    ///
    /// This does not enable the pointer listener, only if the pointer should
    /// be automatically captured when a listener is enabled.
    ///
    /// \param implicitPointerCapture True if the pointer should be captured.
    void setImplicitPointerCapture(bool implicitPointerCapture);

    /// \brief Determine if pointer is automatically captured on pointer down.
    /// \returns true iff implicit pointer capture is enabled.
    bool getImplicitPointerCapture() const;

	/// \brief apply the local transform related to this Element.
	/// This function gets called inside _draw before drawing.
	/// override if you want to apply a different transform.
	/// if you do so you have to override other
	// TODO: define the other stuff to override
	virtual void _applyTransform();
	
	///\brief restore the transformation applied by this node.
	/// this function gets called after drawing the current Element and its children
	/// override if you have overriden _applytransform
	virtual void _restoreTransform();
	
	
private:
    /// \brief Not construction-copyable.
    Element(const Element& other) = delete;

    /// \brief Non copyable.
    Element& operator = (const Element&) = delete;

    /// \brief A callback for child Elements to notify their parent of movement.
    void _onChildMoved(MoveEventArgs&);

    /// \brief A callback for child Elements to notify their parent size changes.
    void _onChildResized(ResizeEventArgs&);


    /// \brief The basic shape of this element.
    Shape _shape;

    /// \brief The union of all child bounding boxes.
    mutable Shape _childShape;


    /// \brief The enabled state of this Element.
    bool _enabled = true;

    /// \brief The visibility of this Element.
    bool _hidden = false;

    /// \brief The locked state of this Element.
    bool _locked = false;

    /// \brief The focused state of this Element.
    bool _focused = false;

    /// \brief True if this Element can be focused.
    bool _focusable = false;

	/// \brief True draw will draw children behind a viewport, clipping all by this.
    bool _drawAsViewport = false;
	
	/// \brief If true this element will not get drawn but its children will.
	bool _drawChildrenOnly = false;
	
    /// \brief Specifies the tabbing order in the current Element.
    // int _tabIndex = 0;

    /// \brief A collection of named attributes.
    /// \todo This may not be permanent.
    std::unordered_map<std::string, Any> _attributes;

    /// \brief Automatically capture the pointer on pointer down.
    bool _implicitPointerCapture = false;
	
    /// \brief A list of the pointer ids currently captured by this Element.
    /// Captured pointers are pushed back, so the pointer at the front was the
    /// first pointer captured, and thus the primary pointer.
    std::vector<CapturedPointer> _capturedPointers;
	
    /// \brief The Layout associated with this
    std::unique_ptr<Layout> _layout = nullptr;

	/// \brief A vector to Elements.
    std::vector<std::unique_ptr<Element>> _children;

	
	virtual void invalidateChild() const override;

	
	
    /// \brief The Layout class has access to all private variables.
    friend class Layout;

    /// \brief The Document class has access to all private variables.
    friend class Document;
	
	
};


template <typename LayoutType, typename... Args>
LayoutType* Element::createLayout(Args&&... args)
{
    return setLayout(std::make_unique<LayoutType>(std::forward<Args>(args)...));
}


template <typename LayoutType>
LayoutType* Element::setLayout(std::unique_ptr<LayoutType> layout)
{
    if (layout)
    {
        // Get a raw pointer to the node for later.
        LayoutType* pLayout = layout.get();

        // Assign the parent to the node via the raw pointer.
        pLayout->_parent = this;

        // Take ownership of the layout.
        _layout = std::move(layout);

        // Invalidate all cached child shape.
        invalidateChild();

        return pLayout;
    }

    return nullptr;
}


template <typename AnyType>
AnyType Element::getAttribute(const std::string& key, bool inherit) const
{
    auto iter = _attributes.find(key);

    if (iter != _attributes.end() && iter->second.is<AnyType>())
    {
        return iter->second.as<AnyType>();
    }
    else if (inherit && hasParent())
    {
        return parent()->getAttribute<AnyType>(key);
    }

    throw DOMException(DOMException::INVALID_ATTRIBUTE_KEY);
}


} } // namespace ofx::DOM
