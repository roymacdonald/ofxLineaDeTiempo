//
//  ClippedView.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#pragma once
	

#include "Utils.h"
#include "ofMath.h"
#include "ofx/MUI/AutoReziseContainer.h"

namespace ofx {
namespace MUI {


template<typename ContainerType>

class ClippedView_
: public DOM::Element
{
public:
	static_assert(std::is_base_of<DOM::Element, ContainerType>(), "ContainerType must be an DOM::Element or derived from DOM::Element.");
	
	
	template <typename... Args>
	ClippedView_(const std::string& id, const ofRectangle& rect, Args&&... args)
	: DOM::Element(id, rect.x, rect.y, rect.width, rect.height)
	{

		setDrawAsViewport(true);
		setFocusable(false);
		container = addChild<ContainerType>(id+"_Container", ofRectangle(0,0,rect.width, rect.height), std::forward<Args>(args)...);
		
	}
	
	
	virtual ~ClippedView_() = default;
	
	void setOffset(const glm::vec2& offset);
	
	glm::vec2 getOffset()const;
	
	ContainerType* container = nullptr;
	
protected:	
	
	
};


//---------------------------------------------------------------------------------------


typedef ClippedView_<AutoReziseContainer> ClippedView;







} } // ofx::MUI
