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


//template< typename T>
//KeyframeController<T>::KeyframeController( const std::string& name, TimedData_<T> * data, KeyframeCollectionController<T>* parentController)
//: BaseController<KeyframeView>(name, parentController, nullptr)
//,_parentController(parentController)
//,_data(data)
//{
//	
//}
	
template< typename T>
void KeyframeController<T>::generateView()
{
	if(getView() == nullptr && _data && _parentController && _parentController->getView()){
		
			
			
//			auto val = _parentRegion->_parentTrack->getNormalizedValue(_data->value);


	
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
	}
}

//template< typename T>
//TimedData_<T> *  KeyframeController<T>::getData()
//{
//	return _data;
//}
//template< typename T>
//const TimedData_<T> *  KeyframeController<T>::getData() const
//{
//	return _data;
//}



template class KeyframeController<glm::vec2>;
template class KeyframeController<glm::vec3>;

template class KeyframeController<char>;
template class KeyframeController<unsigned char>;
template class KeyframeController<signed char>;
template class KeyframeController<short>;
template class KeyframeController<unsigned short>;
template class KeyframeController<int>;
template class KeyframeController<unsigned int>;
template class KeyframeController<long>;
template class KeyframeController<unsigned long>;
template class KeyframeController<long long>;
template class KeyframeController<unsigned long long>;
template class KeyframeController<float>;
//template class KeyframeController<double, double>;
//template class KeyframeController<long double, long double>;

//template class KeyframeController<int>;
//template class KeyframeController<float>;

} } // ofx::LineaDeTiempo
