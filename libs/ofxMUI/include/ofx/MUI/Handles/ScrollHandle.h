//
//  ScrollHandle.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/9/20.
//

#pragma once
#include "ConstrainedGrabHandle.h"

#include "Constants.h"
#include "BaseScrollHandle.h"

namespace ofx {
namespace MUI {


class ScrollHandle
: public BaseScrollHandle<float>
, public ConstrainedGrabHandle
{
public:
	ScrollHandle(const std::string& id, DOM::Orientation orientation, const ofRectangle& rect);
	virtual ~ScrollHandle(){}
	virtual void updateLayout() override;

	virtual bool setValue(const float& val ) override;
	
protected:
	virtual void _onDragging(const DOM::CapturedPointer& pointer)override;
	bool _updateValueFromScroll();// override;
	bool _updateScrollFromValue();//; override;

};


} } // ofx::MUI
