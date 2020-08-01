//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofParameter.h"
#include "ofGraphics.h"
#include "ofx/DOM/Element.h"
#include "ofx/DOM/Events.h"
#include "ofx/MUI/Types.h"


namespace ofx {
namespace MUI {


class Styles;


/// \brief A Widget is the base class for all MUI interactive elements.
class Widget: public DOM::Element
{
public:
	Widget(const ofRectangle& rect);
	Widget(const std::string& id, const ofRectangle& rect);
	Widget(float x, float y, float width, float height);
    Widget(const std::string& id, float x, float y, float width, float height);

    /// \brief Destroy this Widget.
    virtual ~Widget();

    virtual void onDraw() const override;

    /// \returns true if the pointer is over this Widget.
    bool isPointerOver() const;

    /// \returns true if the pointer is down on this Widget.
    bool isPointerDown() const;

    /// \brief Enable or disable the Widget as a drop target.
    /// \param dropTarget True iff this Widget is a drop target.
    void setDropTarget(bool dropTarget);

    /// \brief Determine if this Widget is a drop target.
    /// \returns true iff this Widget is a drop target.
    bool isDropTarget() const;

    /// \brief Set draggability for this Widget.
    /// \param draggable True iff draggability is enabled.
    void setDraggable(bool draggable);

    /// \brief Determine if draggability is enabled for this Widget.
    /// \returns true iff the draggability is enabled.
    bool isDraggable() const;

    /// \brief Determine if this Widget is being dragged.
    /// \returns true if this Widget is being dragged.
    bool isDragging() const;

    /// \brief Set the elevation of the widget.
    /// \param elevation The elevation in pixels.
    void setElevation(float elevation);

    /// \returns the elevation in pixels.
    float getElevation() const;
    
	
	/// \brief sets the way this widget's shape is going to be drawn
	/// \param drawMode  the draw mode to set (ELLIPSE, RECTANGLE, ROUNDED_RECTANGLE, TOP_ROUNDED_RECTANGLE, BOTTOM_ROUNDED_RECTANGLE, LEFT_ROUNDED_RECTANGLE or RIGHT_ROUNDED_RECTANGLE). RECTANGLE by default
	void setShapeDrawMode(ShapeDrawMode drawMode);
	
	/// \brief Gets the way this widget's shape is going to be drawn
    /// \returns the Widget's draw mode.
	ShapeDrawMode getShapeDrawMode() const;
	
	
	
	///\brief This event gets triggered whenever the dragging state changes. 
	ofEvent<bool> isDraggingEvent;
	
	///\brief If enabled when a pointer is captured (clicked over) will move to the front of the stack, thus drawing on top of all of its siblings.
	///Othewise stay where it is.
	/// default is true.
	void setMoveToFrontOnCapture(bool moveToFront);

	
	///\brief returns werther or not it will move to the front when this widgets captures a pointer
	bool isMoveToFrontOnCapture();
	
	
	/// \brief Enable or disable highlighting while pointer is over.
    /// \param bHighlight True to enable, false otherwise
	void setHighlightOnOver(bool bHighlight);
	
	///\brief returns true if will highlight when the position pointer is over
	bool isHighlightingOnOver();
	
	virtual void printStructure(std::string prefix = "") override;
	
	
	///\brief set the style role for this widget.
	/// this will define which colors to use when rendering.
	///\param role The role to set
	void setStyleRole(Styles::Role role);
	
protected:
	///\brief Callback when dragging happens. override to change behavior
	virtual void _onDragging(const DOM::CapturedPointer& pointer);
	
    /// \brief Default callback for built-in events, including dragging.
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e);

    /// \brief Default callback for built-in events, including dragging.
    virtual void _onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e);

    /// \brief True iff the Widget is a target for dragged Widgets.
    bool _isDropTarget = false;

    /// \brief True iff the Widget is configured to be dragged.
    bool _isDraggable = false;

    /// \brief True iff the widget is currently being dragged.
//	ofParameter<bool> _isDragging = {"isDragging",false};
	bool _isDragging = false;

	void _setIsDragging(bool bDragging);
    /// \brief True iff the pointer is over the widget.
    bool _isPointerOver = false;

    /// \brief True if the element should move to the fron upon pointer capture.
    bool _moveToFrontOnCapture = true;

    /// \brief The elevation of the widget in pixels.
    float _elevation = 0;
    
    /// \brief A map of callbacks key-down events.
    std::map<uint64_t, std::function<void(DOM::KeyboardUIEventArgs& event)>> _keyboardListeners;

	
	/// \brief the the way the shape is going to be drawn (ELLIPSE, RECTANGLE, ROUNDED_RECTANGLE, TOP_ROUNDED_RECTANGLE, BOTTOM_ROUNDED_RECTANGLE, LEFT_ROUNDED_RECTANGLE or RIGHT_ROUNDED_RECTANGLE)
	ShapeDrawMode _drawMode = ShapeDrawMode::RECTANGLE;
	
	
	/// \ brief Helper function that will draw according to the widget's current shape draw mode;
	void drawShape(float x, float y, float width, float height, float cornerRadius = 5) const;
	

	///\ brief Highlihgt the widget when the pointer is over.
	bool _highlightOnOver = true;

	Styles::Role _widgetRole = Styles::ROLE_BACKGROUND;
	Styles::Role _borderStyleRole = Styles::ROLE_BORDER_BACKGROUND;
	
};


} } // ofx::MUI
