//
//  KeyframeTrackView.cpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/13/20.
//

#include "KeyframeTrackView.h"
#include "LineaDeTiempo/Controller/KeyframeTrackController.h"
#include "LineaDeTiempo/View/KeyframeTrackHeader.h"


namespace ofx {
namespace LineaDeTiempo {

template<typename T>
KeyframeTrackView<T>::KeyframeTrackView(TrackGroupView* parentGroup, TrackController* controller, TimeRuler * timeRuler, TrackHeader* _headerContainer, bool belongsToPanel )
:TrackView(parentGroup, controller, timeRuler )
{

	_keyframeTrackController  = dynamic_cast<KeyframeTrackController_<T> *> (controller);

	
	if(!_keyframeTrackController)
	{
		ofLogError(":KeyframeTrackView constructor") << "Cant cast the controller";
		return;
	}
		
	_headerContainer->addChild<KeyframeTrackHeader<T>>(getParameter(), getId() + "_header" , ofRectangle(0, 0, parentGroup->getTracksHeaderWidth(), ConstVars::TrackInitialHeight), this, parentGroup, belongsToPanel);
}

	
template<typename T>
ofParameter<T>& KeyframeTrackView<T>::getParameter()
{
	return _keyframeTrackController->getParameter();
}


template<typename T>
const ofParameter<T>& KeyframeTrackView<T>::getParameter() const
{
	return _keyframeTrackController->getParameter();
}

//template class KeyframeTrackView<ofRectangle>;


template class KeyframeTrackView<ofColor>;
template class KeyframeTrackView<ofShortColor>;
template class KeyframeTrackView<ofFloatColor>;

//template class KeyframeTrackView<ofColor_<char>>;
//template class KeyframeTrackView<ofColor_<unsigned char>>;
//template class KeyframeTrackView<ofColor_<short>>;
//template class KeyframeTrackView<ofColor_<unsigned short>>;
//template class KeyframeTrackView<ofColor_<int>>;
//template class KeyframeTrackView<ofColor_<unsigned int>>;
//template class KeyframeTrackView<ofColor_<long>>;
//template class KeyframeTrackView<ofColor_<unsigned long>>;
//template class KeyframeTrackView<ofColor_<float>>;
//template class KeyframeTrackView<ofColor_<double>>;
template class KeyframeTrackView<glm::vec2>;
template class KeyframeTrackView<glm::vec3>;
template class KeyframeTrackView<glm::vec4>;
//template class KeyframeTrackView<glm::quat>;
//template class KeyframeTrackView<glm::mat4>;
template class KeyframeTrackView<bool>;
template class KeyframeTrackView<void>;
//template class KeyframeTrackView<char>;
//template class KeyframeTrackView<unsigned char>;
//template class KeyframeTrackView<signed char>;
//template class KeyframeTrackView<short>;
//template class KeyframeTrackView<unsigned short>;
//template class KeyframeTrackView<int>;
//template class KeyframeTrackView<unsigned int>;
//template class KeyframeTrackView<long>;
//template class KeyframeTrackView<unsigned long>;
//template class KeyframeTrackView<long long>;
//template class KeyframeTrackView<unsigned long long>;
//template class KeyframeTrackView<float>;
//template class KeyframeTrackView<double>;
//template class KeyframeTrackView<long double>;


template class KeyframeTrackView<int8_t>;
template class KeyframeTrackView<uint8_t>;
template class KeyframeTrackView<int16_t>;
template class KeyframeTrackView<uint16_t>;
template class KeyframeTrackView<int32_t>;
template class KeyframeTrackView<uint32_t>;
template class KeyframeTrackView<int64_t>;
template class KeyframeTrackView<uint64_t>;
template class KeyframeTrackView<float>;
template class KeyframeTrackView<double>;
template class KeyframeTrackView<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;




} } // ofx::LineaDeTiempo
