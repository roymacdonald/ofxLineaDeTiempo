//
//  EdgeHandle.h
//  edgeHandle
//
//  Created by Roy Macdonald on 2/21/20.
//

#pragma once
#include "ConstrainedGrabHandle.h"
#include "ofRectangleHelper.h"

namespace ofx {
namespace MUI {

//enum RectEdge{
//	RECT_TOP = 0,
//	RECT_RIGHT,
//	RECT_BOTTOM,
//	RECT_LEFT
//};

class EdgeHandle: public ConstrainedGrabHandle{
public:
	
	EdgeHandle(const std::string& id, DOM::RectEdge edge, DOM::Element* target);
	virtual ~EdgeHandle(){}
	
	static ofRectangle getEdgeRect(DOM::Element* element, DOM::RectEdge edge);
	
	
	///\ brief the ammount of time, in milliseconds that will pass once the pointer is over and that the Handle starts showing.
	static const uint64_t onOverDrawDelay;
	
	
	
protected:
	virtual void onUpdate() override;
	
	DOM::RectEdge _edge;
	
	ofEventListener _targetListener;
	
	
	void _targetShapeChanged(DOM::ShapeChangeEventArgs&);
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
	virtual  void _onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)override;
	
	DOM::Element* _target = nullptr;
	
	
	
private:
	uint64_t _pointerCaptureTime = 0;
	
	bool _wasPointerOver = false;
	
};

} } // ofx::MUI
