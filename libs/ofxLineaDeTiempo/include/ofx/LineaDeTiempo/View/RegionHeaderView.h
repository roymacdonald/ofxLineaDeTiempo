//
//  RegionHeaderView.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/27/20.
//

#pragma once

#include "MUI/Handles/ConstrainedGrabHandle.h"

namespace ofx {
namespace LineaDeTiempo {

class RegionView;

class RegionHeaderView
: public MUI::ConstrainedGrabHandle
{
public:
	
	
	RegionHeaderView (RegionView* parentRegion);
	
	virtual ~RegionHeaderView() = default;


	virtual void onDraw() const override;
	
	
protected:
	virtual void _onDragging(const DOM::CapturedPointer& pointer)override;
	
	
	void _parentResized(DOM::ResizeEventArgs &);
	
	RegionView* _parentRegion = nullptr;
                                                            

	ofEventListeners _parentListeners;
	
private:
	
	
};


} } // ofx::LineaDeTiempo
