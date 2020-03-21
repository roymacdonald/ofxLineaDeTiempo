//
//  KeyframedParameter.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#pragma once
#include "ofParameter.h"
#include "KeyframedData.h"
#include "LineaDeTiempo/BaseTypes/BaseHasTimeControl.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename ParameterType>

class KeyframedParameter_
: public KeyframedData_<ParameterType>
, public BaseHasTimeControl
{
public:
	KeyframedParameter_(ofParameter<ParameterType>& param, TimeControl* timeControl);//, std::shared_ptr<TimeControl> timeControl);
	virtual ~KeyframedParameter_(){}
	
	virtual bool update(const uint64_t& time) override;
	
protected:
	
//private:

	ofParameter<ParameterType> _param;

	ofEventListener _paramListener;
	
	void _paramChanged(ParameterType& );
	
	//	// this is set to true when the param is being modified by the manager, so it does not generate an infinite loop because of the cyclic callbacks.
	bool _bModifyingParam = false;

	
	
};


} } // ofx::LineaDeTiempo
