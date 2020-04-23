//
//  ZoomScrollbar.h
//  example
//
//  Created by Roy Macdonald on 4/20/20.
//

#pragma once

//#include "ofxMUI.h"
#include "DOM/Element.h"
#include "MUI/Handles/ConstrainedGrabHandle.h"
#include "ofRange.h"
#include "MUI/Handles/EdgeHandle.h"
#include "MUI/ClippedView.h"
#include "MUI/Handles/BaseScrollHandle.h"
#include "MUI/OrientedElement.h"

namespace ofx {
namespace MUI {


class ZoomScrollbar: public DOM::Element, public BaseScrollHandle<ofRange>, public DOM::OrientedElement
{
public:
	/// \brief Create a Scrollbar with the given parameters.
	/// \param id The Widget's id string.
	/// \param orientation The orientation of the .
	/// \param mode The DragMode of the Scrollbar.
	ZoomScrollbar(const std::string& id, DOM::Orientation orientation, ClippedView* clippedView);

	/// \brief Destroy the Scrollbar.
	virtual ~ZoomScrollbar(){}


	virtual bool setValue(const ofRange& val ) override;



	///\brief will move the scroll handle by amt
	///\param amt amount to scroll by. Normalized
	///\return true if it was able to move the scroll handle
	bool scroll(float amt);

	static float scrollSpeed;


//	virtual void updateLayout() override;

	virtual void onDraw() const override;

	float minPosToNormalizedValue();
	float maxPosToNormalizedValue();

	bool normalizedValueToMinPos(float val);
	bool normalizedValueToMaxPos(float val);


	void updateValueFromClippedView();

protected:

	ConstrainedGrabHandle* mainHandle = nullptr;
	EdgeHandle* inHandle = nullptr ;
	EdgeHandle* outHandle = nullptr;
	
//	std::unique_ptr<Widget> _inHandleConstraint = nullptr;
//	std::unique_ptr<Widget> _outHandleConstraint = nullptr;
//
//	void _setInHandleConstraint();
//	void _setOutHandleConstraint();
	
	void _onMainHandleShapeChanged(DOM::ShapeChangeEventArgs&);
//	void _onInHandleShapeChanged(DOM::ShapeChangeEventArgs&);
//	void _onOutHandleShapeChanged(DOM::ShapeChangeEventArgs&);
	
//	bool _updateInHandle();
//	bool _updateOutHandle();

	ofEventListener _mainHandleListener;
	
	void _onClippedViewShapeChanged(DOM::ShapeChangeEventArgs&);

	bool _onScrollEvent(ofMouseEventArgs & e);

	ClippedView* _clippedView = nullptr;

	void _updateShape();

	bool _updateValue();

private:
	
	ofEventListener _clippedViewShapeListener;
	ofEventListener _scrollListener;

	void _setIOHandle(EdgeHandle* handle);

};




//
//class ZoomScrollbar: public DOM::Element, public BaseScrollHandle<ofRange>, public DOM::OrientedElement
//{
//public:
//	/// \brief Create a Scrollbar with the given parameters.
//	/// \param id The Widget's id string.
//	/// \param orientation The orientation of the .
//	/// \param mode The DragMode of the Scrollbar.
//	ZoomScrollbar(const std::string& id, DOM::Orientation orientation, ClippedView* clippedView);
//
//	/// \brief Destroy the Scrollbar.
//	virtual ~ZoomScrollbar(){}
//
//
//	virtual bool setValue(const ofRange& val ) override;
//
//
//
//	///\brief will move the scroll handle by amt
//	///\param amt amount to scroll by. Normalized
//	///\return true if it was able to move the scroll handle
//	bool scroll(float amt);
//
//	static float scrollSpeed;
//
//
////	virtual void updateLayout() override;
//
//	virtual void onDraw() const override;
//
//	float minPosToNormalizedValue();
//	float maxPosToNormalizedValue();
//
//	bool normalizedValueToMinPos(float val);
//	bool normalizedValueToMaxPos(float val);
//
//
//	void updateValueFromClippedView();
//
//protected:
//
//
//	ConstrainedGrabHandle* _mainHandle = nullptr;
//	EdgeHandle* _inHandle = nullptr ;
//	EdgeHandle* _outHandle = nullptr;
//
//	DOM::Element * _inConstraint = nullptr;
//	DOM::Element * _outConstraint = nullptr;
//
//
//	virtual void _onMainHandleShapeChanged(DOM::ShapeChangeEventArgs&);
//
//	virtual void _onClippedViewShapeChanged(DOM::ShapeChangeEventArgs&);
//
//
//
//	bool _onScrollEvent(ofMouseEventArgs & e);
//
//	ClippedView* _clippedView = nullptr;
//
//	void _updateShape();
//
//	bool _updateValue();
//
//private:
//	ofEventListener _mainHandleListener;
//	ofEventListener _clippedViewShapeListener;
//	ofEventListener _scrollListener;
//
//
//};

} } // ofx::MUI

