//
//  EdgeHandle.h
//  edgeHandle
//
//  Created by Roy Macdonald on 2/21/20.
//

#pragma once
#include "ConstrainedGrabHandle.h"
#include "ofRectangleHelper.h"
#include "Constants.h"

namespace ofx {
namespace MUI {

enum EdgeHandleAlignment{
	ALIGN_INSIDE = 0,
	ALIGN_CENTER,
	ALIGN_OUTSIDE
};

class EdgeHandle: public ConstrainedGrabHandle{
public:
	
	EdgeHandle(const std::string& id, DOM::RectEdge edge, DOM::Element* target, EdgeHandleAlignment edgeAlignment = ALIGN_CENTER, bool bAutoHide = true);
	virtual ~EdgeHandle(){}
	
//	static ofRectangle getEdgeRect(DOM::Element* element, DOM::RectEdge edge, EdgeHandleAlignment alignment);
	
	
	///\ brief the ammount of time, in milliseconds that will pass once the pointer is over and that the Handle starts showing.
	static const uint64_t onOverDrawDelay;
	
	bool isFollowingTarget();
	
	
	virtual void updateLayout() override;
	
	void setHandleSize(float handleSize);
	float  getHandleSize() const;
	
	void setAutoHide(bool autoHide);
	void enableAutoHide();
	void disableAutoHide();
	bool isAutoHidding();
	
	void setAlignment( EdgeHandleAlignment edgeAlignment);
	EdgeHandleAlignment getAlignment() const;
	
	
	void setTargetMinSize(float minSize);
	float getTargetMinSize() const;
	bool hasTargetMinSize() const;
	void removeTargetMinSize();
	
	
protected:
	virtual void onUpdate() override;
	
	DOM::RectEdge _edge;
	
	ofEventListener _targetListener;
	
	
	void _targetShapeChanged(DOM::ShapeChangeEventArgs&);
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
	virtual  void _onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e)override;
	
	DOM::Element* _target = nullptr;
	
	
	EdgeHandleAlignment _edgeAlignment = ALIGN_CENTER;

	float _handleSize = EDGE_HANDLE_SIZE;
	
	
	ofAlignHorz hTargetAnchor;
	ofAlignHorz hThisAnchor;
	
	ofAlignVert vTargetAnchor;
	ofAlignVert vThisAnchor;
	

	void setAnchors();

	
private:
	uint64_t _pointerCaptureTime = 0;
	
	bool _wasPointerOver = false;
	
	bool _followingTarget = false;
	
	bool _bAutoHide = true;

	bool _targetMinSizeEnabled = false;
	float _targetMinSize =0;

	DOM::Element* _targetConstraint = nullptr;
	
};

} } // ofx::MUI
