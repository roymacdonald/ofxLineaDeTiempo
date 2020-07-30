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

//		_zoom[0] = {0,1};
//		_zoom[1] = {0,1};
//
		setDrawAsViewport(true);
		setFocusable(false);
		container = addChild<ContainerType>(id+"_Container", ofRectangle(0,0,rect.width, rect.height), std::forward<Args>(args)...);

	}
	
	
	virtual ~ClippedView_() = default;
	
	void setOffset(const glm::vec2& offset);
	
	glm::vec2 getOffset()const;
	
	ContainerType* container = nullptr;
	
//	virtual void setZoom(DOM::Orientation orientation, const ofRange& zoom);

//	void setZoomV(ofRange& v);
//	void setZoomH(ofRange& v);
	
//	ofRange getZoom(DOM::Orientation orientation) const;
	
protected:	
	
	
//	glm::vec2 _minZoom = {
//		0.0001, //std::numeric_limits<float>::epsilon(),
//		0.0001 //std::numeric_limits<float>::epsilon()
//	};

	
//	ofRange _zoom [2];
};


//---------------------------------------------------------------------------------------


typedef ClippedView_<AutoReziseContainer> ClippedView;







} } // ofx::MUI
