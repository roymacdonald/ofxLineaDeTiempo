//
//  ClippedView.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#pragma once
	

#include "ofx/MUI/Widget.h"
#include "ofx/DOM/Layout.h"
#include "Utils.h"

namespace ofx {
namespace MUI {


template<typename ContainerType>

class ClippedView_
: public DOM::Element
{
public:
	static_assert(std::is_base_of<DOM::Element, ContainerType>(), "ContainerType must be an DOM::Element or derived from DOM::Element.");
	ClippedView_(const std::string& id, const ofRectangle& rect);
	    
	
	virtual ~ClippedView_(){}
	
	void setOffset(const glm::vec2& offset)
	{
		if(container){
			container->setPosition(offset);
		}
	}
	glm::vec2 getOffset()const
	{
		if(container){
			return container->getPosition();
		}
		return {0,0};
	}
	
	ContainerType* container = nullptr;
	
	virtual void updateLayout() override;
	
protected:	
	
	
};


//---------------------------------------------------------------------------------------


typedef ClippedView_<DOM::Element> ClippedView;







} } // ofx::MUI
