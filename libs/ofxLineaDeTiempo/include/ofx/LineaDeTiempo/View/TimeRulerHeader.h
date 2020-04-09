//
//  TimeRulerHeader.hpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//



#pragma once


#include "ofx/DOM/Element.h"
#include "LineaDeTiempo/Controller/TimeControl.h"



namespace ofx {
namespace LineaDeTiempo {


class TimeRulerHeader
: public DOM::Element
{
public:
	TimeRulerHeader( TimeControl* timeControl);
	
	virtual ~TimeRulerHeader() = default;
	
	virtual void onDraw() const override;
	
	virtual void updateLayout() override;
protected:
	TimeControl* _timeControl = nullptr;
	
	static ofBitmapFont _bf;

	mutable std::string _timeText;

	void _makeTimeText() const;
	
	glm::vec2 _textPos;
};



} } // ofx::LineaDeTiempo
