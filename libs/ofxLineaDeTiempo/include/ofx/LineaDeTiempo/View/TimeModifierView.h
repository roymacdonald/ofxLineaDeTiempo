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
	void setup(const std::string& name, size_t numDigits, size_t maxValue, TimeSubDiv* larger, TimeSubDiv* smaller);

//	void keyPressed(ofKeyEventArgs & args);

	
	void enableKeys();
	void disableKeys();
	
	int value = 0;
	
	void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt);

	virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;
//	virtual void _onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e) override;
	
//	const ofRectangle& getShape() const;
	
//	void draw();
	virtual void onDraw() const override;
	
	bool hasKeysEnabled()const;

	void printCurrentDigitIndex();
	
protected:
	
	bool _bNeedsValueReset = true;
	
	void _enableParentKeys();
	
	std::string _delimiter = "";
	
	void _enableLarger();
	

	void _enableSmaller();
	
//	ofRectangle _shape;
	
	size_t _currentDigitIndex = 1;
	int _maxValue = 10;
	
	TimeSubDiv* _smaller = nullptr;
	TimeSubDiv* _larger = nullptr;
	
//	ofEventListener listener;
	
	size_t _numDigits = 2;
	
	bool _bKeysEnabled = false;
	
	float _fontYOffset = 0;
	
	friend class TimeModifier;
};

class TimeModifier
: public MUI::Widget
{
public:
	TimeModifier();
	
	void mousePressed(ofMouseEventArgs& args);
	
	
//	void draw();
	virtual void onDraw() const override;
	
//	const ofRectangle& getShape() const;
		
//	void keyPressed(ofKeyEventArgs & args);
	void onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt);
		
	
	void enableKeys();
	void disableKeys();

	ofEvent<void> valueSetEvent;
	
	
protected:
	
	bool _subDivsKeysEnabled() const;

//	ofEventListener mouseListener;
//	ofEventListener keysListener;
	
	
	std::vector<TimeSubDiv*> _subDivs;
//	ofRectangle _shape;
	
};

} } // ofx::LineaDeTiempo
