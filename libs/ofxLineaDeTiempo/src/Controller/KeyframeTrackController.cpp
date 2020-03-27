//
//  KeyframeTrackController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#include "LineaDeTiempo/Controller/KeyframeTrackController.h"

#include "LineaDeTiempo/Controller/TrackGroupController.h"

#include "LineaDeTiempo/Utils/ofxTypeTraits.h"
//#include "LineaDeTiempo/View/MultiDimTrackView.h"


namespace ofx {
namespace LineaDeTiempo {
//
template <typename DataType>
KeyframeTrackController_<DataType>::KeyframeTrackController_(ofParameter<DataType>& parameter,TrackGroupController* parent, TimeControl* timeControl)
: KeyframeTrackController_<DataType>(parameter.getName(), parent, timeControl)
{
	_parameter.makeReferenceTo(parameter);
}

template <typename DataType>
KeyframeTrackController_<DataType>::KeyframeTrackController_(const std::string& name, TrackGroupController* parent, TimeControl* timeControl)
: TrackController(name, parent, timeControl)
{
	_parameter.setName(name);
	
	_paramListener = _parameter.newListener(this, &KeyframeTrackController_<DataType>::_paramChanged);

	_timeControlListeners.push(timeControl->playEvent.newListener(this, &KeyframeTrackController_<DataType>::_findCurrentRegion));
	_timeControlListeners.push(timeControl->stopEvent.newListener(this, &KeyframeTrackController_<DataType>::_resetCurrentRegion));
		

	enableTimeUpdate();
}

template <typename DataType>
void KeyframeTrackController_<DataType>::_resetCurrentRegion()
{
 _currentRegion = 0;
}

template <typename DataType>
void KeyframeTrackController_<DataType>::_findNextRegion(const size_t& startIndex)
{
	auto t = getTimeControl()->getCurrentTime();
	for(size_t i =startIndex; i < _regions.size(); i++)
	{
		if(_regions[i]->getTimeRange().contains(t))
		{
			_currentRegion =i;
			break;
		}
	}
	_currentRegion = _regions.size();
}


template <typename DataType>
void KeyframeTrackController_<DataType>::_findCurrentRegion()
{
	_findNextRegion(0);
//	auto t = getTimeControl()->getCurrentTime();
//
//	for(size_t i =0; i < _regions.size(); i++)
//	{
//		if(_regions[i]->getTimeRange().contains(t))
//		{
//			_currentRegion =i;
//			break;
//		}
//	}
}







template <typename DataType>
KeyframeRegionController_<DataType> * KeyframeTrackController_<DataType>::addRegion( const std::string& regionName, const ofRange64u& timeRange)
{
	auto r = _addRegion<KeyframeRegionController_<DataType>>( regionName, timeRange);
	_regions.push_back(r);
	return r;
}

template <typename DataType>
bool KeyframeTrackController_<DataType>::removeRegion(KeyframeRegionController_<DataType>* region)
{
	ofRemove(_regions, [&](KeyframeRegionController_<DataType>* a){
		return a ==  region;
	});
	return _removeRegion(region);
}

template <typename DataType>
ofParameter<DataType>& KeyframeTrackController_<DataType>::getParameter()
{
	return _parameter;
}

template <typename DataType>
const ofParameter<DataType>& KeyframeTrackController_<DataType>::getParameter() const
{
	return _parameter;
}

template <typename DataType>
void KeyframeTrackController_<DataType>::update(uint64_t& time)
{
	
	if(_currentRegion < _regions.size() && _regions[_currentRegion])
	{
		if( _regions[_currentRegion]->getTimeRange().contains(time) )
		{
			_regions[_currentRegion]->update(time);
		}
		else if(_regions[_currentRegion]->getTimeRange().max < time)
		{
			_findNextRegion(_currentRegion+1);
			update(time);
		}
	}
	
//	if(_keyframedData.update(time))
//	{
//		_bModifyingParam = true;
//		auto v = _keyframedData.getCurrentValue();
//		if(_parameter.get() != v)// avoid setting the parameter constantly as this will trigger the parameters events.
//		{
//
//			_parameter = v;
//		}
//
//		_bModifyingParam = false;
//	}
}


template <typename DataType>
void KeyframeTrackController_<DataType>::_paramChanged(DataType& ){
//	if(!_bModifyingParam)
//	{
//		_keyframedData.setValue(_parameter, getTimeControl()->getCurrentTime(), _keyframedData.isKeyFramingEnabled() );
//	}
}

template <typename DataType>
void KeyframeTrackController_<DataType>::generateView()
{

	if(is_multi_dim_param<DataType>::value)
	{
//		_generateView<MultiDimTrackView>();
	}
	else
	{
		TrackController::generateView();
	}



}

template <typename DataType>
void KeyframeTrackController_<DataType>::destroyView()
{
	if(is_multi_dim_param<DataType>::value)
	{

	}
	else
	{
		TrackController::destroyView();
	}


}

template <typename DataType>
DataType KeyframeTrackController_<DataType>::getUnnormalizedValue(float val)
{
return ofMap((float)val, 0, 1, (float)_parameter.getMin(), (float)_parameter.getMax(), true);
}

template <typename DataType>
float KeyframeTrackController_<DataType>::getNormalizedValue(const DataType& val)
{
	return ofMap((float)val, (float)_parameter.getMin(), (float)_parameter.getMax(), 0, 1, true);
}

} } // ofx::LineaDeTiempo

//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofRectangle>;

//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<char>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<unsigned char>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<short>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<unsigned short>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<int>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<unsigned int>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<long>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<unsigned long>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<float>>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofColor_<double>>;

//template class ofx::LineaDeTiempo::KeyframeTrackController_<glm::vec2>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<glm::vec3>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<glm::vec4>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<glm::quat>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<glm::mat4>;
//
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofVec2f>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofVec3f>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<ofVec4f>;

//template class ofx::LineaDeTiempo::KeyframeTrackController_<bool>;
//template class ofx::LineaDeTiempo::KeyframeTrackController_<void>;

template class ofx::LineaDeTiempo::KeyframeTrackController_<char>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<unsigned char>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<signed char>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<short>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<unsigned short>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<int>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<unsigned int>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<long>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<unsigned long>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<long long>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<unsigned long long>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<float>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<double>;
template class ofx::LineaDeTiempo::KeyframeTrackController_<long double>;






