//
//  KeyframeController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/25/20.
//

#include "LineaDeTiempo/Controller/KeyframeController.h"
#include "LineaDeTiempo/Controller/KeyframeRegionController.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"
#include "LineaDeTiempo/View/RegionView.h"
#include "LineaDeTiempo/View/KeyframesRegionView.h"
#include "LineaDeTiempo/Controller/KeyframeCollectionController.h"

namespace ofx {
namespace LineaDeTiempo {


template<typename ParamDataType>
KeyframeController<ParamDataType>::~KeyframeController(){
	destroyView();
}


template< typename T>
void KeyframeController<T>::generateView()
{
	if(getView() == nullptr && _data && _parentController && _parentController->getView()){
		
	
			auto view = _parentController->getView()->addKeyframe(_parentController->normalizeValue(_data->value), _data->time);
			
			
			setView(view);
			
			viewListeners.push(view->valueChangedEvent.newListener(this, &KeyframeController<T>::_valueChanged));
			viewListeners.push(view->timeChangedEvent.newListener(this, &KeyframeController<T>::_timeChanged));
			
			
			
		

		generateChildrenViews(this);
	}
}

template< typename T>
void KeyframeController<T>::destroyView()
{
	if(getView()){
		destroyChildrenViews(this);
		if(_parentController && _parentController->getView()){
			
			
			if(_parentController->getView()->removeKeyframe(getView()) == false)
			{
				ofLogError("KeyframeController_<T>::destroyView") << "Could not remove track correctly. " << getId();
			}
			
		}
		viewListeners.unsubscribeAll();
		setView(nullptr);
	}
}





template< typename T>
void KeyframeController<T>::_valueChanged(float& v)
{
	if(_parentController && _data){
		_data->value = _parentController->unnormalizeValue(v);
	}
}

template< typename T>
void KeyframeController<T>::_timeChanged(uint64_t& t)
{
	if(_data){
		_data->time = t;
		_parentController->sortData();
	}
}







KeyframeController<void>::KeyframeController( const std::string& name, uint64_t * data, KeyframeCollectionController<void>* parentController)
: BaseController<KeyframeView>(name, parentController, nullptr)
,_parentController(parentController)
,_data(data)
{
		
}


KeyframeController<void>::~KeyframeController(){
	destroyView();
}



void KeyframeController<void>::generateView()
{
	if(getView() == nullptr && _data && _parentController && _parentController->getView()){
	
		auto view = _parentController->getView()->addKeyframe(*_data);
			
		setView(view);
			
		viewListeners.push(view->timeChangedEvent.newListener(this, &KeyframeController<void>::_timeChanged));
		
		generateChildrenViews(this);
	}
}


void KeyframeController<void>::destroyView()
{
	if(getView()){
		destroyChildrenViews(this);
		if(_parentController && _parentController->getView()){
			
			
			if(_parentController->getView()->removeKeyframe(getView()) == false)
			{
				ofLogError("KeyframeController_<T>::destroyView") << "Could not remove track correctly. " << getId();
			}
			
		}
		viewListeners.unsubscribeAll();
		setView(nullptr);
	}
}


void KeyframeController<void>::_timeChanged(uint64_t& t)
{
	if(_data){
		*_data = t;
		_parentController->sortData();
	}
}









template class KeyframeController<glm::vec2>;
template class KeyframeController<glm::vec3>;
template class KeyframeController<glm::vec4>;

template class KeyframeController<bool>;

template class KeyframeController<ofColor>;
template class KeyframeController<ofShortColor>;
template class KeyframeController<ofFloatColor>;



template class KeyframeController<int8_t>;
template class KeyframeController<uint8_t>;
template class KeyframeController<int16_t>;
template class KeyframeController<uint16_t>;
template class KeyframeController<int32_t>;
template class KeyframeController<uint32_t>;
template class KeyframeController<int64_t>;
template class KeyframeController<uint64_t>;
template class KeyframeController<float>;
template class KeyframeController<double>;
template class KeyframeController<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;


} } // ofx::LineaDeTiempo
