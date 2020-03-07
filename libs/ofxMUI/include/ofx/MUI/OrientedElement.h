//
//  OrientedWidget.h
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/14/20.
//
#pragma once
#include "ofEvents.h"
#include "ofxDOM.h"

namespace ofx {
namespace DOM {


class OrientedElement{
public:

	OrientedElement(DOM::Orientation orientation):
		_orientation(orientation)
	{
		_setDimIndex();
	}
	
	virtual ~OrientedElement(){}

	DOM::Orientation getOrientation()
	{
		return _orientation;
	}
	
	virtual void setOrientation(DOM::Orientation orientation)
	{
		_orientation = orientation;
		_setDimIndex();
		ofNotifyEvent(orientationChangedEvent, _orientation, this);
	}

	ofEvent<DOM::Orientation> orientationChangedEvent;

	const int& dimIndex()
	{
		return _dimIndex;
		
	}
	
protected:
	void _setDimIndex(){
		if(_orientation == DOM::HORIZONTAL){
			_dimIndex = 0;
		}else{
			_dimIndex = 1;
		}
	}
	
	
	
	DOM::Orientation _orientation;

private:
	int _dimIndex;
};


} } // ofx::DOM

