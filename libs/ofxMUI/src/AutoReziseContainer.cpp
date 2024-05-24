//
//  AutoReziseContainer.cpp
//  example
//
//  Created by Roy Macdonald on 4/18/20.
//

#include "AutoReziseContainer.h"

namespace ofx {
namespace MUI {


	
	AutoReziseContainer::AutoReziseContainer(const std::string& id, const ofRectangle& rect)
	: DOM::Element(id, rect)
	{
		setFocusable(false);
		setDrawChildrenOnly(true);
		
	}
	

	
	
	void AutoReziseContainer::_onChildShapeChanged(DOM::ShapeChangeEventArgs&)
	{
		auto mx = getChildShape().getMax();
		setSize(mx.x, mx.y);
		
	}

} } // ofx::MUI
