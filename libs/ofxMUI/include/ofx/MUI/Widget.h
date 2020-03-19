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

#define OFX_MUI_WIDGET_DEBUG

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
    
    /// \brief Get the Styles for this Widget.
    /// \returns the Widget's styles.
    std::shared_ptr<Styles> getStyles() const;

    /// \brief Set the Styles for this Widget.
    ///
    /// If the style is set to nullptr, it will automatically adopt the root
    /// document style.
    ///
    /// \param style The style to set.
    void setStyles(std::shared_ptr<Styles> styles);
	
	
	/// \brief sets the way this widget's shape is going to be drawn
	/// \param drawMode  the draw mode to set (ELLIPSE, RECTANGLE or ROUNDED_RECTANGLE). RECTANGLE by default
	void setShapeDrawMode(ShapeDrawMode drawMode);
	
	/// \brief Gets the way this widget's shape is going to be drawn
    /// \returns the Widget's draw mode.
	ShapeDrawMode getShapeDrawMode() const;
	
	
	#ifdef OFX_MUI_WIDGET_DEBUG
		void setDebugString(const std::string& str){
			debugString = str;
		}
	#endif
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

	
	/// \brief the the way the shape is going to be drawn (ELLIPSE, RECTANGLE or ROUNDED_RECTANGLE)
	ShapeDrawMode _drawMode = ShapeDrawMode::RECTANGLE;
	
	
	/// \ brief Helper function that will draw according to the widget's current shape draw mode;
	void drawShape(float x, float y, float width, float height, float cornerRadius = 5) const;
	

	///\ brief Highlihgt the widget when the pointer is over.
	bool _highlightOnOver = true;

	
private:
    /// \brief The shared Styles.
    mutable std::shared_ptr<Styles> _styles = nullptr;

	#ifdef OFX_MUI_WIDGET_DEBUG
		std::string debugString;
//		mutable bool bDrawDebugString = false;
	#endif

	
};


} } // ofx::MUI
