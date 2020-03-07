//
//  ZoomHandle.h
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//
#pragma once


#include "ResizableHandle.h"
//#include "ConstrainedGrabHandle.h"
#include "BaseScrollHandle.h"
#include "ofRange.h"
#include "Constants.h"
namespace ofx {
namespace MUI {


class ZoomHandle: public ResizableHandle, public BaseScrollHandle<ofRange>{
public:

	ZoomHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect);
	virtual ~ZoomHandle(){}



//	const ofRange& getZoom()const;
	virtual bool setValue(const ofRange& val ) override;
//	void setZoomMin(float mn);
//	void setZoomMax(float mx);

protected:

//	float _minPosToValue();
//	float _maxPosToValue();
//	bool _valueToMinPos(float val);
//	bool _valueToMaxPos(float val);

	
	virtual void _onMainHandleMoved(DOM::MoveEventArgs& m) override;
	virtual void _onMainHandleResize(DOM::ResizeEventArgs& m)override;
	
	void _mainHandleChanged();
	
};



} } // ofx::MUI
