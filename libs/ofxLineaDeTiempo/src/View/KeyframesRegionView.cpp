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

namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------------------------------------------------------
KeyframesRegionView::KeyframesRegionView(TrackView* parentTrack, RegionController *controller)
: RegionView(parentTrack, controller)
, Selector<KeyframeView>(this, this)
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
void KeyframesRegionView::onKeyframeDrag(KeyframeView* k, const glm::vec2& delta)
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
	_makeInterpolationLine();
}
std::vector<KeyframeView*> & KeyframesRegionView::getCollection()
{
	return keyFrames;
}
const std::vector<KeyframeView*> & KeyframesRegionView::getCollection() const
{
	return keyFrames;
}
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
		_SelectorPointerDown(local);

	}
	else if (e.type() == PointerEventArgs::POINTER_UP)
	{
//		_onPointerUp(e);
		auto wasSelecting = _SelectorPointerUp(local);
		if(!wasSelecting)
		{
			
//			auto p =  screenToLocal(e.screenPosition());
			auto p =  e.screenPosition();
			
//			std::cout << ofGetMouseX() << ", " << ofGetMouseY() << " -- " << p << endl;
			
			
			ofNotifyEvent(addKeyframeEvent, p, this);
			
//			addKeyframe();
			
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::selectKeyframe(KeyframeView* keyframe)
{
	selectElement(keyframe);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::unselectKeyframe(KeyframeView* k)
{
	unselectElement(k);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::unselectAllKeyframes()
{
	unselectAllElements();
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::selectAllKeyframes()
{
	selectAllElements();
}
//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::isKeyframeSelected(KeyframeView* k)
{
	return isElementSelected(k);
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframesRegionView::_makeInterpolationLine(){
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
void KeyframesRegionView::onDraw() const{
	Widget::onDraw();
	
	ofPushStyle();
	Selector<KeyframeView>::draw();
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
void KeyframesRegionView::updateKeyframeSort(){
	if(numChildren() > 1){
		std::sort(keyFrames.begin(), keyFrames.end(), compareKeyframeView);
	}
	auto & selectedKeyframes = getSelectedElements();
	
	if(selectedKeyframes.size() > 1){
		std::sort(selectedKeyframes.begin(), selectedKeyframes.end(), compareKeyframeView);
	}
	_makeInterpolationLine();
}
KeyframeView* KeyframesRegionView::addKeyframe(const glm::vec2& localPos)
{
	
	auto c = this->addChild<KeyframeView>("_k"+ofToString(keyFrames.size()), localPos , this);
	keyFrames.push_back(c);
	updateKeyframeSort();
	return c;
}

KeyframeView* KeyframesRegionView::addKeyframe(float value, uint64_t time)
{
	auto c = this->addChild<KeyframeView>("_k"+ofToString(keyFrames.size()), value, time , this);
	keyFrames.push_back(c);
	updateKeyframeSort();
	return c;
}

//---------------------------------------------------------------------------------------------------------------------
bool KeyframesRegionView::removeKeyframe(KeyframeView* k){
	if(k == nullptr) return false;

	auto c = removeChild(k);
	if(c){
		ofRemove(keyFrames, [&](KeyframeView*& key){return key == k;});
		ofRemove(getSelectedElements(), [&](KeyframeView*& key){return key == k;});
		
		updateKeyframeSort();


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

		if(s == nullptr) continue;
//		ofRemove(keyFrames, [&](KeyframeView*& key){return key == s;});
		
		ofNotifyEvent(removeKeyframeEvent, s, this);
		
	}
	updateKeyframeSort();
	
	sel.clear();
	
}

//void KeyframesRegionView::updateKeyframeTimeAndValue(KeyframeView* k)
//{
//	auto c = dynamic_cast<KeyframeRegionController*>(getController());
//	if(c)
//	{
//		c->updateKeyframeTimeAndValue(k);
//	}
//}

} } // ofx::LineaDeTiempo

