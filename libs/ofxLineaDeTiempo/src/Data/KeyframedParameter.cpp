//
//  TimedParameter.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/6/20.
//

#include "LineaDeTiempo/Data/KeyframedParameter.h"
#include "LineaDeTiempo/Controller/TimeControl.h"


namespace ofx {
namespace LineaDeTiempo {

//---------------------------------------------------------------------
template<typename T>
KeyframedParameter_<T>::KeyframedParameter_(ofParameter<T>& param)//, std::shared_ptr<TimeControl> timeControl):
: KeyframedData_<T>(param.getName())
{
	_param.makeReferenceTo(param);
	_paramListener = _param.newListener(this, &KeyframedParameter_<T>::_paramChanged);
}
	
//---------------------------------------------------------------------
template<typename T>
bool KeyframedParameter_<T>::update(const uint64_t& time)
{
	if(KeyframedData_<T>::update(time))
	{
		_bModifyingParam = true;
		_param = KeyframedData_<T>::getCurrentValue(); //why does this work sometimes and other I have to explicitly put the parent class~!!!
		_bModifyingParam = false;
	}
}
//---------------------------------------------------------------------
template<typename T>
void KeyframedParameter_<T>::_paramChanged(T& param)
{
	
	if(!_bModifyingParam)
	{
		KeyframedData_<T>::setValue(param, getTimeControl().getCurrentTime(), KeyframedData_<T>::isKeyFramingEnabled() );
	}
}



	
} } // ofx::LineaDeTiempo
