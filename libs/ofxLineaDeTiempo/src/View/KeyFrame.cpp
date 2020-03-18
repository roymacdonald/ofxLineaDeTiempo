//
//  KeyFrame.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#include "KeyFrame.h"
#include "ofRectangleHelper.h"
#include "KeyFrames.h"
#include "TrackView.h"
namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------------------------------------------------------
float KeyFrame::defaultKeyFrameSize = 15;
//---------------------------------------------------------------------------------------------------------------------

KeyFrame::KeyFrame(const std::string& id, const glm::vec2& pos):
Widget(id,0,0, defaultKeyFrameSize, defaultKeyFrameSize)
{
	setDraggable(true);
	setShapeDrawMode(MUI::ShapeDrawMode::ELLIPSE);
	setCenterPosition(pos);
	
	_updateValue();

}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrame::onDraw() const {
	Widget::onDraw();
	if(bSelected){
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
void KeyFrame::setSelected(bool select){
	auto p = dynamic_cast<KeyFrames*>(parent());
    if(p){
        if(!bSelected && select){
          
			if(!ofGetKeyPressed(OF_KEY_SHIFT)){
				p->unselectAllKeyframes();
			}
			bSelected = true;
            p->selectKeyframe(this);
        }else if(bSelected && !select){
            bSelected = false;
            p->unselectKeyframe(this);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
void KeyFrame::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto delta = getPosition();
	
	Widget::_onDragging(pointer);
	
	auto p = dynamic_cast<KeyFrames*>(parent());
    if(p){
		
		DOM::ofRectangleHelper::keepInside(this, ofRectangle(0,0, p->getWidth(), p->getHeight()));
			
		_updateValue();
		
		delta = delta - getPosition();
		
		p->onKeyFrameDrag(this, delta);
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrame::_updatePosition()
{
	glm::vec2 pos;
	auto p = dynamic_cast<KeyFrames*>(parent());
    if(p && p->parentTrack()){
		pos.y = ofMap(_value, 0, 1, 0 , p->getHeight() - defaultKeyFrameSize, true) + (defaultKeyFrameSize*0.5);
		
		pos.x = screenToParent({p->parentTrack()->timeToScreenPosition(_time),0}).x;
		setCenterPosition(pos);
	}
}
//---------------------------------------------------------------------------------------------------------------------
float KeyFrame::getValue() const 
{
	return _value;
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t KeyFrame::getTime() const{
	return _time;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrame::_updateValue(){
	auto p = dynamic_cast<KeyFrames*>(parent());
    if(p && p->parentTrack()){
		_time = p->parentTrack()->screenPositionToTime(getScreenCenterPosition().x);
		_value = ofMap(getY(), 0 , p->getHeight() - defaultKeyFrameSize, 0, 1, true);
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrame::_onPointerEvent(DOM::PointerUIEventArgs& e)
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
bool KeyFrame::isSelected(){
    return bSelected;
}

} } // ofx::LineaDeTiempo
