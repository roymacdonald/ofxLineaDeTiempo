//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <unordered_set>
#include "ofx/PointerEvents.h"
#include "ofx/DOM/CapturedPointer.h"
#include "ofx/DOM/Events.h"
#include "ofx/DOM/EventTarget.h"
#include "ofx/DOM/Exceptions.h"
#include "ofx/DOM/Layout.h"
#include "ofx/DOM/Types.h"
#include "ofx/DOM/Node.h"

#include "ofx/MUI/Styles.h"



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
class Element: public EventTarget<Element>
#ifdef ENABLE_NODE_BASE
, public NodeBase<Element>
#endif
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

    /// \brief Take ownership of the passed std::unique_ptr<Element>.
    ///
    /// This this is "sink" meaning that any child passed to this will be
    /// owned by this Node.
    ///
    /// \param element the rvalue reference to the child node.
    /// \returns A pointer to the added Element. The parent Element retains
    /// ownership of the pointer via a std::unique_ptr.
    /// \tparam ElementType The Element Type.
    template <typename ElementType>
    ElementType* addChild(std::unique_ptr<ElementType> element);

    /// \brief Create a child using a templated Element type.
    ///
    /// To create a child Element you can use this method like:
    ///
    /// ElementType* element = parentElement->addChild<ElementType>(arguments ...);
    ///
    /// \param args The variable constructor arguments for the ElementType.
    /// \returns A pointer to the added Element. The parent Element retains
    /// ownership of the pointer via a std::unique_ptr.
    /// \tparam ElementType The subclass of Element that will be added.
    /// \tparam Args The variable constructor arguments for the ElementType.
    template <typename ElementType, typename... Args>
    ElementType* addChild(Args&&... args);

    /// \brief Release ownership of a child Element.
    /// \param element The Element to release.
    /// \returns a std::unique_ptr<Element> to the child.
    std::unique_ptr<Element> removeChild(Element* element);

    /// \brief Move this Element in front of all of its siblings.
    void moveToFront();

    /// \brief Move this Element in front of its next sibling.
    void moveForward();

    /// \brief Move this Element in back of all of its siblings.
    void moveToBack();

    /// \brief Move this Element in back of its next sibling.
    void moveBackward();

    /// \brief Move the given Element to the the given index.
    ///
    /// If the index value is greater than the number of children, the element
    /// will be moved into the last position.
    ///
    /// \param element The child element to move.
    /// \param index The child index to move to.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child element exists.
    void moveChildToIndex(Element* element, std::size_t index);

    /// \brief Move the given Element in front of all of its siblings.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child element exists.
    void moveChildToFront(Element* element);

    /// \brief Move the given Element in front of its next sibling.
    /// \param element The child element to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child element exists.
    void moveChildForward(Element* element);

    /// \brief Move the given Element in back of all of its siblings.
    /// \param element The child element to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child element exists.
    void moveChildToBack(Element* element);

    /// \brief Move the given Element in back of its next sibling.
    /// \param element The child element to move.
    /// \throws DOMException(DOMException::INVALID_STATE_ERROR) if no matching
    /// child element exists.
    void moveChildBackward(Element* element);

    /// \brief Determine if the given Element is a child of this Element.
    /// \param element A pointer the the Element to test.
    /// \returns true iff the given element is a child of this Element.
    bool isChild(Element* element) const;

    /// \brief Determine if the given Element is a sibling of this Element.
    /// \param element A pointer the the Element to test.
    /// \returns true iff the given element is a sibling of this Element.
    bool isSibling(Element* element) const;

    /// \returns the number of siblings.
    std::size_t numSiblings() const;

    /// \returns a list of pointers to sibling elements.
    std::vector<Element*> siblings();

    /// \brief Get a list of siblings of a given Element or Element subclass.
    ///
    /// If the there are no siblings of the given type,
    ///
    /// \returns a list of pointers to sibling elements of a given type.
    template <typename ElementType>
    std::vector<ElementType*> siblings();

    /// \brief Determine if the given Element is the parent of this Element.
    /// \param element A pointer the the Element to test.
    /// \returns true iff the given element is the parent of this Element.
    bool isParent(Element* element) const;

    /// \returns the number of children.
    std::size_t numChildren() const;

    /// \brief Get a list of pointers to the child elements.
    ///
    /// The parent Element retains ownership.
    ///
    /// \returns a list of pointers to child elements.
    std::vector<Element*> children();

    /// \brief Get a list of pointers to the child elements.
    ///
    /// The parent Element retains ownership.
    ///
    /// \returns a list of pointers to child elements.
    template <typename ElementType>
    std::vector<ElementType*> children();

    /// \brief Determine if this Element has a parent Element.
    /// \returns true if this Element has a parent Element.
    bool hasParent() const;

    /// \brief Find this Element's first child by its id.
    /// \param id The id of the child Element to find.
    /// \returns a pointer to the first child or nullptr if no such child exists.
    Element* findFirstChildById(const std::string& id);

    /// \brief Find all of this Element's matching the given id.
    /// \param id The id of the child Elements to find.
    /// \returns a vector of pointers to child elements or an empty vector if none exist.
    std::vector<Element*> findChildrenById(const std::string& id);
#ifdef ENABLE_NODE_BASE
    virtual Element* parent() override;
    virtual const Element* parent() const  override;
#else
	/// \brief Get a pointer to the parent.
    /// \returns a pointer to the parent or a nullptr.
	Element* parent();

    /// \brief Get a pointer to the parent.
    /// \returns a pointer to the parent or a nullptr.
	const Element* parent() const;
#endif
	void setParent(Element* parent);
	
	
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

	///\brief override this function for updating the layout of this element's children
	virtual void updateLayout(){}

	///\brief Call updateLayout recursively throught the whole inheritance tree.
	void recursiveUpdateLayout();
	
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

	
	/// \brief Convert a X-axis value from local to screen coordinates.
	/// \param localX The local X coordinates to convert.
	/// \returns the X coordinate value converted from local to screen coordinates.
    float localToScreenX(const float& localX) const;

	
	/// \brief Convert a y-axis value from local to screen coordinates.
	/// \param localY The local y coordinates to convert.
	/// \returns the y coordinate value converted from local to screen coordinates.
    float localToScreenY(const float& localY) const;

	
    /// \brief Convert a X-axis value from screen to local coordinates.
	/// \param screenX The screen X coordinates to convert.
	/// \returns the X coordinate value converted from screen to local coordinates.
    float screenToLocalX(const float& screenX) const;

	/// \brief Convert a y-axis value from screen to local coordinates.
	/// \param screenY The screen y coordinates to convert.
	/// \returns the y coordinate value converted from screen to local coordinates.
    float screenToLocalY(const float& screenY) const;
	
    /// \brief Convert a X-axis value from parent to screen coordinates.
    /// \param parentX The parent X coordinates to convert.
    /// \returns the X-axis coordinate converted from parent to screen .
    float parentToScreenX(const float& parentX) const;

    /// \brief Convert a Y-axis value from parent to screen coordinates.
    /// \param parentY The parent Y coordinates to convert.
    /// \returns the Y-axis coordinate converted from parent to screen .
    float parentToScreenY(const float& parentY) const;


    /// \brief Convert a X-axis value from screen to parent coordinates.
    /// \param screenX The screen X coordinates to convert.
    /// \returns the X-axis coordinate converted from screen to parent .
    float screenToParentX(const float& screenX) const;

	/// \brief Convert a Y-axis value from screen to parent coordinates.
    /// \param screenY The screen Y coordinates to convert.
    /// \returns the Y-axis coordinate converted from screen to parent .
    float screenToParentY(const float& screenY) const;
	
	
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

    /// \brief Set the width of the Element.
    void setWidth(float width);

    /// \brief Set the height of the Element.
    void setHeight(float height);

	
	
	
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

    /// \brief Get the id of this Element.
    ///
    /// The id is optional and an empty std::string by default.
    ///
    /// \returns the id of the Element.
    std::string getId() const;

    /// \brief Set the id of the Element.
    /// \param id The new id of the Element.
    void setId(const std::string& id);

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
	
    /// \brief Get the Styles for this Element.
    /// \returns the Elements's styles.
    std::shared_ptr<MUI::Styles> getStyles() const;

    /// \brief Set the Styles for this Element.
    ///
    /// If the style is set to nullptr, it will automatically adopt the root
    /// document style.
    ///
    /// \param style The style to set.
    void setStyles(std::shared_ptr<MUI::Styles> styles);
	

	
	virtual void printStructure(std::string prefix = "");
	
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

    /// \brief Called internally to invalidate the child geometry tree.
    virtual void invalidateChildShape() const;

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
	
	
	virtual void _onShapeChange(const ShapeChangeEventArgs& )
	{
		
	}
	
	virtual void _onChildShapeChanged(ShapeChangeEventArgs&)
	{
		
	}
	

private:
    /// \brief Not construction-copyable.
    Element(const Element& other) = delete;

    /// \brief Non copyable.
    Element& operator = (const Element&) = delete;

    
    /// \brief A callback for child Elements to notify their parent size changes.
    void _childShapeChange(ShapeChangeEventArgs&);

    /// \brief The id for this element.
    std::string _id;

    /// \brief The basic shape of this element.
    Shape _shape;
	
    /// \brief The union of all child bounding boxes.
    mutable Shape _childShape;

    /// \brief True if the child shape is invalid.
    ///
    /// This variable usually set by callbacks from the child elements.
    mutable bool _childShapeInvalid = true;

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

    /// \brief An optional pointer to a parent Node.
    Element* _parent = nullptr;

    /// \brief A vector to Elements.
    std::vector<std::unique_ptr<Element>> _children;

    /// \brief The Layout class has access to all private variables.
    friend class Layout;

    /// \brief The Document class has access to all private variables.
    friend class Document;
	
    /// \brief The shared Styles.
    mutable std::shared_ptr<MUI::Styles> _styles = nullptr;


	

};


template <typename ElementType, typename... Args>
ElementType* Element::addChild(Args&&... args)
{
    return addChild(std::make_unique<ElementType>(std::forward<Args>(args)...));
}


template <typename ElementType>
ElementType* Element::addChild(std::unique_ptr<ElementType> element)
{
    static_assert(std::is_base_of<Element, ElementType>(), "ElementType must be an Element or derived from Element.");

    if (element)
    {
        // Get a raw pointer to the node for later.
        ElementType* pNode = element.get();

        // Assign the parent to the node via the raw pointer.
        pNode->setParent(this);
		
        // Take ownership of the node.
        _children.push_back(std::move(element));

        // Invalidate all cached child shape.
        invalidateChildShape();

        // Alert the node that its parent was set.
        ElementEventArgs addedEvent(this);
        ofNotifyEvent(pNode->addedTo, addedEvent, this);

        ElementEventArgs childAddedEvent(pNode);
        ofNotifyEvent(childAdded, childAddedEvent, this);

        // Attach child listeners.
		ofAddListener(pNode->shapeChanged, this, &Element::_childShapeChange);


        /// Alert the node's siblings that they have a new sibling.
        for (auto& child : _children)
        {
            // Don't alert itself.
            if (child.get() != pNode)
            {
                ElementEventArgs event(pNode);
                ofNotifyEvent(child->siblingAdded, event, this);
            }
        }

        return pNode;
    }

    return nullptr;
}


template <typename ElementType>
std::vector<ElementType*> Element::siblings()
{
    static_assert(std::is_base_of<Element, ElementType>(), "ElementType must be an Element or derived from Element.");

    std::vector<ElementType*> results;

    if (_parent)
    {
        for (auto& child : _parent->_children)
        {
            ElementType* pChild = dynamic_cast<ElementType*>(child.get());

            if (pChild != this)
            {
                results.push_back(pChild);
            }
        }
    }
    
    return results;
}


template <typename ElementType>
std::vector<ElementType*> Element::children()
{
    static_assert(std::is_base_of<Element, ElementType>(), "ElementType must be an Element or derived from Element.");

    std::vector<ElementType*> results;

    for (auto& child : _children)
    {
        ElementType* pChild = dynamic_cast<ElementType*>(child.get());

        if (pChild)
        {
            results.push_back(pChild);
        }
    }

    return results;
}


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
        invalidateChildShape();

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
