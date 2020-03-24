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
: RegionView(parentTrack, controller)
, Selector<KeyFrameView>(this, this)
{
	addEventListener(keyDown,
	&KeyframesRegionView::onKeyboardEvent,
	false,
	std::numeric_limits<int>::lowest());
	addEventListener(keyUp,
	&KeyframesRegionView::onKeyboardEvent,
	false,
	std::numeric_limits<int>::lowest());
	
	
	setDraggable(true);
//	setMoveToFrontOnCapture(false);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::onKeyFrameDrag(KeyFrameView* k, const glm::vec2& delta)
{
	auto & selectedKeyframes = getSelectedElements();
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
std::vector<KeyFrameView*> & KeyframesRegionView::getCollection()
{
	return keyFrames;
}
const std::vector<KeyFrameView*> & KeyframesRegionView::getCollection() const
{
	return keyFrames;
}

////---------------------------------------------------------------------------------------------------------------------
//bool keyframesort(KeyFrameView* a, KeyFrameView* b)
//{
//	return a->getX() < b->getX();
//}
////---------------------------------------------------------------------------------------------------------------------
//bool KeyframesRegionView::_isSelectingRect() const
//{
//	return selectionRect.getArea() > 0.5;
//}
////---------------------------------------------------------------------------------------------------------------------
//void KeyframesRegionView::_onPointerDown(DOM::PointerUIEventArgs& e)
//{
//	selectionRectStart = screenToLocal( e.screenPosition());
//	selectionRect.set(selectionRectStart, 0, 0);
//
//}
////---------------------------------------------------------------------------------------------------------------------
//void KeyframesRegionView::_onPointerUp(DOM::PointerUIEventArgs& e)
//{
//	if(_isSelectingRect()){
//		updateSelectionRect(screenToLocal( e.screenPosition()));
//		selectionRect.set(0, 0, 0, 0);
//	}else if(selectedKeyframes.size()){
//		unselectAllKeyframes();
//	}else {
//		addKeyframe(screenToLocal( e.screenPosition()));
//	}
//}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto local = screenToLocal(pointer.position());
//	updateSelectionRect(local);

	_SelectorDragging(local);
	
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	RegionView::_onPointerEvent(e);
	auto local = screenToLocal( e.screenPosition());
	if (e.type() == PointerEventArgs::POINTER_DOWN)
	{
//		_onPointerDown(e);
		_SelectorPointerDown(local);

	}
	else if (e.type() == PointerEventArgs::POINTER_UP)
	{
//		_onPointerUp(e);
		auto wasSelecting = _SelectorPointerUp(local);
		if(!wasSelecting)
		{
			addKeyframe(screenToLocal( e.screenPosition()));
			
		}
	}
}
//void KeyframesRegionView::_selectorRectChanged(ofRectangle& r)
//{
//	auto selectionRect = selector.getRect().getIntersection(ofRectangle(0,0, getWidth(), getHeight()));
//
//	_setSelectedKeyframesFromRect(selectionRect, ofGetKeyPressed(' '));
//}

//---------------------------------------------------------------------------------------------------------------------
//void KeyframesRegionView::updateSelectionRect(const glm::vec2& args)
//{
//
//	selectionRect.set(selectionRectStart, 0, 0);
//
//	selectionRect.width = args.x - selectionRectStart.x;
//	selectionRect.height = args.y - selectionRectStart.y;
//
//	selectionRect.standardize();
//	selectionRect = selectionRect.getIntersection(ofRectangle(0,0, getWidth(), getHeight()));
//
//	_setSelectedKeyframesFromRect(selectionRect, ofGetKeyPressed(' '));
//}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::selectKeyframe(KeyFrameView* keyframe)
{
	selectElement(keyframe);
//	if(!keyframe) return;
//	keyframe->bSelected = true;
//	if(isKeyframeSelected(keyframe)) return;
//	selectedKeyframes.push_back(keyframe);

}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::unselectKeyframe(KeyFrameView* k)
{
	unselectElement(k);
//	if(k == nullptr) return;
//
//	k->bSelected = false;
//	ofRemove(selectedKeyframes, [&](KeyFrameView*& key){return key == k;});

}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::unselectAllKeyframes()
{
	unselectAllElements();
//	for(auto& k: selectedKeyframes){
//		k->bSelected = false;
//	}
//	selectedKeyframes.clear();
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::selectAllKeyframes()
{
	selectAllElements();
//	selectedKeyframes = keyFrames;
//	for(auto& k: keyFrames){
//		k->bSelected = true;
//	}
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::isKeyframeSelected(KeyFrameView* k)
{
	return isElementSelected(k);
//	if(k == nullptr) return false;
//	if(selectedKeyframes.size()==0) return false;
//	return binary_search(selectedKeyframes.begin(), selectedKeyframes.end(), k, keyframesort);
}
//---------------------------------------------------------------------------------------------------------------------
//void KeyframesRegionView::_setSelectedKeyframesFromRect(const ofRectangle& r, bool bAddToCurrentSelection)
//{
//	if(!bAddToCurrentSelection){
//		unselectAllKeyframes();
//	}
//	for(auto& k: keyFrames){
//		if(r.inside(k->getCenterPosition())){
//			selectKeyframe(k);//Not sure if the overhead that this function adds with the checks it performs is relevant or not
//		}
//	}
//}
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
	
//	if(_isSelectingRect()){
//		ofPushStyle();
//		ofSetColor(0);
//		ofNoFill();
//		ofDrawRectangle(selectionRect);
//		ofPopStyle();
//	}
	
	Selector<KeyFrameView>::draw();
	
	ofSetColor(ofColor::yellow);
	preview.draw();
	
	ofPopStyle();
	
}
//---------------------------------------------------------------------------------------------------------------------
KeyFrameView* KeyframesRegionView::addKeyframe(const glm::vec2& k){
	_count++;
	auto c = this->addChild<KeyFrameView>(getId()+"_k"+ofToString(_count), k);
	keyFrames.push_back(c);
	c->_updateValue();
	updateKeyframeSort();
	
	ofNotifyEvent(keyframeAddedEvent, c, this);
	
}

bool compareKeyFrameView(KeyFrameView* a, KeyFrameView* b)
{
	return a->getX() < b->getX();
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::updateKeyframeSort(){
	if(numChildren() > 1){
		std::sort(keyFrames.begin(), keyFrames.end(), compareKeyFrameView);
	}
	auto & selectedKeyframes = getSelectedElements();
	
	if(selectedKeyframes.size() > 1){
		std::sort(selectedKeyframes.begin(), selectedKeyframes.end(), compareKeyFrameView);
	}
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::removeKeyframe(KeyFrameView* k){
	if(k == nullptr) return false;
	
	auto c = removeChild(k);
	if(c){
		ofRemove(keyFrames, [&](KeyFrameView*& key){return key == k;});
		auto & selectedKeyframes = getSelectedElements();
		ofRemove(selectedKeyframes, [&](KeyFrameView*& key){return key == k;});
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

void KeyframesRegionView::onKeyboardEvent(DOM::KeyboardUIEventArgs& evt)
{
	if (this == evt.target())
    {
		_SelectorKeyboardEvent(evt);
    }
}

void KeyframesRegionView::_removeSelectedElements()
{
	auto& sel = getSelectedElements();
	
	for(auto s: sel)
	{
//		removeKeyframe(s);
		if(s == nullptr) continue;
		
		auto c = removeChild(s);
		if(c){
			ofRemove(keyFrames, [&](KeyFrameView*& key){return key == s;});
		}

		
		
	}
	updateKeyframeSort();
	
//	ofNotifyEvent(keyframeRemovedEvent, k, this);
	
	sel.clear();
	
}


} } // ofx::LineaDeTiempo

