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
#include "ofMath.h"

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
		container = addChild<ContainerType>(id+"_Container", rect, std::forward<Args>(args)...);
		container->setFocusable(false);
		container->setDrawChildrenOnly(true);
	//	createLayout<ClippedViewLayout>(this);
	}
	
	
	virtual ~ClippedView_(){}
	
	void setOffset(const glm::vec2& offset)
	{
		if(container && (!ofIsFloatEqual(offset.x, container->getX())
					  || !ofIsFloatEqual(offset.y, container->getY()))){
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
