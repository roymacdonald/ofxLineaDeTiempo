//
//  KeyframeController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/25/20.
//


#pragma once
#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/Data/KeyframedData.h"
#include "LineaDeTiempo/View/KeyframeCollectionView.h"
#include "LineaDeTiempo/Controller/BaseController.h"
#include "LineaDeTiempo/Utils/ofxTypeTraits.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename >
class KeyframeCollectionController;


template< typename ParamDataType>
class KeyframeController
: public BaseController<KeyframeView>
{
public:
	
	typedef  typename std::conditional<is_multi_dim_param<ParamDataType>::value, float, ParamDataType>::type innerDataType;
	
	KeyframeController( const std::string& name, TimedData_<innerDataType> * data, KeyframeCollectionController<ParamDataType>* parentController)
	: BaseController<KeyframeView>(name, parentController, nullptr)
	,_parentController(parentController)
	,_data(data)
	{
			
	}

	
	
	virtual ~KeyframeController();
	
	virtual void generateView() override;
	virtual void destroyView() override;
	

	TimedData_<innerDataType> * getData()
	{
		return _data;
	}
	
	const TimedData_<innerDataType> * getData() const
	{
		return _data;
	}
	
protected:

	
private:
	ofEventListeners viewListeners;
	
	void _valueChanged(float& v);
	void _timeChanged(uint64_t& t);
	
	KeyframeCollectionController<ParamDataType>* _parentController = nullptr;
	
	TimedData_<innerDataType> * _data = nullptr;
	
	
	
};










template<>
class KeyframeController<void>
: public BaseController<KeyframeView>
{
public:
	
	
	KeyframeController( const std::string& name, uint64_t * data, KeyframeCollectionController<void>* parentController);
//	: BaseController<KeyframeView>(name, parentController, nullptr)
//	,_parentController(parentController)
//	,_data(data)
//	{
//
//	}

	
	
	virtual ~KeyframeController();
	
	virtual void generateView() override;
	virtual void destroyView() override;
	

	uint64_t * getData()
	{
		return _data;
	}
	
	const uint64_t * getData() const
	{
		return _data;
	}
	
protected:

	
private:
	ofEventListeners viewListeners;
	
	void _timeChanged(uint64_t& t);
	
	KeyframeCollectionController<void>* _parentController = nullptr;
	
	uint64_t * _data = nullptr;
	
	
	
};





} } // ofx::LineaDeTiempo
