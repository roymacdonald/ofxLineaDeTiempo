//
//  TimeModifierView.cpp
//  example-basic
//
//  Created by Roy Macdonald on 5/5/20.
//

#include "LineaDeTiempo/View/TimeModifierView.h"
#include "ofBitmapFont.h"
#include "DOM/Document.h"
#include "ofxTimecode.h"

namespace ofx {
namespace LineaDeTiempo {


TimeSubDiv::TimeSubDiv()
: MUI::Widget("TimeSubDiv",0,0,0,0)
{
	
}


TimeSubDiv::~TimeSubDiv()
{
	disableKeys();
}


void TimeSubDiv::setup(const std::string& name, int value,  size_t numDigits, size_t maxValue, TimeSubDiv* larger, TimeSubDiv* smaller)
{
	this->value = value;
	_numDigits = numDigits;
	_maxValue = maxValue;
	_smaller = smaller;
	_larger = larger;
	
	if(_smaller) _delimiter = ":";
	
	_currentDigitIndex = _numDigits;
	
	setId(name);
	
	ofBitmapFont bf;
	ofRectangle _shape = bf.getBoundingBox("0", 0, 0);
	_fontYOffset = - _shape.y;
	_shape.x = 0;
	_shape.y = 0;
	_shape.width *= _numDigits;
	
	setShape(_shape);
	
	setFocusable(true);
	
}


void TimeSubDiv::_onPointerEvent(DOM::PointerUIEventArgs& e)
{
	
	
	if (e.type() == PointerEventArgs::POINTER_DOWN)
    {
		enableKeys();
		for(auto& s: siblings())
		{
			auto f = dynamic_cast<TimeSubDiv*>(s);
			if(f)
			{
				f->disableKeys();
			}
		}
    }
}


void TimeSubDiv::onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt)
{
	if (this == evt.target())
	{
		
		if(evt.key().key == OF_KEY_UP)
		{
			if(value+1 < _maxValue)
			{
				++value;
			}else
			{
				if(_larger)
				{
					value = 0;
					_larger->value += 1;
				}
			}
		}
		else if(evt.key().key == OF_KEY_DOWN)
		{
			if(value > 0)
			{
				--value;
			}else
			{
				if(_larger && _larger->value > 0)
				{
					value = _maxValue -1;
					_larger->value -= 1;
				}
			}
		}
		else if(evt.key().key >= '0' && evt.key().key <= '9')
		{
			if(_currentDigitIndex > 0)
			{
				
				int newVal =  evt.key().key - '0';
				if(!_bNeedsValueReset)
					newVal += (value*10);
				
				
				if(newVal < _maxValue){
					--_currentDigitIndex;
					_bNeedsValueReset = false;
					
					value = newVal;
				}
			}
			if(_currentDigitIndex == 0)
			{
				_enableSmaller();
			}
		}
		else if(evt.key().key == OF_KEY_BACKSPACE)
		{
			if(_currentDigitIndex < _numDigits)
			{
				++_currentDigitIndex;
				value = (int)floor(value/10.f);// just making sure it is rounded correctly
			}
			else
			{
				value = 0;
			}
		}
		
		else if(evt.key().key == OF_KEY_LEFT)
		{
			_enableLarger();
		}
		else if(evt.key().key == OF_KEY_RIGHT)
		{
			_enableSmaller();
		}
		else if(evt.key().key == OF_KEY_RETURN)
		{
			auto p = dynamic_cast<TimeModifier*>(parent());
			if(p)
			{
				ofNotifyEvent(p->valueSetEvent, this);
			}
			disableKeys();
		}
	}
}


void TimeSubDiv::enableKeys()
{
	if(document())
	{
		document()->focusElement(this);
			addEventListener(keyDown,
					 &TimeSubDiv::onKeyboardDownEvent,
					 false,
					 std::numeric_limits<int>::lowest());
		_currentDigitIndex = _numDigits;
		_bNeedsValueReset = true;
		_bKeysEnabled = true;
	}
}


void TimeSubDiv::disableKeys()
{
	_bKeysEnabled = false;
	auto d = document();
	if(d) d->unfocusElement(this);
	
	removeEventListener(keyDown,
						&TimeSubDiv::onKeyboardDownEvent,
						false,
						std::numeric_limits<int>::lowest());
}


void TimeSubDiv::onDraw() const
{
	if(_bKeysEnabled)
	{
		ofSetColor(120);
		ofDrawRectangle(0,0,getWidth(), getHeight());
	
	ofNoFill();
	ofSetColor(ofColor::yellow);
	ofDrawRectangle(0,0,getWidth(), getHeight());
	}
	
	ofFill();
	ofSetColor(255);
	ofDrawBitmapString(getValueAsString(), 0,  _fontYOffset);
}


bool TimeSubDiv::hasKeysEnabled() const
{
	return _bKeysEnabled;
}


void TimeSubDiv::_enableLarger()
{
	disableKeys();
	if(_larger)
	{
		_larger->enableKeys();
	}
	else
	{
		_enableParentKeys();
	}
	
}


void TimeSubDiv::_enableSmaller()
{
	disableKeys();
	if(_smaller)
	{
		_smaller->enableKeys();
	}
	else
	{
		_enableParentKeys();
	}
}


void TimeSubDiv::_enableParentKeys()
{
	auto p = dynamic_cast<TimeModifier*>(parent());
	if(p)
	{
		p->enableKeys();
	}
}


std::string TimeSubDiv::getValueAsString() const
{
	return ofToString(value, _numDigits, '0') + _delimiter;
}

//----------------------------------------------------------------------------

TimeModifier::TimeModifier(const std::string& id, const ofRectangle& shape, size_t initialMillis)
: MUI::Widget((id.empty()?"TimeModifier":id),0,0,0,0)
{
	//	_subDivs.reserve(4);
	for(int i = 0; i < 4; i++)
	{
		_subDivs.push_back(addChild<TimeSubDiv>());
		
		//		_subDivs.push_back(std::move(std::make_unique<TimeSubDiv>()));
	}
	
	_subDivs[0]->setup("HOURS"        , int(initialMillis / (60 * 60 * 1000))   , 2 , 100  , nullptr     , _subDivs[1]);//HOURS
	_subDivs[1]->setup("MINUTES"      , int((initialMillis / (60 * 1000)) % 60) , 2 , 60   , _subDivs[0] , _subDivs[2]);//MINUTES
	_subDivs[2]->setup("SECONDS"      , int((initialMillis / 1000) % 60)        , 2 , 60   , _subDivs[1] , _subDivs[3]);//SECONDS
	_subDivs[3]->setup("MILLISECONDS" , initialMillis%1000                      , 3 , 1000 , _subDivs[2] , nullptr);//MILLISECONDS
	
	ofBitmapFont bf;
	auto delimWidth = bf.getBoundingBox(":", 0, 0).width;
	
	
	float x = 0;
	
	ofRectangle _shape;
	for(int i = 0; i < 4; i++)
	{
		_subDivs[i]->setPosition(x, _subDivs[i]->getY());
		x+= delimWidth + _subDivs[i]->getWidth();
		
		if(i == 0)
		{
			_shape = _subDivs[i]->getShape();
		}
		else
		{
			_shape.growToInclude(_subDivs[i]->getShape());
		}
	}
	setShape(_shape);
	

	setFocusable(true);
	
	_subDivs[0]->enableKeys();
}


TimeModifier::~TimeModifier()
{

	disableKeys();
}


void TimeModifier::enableKeys()
{
	if(document())
	{
		document()->focusElement(this);
		addEventListener(keyDown,
					 &TimeModifier::onKeyboardDownEvent,
					 false,
					 std::numeric_limits<int>::lowest());
	}
}


void TimeModifier::disableKeys()
{
	for(auto s: _subDivs){s->disableKeys();}
	auto d = document();
	if(d) d->unfocusElement(this);
	removeEventListener(keyDown,
						&TimeModifier::onKeyboardDownEvent,
						false,
						std::numeric_limits<int>::lowest());

}



void TimeModifier::onDraw() const
{
	ofSetColor(0);
	ofDrawRectangle(0,0,getWidth(), getHeight());
	
	
}


void TimeModifier::onKeyboardDownEvent(DOM::KeyboardUIEventArgs& evt)
{
	if (this == evt.target())
	{
		
		if(evt.key().key == OF_KEY_RETURN)
		{
			ofNotifyEvent(valueSetEvent, this);
		}
		else if(evt.key().key == OF_KEY_LEFT)
		{
			if(!_subDivsKeysEnabled())
			{
				_subDivs.back()->enableKeys();
			}
		}
		else if(evt.key().key == OF_KEY_RIGHT)
		{
			if(!_subDivsKeysEnabled())
			{
				_subDivs.front()->enableKeys();
			}
		}
	}
}



bool TimeModifier::_subDivsKeysEnabled() const
{
	for(auto& s: _subDivs)
	{
		if(s->hasKeysEnabled())
		{
			return true;
		}
	}
	return false;
}

std::string TimeModifier::getTimecodeString() const
{
	return _subDivs[0]->getValueAsString()+
		   _subDivs[1]->getValueAsString()+
		   _subDivs[2]->getValueAsString()+
		   _subDivs[3]->getValueAsString();
}

} } // ofx::LineaDeTiempo
