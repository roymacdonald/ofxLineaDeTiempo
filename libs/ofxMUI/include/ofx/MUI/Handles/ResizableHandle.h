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
#include "BaseClasses.h"

namespace ofx {
namespace MUI {


//class ResizableHandle: public BaseScrollHandle<ofRange>, public Widget{
//public BaseScrollHandle<ofRange>,
class ResizableHandle: public DOM::OrientedElement, public BaseHasLayout, public Widget{
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
	
	virtual void _onMainHandleMoved(DOM::MoveEventArgs& m);
	virtual void _onMainHandleResize(DOM::ResizeEventArgs& m);
	void _onInHandleMoved(DOM::MoveEventArgs& m);
	void _onOutHandleMoved(DOM::MoveEventArgs& m);

	bool _updateInHandle();
	bool _updateOutHandle();

	ofEventListeners handlesListeners;
	
	
};



} } // ofx::MUI
