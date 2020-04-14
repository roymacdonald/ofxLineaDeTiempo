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
KeyframeView::KeyframeView(const std::string& id, float value, uint64_t time, KeyframeCollectionView * parentView, bool paramTypeIsVoid)
: Widget(id,0,0, ConstVars::DefaultKeyframeSize, ConstVars::DefaultKeyframeSize)
, _parentView(parentView)
, _time(time)
, _value(value)
, _bParamTypeIsVoid(paramTypeIsVoid)
{
	if(!_parentView)
	{
		std::cout << "null parentView\n";
	}
	
	setDraggable(true);
	if(!_bParamTypeIsVoid){
		setShapeDrawMode(MUI::ShapeDrawMode::ELLIPSE);
	}
	_updatePosition();
}


//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::onDraw() const 
{
	Widget::onDraw();
	if(isSelected()){
		ofPushStyle();
		ofFill();
//		ofSetColor(ConstVars::SelectedColor);
		ofSetColor(ofColor::yellow);
		if(_bParamTypeIsVoid)
		{
			ofDrawRectangle(1, 1, getWidth()-2, getHeight()-2);
		}
		else
		{
			ofPushMatrix();
			ofTranslate(getWidth() / 2, getHeight() / 2);
			ofDrawEllipse(0, 0, getWidth()-2, getHeight()-2);
			ofPopMatrix();
		}
		ofPopStyle();
	}
}

//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::setSelected(bool select)
{
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
    if(_parentView){
		
		DOM::ofRectangleHelper::keepInside(this, { 0,0, _parentView->getWidth(), _parentView->getHeight() });
		
		
		if(_parentView->isParamTypeIsBool() )
		{
			auto v = _parentView->keyframePositionToValue(screenToParentY(pointer.position().y));
			 ///TODO: This could probably be more efficient
			setCenterPosition({getX(), _parentView->keyframeValueToPosition(v)});
		}
		
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
uint64_t KeyframeView::getTime() const
{
	return _time;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_updatePosition()
{
	glm::vec2 pos;
	auto p = _parentView;
	
    if(p && p->parentTrack() && p->parentTrack()->getTimeRuler()){
//		auto m = (ConstVars::DefaultKeyframeSize*0.5);
		pos.y = p->keyframeValueToPosition(_value);
		
		auto s = p->parentTrack()->getTimeRuler()->timeToScreenPosition(_time);
		
		pos.x = p->screenToParent({s,0}).x;
		
		
		setCenterPosition(pos);
	}
}


bool KeyframeView::isSelected() const
{
	return _isSelected;
}


//---------------------------------------------------------------------------------------------------------------------
void KeyframeView::_updateValue()
{
	auto p = _parentView;
    if(p && p->parentTrack() && p->parentTrack()->getTimeRuler()){
	
		auto t = p->parentTrack()->getTimeRuler()->screenPositionToTime(getScreenCenterPosition().x);
		auto v = p->keyframePositionToValue(getCenterPosition().y);
		
		if(t != _time)
		{
			_time = t;
			ofNotifyEvent(timeChangedEvent, t, this);
		}
		if(!_bParamTypeIsVoid && v != _value)
		{
			_value = v;
			ofNotifyEvent(valueChangedEvent, v, this);
		}
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
//---------------------------------------------------------------------------------------------------------------------
bool KeyframeView:: isParamTypeVoid() const
{
	return _bParamTypeIsVoid;
}
} } // ofx::LineaDeTiempo
