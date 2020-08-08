//
//  ConstrainedGrabHandle.h
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/5/20.
//
#pragma once

#include "ofx/MUI/Widget.h"
#include "ofx/MUI/Types.h"
#include "OrientedElement.h"

namespace ofx {
namespace MUI {

class ConstrainedGrabHandle: public Widget, public DOM::OrientedElement{
public:
	
	ConstrainedGrabHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect);
	virtual ~ConstrainedGrabHandle();
	
	void setConstrainedToParent(bool bConstrained);
	bool isConstrainedToParent();

	
	void constrainTo(DOM::Element* constraint);
	DOM::Element* getConstraint();
	void removeConstraint();
	
	
protected:

	virtual void _onDragging(const DOM::CapturedPointer& pointer)override;
	
	bool bConstrainToParent = true;
	

	DOM::Element * _constraint = nullptr;
	
	
};

} } // ofx::MUI
