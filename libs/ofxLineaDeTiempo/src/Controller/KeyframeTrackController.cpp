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
: TrackController(parameter.getName(), parent, timeControl)
{

	_parameter.makeReferenceTo(parameter);

	
//	_paramListener = _parameter.newListener(this, &KeyframeTrackController_<DataType>::_paramChanged);
	this->enableTimeUpdate();
	_dataTypeName = typeid(DataType).name();
}

template <typename DataType>
KeyframeTrackController_<DataType>::KeyframeTrackController_(const std::string& name, TrackGroupController* parent, TimeControl* timeControl)
: TrackController(name, parent, timeControl)
{
//	_parameter.setName(name);
//
//	_paramListener = _parameter.newListener(this, &KeyframeTrackController_<DataType>::_paramChanged);

	_parameter.setName(name);
	
//	_paramListener = _parameter.newListener(this, &KeyframeTrackController_<DataType>::_paramChanged);
	
	enableTimeUpdate();
	
	_dataTypeName = typeid(DataType).name();
	
}

template <typename DataType>
KeyframeRegionController_<DataType> * KeyframeTrackController_<DataType>::addRegion( const std::string& regionName)
{
	auto r = _addRegion<KeyframeRegionController_<DataType>>( regionName);
	return r;
}


template <typename DataType>
KeyframeRegionController_<DataType> * KeyframeTrackController_<DataType>::addRegion( const std::string& regionName, const ofRange64u& timeRange)
{
	auto r = _addRegion<KeyframeRegionController_<DataType>>( regionName, timeRange);
	return r;
}

//template <typename DataType>
//bool KeyframeTrackController_<DataType>::removeRegion(KeyframeRegionController_<DataType>* region)
//{
//	return _removeRegion(region);
//}

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
void KeyframeTrackController_<DataType>::_paramChanged(DataType& ){
//	if(!_bModifyingParam)
//	{
//		_keyframedData.setValue(_parameter, getTimeControl()->getCurrentTime(), _keyframedData.isKeyFramingEnabled() );
//	}
}
//
//template <typename DataType>
//void KeyframeTrackController_<DataType>::generateView()
//{
//
//	if(is_multi_dim_param<DataType>::value)
//	{
////		_generateView<MultiDimTrackView>();
//	}
//	else
//	{
//		TrackController::generateView();
//	}
//
//
//
//}
//
//template <typename DataType>
//void KeyframeTrackController_<DataType>::destroyView()
//{
//	if(is_multi_dim_param<DataType>::value)
//	{
//
//	}
//	else
//	{
//		TrackController::destroyView();
//	}
//
//
//}

template <typename DataType>
DataType KeyframeTrackController_<DataType>::getUnnormalizedValue(float val)
{
return ofMap((float)val, 0, 1, (float)getParameter().getMin(), (float)getParameter().getMax(), true);
}

template <typename DataType>
float KeyframeTrackController_<DataType>::getNormalizedValue(const DataType& val)
{
	return ofMap((float)val, (float)getParameter().getMin(), (float)getParameter().getMax(), 0, 1, true);
}
template <typename DataType>
void KeyframeTrackController_<DataType>::_addRegionFromJson(const std::string& name, ofJson j)
{
	addRegion(name)->fromJson(j);
}


template <typename DataType>
void KeyframeTrackController_<DataType>::fromJson(const ofJson& j)
{
	if(	j.count("class") > 0 && j.count("name") > 0){
		auto clss = j["class"].get<std::string>();
		if(clss != "KeyframeTrackController_")
		{
			ofLogError("KeyframeTrackController_<DataType>::fromJson") << "failed. class name stored in json is different from this one : " << clss;
			return;
		}
		
		auto dt = j["_dataTypeName"].get<std::string>();
		
		if(dt != std::string(typeid(DataType).name()))
		{
			ofLogError("KeyframeTrackController_<DataType>::fromJson") << "failed. DataType seems to be different to the one saved on file";
			return;
		}
		
		TrackController::fromJson(j);
		
	}
	else{
		ofLogError("KeyframeTrackController_<DataType>::fromJson") << "json malformed. No class or name objects.";
	}
}

template <typename DataType>
ofJson KeyframeTrackController_<DataType>::toJson()
{
	
	ofJson j = TrackController::toJson();
	j["class"] = "KeyframeTrackController_";
	j["name"] = getId();
	j["view"] = bool(getView());
	
	


	return j;
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






