//
//  ResizableHandle.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/10/20.
//

#pragma once
#include "ConstrainedGrabHandle.h"
#include "BaseScrollHandle.h"
#include "ofRange.h"


namespace ofx {
namespace MUI {


class ResizableHandle
: public DOM::OrientedElement
, public Widget
{
public:
	ResizableHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect);
	virtual ~ResizableHandle(){}
	
	virtual void updateLayout() override;
	
	float minPosToNormalizedValue();
	float maxPosToNormalizedValue();
	
	bool normalizedValueToMinPos(float val);
	bool normalizedValueToMaxPos(float val);
	
	
protected:
	
	
	ConstrainedGrabHandle* mainHandle = nullptr;
	ConstrainedGrabHandle* inHandle = nullptr ;
	ConstrainedGrabHandle* outHandle = nullptr;
	
	std::unique_ptr<Widget> _inHandleConstraint = nullptr;
	std::unique_ptr<Widget> _outHandleConstraint = nullptr;
		
	void _setInHandleConstraint();
	void _setOutHandleConstraint();
	
	virtual void _onMainHandleShapeChanged(DOM::ShapeChangeEventArgs&);
	void _onInHandleShapeChanged(DOM::ShapeChangeEventArgs&);
	void _onOutHandleShapeChanged(DOM::ShapeChangeEventArgs&);
	
	bool _updateInHandle();
	bool _updateOutHandle();

	ofEventListeners handlesListeners;
	
	
};



} } // ofx::MUI
