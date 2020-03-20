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

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
KeyframesRegionView::KeyframesRegionView(TrackView* parentTrack, RegionController *controller)
:RegionView(parentTrack, controller)
{
	setDraggable(true);
//	setMoveToFrontOnCapture(false);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::onKeyFrameDrag(KeyFrame* k, const glm::vec2& delta)
{
	
	for(auto s : selectedKeyframes){
		if(s != k ){
			
			auto r = s->getShape();
			r.x = s->getX() - delta.x;
			r.y = s->getY() - delta.y;
			
			DOM::ofRectangleHelper::keepInside(r, ofRectangle(0,0, getWidth(), getHeight()));
			
			s->setPosition(r.getPosition());
			s->_updateValue();
			
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
bool keyframesort(KeyFrame* a, KeyFrame* b)
{
	return a->getX() < b->getX();
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::_isSelectingRect() const
{
	return selectionRect.getArea() > 0.5;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_onPointerDown(DOM::PointerUIEventArgs& e)
{
	selectionRectStart = screenToLocal( e.screenPosition());
	selectionRect.set(selectionRectStart, 0, 0);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_onPointerUp(DOM::PointerUIEventArgs& e)
{
	if(_isSelectingRect()){
		updateSelectionRect(screenToLocal( e.screenPosition()));
		selectionRect.set(0, 0, 0, 0);
	}else if(selectedKeyframes.size()){
		unselectAllKeyframes();
	}else {
		addKeyframe(screenToLocal( e.screenPosition()));
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto local = screenToLocal(pointer.position());
	updateSelectionRect(local);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	RegionView::_onPointerEvent(e);
	if (e.type() == PointerEventArgs::POINTER_DOWN)
	{
		_onPointerDown(e);

	}
	else if (e.type() == PointerEventArgs::POINTER_UP)
	{
		_onPointerUp(e);
	}


}

//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::updateSelectionRect(const glm::vec2& args)
{
	
	selectionRect.set(selectionRectStart, 0, 0);
	
	selectionRect.width = args.x - selectionRectStart.x;
	selectionRect.height = args.y - selectionRectStart.y;
	
	selectionRect.standardize();
	selectionRect = selectionRect.getIntersection(ofRectangle(0,0, getWidth(), getHeight()));
	
	_setSelectedKeyframesFromRect(selectionRect, ofGetKeyPressed(' '));
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::selectKeyframe(KeyFrame* keyframe)
{
	if(!keyframe) return;
	keyframe->bSelected = true;
	if(isKeyframeSelected(keyframe)) return;
	selectedKeyframes.push_back(keyframe);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::unselectKeyframe(KeyFrame* k)
{
	if(k == nullptr) return;
	
	k->bSelected = false;
	ofRemove(selectedKeyframes, [&](KeyFrame*& key){return key == k;});

}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::unselectAllKeyframes()
{
	for(auto& k: selectedKeyframes){
		k->bSelected = false;
	}
	selectedKeyframes.clear();
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::selectAllKeyframes()
{
	selectedKeyframes = keyFrames;
	for(auto& k: keyFrames){
		k->bSelected = true;
	}
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::isKeyframeSelected(KeyFrame* k)
{
	if(k == nullptr) return false;
	if(selectedKeyframes.size()==0) return false;
	return binary_search(selectedKeyframes.begin(), selectedKeyframes.end(), k, keyframesort);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_setSelectedKeyframesFromRect(const ofRectangle& r, bool bAddToCurrentSelection)
{
	if(!bAddToCurrentSelection){
		unselectAllKeyframes();
	}
	for(auto& k: keyFrames){
		if(r.inside(k->getCenterPosition())){
			selectKeyframe(k);//Not sure if the overhead that this function adds with the checks it performs is relevant or not
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::onDraw() const{
	Widget::onDraw();
	ofPolyline preview;
	glm::vec2 cp;
	for(auto& k: keyFrames){
		cp = k->getCenterPosition();
		preview.addVertex(cp.x, cp.y);
	}
	ofPushStyle();
	
	if(_isSelectingRect()){
		ofPushStyle();
		ofSetColor(0);
		ofNoFill();
		ofDrawRectangle(selectionRect);
		ofPopStyle();
	}
	
	ofSetColor(ofColor::yellow);
	preview.draw();
	
	ofPopStyle();
	
}
//---------------------------------------------------------------------------------------------------------------------
KeyFrame* KeyframesRegionView::addKeyframe(const glm::vec2& k){
	_count++;
	auto c = this->addChild<KeyFrame>(getId()+"_k"+ofToString(_count), k);
	keyFrames.push_back(c);
	c->_updateValue();
	updateKeyframeSort();
	
	ofNotifyEvent(keyframeAddedEvent, c, this);
	
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::updateKeyframeSort(){
	if(numChildren() > 1){
		std::sort(keyFrames.begin(), keyFrames.end(), keyframesort);
	}
	if(selectedKeyframes.size() > 1){
		std::sort(selectedKeyframes.begin(), selectedKeyframes.end(), keyframesort);
	}
}

//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::removeKeyframe(KeyFrame* k){
	if(k == nullptr) return false;
	
	auto c = removeChild(k);
	if(c){
		ofRemove(keyFrames, [&](KeyFrame*& key){return key == k;});
		ofRemove(selectedKeyframes, [&](KeyFrame*& key){return key == k;});
		updateKeyframeSort();
		
		ofNotifyEvent(keyframeRemovedEvent, k, this);
		
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::updateLayout()
{
	RegionView::updateLayout();
	
	for(auto k: keyFrames){
		if(k)k->_updatePosition();
	}
	
}
} } // ofx::LineaDeTiempo

