//
//  KeyframeCollectionView.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/28/20.
//

#include "LineaDeTiempo/View/KeyframeCollectionView.h"
#include "ofRectangleHelper.h"
#include "ofEvent.h"

#include "LineaDeTiempo/View/TrackView.h"
#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"
#include "LineaDeTiempo/View/RegionView.h"

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
KeyframeCollectionView::KeyframeCollectionView (const std::string & name, float width, float height, KeyframesRegionView* parentRegion, Selector<KeyframeView>* selector, RegionController *controller)
//: DOM::Element(name, 0, RegionView::headerHeight, width, height)
: MUI::Widget(name, 0, RegionView::headerHeight, width, height)
, _parentRegion(parentRegion)
, _selector(selector)
{
	addEventListener(keyDown,
					 &KeyframeCollectionView::onKeyboardEvent,
					 false,
					 std::numeric_limits<int>::lowest());
	addEventListener(keyUp,
					 &KeyframeCollectionView::onKeyboardEvent,
					 false,
					 std::numeric_limits<int>::lowest());
	
	_parentListener = _parentRegion->resize.newListener(this, &KeyframeCollectionView::_parentResized);
	
	setDraggable(true);
	setFocusable(true);
//	setDrawChildrenOnly(true);
	setMoveToFrontOnCapture(false);
	setHighlightOnOver(true);
}

void KeyframeCollectionView::_parentResized(DOM::ResizeEventArgs &args)
{
//	std::cout << "KeyframeCollectionView::_parentResized\n";
//	if(ofGetKeyPressed('q')){
	setShape({0, RegionView::headerHeight, _parentRegion->getWidth(), getHeight()});
	
	updateLayout();
	_makeInterpolationLine();
//	}
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::onKeyframeDrag(KeyframeView* k, const glm::vec2& delta)
{
	if(_parentRegion){
		auto selectedKeyframes =  _selector->getSelectedElements(this);
		if(selectedKeyframes){
			for(auto s : *selectedKeyframes){
				if(s != k ){
					
					auto r = s->getShape();
					r.x = s->getX() - delta.x;
					r.y = s->getY() - delta.y;
					
					DOM::ofRectangleHelper::keepInside(r, ofRectangle(0,0, getWidth(), getHeight()));
					
					s->setPosition(r.getPosition());
					s->_updateValue();
					
				}
			}
			_makeInterpolationLine();
		}
	}
}
std::vector<KeyframeView*> & KeyframeCollectionView::getCollection()
{
	return keyFrames;
}
const std::vector<KeyframeView*> & KeyframeCollectionView::getCollection() const
{
	return keyFrames;
}

////---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::_onDragging(const DOM::CapturedPointer& pointer)
{
//	auto local = screenToLocal(pointer.position());
	//	updateSelectionRect(local);
//	std::cout << "KeyframesRegionView::_onDragging " << local << "\n";
	if(_parentRegion) _selector->onPointerDrag(pointer.position(), this);
	
}
////---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	MUI::Widget::_onPointerEvent(e);
	if (e.type() == PointerEventArgs::POINTER_DOWN)
	{
		if(_parentRegion) _selector->onPointerDown(e.screenPosition(), this);
		
	}
	else if (e.type() == PointerEventArgs::POINTER_UP)
	{
		//		_onPointerUp(e);
		if(_parentRegion){
			auto wasSelecting =  _selector->onPointerUp(e.screenPosition(), this);
			if(!wasSelecting)
			{
				
				//			auto p =  screenToLocal(e.screenPosition());
				auto p =  e.screenPosition();
				
//							std::cout << ofGetMouseX() << ", " << ofGetMouseY() << " -- " << p << endl;
				
//				if(ofRectangle(0,0,getWidth(), getHeight()).inside(e.localPosition())){

					ofNotifyEvent(addKeyframeEvent, p, this);
//				}
//				ofNotifyEvent(addKeyframeEvent, p, this);
				
				//			addKeyframe();
				
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::selectKeyframe(KeyframeView* keyframe)
{
	if(_parentRegion) _selector->selectElement(keyframe, this);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::unselectKeyframe(KeyframeView* k)
{
	if(_parentRegion) _selector->unselectElement(k, this);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::unselectAllKeyframes()
{
	if(_parentRegion) _selector->unselectAllElements();
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::selectAllKeyframes()
{
	if(_parentRegion) _selector->selectAllElements();
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyframeCollectionView::isKeyframeSelected(KeyframeView* k)
{
	if(_parentRegion) return _selector->isElementSelected(k, this);
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::_makeInterpolationLine(){
	glm::vec2 cp;
	_interpolationLine.clear();
	_inLine.clear();
	_outLine.clear();
	if(keyFrames.size())
	{
		//		_inLine.addVertex(getShape().getMinX(), keyFrames[0]->getCenterPosition().y);
		_inLine.addVertex(0, keyFrames[0]->getCenterPosition().y);
		_inLine.addVertex(glm::vec3(keyFrames[0]->getCenterPosition(),0));
		
		
		
		_outLine.addVertex(glm::vec3(keyFrames.back()->getCenterPosition(),0));
		_outLine.addVertex(getWidth(), keyFrames.back()->getCenterPosition().y);
		
	}
	for(auto& k: keyFrames){
		cp = k->getCenterPosition();
		_interpolationLine.addVertex(cp.x, cp.y);
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::onDraw() const{
//	Widget::onDraw();
	
	ofPushStyle();
//	ofSetColor(10, 200);
//	ofNoFill();
//	ofDrawRectangle(getShape());
	ofSetColor(ofColor::white, 100);
	_inLine.draw();
	_outLine.draw();
	ofSetColor(ofColor::yellow);
	_interpolationLine.draw();
	ofPopStyle();
	
}

bool compareKeyframeView(KeyframeView* a, KeyframeView* b)
{
	return a->getX() < b->getX();
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::updateKeyframeSort(){
	if(numChildren() > 1){
		std::sort(keyFrames.begin(), keyFrames.end(), compareKeyframeView);
	}
	if(_parentRegion){
		auto selectedKeyframes = _selector->getSelectedElements(this);
		if(selectedKeyframes){
			if(selectedKeyframes->size() > 1){
				std::sort(selectedKeyframes->begin(), selectedKeyframes->end(), compareKeyframeView);
			}
			_makeInterpolationLine();
		}
	}
}

//KeyframeView* KeyframeCollectionView::addKeyframe(const glm::vec2& screenPos)
//{
//
//	std::cout << "new keyframe at "<< screenPos << std::endl;
// 	auto c = this->addChild<KeyframeView>("_k"+ofToString(keyFrames.size()), screenToLocal(screenPos) , this);
//	keyFrames.push_back(c);
//	updateKeyframeSort();
//	return c;
//}

KeyframeView* KeyframeCollectionView::addKeyframe(float value, uint64_t time)
{
//	std::cout << "new keyframe val: "<< value << " time: " << time << std::endl;
	auto c = this->addChild<KeyframeView>("_k"+ofToString(keyFrames.size()), value, time , this);
	keyFrames.push_back(c);
	updateKeyframeSort();
	return c;
}

//---------------------------------------------------------------------------------------------------------------------
bool KeyframeCollectionView::removeKeyframe(KeyframeView* k){
	if(k == nullptr) return false;
	
	auto c = removeChild(k);
	if(c){
		ofRemove(keyFrames, [&](KeyframeView*& key){return key == k;});
		if(_parentRegion)
		{
			auto selected = _selector->getSelectedElements(this);
			if(selected)
				ofRemove(*selected, [&](KeyframeView*& key){return key == k;});
		}
		updateKeyframeSort();
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeCollectionView::updateLayout()
{
	for(auto k: keyFrames)
	{
		if(k)k->_updatePosition();
	}
}

//void KeyframeCollectionView::onKeyboardEvent(DOM::KeyboardUIEventArgs& evt)
//{
//	if (this == evt.target())
//	{
//		if(_parentRegion) _selector->onKeyboardEvent(evt, this);
//	}
//}

void KeyframeCollectionView::removeElements(std::vector<KeyframeView*> & elementsToRemove)
{
	for(auto s: elementsToRemove)
	{
		
		if(s == nullptr) continue;
		
		ofNotifyEvent(removeKeyframeEvent, s, this);
		
	}
	updateKeyframeSort();
	
	elementsToRemove.clear();
	
}

TrackView* KeyframeCollectionView::parentTrack()
{
	if(_parentRegion) return _parentRegion->parentTrack();
	return nullptr;
}


void KeyframeCollectionView::onKeyboardEvent(DOM::KeyboardUIEventArgs& evt)
{
	if (this == evt.target())
    {
		if(_parentRegion) _selector->onKeyboardEvent(evt, this);
    }
}


} } // ofx::LineaDeTiempo

