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

namespace ofx {
namespace LineaDeTiempo {


template<typename DataType>
KeyframeController<DataType>::KeyframeController( const std::string& name, TimedData_<DataType> * data, KeyframeRegionController_<DataType>* parentRegion)
: BaseController<KeyframeView>(name, parentRegion, nullptr)
,_parentRegion(parentRegion)
,_data(data)
{
	
}
	
template<typename DataType>
void KeyframeController<DataType>::generateView()
{
	if(getView() == nullptr && _parentRegion && _data){
		auto p_view = dynamic_cast<KeyframesRegionView*>(_parentRegion->getView());
		if(p_view )
		{
			
			auto val = _parentRegion->_parentTrack->getNormalizedValue(_data->value);
		
			auto view =p_view->addKeyframe(val, _data->time);
	
			setView(view);
			
			viewListeners.push(view->valueChangedEvent.newListener(this, &KeyframeController<DataType>::_valueChanged));
			viewListeners.push(view->timeChangedEvent.newListener(this, &KeyframeController<DataType>::_timeChanged));
			
			
			
		}

		generateChildrenViews(this);
	}
}

template<typename DataType>
void KeyframeController<DataType>::destroyView()
{
	if(getView()){
		destroyChildrenViews(this);
		if(_parentRegion){
			auto p_view = dynamic_cast<KeyframesRegionView*>(_parentRegion->getView());
			if(p_view)
			{
				
				if(p_view->removeKeyframe(getView()) == false)
				{
					ofLogError("KeyframeController_<T>::destroyView") << "Could not remove track correctly. " << getId();
				}
				
			}
			viewListeners.unsubscribeAll();
			setView(nullptr);
		}
	}
}




template<typename DataType>
void KeyframeController<DataType>::_valueChanged(float& v)
{
	if(_parentRegion && _data){
		_data->value = _parentRegion->_parentTrack->getUnnormalizedValue(v);
	}
}

template<typename DataType>
void KeyframeController<DataType>::_timeChanged(uint64_t& t)
{
	if(_data){
		_data->time = t;
	}
}

template<typename DataType>
TimedData_<DataType> *  KeyframeController<DataType>::getData()
{
	return _data;
}
template<typename DataType>
const TimedData_<DataType> *  KeyframeController<DataType>::getData() const
{
	return _data;
}

//template class KeyframeController<int8_t>;
//template class KeyframeController<int16_t>;
//template class KeyframeController<int32_t>;
//template class KeyframeController<int64_t>;
//template class KeyframeController<uint8_t>;
//template class KeyframeController<uint16_t>;
//template class KeyframeController<uint32_t>;
//template class KeyframeController<uint64_t>;
//template class KeyframeController<size_t>;
//template class KeyframeController<float>;


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
template class KeyframeController<double>;
template class KeyframeController<long double>;

//template class KeyframeController<int>;
//template class KeyframeController<float>;

} } // ofx::LineaDeTiempo
