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


template<typename ContainerType>
void ClippedView_<ContainerType>::setOffset(const glm::vec2& offset)
{
	if(container && (!ofIsFloatEqual(offset.x, container->getX())
				  || !ofIsFloatEqual(offset.y, container->getY()))){
		container->setPosition(offset);
	}
}


template<typename ContainerType>
glm::vec2 ClippedView_<ContainerType>::getOffset()const
{
	if(container){
		return container->getPosition();
	}
	return {0,0};
}

//template<typename ContainerType>
//void ClippedView_<ContainerType>::setZoom(DOM::Orientation index, const ofRange& zoom)
//{
//	if(index == DOM::HORIZONTAL || index == DOM::VERTICAL){
//		_zoom[index] = zoom;
//		MUI::keepRangeMinSpan(_zoom[index], _minZoom[index], {0,1});
//	}
//}
//
//template<typename ContainerType>
//void ClippedView_<ContainerType>::setZoomV(ofRange& v)
//{
//	setZoom(DOM::VERTICAL, v);
//}
//
//template<typename ContainerType>
//void ClippedView_<ContainerType>::setZoomH(ofRange& h)
//{
//	setZoom(DOM::HORIZONTAL, h);
//}
//
//template<typename ContainerType>
//ofRange ClippedView_<ContainerType>::getZoom(DOM::Orientation orientation) const
//{
//	if(orientation == DOM::HORIZONTAL || orientation == DOM::VERTICAL){
//		return _zoom[orientation];
//	}
//	return {0,1};
//}
//


template class ClippedView_<DOM::Element>;
template class ClippedView_<AutoReziseContainer>;
template class ClippedView_<LineaDeTiempo::TrackHeader>;


} } // namespace ofx::MUI
