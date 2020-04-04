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

class TracksPanel;


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
	
	static ofBitmapFont bf;
	
};


class TimeRulerBar
: public MUI::Widget

{
public:
	TimeRulerBar( TracksPanel* panel, TimeControl* timeControl);
	
	virtual ~TimeRulerBar() = default;

	
	virtual void onDraw() const override;

	virtual void updateLayout() override;
	
protected:
	
	virtual void _onDragging(const DOM::CapturedPointer& pointer) override;
	
    virtual void _onPointerEvent(DOM::PointerUIEventArgs& e) override;
	
	
	
	TracksPanel* _panel = nullptr;
	
	void _makeRulerLines();
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
	void _updatePlayheadSize();
	
	ofEventListener _panelResizeListener;
	void _onPanelResize(DOM::ResizeEventArgs& e);
	
	
	
};

class TimeRuler
: public DOM::Element
{
public:
	TimeRuler( TracksPanel* panel, TimeControl* timeControl);
	
	virtual ~TimeRuler() = default;
	
	virtual void updateLayout() override;
	


protected:
	TimeRulerHeader* _header = nullptr;

	TimeRulerBar* _bar = nullptr;
	

	TracksPanel* _panel = nullptr;
	
	
	ofEventListeners _panelListeners;
	
	
	
	
	void _tracksContainerMoved(DOM::MoveEventArgs& e);
	void _tracksContainerResized(DOM::ResizeEventArgs& e);
	void _panelResized(DOM::ResizeEventArgs& e);
	
	
	
	
	
};


} } // ofx::LineaDeTiempo
