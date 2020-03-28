//
//  BaseHasOfParameter.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/27/20.
//

#pragma once
#include "ofParameter.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename DataType>
class BaseHasOfParameter{
public:

	BaseHasOfParameter(ofParameter<DataType>& parameter)
	{
		_parameter.makeReferenceTo(parameter);
		_paramListener = _parameter.newListener(this, &BaseHasOfParameter<DataType>::_paramChanged);
	}

	BaseHasOfParameter(const std::string& name)
	{
		_parameter.setName(name);
		
		_paramListener = _parameter.newListener(this, &BaseHasOfParameter<DataType>::_paramChanged);

	}
	
	ofParameter<DataType>& getParameter()
	{
		return _parameter;
	}
	
	const ofParameter<DataType>& getParameter() const
	{
		return _parameter;
	}
	
protected:
	ofParameter<DataType> _parameter;
	
	ofEventListener _paramListener;
	
	virtual void _paramChanged(DataType& ) =0;
};



}}//ofx::LineaDeTiempo
