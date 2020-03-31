//
//  ClippedView.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#include "ClippedView.h"
#include "ofGraphics.h"
#include "LineaDeTiempo/View/TrackHeader.h"

namespace ofx {
namespace MUI {
//---------------------------------------------------------------------------------------
//template<typename ContainerType>
//ClippedView_<ContainerType>::ClippedView_(const std::string& id, const ofRectangle& rect):
//    DOM::Element(id, rect.x, rect.y, rect.width, rect.height)
//{
//
//	setDrawAsViewport(true);
//	setFocusable(false);
//	container = addChild<ContainerType>(id+"_Container", rect);
//	container->setFocusable(false);
//	container->setDrawChildrenOnly(true);
////	createLayout<ClippedViewLayout>(this);
//}


//---------------------------------------------------------------------------------------
template<typename ContainerType>
void ClippedView_<ContainerType>::updateLayout()
{
	if(container){
		auto s = container->getChildShape();
		container->setSize(s.width, s.height);
	}
}
template class ClippedView_<DOM::Element>;
template class ClippedView_<LineaDeTiempo::TrackHeader>;
} } // namespace ofx::MUI
