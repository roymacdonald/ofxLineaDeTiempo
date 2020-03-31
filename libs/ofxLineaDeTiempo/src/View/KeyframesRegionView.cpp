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
#include "LineaDeTiempo/Utils/Constants.h"


namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
KeyframesRegionView::KeyframesRegionView(TrackView* parentTrack, RegionController *controller, shared_ptr<MUI::Styles> regionStyles)
: RegionView(parentTrack, controller, regionStyles)
{
	
	_collectionView = addChild<KeyframeCollectionView>(getId()+"_view", getWidth(), getHeight()- RegionViewHeaderHeight, this, &_selector, controller);
	
	_collectionView->setStyles(regionStyles);
	
	_selector.setLimitingElement(_collectionView);
	_selector.addTarget(_collectionView);
	
	setDraggable(false);
	
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::onDraw() const{
	Widget::onDraw();
	_selector.draw();
	
}

KeyframeView* KeyframesRegionView::addKeyframe(float value, uint64_t time)
{
	return _collectionView->addKeyframe(value, time);
}

//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::removeKeyframe(KeyframeView* k){
	return _collectionView->removeKeyframe(k);

}

Selector<KeyframeView>& KeyframesRegionView::getSelector()
{
	return _selector;
}

const Selector<KeyframeView>& KeyframesRegionView::getSelector() const
{
	return _selector;
}

} } // ofx::LineaDeTiempo

