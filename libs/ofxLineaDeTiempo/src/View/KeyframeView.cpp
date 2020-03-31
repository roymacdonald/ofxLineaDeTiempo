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

#include "LineaDeTiempo/Utils/ConstVars.h"


namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
KeyframeView::KeyframeView(const std::string& id, KeyframeCollectionView * parentView)
: Widget(id,0,0, DefaultKeyframeSize, DefaultKeyframeSize)
, _parentView(parentView)
{
	if(!_parentView)
	{
		std::cout << "null parentView\n";
	}
	
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
void KeyframeView::setSelectedNoEvents(bool selected)
{
	_isSelected = selected;
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto delta = getPosition();
	
	Widget::_onDragging(pointer);
		std::cout << "KeyframeView::_onDragging";
//	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(_parentView){
		
		std::cout << "xxx";
		
		DOM::ofRectangleHelper::keepInside(this, ofRectangle(0,0, _parentView->getWidth(), _parentView->getHeight()));
			
		_updateValue();
		
		delta = delta - getPosition();
		
		_parentView->onKeyframeDrag(this, delta);
	}
	std::cout << "\n";
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
		auto m = (DefaultKeyframeSize*0.5);
		pos.y = ofMap(_value, 0, 1, m , p->getHeight() -m, true);
		
//		pos.y = timeToLocalPosition()
		auto s = p->parentTrack()->timeToScreenPosition(_time);
		
		pos.x = p->screenToParent({s,0}).x;
		
//		std::cout << "time: " << _time << " value: " << _value << " t2s: " << s <<"  x: " << pos.x << "\n";
		
		
		setCenterPosition(pos);
	}
}


bool KeyframeView::isSelected() const
{
	return _isSelected;
}


//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_updateValue(){
//	auto p = dynamic_cast<KeyframesRegionView*>(parent());
	std::cout << "KeyframeView::_updateValue";
	auto p = _parentView;
    if(p && p->parentTrack()){
		std::cout << "xxx";
		auto t = p->parentTrack()->screenPositionToTime(getScreenCenterPosition().x);
		auto v = ofMap(getY(), 0 , p->getHeight() - DefaultKeyframeSize, 0, 1, true);
		
		if(t != _time)
		{
			_time = t;
			ofNotifyEvent(timeChangedEvent, t, this);
		}
		if(v != _value)
		{
			_value = v;
			ofNotifyEvent(valueChangedEvent, v, this);
		}
		
	}
	std::cout << "\n";
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
