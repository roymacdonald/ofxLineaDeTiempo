//
//  KeyframeController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/25/20.
//


#pragma once
#include "LineaDeTiempo/View/KeyframeView.h"
#include "LineaDeTiempo/Data/KeyframedData.h"
#include "LineaDeTiempo/Controller/BaseController.h"


namespace ofx {
namespace LineaDeTiempo {

template<typename T>
class KeyframeRegionController_;

template<typename DataType>
class KeyframeController
: public BaseController<KeyframeView>
{
public:

	KeyframeController( const std::string& name, TimedData_<DataType> * data, KeyframeRegionController_<DataType>* parentRegion);
	
	virtual ~KeyframeController(); //DEFAULT_BASE_VIEW_CONTROLLER_DESTRUCTOR
	
	virtual void generateView() override;
	virtual void destroyView() override;
	

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

template<typename DataType>
KeyframeController<DataType>::~KeyframeController(){
	destroyView();
}



} } // ofx::LineaDeTiempo
