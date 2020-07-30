//
//  Header.h
//  example-basic
//
//  Created by Roy Macdonald on 5/2/20.
//

#pragma once


#include "ofx/DOM/Element.h"
#include "MUI/OrientedElement.h"
#include "MUI/Button.h"
#include "LineaDeTiempo/Controller/TimeControl.h"

namespace ofx {
namespace LineaDeTiempo {

class TracksPanel;
//class TimeControl;

class AbstractTimeControlButton
{
public:
	AbstractTimeControlButton(TimeControl* timeControl);
	virtual ~AbstractTimeControlButton() = default;

	virtual void _setButtonIcon() = 0;

protected:

	TimeControl* _timeControl = nullptr;
	ofEventListener _listener;

	virtual void _setListeners() = 0;

	ofPath _getButtonLabel(std::string label, DOM::Element* e);

	ofRectangle _getButtonRect(DOM::Element* e);
};


class BaseTimeControlButton 
: public AbstractTimeControlButton
, public MUI::Button
{
public:
	BaseTimeControlButton(const std::string& name, const ofRectangle& shape, TimeControl* timeControl);

	~BaseTimeControlButton () = default;

protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& )= 0;
	virtual void _setListeners() override;
};


class BaseTimeControlToogle 
: public AbstractTimeControlButton
, public MUI::ToggleButton
{
public:
	BaseTimeControlToogle(const std::string& name, const ofRectangle& shape, TimeControl* timeControl);
	~BaseTimeControlToogle () = default;

protected:
	virtual void _valueChanged(int& )= 0;
	virtual void _setListeners() override;
};





class PlayPauseToggle
: public BaseTimeControlToogle
{
public:
	PlayPauseToggle(const ofRectangle& shape, TimeControl* timeControl);
	~PlayPauseToggle() = default;
protected:
	bool _bIgnoreTimeControlStateChange = false;
	void _timeControlStateChanged(TimeControlState& s);
	ofEventListener _stateListener;
	virtual void _valueChanged(int& ) override;
	virtual void _setButtonIcon() override;
};
class LoopToggle
: public BaseTimeControlToogle
{
public:
	LoopToggle(const ofRectangle& shape, TimeControl* timeControl);
	~LoopToggle() = default;
protected:
	virtual void _valueChanged(int& ) override;
	virtual void _setButtonIcon() override;
};
class StopButton
: public BaseTimeControlButton
{
public:
	StopButton(const ofRectangle& shape, TimeControl* timeControl);
	~StopButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};
class TriggerButton
: public BaseTimeControlButton
{
public:
	TriggerButton(const ofRectangle& shape, TimeControl* timeControl);
	~TriggerButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};
class SetInButton
: public BaseTimeControlButton
{
public:
	SetInButton(const ofRectangle& shape, TimeControl* timeControl);
	~SetInButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};
class SetOutButton
: public BaseTimeControlButton
{
public:
	SetOutButton(const ofRectangle& shape, TimeControl* timeControl);
	~SetOutButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};
class GotoInButton
: public BaseTimeControlButton
{
public:
	GotoInButton(const ofRectangle& shape, TimeControl* timeControl);
	~GotoInButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};
class GotoOutButton
: public BaseTimeControlButton
{
public:
	GotoOutButton(const ofRectangle& shape, TimeControl* timeControl);
	~GotoOutButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};
class JumpForwardsButton
: public BaseTimeControlButton
{
public:
	JumpForwardsButton(const ofRectangle& shape, TimeControl* timeControl, TracksPanel* tracksPanel);
	~JumpForwardsButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
	TracksPanel* _tracksPanel = nullptr;
};
class JumpBackwardsButton
: public BaseTimeControlButton
{
public:
	JumpBackwardsButton(const ofRectangle& shape, TimeControl* timeControl, TracksPanel* tracksPanel);
	~JumpBackwardsButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
	TracksPanel* _tracksPanel = nullptr;
};
class SetTotalTimeButton
: public BaseTimeControlButton
{
public:
	SetTotalTimeButton(const ofRectangle& shape, TimeControl* timeControl);
	~SetTotalTimeButton() = default;
protected:
	virtual void _buttonPressed(MUI::ButtonEventArgs& ) override;
	virtual void _setButtonIcon() override;
};


class TimeDisplay
: public DOM::Element
{
public:
	TimeDisplay(const ofRectangle& shape, TimeControl* timeControl);

	virtual void updateLayout() override;
	
	virtual void onDraw() const override;

protected:
		
		mutable std::string _timeText;

		void _makeTimeText() const;
		
		glm::vec2 _textPos;
	
	TimeControl* _timeControl = nullptr;
	

};

	
	enum TimeControlViewElement
	{
		PLAY_PAUSE_TOGGLE,
		LOOP_TOGGLE,
		STOP_BUTTON,
		TRIGGER_BUTTON,
		SET_IN_BUTTON,
		SET_OUT_BUTTON,
		GOTO_IN_BUTTON,
		GOTO_OUT_BUTTON,
		JUMP_FORWARDS_BUTTON,
		JUMP_BACKWARDS_BUTTON,
		SET_TOTAL_TIME_BUTTON,
		TIME_DISPLAY,
		SPACER
	};


class TimeControlView
: public DOM::Element
, public DOM::OrientedElement
{
public:
	TimeControlView(const ofRectangle& shape, TracksPanel* tracksPanel,  TimeControl* timeControl, DOM::Orientation orientation);
	
	~TimeControlView() = default;
	

	void add(TimeControlViewElement e);

	virtual void updateLayout() override;
	
	
	void setButtonsSpacing(float spacing);
	float getButtonsSpacing() const;
	
protected:
		
	float _buttonsMargin = 3;
	
	TimeControl* _timeControl = nullptr;
	TracksPanel * _tracksPanel = nullptr;
	
	
	DOM::Element* addSpacer();
	size_t _numSpacers = 0;
	
};

}} //ofx::LineaDeTiempo
