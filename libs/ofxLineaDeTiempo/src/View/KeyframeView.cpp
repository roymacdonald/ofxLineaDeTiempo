//
//  Keyframe.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/View/TrackView.h"
#include "ofRectangleHelper.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"

//#include "LineaDeTiempo/Controller/KeyframeController.h"

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------------------------------------------------------
float KeyframeView::defaultKeyframeSize = 15;
//---------------------------------------------------------------------------------------------------------------------
KeyframeView::KeyframeView(const std::string& id, KeyframeCollectionView * parentView)
: Widget(id,0,0, defaultKeyframeSize, defaultKeyframeSize)
, _parentView(parentView)
{
	setDraggable(true);
	setShapeDrawMode(MUI::ShapeDrawMode::ELLIPSE);
}
KeyframeView::KeyframeView(const std::string& id, float value, uint64_t time, KeyframeCollectionView * parentView)
: KeyframeView(id, parentView)
{
	_time = time;
	_value = value;
	_updatePosition();
}


//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::onDraw() const {
	Widget::onDraw();
	if(isSelected()){
		ofPushStyle();
		ofPushMatrix();
		ofFill();
		ofSetColor(ofColor::yellow);
		ofTranslate(getWidth() / 2, getHeight() / 2);
		ofDrawEllipse(0, 0, getWidth()-2, getHeight()-2);
		ofPopMatrix();
		ofPopStyle();
	}
	
	ofDrawBitmapString(ofToString(getValue()) +"\n"+ofToString(getTime()),  20,  getHeight() );
	
	
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::setSelected(bool select){
//	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(_parentView){
        if(!_isSelected && select){
			_isSelected = true;
            _parentView->selectKeyframe(this);
        }else if(_isSelected && !select){
            _isSelected = false;
            _parentView->unselectKeyframe(this);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto delta = getPosition();
	
	Widget::_onDragging(pointer);
	
//	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(_parentView){
		
		DOM::ofRectangleHelper::keepInside(this, ofRectangle(0,0, _parentView->getWidth(), _parentView->getHeight()));
			
		_updateValue();
		
		delta = delta - getPosition();
		
		_parentView->onKeyframeDrag(this, delta);
	}
}
//---------------------------------------------------------------------------------------------------------------------
float KeyframeView::getValue() const
{
	return _value;
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t KeyframeView::getTime() const{
	return _time;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_updatePosition()
{
	glm::vec2 pos;
	auto p = _parentView;
	
    if(p && p->parentTrack()){
		auto m = (defaultKeyframeSize*0.5);
		pos.y = ofMap(_value, 0, 1, m , p->getHeight() -m, true);
		
//		pos.y = timeToLocalPosition()
		auto s = p->parentTrack()->timeToScreenPosition(_time);
		
		pos.x = p->screenToParent({s,0}).x;
		
//		std::cout << "time: " << _time << " value: " << _value << " t2s: " << s <<"  x: " << pos.x << "\n";
		
		
		setCenterPosition(pos);
	}
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_updateValue(){
//	auto p = dynamic_cast<KeyframesRegionView*>(parent());
	auto p = _parentView;
    if(p && p->parentTrack()){
		auto t = p->parentTrack()->screenPositionToTime(getScreenCenterPosition().x);
		auto v = ofMap(getY(), 0 , p->getHeight() - defaultKeyframeSize, 0, 1, true);
		
		if(t != _time) ofNotifyEvent(timeChangedEvent, t, this);
		if(v != _value) ofNotifyEvent(valueChangedEvent, v, this);
		
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
    if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
		_moved = false;
    }
    else if (e.type() == PointerEventArgs::POINTER_MOVE)
    {
        if (_isDragging)
        {
			_moved = true;
			setSelected(true);
            if (!capturedPointers().empty())
            {
				this->_onDragging(*capturedPointers().begin());
            }
            else
            {
                ofLogError("Widget::_onPointerEvent") << "No captured pointers to drag with.";
            }
        }
    }
	else if (e.type() == PointerEventArgs::POINTER_UP)
	{
		
		if(!_moved){
			setSelected(!isSelected());
		}
		
		_moved = false;
	}
    else if (e.type() == PointerEventArgs::POINTER_OVER)
    {
        _isPointerOver = true;
    }
    else if (e.type() == PointerEventArgs::POINTER_OUT)
    {
        _isPointerOver = false;
    }
    else
    {
        // unhandled.
    }
}
////---------------------------------------------------------------------------------------------------------------------
//bool KeyframeView::isSelected(){
//    return bSelected;
//}

} } // ofx::LineaDeTiempo
