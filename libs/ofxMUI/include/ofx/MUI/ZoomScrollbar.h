//
//  ZoomScrollbar.h
//  example
//
//  Created by Roy Macdonald on 4/20/20.
//

#pragma once


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
	/// \param clippedView The clippedView that this scrollbar will control
	ZoomScrollbar(const std::string& id, DOM::Orientation orientation, ClippedView* clippedView);

	/// \brief Destroy the Scrollbar.
	virtual ~ZoomScrollbar(){}


	virtual bool setValue(const ofRange& val ) override;



	///\brief will move the scroll handle by amt
	///\param amt amount to scroll by. Normalized
	///\return true if it was able to move the scroll handle
	bool scroll(float amt);

	static float scrollSpeed;


	virtual void onDraw() const override;

//	float minPosToNormalizedValue();
//	float maxPosToNormalizedValue();
	
//	bool normalizedValueToMinPos(float val);
//	bool normalizedValueToMaxPos(float val);

	
	ofRange shapeToNormalizedValue(const DOM::Shape& shape);
	DOM::Shape normalizedValueToShape(const ofRange& val);
	
	void updateValueFromClippedView();

protected:

	ConstrainedGrabHandle* mainHandle = nullptr;
	EdgeHandle* inHandle = nullptr ;
	EdgeHandle* outHandle = nullptr;
	
	
	void _onMainHandleShapeChanged(DOM::ShapeChangeEventArgs&);

	ofEventListener _mainHandleListener;
	
	void _onClippedViewShapeChanged(DOM::ShapeChangeEventArgs&);

	void _onContainerShapeChanged(DOM::ShapeChangeEventArgs&);
	
	bool _onScrollEvent(ofMouseEventArgs & e);

	ClippedView* _clippedView = nullptr;

	void _updateShape();

	bool _updateMainHandleShape();

	void _zoomUpdate(ofRange r, bool forceUpdate = false);
	
	bool _setValue(const ofRange& val , bool bUpdateContainer = true);
	
private:
	
	ofEventListener _clippedViewShapeListener;
	ofEventListener _containerShapeListener;
	ofEventListener _scrollListener;

	void _setIOHandle(EdgeHandle* handle);

	
	///\ this is used to avoid recursive callbacks
	bool _bIgnoreMainHandleShapeChange = false;
	
	bool _bIgnoreContainerShapeChange = false;
	
};

} } // ofx::MUI

