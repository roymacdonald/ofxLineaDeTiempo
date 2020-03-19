//
//  KeyFrames.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#include "LineaDeTiempo/View/KeyFrames.h"
#include "ofRectangleHelper.h"
#include "ofEvent.h"

#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Controller/RegionController.h"

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
KeyFrames::KeyFrames(TrackView* parentTrack, RegionController *controller)
:RegionView(parentTrack, controller)
{
	setDraggable(true);
//	setMoveToFrontOnCapture(false);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::onKeyFrameDrag(KeyFrame* k, const glm::vec2& delta)
{
	
	for(auto s : selectedKeyFrames){
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
bool KeyFrames::_isSelectingRect() const
{
	return selectionRect.getArea() > 0.5;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::_onPointerDown(DOM::PointerUIEventArgs& e)
{
	selectionRectStart = screenToLocal( e.screenPosition());
	selectionRect.set(selectionRectStart, 0, 0);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::_onPointerUp(DOM::PointerUIEventArgs& e)
{
	if(_isSelectingRect()){
		updateSelectionRect(screenToLocal( e.screenPosition()));
		selectionRect.set(0, 0, 0, 0);
	}else if(selectedKeyFrames.size()){
		unselectAllKeyframes();
	}else {
		addKeyframe(screenToLocal( e.screenPosition()));
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto local = screenToLocal(pointer.position());
	updateSelectionRect(local);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::_onPointerEvent(DOM::PointerUIEventArgs& e)
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
void KeyFrames::updateSelectionRect(const glm::vec2& args)
{
	
	selectionRect.set(selectionRectStart, 0, 0);
	
	selectionRect.width = args.x - selectionRectStart.x;
	selectionRect.height = args.y - selectionRectStart.y;
	
	selectionRect.standardize();
	selectionRect = selectionRect.getIntersection(ofRectangle(0,0, getWidth(), getHeight()));
	
	_setSelectedKeyframesFromRect(selectionRect, ofGetKeyPressed(' '));
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::selectKeyframe(KeyFrame* keyframe)
{
	if(!keyframe) return;
	keyframe->bSelected = true;
	if(isKeyframeSelected(keyframe)) return;
	selectedKeyFrames.push_back(keyframe);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::unselectKeyframe(KeyFrame* k)
{
	if(k == nullptr) return;
	
	k->bSelected = false;
	ofRemove(selectedKeyFrames, [&](KeyFrame*& key){return key == k;});

}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::unselectAllKeyframes()
{
	for(auto& k: selectedKeyFrames){
		k->bSelected = false;
	}
	selectedKeyFrames.clear();
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::selectAllKeyframes()
{
	selectedKeyFrames = keyFrames;
	for(auto& k: keyFrames){
		k->bSelected = true;
	}
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyFrames::isKeyframeSelected(KeyFrame* k)
{
	if(k == nullptr) return false;
	if(selectedKeyFrames.size()==0) return false;
	return binary_search(selectedKeyFrames.begin(), selectedKeyFrames.end(), k, keyframesort);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::_setSelectedKeyframesFromRect(const ofRectangle& r, bool bAddToCurrentSelection)
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
void KeyFrames::onDraw() const{
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
KeyFrame* KeyFrames::addKeyframe(const glm::vec2& k){
	_count++;
	auto c = this->addChild<KeyFrame>(getId()+"_k"+ofToString(_count), k);
	keyFrames.push_back(c);
	c->_updateValue();
	updateKeyframeSort();
	
	ofNotifyEvent(keyframeAddedEvent, c, this);
	
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::updateKeyframeSort(){
	if(numChildren() > 1){
		std::sort(keyFrames.begin(), keyFrames.end(), keyframesort);
	}
	if(selectedKeyFrames.size() > 1){
		std::sort(selectedKeyFrames.begin(), selectedKeyFrames.end(), keyframesort);
	}
}

//---------------------------------------------------------------------------------------------------------------------
bool KeyFrames::removeKeyframe(KeyFrame* k){
	if(k == nullptr) return false;
	
	auto c = removeChild(k);
	if(c){
		ofRemove(keyFrames, [&](KeyFrame*& key){return key == k;});
		ofRemove(selectedKeyFrames, [&](KeyFrame*& key){return key == k;});
		updateKeyframeSort();
		
		ofNotifyEvent(keyframeRemovedEvent, k, this);
		
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrames::updateLayout()
{
	std::cout << __PRETTY_FUNCTION__ << "\n";
	RegionView::updateLayout();
	
	for(auto k: keyFrames){
		if(k)k->_updatePosition();
	}
	
}
} } // ofx::LineaDeTiempo

