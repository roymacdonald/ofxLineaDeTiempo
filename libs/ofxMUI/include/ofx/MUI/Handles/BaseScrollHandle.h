//
//  BaseScrollHandle.h
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/9/20.
//

#pragma once
#include "ofEvents.h"

namespace ofx {
namespace MUI {

template <typename DataType>
class BaseScrollHandle{
public:

	
	virtual ~BaseScrollHandle(){}
	

	ofEvent<DataType> handleChangeEvent;
	
	
	
	///\brief sets the handleValue to the passed argument. Will notify handleChangeEvent if passed value is different to handleValue
	///returns true if value passed value was different, false otherwise
	/// possible implementation:
	///	if(handleValue != val){
	///		handleValue = val;
	///		ofNotifyEvent(handleChangeEvent, handleValue, this);
	///		return true;
	///	}
	///	return false;

	virtual bool setValue(const DataType& val ) = 0;
	
	const DataType& getValue() const {
		return handleValue;
	}
	
	
	///\brief will move the handle
	bool addToValue(float amt);
	
protected:
	
	
	DataType handleValue;
	
};



} } // ofx::MUI

