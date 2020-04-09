//
//  TimeRulerBar.hpp
//  example
//
//  Created by Roy Macdonald on 4/5/20.
//
//
//  TimeRuler.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 4/2/20.
//

#pragma once


#include "ofx/MUI/Widget.h"
#include "ofMesh.h"
#include "LineaDeTiempo/Controller/TimeControl.h"
#include "ofRange.h"
#include "LineaDeTiempo/View/Playhead.h"


namespace ofx {
namespace LineaDeTiempo {

//class TracksPanel;

class TimeRuler;

class TimeRulerBar
: public MUI::Widget

{
public:
	TimeRulerBar( TimeRuler* timeRuler, TimeControl* timeControl);
	
	virtual ~TimeRulerBar() = default;

	
	virtual void onDraw() const override;

	virtual void updateLayout() override;
	
	
	void makeRulerLines();
	
	void setPlayheadHeight(float height);
	
protected:
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;
	
	
	
	TimeRuler* _timeRuler = nullptr;
	
	
	ofMesh _rulerLines;
	

	TimeControl* _timeControl = nullptr;
	
	ofRange64u _currentRange;

	float _minLineDist = 4;

	
	enum {
		_MILLIS =0,
		_CENTS,
		_TENS,
		_SECONDS,
		_MINUTES,
		_HOURS,
		_NUM_SUBDIVISIONS
	};
	
	std::vector<float> distances ;
	std::vector<bool> bDraw ;
	std::vector<float> multipliers ;// = {1.f, 1000.f, (1000.f *60 ),  (1000.f *60 *60 ) };
	
	ofVboMesh textMesh;
	Playhead * _playhead = nullptr;
	
	
//	ofEventListener _panelShapeChangeListener;
//	void _onPanelShapeChanged(DOM::ShapeChangeEventArgs& e);
	
	
	
};


} } // ofx::LineaDeTiempo
