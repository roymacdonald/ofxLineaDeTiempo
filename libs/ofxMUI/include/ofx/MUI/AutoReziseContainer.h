//
//  AutoReziseContainer.hpp
//  example
//
//  Created by Roy Macdonald on 4/18/20.
//


#pragma once
#include "ofx/DOM/Element.h"

namespace ofx {
namespace MUI {


class AutoReziseContainer
: public DOM::Element
{
public:
	
	
	AutoReziseContainer(const std::string& id, const ofRectangle& rect);
	
	virtual ~AutoReziseContainer() = default;
	
	
protected:
	
	virtual void _onChildShapeChanged(DOM::ShapeChangeEventArgs&) override;
	
	
	
	
};





} } // ofx::MUI
