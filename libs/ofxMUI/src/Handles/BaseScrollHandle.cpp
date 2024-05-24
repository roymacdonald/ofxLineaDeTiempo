//
//  BaseScrollHandle.cpp
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/14/20.
//

#include "BaseScrollHandle.h"
//#include "Constants.h"
#include "Utils.h"
namespace ofx {
namespace MUI {


template <>
bool BaseScrollHandle<ofRange>::addToValue(float amt){
	if(ofIsFloatEqual(amt, 0.0f))return false;
	auto v = ((amt > 0.0f)?handleValue.max:handleValue.min);
	
	auto m = ofClamp(v + amt, 0, 1);
		m -= v;
	return setValue(handleValue+m);
	
}
template <>
bool BaseScrollHandle<float>::addToValue(float amt){
	return setValue(ofClamp(handleValue + amt,0,1));
}

} } // ofx::MUI
