//
//  KeyframeController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/25/20.
//


#pragma once
#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/Data/KeyframedData.h"
#include "LineaDeTiempo/BaseTypes/BaseViewController.h"
#include "DOM/Node.h"


namespace ofx {
namespace LineaDeTiempo {

template<typename T>
class KeyframeRegionController_;

template<typename DataType>
class KeyframeController
: public DOM::Node
, public BaseViewController<KeyframeView>
{
public:

	KeyframeController( const std::string& name, TimedData_<DataType> * data, KeyframeRegionController_<DataType>* parentRegion);
	
	virtual ~KeyframeController() = default;
	
	virtual void generateView() override;
	virtual void destroyView() override;
	
	using  BaseViewController<KeyframeView>::getView;
	using  BaseViewController<KeyframeView>::setView;
	
	TimedData_<DataType> * getData();
	const TimedData_<DataType> * getData() const;
	
protected:

	
private:
	ofEventListeners viewListeners;
	
	void _valueChanged(float& v);
	void _timeChanged(uint64_t& t);
	
	
	KeyframeRegionController_<DataType>* _parentRegion = nullptr;
	TimedData_<DataType> * _data = nullptr;
};


} } // ofx::LineaDeTiempo
