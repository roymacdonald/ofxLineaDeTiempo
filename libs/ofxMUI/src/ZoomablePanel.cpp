//
//  ZoomablePanel.cpp
//  example
//
//  Created by Roy Macdonald on 4/20/20.
//

#include "ZoomablePanel.h"
#include "LineaDeTiempo/View/TracksClippedView.h"
namespace ofx {
namespace MUI {

//---------------------------------------------------------------------------------------------------
template<typename  C, typename CT>
ZoomablePanel<C, CT>::ZoomablePanel(const std::string& id, const ofRectangle& rect):
DOM::Element(id, rect.x,rect.y,rect.width,rect.height)
{
	this->setFocusable(false);
	
	_clippingPanel = this->addChild<C>("Clipping_Panel", rect);
	_clippingPanel->setFocusable(false);
	
	_scrollbarH = this->addChild<ZoomScrollbar>("H_Scrollbar", DOM::Orientation::HORIZONTAL, _clippingPanel);
	_scrollbarV = this->addChild<ZoomScrollbar>("V_Scrollbar", DOM::Orientation::VERTICAL, _clippingPanel);
	
	_setClippingPanelShape();

	
	_scrollbarH->setValue({0,0});
	_scrollbarV->setValue({0,0});
}


template<typename  C, typename CT>
void ZoomablePanel<C, CT>::_onShapeChange(const DOM::ShapeChangeEventArgs& e)
{
	_setClippingPanelShape();
}


template<typename  C, typename CT>
void ZoomablePanel<C, CT>::_setClippingPanelShape()
{
	if(_clippingPanel){
		_clippingPanel->setShape({
			CONTAINER_MARGIN,
			CONTAINER_MARGIN,
			getWidth() - (CONTAINER_MARGIN*2) - _getScrollbarSize(DOM::Orientation::VERTICAL),
			getHeight() - (CONTAINER_MARGIN*2) -  _getScrollbarSize(DOM::Orientation::HORIZONTAL)}
								 );
	}
}


template<typename  C, typename CT>
void ZoomablePanel<C, CT>::setForceShowScrollbars(bool show)
{
	_forceShowScrollbars = show;
	_setClippingPanelShape();
}


template<typename  C, typename CT>
bool ZoomablePanel<C, CT>::isForceShowScrollbars()
{
	return _forceShowScrollbars;
}


template<typename  C, typename CT>
CT* ZoomablePanel<C, CT>::getContainer()
{
	if(_clippingPanel)return _clippingPanel->container;
	return nullptr;
}


template<typename  C, typename CT>
bool ZoomablePanel<C, CT>::_isScrollbarActive(DOM::Orientation scrollbarOrientation)
{
	if(_forceShowScrollbars)return true;
	if(_clippingPanel){
		auto c = getContainer();
		if(c){
			int index = (int)scrollbarOrientation;
			return (c->getPosition()[index] < 0) || (c->getSize()[index] > _clippingPanel->getSize()[index]);
		}
	}
	return false;
}


template<typename  C, typename CT>
float ZoomablePanel<C, CT>::_getScrollbarSize(DOM::Orientation scrollbarOrientation)
{
	if(_isScrollbarActive(scrollbarOrientation)){
		return SCROLL_BAR_SIZE;
	}else{
		return 0;
	}
}


template<typename  C, typename CT>
C*  ZoomablePanel<C, CT>::getClippingView()
{
	return _clippingPanel;
}


template<typename  C, typename CT>
ZoomScrollbar * ZoomablePanel<C, CT>::getScrollbarH()
{
	return _scrollbarH;
}


template<typename  C, typename CT>
ZoomScrollbar * ZoomablePanel<C, CT>::getScrollbarV()
{
	return _scrollbarV;
}




template class ZoomablePanel<ClippedView, AutoReziseContainer>;

template class ZoomablePanel<LineaDeTiempo::TracksClippedView, AutoReziseContainer>;

}

} // ofx::MUI

