//
//  TimeModifierView.hpp
//  example-basic
//
//  Created by Roy Macdonald on 5/5/20.
//

#pragma once

#include "ofRectangle.h"
#include "ofEvents.h"
#include "MUI/Widget.h"


namespace ofx {
namespace LineaDeTiempo {


class TimeModifier;

class TimeSubDiv
: public MUI::Widget
{
public:
	TimeSubDiv();
	virtual ~TimeSubDiv();
	void setup(const std::string& name, int value,  size_t numDigits, size_t maxValue, TimeSubDiv* larger, TimeSubDiv* smaller);

	
	void enableKeys();
	void disableKeys();
	
	int value = 0;
	
	void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt);

	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;

	virtual void onDraw() const override;
	
	bool hasKeysEnabled()const;

	
	
	std::string getValueAsString() const;
	
protected:
	
	bool _bNeedsValueReset = true;
	
	void _enableParentKeys();
	
	std::string _delimiter = "";
	
	void _enableLarger();
	

	void _enableSmaller();
		
	size_t _currentDigitIndex = 1;
	int _maxValue = 10;
	
	TimeSubDiv* _smaller = nullptr;
	TimeSubDiv* _larger = nullptr;
	
	
	size_t _numDigits = 2;
	
	bool _bKeysEnabled = false;
	
	float _fontYOffset = 0;
	
	friend class TimeModifier;
};

class TimeModifier
: public MUI::Widget
{
public:
	
	TimeModifier(const std::string& id, const ofRectangle& shape, size_t initialMillis);
	
	virtual ~TimeModifier();
	
	
	virtual void onDraw() const override;
	
	void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt);
		
	
	void enableKeys();
	void disableKeys();

	ofEvent<void> valueSetEvent;
	
	std::string getTimecodeString() const;
	
protected:
	
	bool _subDivsKeysEnabled() const;
	
	std::vector<TimeSubDiv*> _subDivs;

	
};

} } // ofx::LineaDeTiempo
