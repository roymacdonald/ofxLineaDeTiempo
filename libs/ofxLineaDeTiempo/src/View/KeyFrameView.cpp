//
//  KeyFrame.cpp
//  keyframesTest
//
//  Created by Roy Macdonald on 2/14/20.
//

#include "LineaDeTiempo/View/KeyFrameView.h"
//#include "LineaDeTiempo/View/TrackView.h"
#include "ofRectangleHelper.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"
//#include "LineaDeTiempo/Controller/KeyframeController.h"

namespace ofx {
namespace LineaDeTiempo {
//---------------------------------------------------------------------------------------------------------------------
float KeyFrameView::defaultKeyFrameSize = 15;
//---------------------------------------------------------------------------------------------------------------------

KeyFrameView::KeyFrameView(const std::string& id, const glm::vec2& pos)
: Widget(id,0,0, defaultKeyFrameSize, defaultKeyFrameSize)
//, BaseHasController<KeyframeController>()
{
	setDraggable(true);
	setShapeDrawMode(MUI::ShapeDrawMode::ELLIPSE);
	setCenterPosition(pos);
	
	_updateValue();

}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrameView::onDraw() const {
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
void KeyFrameView::setSelected(bool select){
	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(p){
        if(!_isSelected && select){
          
			if(!ofGetKeyPressed(OF_KEY_SHIFT)){
				p->unselectAllKeyframes();
			}
			_isSelected = true;
            p->selectKeyframe(this);
        }else if(_isSelected && !select){
            _isSelected = false;
            p->unselectKeyframe(this);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
void KeyFrameView::_onDragging(const DOM::CapturedPointer& pointer)
{
	auto delta = getPosition();
	
	Widget::_onDragging(pointer);
	
	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(p){
		
		DOM::ofRectangleHelper::keepInside(this, ofRectangle(0,0, p->getWidth(), p->getHeight()));
			
		_updateValue();
		
		delta = delta - getPosition();
		
		p->onKeyFrameDrag(this, delta);
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrameView::_updatePosition()
{
	glm::vec2 pos;
	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(p && p->parentTrack()){
		pos.y = ofMap(_value, 0, 1, 0 , p->getHeight() - defaultKeyFrameSize, true) + (defaultKeyFrameSize*0.5);
		
		pos.x = screenToParent({p->parentTrack()->timeToScreenPosition(_time),0}).x;
		setCenterPosition(pos);
	}
}
//---------------------------------------------------------------------------------------------------------------------
float KeyFrameView::getValue() const
{
	return _value;
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t KeyFrameView::getTime() const{
	return _time;
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrameView::_updateValue(){
	auto p = dynamic_cast<KeyframesRegionView*>(parent());
    if(p && p->parentTrack()){
		_time = p->parentTrack()->screenPositionToTime(getScreenCenterPosition().x);
		_value = ofMap(getY(), 0 , p->getHeight() - defaultKeyFrameSize, 0, 1, true);
	}
}
//---------------------------------------------------------------------------------------------------------------------
void KeyFrameView::_onPointerEvent(DOM::PointerUIEventArgs& e)
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
//bool KeyFrameView::isSelected(){
//    return bSelected;
//}

} } // ofx::LineaDeTiempo
