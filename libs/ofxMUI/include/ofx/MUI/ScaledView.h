//
//  ZoomingPanel.hpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/9/20.
//

#pragma once
#include "ClippedView.h"


namespace ofx {
namespace MUI {


class ScaledContainer: public DOM::Element{
public:
	
	
	ScaledContainer(const std::string& id, const ofRectangle& rect):
	DOM::Element(id, rect)
	{}

	virtual ~ScaledContainer(){}
	
	glm::vec2 scale = {1,1};
protected:
	virtual void _applyTransform() override{
		Element::_applyTransform();
		ofScale(scale.x, scale.y);
	}
	virtual void _restoreTransform() override{
		Element::_restoreTransform();
	}
	
};

class ScaledView:public ClippedView_<ScaledContainer>
{
public:
	
	ScaledView(const std::string& id, const ofRectangle& rect):
	ClippedView_<ScaledContainer>(id, rect)
	{
	}
	
	void setScale(const glm::vec2& scale){
		if(container){
			container->scale.x  =  std::max(scale.x, minScale.x);
			container->scale.y  =  std::max(scale.y, minScale.y);
		}
	}
	
	glm::vec2 getScale() const{
		if(container){
			return container->scale;
		}
		return {1,1};
	}

	glm::vec2 minScale = {std::numeric_limits<float>::epsilon(),
						  std::numeric_limits<float>::epsilon()};
	
	virtual ~ScaledView(){}
		
protected:
	

};


} } // ofx::MUI
