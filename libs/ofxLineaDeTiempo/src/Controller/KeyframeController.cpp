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


template class KeyframeController<glm::vec2>;
template class KeyframeController<glm::vec3>;
template class KeyframeController<glm::vec4>;

template class KeyframeController<bool>;

template class KeyframeController<         char>;
template class KeyframeController<unsigned char>;
template class KeyframeController<  signed char>;
template class KeyframeController<         short>;
template class KeyframeController<unsigned short>;
template class KeyframeController<         int>;
template class KeyframeController<unsigned int>;
template class KeyframeController<         long>;
template class KeyframeController<unsigned long>;
template class KeyframeController<         long long>;
template class KeyframeController<unsigned long long>;
template class KeyframeController<float>;
template class KeyframeController<double>;
template class KeyframeController<long double>;

template class KeyframeController<ofColor_<char>>;
template class KeyframeController<ofColor_<unsigned char>>;
template class KeyframeController<ofColor_<short>>;
template class KeyframeController<ofColor_<unsigned short>>;
template class KeyframeController<ofColor_<int>>;
template class KeyframeController<ofColor_<unsigned int>>;
template class KeyframeController<ofColor_<long>>;
template class KeyframeController<ofColor_<unsigned long>>;
template class KeyframeController<ofColor_<float>>;
//template class KeyframeController<ofColor_<double>>;


} } // ofx::LineaDeTiempo
