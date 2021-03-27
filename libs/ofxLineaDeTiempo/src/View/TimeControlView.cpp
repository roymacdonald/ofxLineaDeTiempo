//
//  TimeControlView.cpp
//  example-basic
//
//  Created by Roy Macdonald on 5/2/20.
//


#include "LineaDeTiempo/View/TimeControlView.h"
#include "LineaDeTiempo/View/TimeModifierView.h"

#include "LineaDeTiempo/View/TracksPanel.h"
#include "LineaDeTiempo/Utils/ConstVars.h"
#include "LineaDeTiempo/Utils/FontUtils.h"
#include "ofxTimecode.h"


namespace ofx {
namespace LineaDeTiempo {

//-----------------------------------------------------------------------------------------------------
AbstractTimeControlButton::AbstractTimeControlButton(TimeControl* timeControl)
:_timeControl(timeControl)
{
	
}


ofRectangle AbstractTimeControlButton::_getButtonRect(DOM::Element* e)
{
	ofRectangle  pathRect;
	if(e)
	{
	auto w = e->getWidth();
	pathRect.set(0,0,w,w);
	pathRect.scaleFromCenter(0.7);
	}
	return  pathRect;
}

ofRectangle getPathsBoundingBox(const std::vector<ofPath> & paths)
{
	ofRectangle r;
	bool bFirst = true;
	for(auto& p: paths)
	{
		auto t = p.getTessellation();
		
		for(auto& v: t.getVertices())
		{
			if(bFirst)
			{
				r.set(v,0,0);
				bFirst = false;
			}
			else
			{
				r.growToInclude(v);
			}
		}
	}
	return r;
}


ofPath AbstractTimeControlButton::_getButtonLabel(std::string label, DOM::Element* e)
{
	ofTrueTypeFont f;
	auto pathRect = _getButtonRect(e);
	f.load(	MUI::TrueTypeFontSettings::DEFAULT_FONT,pathRect.height, true, true, true);
		
	auto paths = f.getStringAsPoints(label);
	auto r = getPathsBoundingBox(paths);
	ofPath p;
	if(paths.size())
	{
		p = paths[0];
		for(size_t i = 1; i < paths.size(); ++i)
		{
			p.append(paths[i]);
		}
		p.translate(pathRect.getCenter() - r.getCenter());

	}
	return p;
}

//-----------------------------------------------------------------------------------------------------
BaseTimeControlButton::BaseTimeControlButton(const std::string& name, const std::string& tooltip, const ofRectangle& shape,TimeControl* timeControl)
: AbstractTimeControlButton(timeControl)
, MUI::Button(name, shape.x, shape.y, shape.width, shape.height)
, TooltipOwner(this, tooltip)
{
	_setListeners();
}


void BaseTimeControlButton::_setListeners()
{
	_listener = this->buttonPressed.event().newListener(this, &BaseTimeControlButton::_buttonPressed);
	
}


void BaseTimeControlButton::onUpdate()
{
	MUI::Widget::onUpdate();
	_updateShowTooltip( isPointerMoving(), isPointerOver(), getOverPointers(), document());
	
}


//-----------------------------------------------------------------------------------------------------
BaseTimeControlToogle::BaseTimeControlToogle(const std::string& name, const std::string& tooltip, const ofRectangle& shape, TimeControl* timeControl)
: AbstractTimeControlButton(timeControl)
, MUI::ToggleButton(name, shape.x, shape.y, shape.width, shape.height)
, TooltipOwner(this, tooltip)
{
	_setListeners();
}


void BaseTimeControlToogle::_setListeners()
{
	_listener = this->valueChanged.newListener(this, &BaseTimeControlToogle::_valueChanged);
	

}


void BaseTimeControlToogle::onUpdate()
{
	Widget::onUpdate();
	_updateShowTooltip(isPointerMoving(), isPointerOver(), getOverPointers(), document());
}



//-----------------------------------------------------------------------------------------------------
PlayPauseToggle::PlayPauseToggle(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlToogle("PlayPause Toggle", "Play/Pause Toggle", shape, timeControl)
{
	_setButtonIcon();
	_bChangeRoleOnValueChange = false;
	_bIgnoreTimeControlStateChange = true;
	this->setValue(1);
	_bIgnoreTimeControlStateChange = false;
	_stateListener = _timeControl->stateChangeEvent.newListener(this, &PlayPauseToggle::_timeControlStateChanged);
	
	
}


void PlayPauseToggle::_valueChanged(int& v)
{
if(!_bIgnoreTimeControlStateChange && _timeControl)
	{
		if(v == 1)
		{
			_timeControl->pause();
		}
		else
		{
			_timeControl->play();
		}
	}
	
}

void PlayPauseToggle::_timeControlStateChanged(TimeControlState& s)
{
	_bIgnoreTimeControlStateChange = true;
	this->setValue(s==PLAYING? 0: 1);
	_bIgnoreTimeControlStateChange = false;
}


void PlayPauseToggle::_setButtonIcon()
{
	///////// Play
	auto pathRect = _getButtonRect(this);
			ofPath playPath;
			float x =pathRect.x + sin(ofDegToRad(60))*pathRect.width;
			playPath.triangle(pathRect.getMin(), {x , pathRect.getCenter().y}, pathRect.getBottomLeft());

			
			///////// Pause
			ofPath path;
			
			auto r = pathRect;
			r.width*= 0.33;
			
			path.rectangle(r);
			r.x = pathRect.getMaxX() - r.width;
			path.rectangle(r);
			this->setIcon(path, 0);
			
			this->setIcon(playPath, 1);
			
}

//-----------------------------------------------------------------------------------------------------
LoopToggle::LoopToggle(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlToogle("Loop Toggle", "Looping Toogle", shape, timeControl)
{
	_setButtonIcon();
}


void LoopToggle::_valueChanged(int& v)
{
if(_timeControl)_timeControl->setLooping(v==1);
}


void LoopToggle::_setButtonIcon()
{
	this->setIcon(_getButtonLabel("L", this));
}

//-----------------------------------------------------------------------------------------------------
StopButton::StopButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Stop Button", "Stop", shape, timeControl)
{
	_setButtonIcon();
}


void StopButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	if(_timeControl)_timeControl->stop();
}


void StopButton::_setButtonIcon()
{
			///////// STOP
	auto pathRect = _getButtonRect(this);
			ofPath path;
			path.rectangle(pathRect);
			this->setIcon(path);

}

//-----------------------------------------------------------------------------------------------------
TriggerButton::TriggerButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Trigger Button", "Play from IN time", shape, timeControl)
{
	_setButtonIcon();
}


void TriggerButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
if(_timeControl)_timeControl->trigger();
}


void TriggerButton::_setButtonIcon()
{
	this->setIcon(_getButtonLabel("x", this));
}

//-----------------------------------------------------------------------------------------------------
SetInButton::SetInButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Set In Button", "Set IN time", shape, timeControl)
{
	_setButtonIcon();
}


void SetInButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	if(_timeControl)_timeControl->setInTime(_timeControl->getCurrentTime());
}


void SetInButton::_setButtonIcon()
{
	this->setIcon(_getButtonLabel("I", this));
}

//-----------------------------------------------------------------------------------------------------
SetOutButton::SetOutButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Set Out Button", "Set OUT time", shape, timeControl)
{
	_setButtonIcon();
}


void SetOutButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	if(_timeControl)_timeControl->setOutTime(_timeControl->getCurrentTime());
}


void SetOutButton::_setButtonIcon()
{
	this->setIcon(_getButtonLabel("O", this));
}

//-----------------------------------------------------------------------------------------------------
GotoInButton::GotoInButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Goto In Button", "Go to IN time", shape, timeControl)
{
	_setButtonIcon();
}


void GotoInButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	if(_timeControl)_timeControl->setCurrentTime(_timeControl->isInTimeEnabled()?_timeControl->getInTime():0);
}


void GotoInButton::_setButtonIcon()
{
			ofPath path;
			auto pathRect = _getButtonRect(this);
			float x =pathRect.x + sin(ofDegToRad(60))*pathRect.width;
			path.triangle(pathRect.getMin(), {x , pathRect.getCenter().y}, pathRect.getBottomLeft());
			
			auto r = pathRect;
			r.width*= 0.33;
			r.x =x;
			r.width = pathRect.getMaxX() - x;
			path.rectangle(r);
			
			path.scale(-1, 1);
			path.translate({pathRect.width + (pathRect.x*2), 0,0});
			this->setIcon(path);
}

//-----------------------------------------------------------------------------------------------------
GotoOutButton::GotoOutButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Goto Out Button", "Go to OUT time", shape, timeControl)
{
	_setButtonIcon();
}


void GotoOutButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	if(_timeControl)_timeControl->setCurrentTime(_timeControl->isOutTimeEnabled()?_timeControl->getOutTime():_timeControl->getTotalTime());
}


void GotoOutButton::_setButtonIcon()
{

			ofPath path;
			auto pathRect = _getButtonRect(this);
			float x =pathRect.x + sin(ofDegToRad(60))*pathRect.width;
			path.triangle(pathRect.getMin(), {x , pathRect.getCenter().y}, pathRect.getBottomLeft());
			
			auto r = pathRect;
			r.width*= 0.33;
			r.x =x;
			r.width = pathRect.getMaxX() - x;
			path.rectangle(r);
			
			this->setIcon(path);

}


void _timeJumpByVisibleTimeFactor(float factor, TimeControl* _timeControl,  TracksPanel* _tracksPanel )
{
	if(_timeControl && _tracksPanel && _tracksPanel->getTimeRuler())
	{
		auto s = _tracksPanel->getTimeRuler()->getVisibleTimeRange().span();
		
		float jumpSpan = s/factor;
		if(jumpSpan < 0.0f) // is negative
		{
			uint64_t j = (jumpSpan * -1);
			if(_timeControl->getCurrentTime() < j)
			{
				_timeControl->setCurrentTime(0);
			}
		}
		else
		{
			_timeControl->setCurrentTime(_timeControl->getCurrentTime() + s/factor);
		}
	}
}

//-----------------------------------------------------------------------------------------------------
JumpForwardsButton::JumpForwardsButton(const ofRectangle& shape, TimeControl* timeControl, TracksPanel* tracksPanel)
: BaseTimeControlButton("Jump Forwards Button", "Jump forwards", shape, timeControl)
, _tracksPanel(tracksPanel)
{
	_setButtonIcon();
}


void JumpForwardsButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	_timeJumpByVisibleTimeFactor(10.f, _timeControl, _tracksPanel);
}


void JumpForwardsButton::_setButtonIcon()
{
	ofPath path;
	auto pathRect = _getButtonRect(this);
			path.triangle(pathRect.getMin(), pathRect.getCenter(), pathRect.getBottomLeft());
			glm::vec3 w2 (pathRect.getWidth()/2, 0,0);
			path.triangle(pathRect.getMin() + w2, pathRect.getCenter() + w2, pathRect.getBottomLeft() + w2);
			this->setIcon(path);
}

//-----------------------------------------------------------------------------------------------------
JumpBackwardsButton::JumpBackwardsButton(const ofRectangle& shape, TimeControl* timeControl, TracksPanel* tracksPanel)
: BaseTimeControlButton("Jump Backwards Button", "Jump backwards", shape, timeControl)
, _tracksPanel(tracksPanel)
{
	_setButtonIcon();
}


void JumpBackwardsButton::_buttonPressed(MUI::ButtonEventArgs& args)
{
	_timeJumpByVisibleTimeFactor(-10.f, _timeControl, _tracksPanel);
}


void JumpBackwardsButton::_setButtonIcon()
{
	auto pathRect = _getButtonRect(this);
			ofPath path;
			auto c = pathRect.getCenter();
			path.triangle(pathRect.getTopRight(), c, pathRect.getBottomRight());
			
			path.triangle({pathRect.getMinX(), c.y}, {c.x, pathRect.getMinY()}, {c.x, pathRect.getMaxY()});
			this->setIcon(path);
}

//-----------------------------------------------------------------------------------------------------
SetTotalTimeButton::SetTotalTimeButton(const ofRectangle& shape, TimeControl* timeControl)
: BaseTimeControlButton("Set Total TimeButton", "Set total time", shape, timeControl)
{
	_setButtonIcon();
}


void SetTotalTimeButton::_buttonPressed(MUI::ButtonEventArgs& args)
{	
	auto d = dynamic_cast<TimelineDocument*>( document());
	if(d)
	{
		auto m = d->getModal();
		_modalTimeModifier = m->add<ModalTimeModifier>(this,  _timeControl->getTotalTime());
		auto sp = getScreenPosition();
		sp.x -= _modalTimeModifier->container->getWidth();
		
		_modalTimeModifier->setPosition(m->screenToLocal(sp));
		m->useBackgroundOverlay({0,80});
		
		timeSetListener = _modalTimeModifier->getTimeModifier()->valueSetEvent.newListener(this, &SetTotalTimeButton::_onTimeSet);
	}
}

void SetTotalTimeButton::_onTimeSet()
{
	if(_timeControl && _modalTimeModifier)
	{
		_timeControl->setTotalTime(ofxTimecode::millisForTimecode(_modalTimeModifier->getTimeModifier()->getTimecodeString()));
		_modalTimeModifier->expire();
		_modalTimeModifier = nullptr;
		timeSetListener.unsubscribe();
	}
}

void SetTotalTimeButton::_setButtonIcon()
{
	this->setIcon(_getButtonLabel("T", this));
}

	
		
//-----------------------------------------------------------------------------------------------------

TimeDisplay::TimeDisplay(const ofRectangle& shape, TimeControl* timeControl)
: DOM::Element("TimeDisplay", shape)
, _timeControl(timeControl)
{
	updateLayout();
}


void TimeDisplay::updateLayout()
{

	_makeTimeText();
	
	ofBitmapFont _bf;
	
	auto bb = _bf.getBoundingBox(_timeText, 0, 0);
	
	auto y = bb.y;
	
	auto s = getShape();
	s.x = 0;
	s.y = 0;
//	s.y = s.getCenter().y;
//	s.height*=0.5;
	bb.alignTo(s);
	
	
	_textPos = {bb.x, bb.y - y};
}


void TimeDisplay::onDraw() const
{
	_makeTimeText();
	
	ofPushStyle();
	
	ofSetColor(getStyles()->getColor(MUI::Styles::ROLE_TEXT, MUI::Styles::STATE_NORMAL));
	ofDrawBitmapString( _timeText, _textPos);
	
	
	ofPopStyle();
	
}

void TimeDisplay::_makeTimeText() const
{
	auto t =_timeControl->getCurrentTime();
	_timeText = ofxTimecode::timecodeForMillis(t);
	
}
		





TimeControlView::TimeControlView(const ofRectangle& shape, TracksPanel* tracksPanel,  TimeControl* timeControl, DOM::Orientation orientation)
: DOM::Element( "TimeControlView", shape)
, DOM::OrientedElement(orientation)
, _tracksPanel(tracksPanel)
, _timeControl(timeControl)
{
	
	updateLayout();
	
}


void TimeControlView::add(TimeControlViewElement e)
{
	
	auto s = getSize();
	
	auto w = s[1-dimIndex()]*0.7;
	
	glm::vec2 p (0,0);
	
	p[1-dimIndex()] = (s[1-dimIndex()] - w)/2;
	
	ofRectangle shape(p,w,w);
	switch(e){
		case PLAY_PAUSE_TOGGLE: addChild<PlayPauseToggle>(shape, _timeControl); break;
		case LOOP_TOGGLE: addChild<LoopToggle>(shape, _timeControl); break;
		case STOP_BUTTON: addChild<StopButton>(shape, _timeControl); break;
		case TRIGGER_BUTTON: addChild<TriggerButton>(shape, _timeControl); break;
		case SET_IN_BUTTON: addChild<SetInButton>(shape, _timeControl); break;
		case SET_OUT_BUTTON: addChild<SetOutButton>(shape, _timeControl); break;
		case GOTO_IN_BUTTON: addChild<GotoInButton>(shape, _timeControl); break;
		case GOTO_OUT_BUTTON: addChild<GotoOutButton>(shape, _timeControl); break;
		case JUMP_FORWARDS_BUTTON: addChild<JumpForwardsButton>(shape, _timeControl, _tracksPanel); break;
		case JUMP_BACKWARDS_BUTTON: addChild<JumpBackwardsButton>(shape, _timeControl, _tracksPanel); break;
		case SET_TOTAL_TIME_BUTTON: addChild<SetTotalTimeButton>(shape, _timeControl); break;
		case TIME_DISPLAY: addChild<TimeDisplay>(shape, _timeControl);	 break;
		case SPACER: addSpacer(); addSpacer(); break;
			
	}
}


void TimeControlView::setButtonsSpacing(float spacing)
{
	_buttonsMargin = spacing;
	updateLayout();
}


float TimeControlView::getButtonsSpacing() const
{
	return _buttonsMargin;
}
	


DOM::Element* TimeControlView::addSpacer()
{
	
	++_numSpacers;
	auto sp = addChild<DOM::Element>("spacer",0,0,0,0);
	return sp;

}



void TimeControlView::updateLayout()
{
	auto child = children();
	
	
	float totalButtonsSize = _buttonsMargin;
	for(auto c: child)
	{
		if(c)
		{
			totalButtonsSize += c->getSize()[dimIndex()] + _buttonsMargin;
		}
	}
	
	float spacerWidth = (getSize()[dimIndex()] - totalButtonsSize )/_numSpacers;
	
	float x = _buttonsMargin;
	for(auto b: child)
	{
		auto p = b->getPosition();
		p[dimIndex()] = x;
		b->setPosition(p);

		if(b->getId() == "spacer" && ofIsFloatEqual(b->getSize()[dimIndex()], 0.f))
		{
			x += spacerWidth + _buttonsMargin;
		}
		else
		{
			if(!b->isHidden())
				x += b->getSize()[dimIndex()] + _buttonsMargin;
		}
	}
	
	
}


}} //ofx::LineaDeTiempo


