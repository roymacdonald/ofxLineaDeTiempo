//
//  ScrollablePanel.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/5/20.
//

#include "ScrollablePanel.h"

//#include "Constants.h"
namespace ofx {
namespace MUI {

//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
ScrollablePanel_<H, D, B, C, CT>::ScrollablePanel_(const std::string& id, const ofRectangle& rect):
Widget(id, rect.x,rect.y,rect.width,rect.height)
{
	this->setFocusable(false);
	
	_scrollbarH = this->addChild<B<H, D>>("H_Scrollbar", DOM::Orientation::HORIZONTAL);
	_scrollbarV = this->addChild<B<H, D>>("V_Scrollbar", DOM::Orientation::VERTICAL);

//	_scrollData.resize(2);
	
	
//	createLayout<ScrollablePanelLayout<ScrollablePanel_<H, D, B, C, CT> > >(this);
	
	_scrollListeners.push(_scrollbarH->handleChangedEvent().newListener(this, &ScrollablePanel_<H, D, B, C, CT>::_scrollHChanged));
	_scrollListeners.push(_scrollbarV->handleChangedEvent().newListener(this, &ScrollablePanel_<H, D, B, C, CT>::_scrollVChanged));

	_scrollListeners.push(ofEvents().mouseScrolled.newListener(this, &ScrollablePanel_<H, D, B, C, CT>::_onMouseScrollEvent, OF_EVENT_ORDER_AFTER_APP));
	
	_clippingPanel = this->addChild<C>("Clipping_Panel", rect);
	_clippingPanel->setFocusable(false);
	
	resetScrollbarMargins();
	
}
////---------------------------------------------------------------------------------------------------
//template<>
//void ScrollablePanel_<ZoomHandle, ofRange_<float>, Scrollbar_, LineaDeTiempo::TracksClippedView, DOM::Element>::updateContainerLayout()
//{
//	if(_bInitScrollData)
//	{
//		_bInitScrollData = false;
//		_scrollData[0] = {0,1};
//		_scrollData[1] = {0,1};
//	}
//	 _clippingPanel->setZoom(_scrollData);
//	
//}
////---------------------------------------------------------------------------------------------------
//template<>
//void ScrollablePanel_<ZoomHandle, ofRange_<float>, Scrollbar_, ScaledView, ScaledContainer>::updateContainerLayout()
//{
//	auto c = getContainer();
//	if(c){
//
//		glm::vec2 offset(0,0);
//		glm::vec2 scale(1,1);
//		auto containerSize = c->getSize();
//		auto viewSize = _clippingPanel->getSize();
//
//
//
//		for(int i  = 0; i <2; i++){
//			if(containerSize[i] > viewSize[i]){
//
//				auto range = _scrollData[i];
//				avoidZero(range);
//
//				scale[i] = viewSize[i] / (range.span() * containerSize[i]);
//
//				offset[i] = ofMap(0, range.min * containerSize[i], range.max * containerSize[i], 0, viewSize[i]) ;
//
//			}
//
//		}
//
//		_clippingPanel->setOffset(offset);
//		_clippingPanel->setScale(scale);
//
//
//
//	}
//}
////---------------------------------------------------------------------------------------------------
//template<>
//void ScrollablePanel_<ScrollHandle, float, Scrollbar_, ClippedView_<Widget>, Widget>::updateContainerLayout()
//{
//	auto c = getContainer();
//	if(c){
//		glm::vec2 offset(0,0);
//		auto containerSize = c->getSize();
//		auto clippingSize = _clippingPanel->getSize();
//		for(int i  = 0; i <2; i++){
//			if(containerSize[i] > clippingSize[i]){
//				offset[i] = ofMap(_scrollData[i], 0, 1, 0, -(containerSize[i] - clippingSize[i]));
//			}
//		}
//
//		_clippingPanel->setOffset(offset);
//	}
//}
////---------------------------------------------------------------------------------------------------
//template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
//void ScrollablePanel_<H, D, B, C, CT>::updateContainerLayout()
//{
//	ofLogError(__PRETTY_FUNCTION__) << "This function template specialization is not implemented";
//}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::_scrollVChanged(D& s)
{

//	if(s != _clippingPanel->getZoom(DOM::VERTICAL)) return;
	
	_clippingPanel->setZoomV(s);
	
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::_scrollHChanged(D& s)
{
//	this->_scrollData[0] =s;
//	if(s == _clippingPanel->getZoom(DOM::HORIZONTAL)) return;
	
	_clippingPanel->setZoomH(s);
	
//	updateContainerLayout();
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::_updateScrollbar(B<H, D> * scrollbar)
{
	
	if(scrollbar){
		auto orientation = scrollbar->getOrientation();
		if(isScrollbarActive(orientation)){
			scrollbar->setEnabled(true);
			scrollbar->setHidden(false);
//			std::cout << "scrollbar " << scrollbar->getId();

			if(orientation == DOM::Orientation::HORIZONTAL){
//				std::cout << "HOR orientation ";
				float margin = getScrollbarSize(DOM::Orientation::VERTICAL);
				
				scrollbar->updateLayout({_scrollMargins.left,	getHeight() - SCROLL_BAR_SIZE, getWidth() - margin - _scrollMargins.right - _scrollMargins.left, SCROLL_BAR_SIZE });
			}else{
//				std::cout << "VERT orientation";
				float margin = getScrollbarSize(DOM::Orientation::HORIZONTAL);
				scrollbar->updateLayout({getWidth() - SCROLL_BAR_SIZE, _scrollMargins.top, SCROLL_BAR_SIZE, getHeight() - margin - _scrollMargins.bottom - _scrollMargins.top});
			}

		}else{
			scrollbar->setEnabled(false);
			scrollbar->setHidden(true);
		}
	}else{
		ofLogError("ScrollablePanel_<H, D, B, C, CT>::_updateScrollbar")<< " scrollbar is null";
	}
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::updateLayout()
{
	//TODO: There seems to be an excesive and unnecesary amount of calls to this function
	_updateScrollbar(_scrollbarH);
	_updateScrollbar(_scrollbarV);

	
	if(_clippingPanel){
		_clippingPanel->setShape({
							CONTAINER_MARGIN,
							CONTAINER_MARGIN,
							getWidth() - (CONTAINER_MARGIN*2) - getScrollbarSize(DOM::Orientation::VERTICAL),
							getHeight() - (CONTAINER_MARGIN*2) -  getScrollbarSize(DOM::Orientation::HORIZONTAL)}
							);
	}
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
bool ScrollablePanel_<H, D, B, C, CT>::_onMouseScrollEvent(ofMouseEventArgs & e)
{
	if(_scrollbarH && _scrollbarH->isEnabled())_scrollbarH->scroll(e.scrollX);
	if(_scrollbarV && _scrollbarV->isEnabled())_scrollbarV->scroll(e.scrollY);
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::setForceShowScrollbars(bool show)
{
	_forceShowScrollbars = show;
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
bool ScrollablePanel_<H, D, B, C, CT>::isForceShowScrollbars()
{
	return _forceShowScrollbars;
}


//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::setVScrollMargin(float top, float bottom)
{
	_scrollMargins.top = top;
	_scrollMargins.bottom = bottom;
	_updateScrollbar(_scrollbarV);
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::setHScrollMargin(float left, float right)
{
	_scrollMargins.left = left;
	_scrollMargins.right = right;
	_updateScrollbar(_scrollbarH);
}

//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
const Margins& ScrollablePanel_<H, D, B, C, CT>::getScrollMargins()
{
	return _scrollMargins;
}

//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::resetScrollbarMargins()
{
	_scrollMargins.reset();
}


//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::setScrollH(D d)
{
	if(_scrollbarH){
		_scrollbarH->setValue(d);
	}else{
		ofLogError("ScrollablePanel_::setScrollH") << "scrollbar null";
	}
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::setScrollV(D d)
{
//	std::cout << "--------------------------------------------------------------------------------\n";
	if(_scrollbarV){
		
		_scrollbarV->setValue(d);
	}else{
		ofLogError("ScrollablePanel_::setScrollV") << "scrollbar null";
	}
//	std::cout << "================================================================================\n";
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
CT* ScrollablePanel_<H, D, B, C, CT>::getContainer()
{
	if(_clippingPanel)return _clippingPanel->container;
	return nullptr;
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
bool ScrollablePanel_<H, D, B, C, CT>::isScrollbarActive(DOM::Orientation scrollbarOrientation)
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
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
float ScrollablePanel_<H, D, B, C, CT>::getScrollbarSize(DOM::Orientation scrollbarOrientation)
{
	if(isScrollbarActive(scrollbarOrientation)){
		return SCROLL_BAR_SIZE;
	}else{
		return 0;
	}
}
//---------------------------------------------------------------------------------------------------
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
C*  ScrollablePanel_<H, D, B, C, CT>::getClippingView()
{
	return _clippingPanel;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//template<typename PanelType>
//ScrollablePanelLayout<PanelType>::ScrollablePanelLayout(PanelType* parent):
//    DOM::Layout(parent),
//	parentPanel(parent)
//{
//}
////---------------------------------------------------------------------------------------------------
//template<typename PanelType>
//void ScrollablePanelLayout<PanelType>::doLayout()
//{
//	if (_parent && !_isDoingLayout)
//    {
//		// Prevent recursive calls to doLayout.
//		_isDoingLayout = true;
//		auto p = dynamic_cast<PanelType*>(_parent);
//		if(p){
//			p->updateLayout();
//		}else{
//			ofLogError("ScrollablePanelLayout::doLayout") << "_parent not of type " << typeid(PanelType).name();
//		}
//        _isDoingLayout = false;
//    }
//}
template<typename H, typename D,  template <typename, typename> class B, typename C, typename CT>
void ScrollablePanel_<H, D, B, C, CT>::updateVerticalScrollFromContainersHeight()
{
	
	auto z = _clippingPanel->getVerticalZoomFromContainerHeight();
		
	setScrollV(z);
	
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//template class ScrollablePanel_<ScrollHandle, float, Scrollbar_, ClippedView, DOM::Element>;
//template class ScrollablePanel_<ZoomHandle, ofRange, Scrollbar_, ScaledView, ScaledContainer>;
template class ScrollablePanel_<ZoomHandle, ofRange, Scrollbar_, LineaDeTiempo::TracksClippedView, DOM::Element>;

} } // ofx::MUI

