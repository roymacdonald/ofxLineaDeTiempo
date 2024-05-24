//
//  ClippedView.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#include "ClippedView.h"
#include "ofGraphics.h"
#include "LineaDeTiempo/View/TrackHeaderGroup.h"

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


template class ClippedView_<DOM::Element>;
template class ClippedView_<AutoReziseContainer>;
template class ClippedView_<LineaDeTiempo::TrackHeader>;
template class ClippedView_<LineaDeTiempo::TrackHeaderGroup>;

} } // namespace ofx::MUI
