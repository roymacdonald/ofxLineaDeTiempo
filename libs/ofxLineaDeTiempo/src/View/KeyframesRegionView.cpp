//
//  KeyframesRegionView.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#include "LineaDeTiempo/View/KeyframesRegionView.h"
#include "ofRectangleHelper.h"
#include "ofEvent.h"

#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
KeyframesRegionView::KeyframesRegionView(TrackView* parentTrack, RegionController *controller, shared_ptr<MUI::Styles> regionStyles)
: RegionView(parentTrack, controller, regionStyles)
, _controller(controller)
{
	//TODO: make use of this class only when using a multi dimensional parameter. Otherwise just use the KeyframeCollectionView
	auto numDims = _controller->getNumDimensions();


	ofRectangle rect(0, ConstVars::ViewTopHeaderHeight, getWidth(), _getCollectionViewHeight());
	
	for(size_t i = 0; i < numDims; ++i)
	{
		auto c = addChild<KeyframeCollectionView>(GetNameForDimension(i, numDims), rect, this, &_selector, controller);
		_views.push_back(c);
		c->setStyles(regionStyles);
		_selector.addTarget(c);
		
		rect.y += rect.height;
		
	}
			
	setDraggable(false);
	if(controller->getDataTypeName() == string(typeid(void).name()))
	{
		_selector.setIntersectionMode(SELECTOR_USE_RECTANGLE);
	}
	
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::updateLayout()
{

	
	ofRectangle rect(0, ConstVars::ViewTopHeaderHeight, getWidth(), _getCollectionViewHeight());
	
	for(auto v: _views)
	{
		v->setShape(rect);
		
		rect.y += rect.height;
		
	}
	
	_allViewsRect.set( localToScreen({0, ConstVars::ViewTopHeaderHeight}) , getWidth(), getHeight() - ConstVars::ViewTopHeaderHeight);
	
	
	_selector.setLimitingRect(_allViewsRect);
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::onDraw() const
{
	Widget::onDraw();
	_selector.draw();
	
}

KeyframeView* KeyframesRegionView::addKeyframe(float value, uint64_t time, size_t viewIndex)
{
	if(viewIndex < _views.size()){
		return _views[viewIndex]->addKeyframe(value, time);
	}
	return nullptr;
}

//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::removeKeyframe(KeyframeView* k, size_t viewIndex)
{
	if(viewIndex < _views.size()){
		return _views[viewIndex]->removeKeyframe(k);
	}
	return false;
}

Selector<KeyframeView>& KeyframesRegionView::getSelector()
{
	return _selector;
}

const Selector<KeyframeView>& KeyframesRegionView::getSelector() const
{
	return _selector;
}

float KeyframesRegionView::_getCollectionViewHeight() const
{
	if(_controller)
	{
		return(getHeight() - ConstVars::ViewTopHeaderHeight)/ float(_controller->getNumDimensions());
	}
	ofLogWarning("KeyframesRegionView::_getCollectionViewHeight") << "Region view has no controller. This should never happen.";
	return getHeight() - ConstVars::ViewTopHeaderHeight;
}

const std::vector<KeyframeCollectionView *>& KeyframesRegionView::getViews()
{
	return _views;
}

const std::vector<KeyframeCollectionView *>& KeyframesRegionView::getViews() const
{
	return _views;
}


} } // ofx::LineaDeTiempo

