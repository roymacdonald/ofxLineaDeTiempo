//
//  KeyframeTrackHeader.cpp
//  ofxGuiWidgetDOMintegration
//
//  Created by Roy Macdonald on 4/12/20.
//

#include "LineaDeTiempo/View/KeyframeTrackHeader.h"
#include "LineaDeTiempo/View/TrackGroupView.h"
#include "LineaDeTiempo/View/BaseTrackView.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename ParamType>
KeyframeTrackHeader<ParamType>::KeyframeTrackHeader(ofParameter<ParamType> & param, const std::string& id, const ofRectangle& rect, BaseTrackView* track,  TrackGroupView* group, bool belongsToPanel)
: TrackHeader(id, rect, track, group, belongsToPanel)
{
	
	_gui = addChild<ofxGuiView<ParamType>>(param, group->getTracksHeaderWidth());
	_gui->setPosition(0, ConstVars::ViewTopHeaderHeight);
	
	
	std::cout << "KeyframeTrackHeader  " << typeid(ParamType).name()  << "\n";
	
}


//template<typename ParamType>
//void KeyframeTrackHeader<ParamType>::onDraw() const
//{
//	
//}
//	

template<typename ParamType>
void KeyframeTrackHeader<ParamType>::_onShapeChange(const DOM::ShapeChangeEventArgs&  e)
{
	if(e.widthChanged())
	{
		_gui->setWidth(getWidth());
	}
	
}

template class KeyframeTrackHeader<ofRectangle>;

template class KeyframeTrackHeader<ofColor>;
template class KeyframeTrackHeader<ofShortColor>;
template class KeyframeTrackHeader<ofFloatColor>;


//template class KeyframeTrackHeader<ofColor_<char>>;
//template class KeyframeTrackHeader<ofColor_<unsigned char>>;
//template class KeyframeTrackHeader<ofColor_<short>>;
//template class KeyframeTrackHeader<ofColor_<unsigned short>>;
//template class KeyframeTrackHeader<ofColor_<int>>;
//template class KeyframeTrackHeader<ofColor_<unsigned int>>;
//template class KeyframeTrackHeader<ofColor_<long>>;
//template class KeyframeTrackHeader<ofColor_<unsigned long>>;
//template class KeyframeTrackHeader<ofColor_<float>>;
//template class KeyframeTrackHeader<ofColor_<double>>;
template class KeyframeTrackHeader<glm::vec2>;
template class KeyframeTrackHeader<glm::vec3>;
template class KeyframeTrackHeader<glm::vec4>;
//template class KeyframeTrackHeader<glm::quat>;
//template class KeyframeTrackHeader<glm::mat4>;
template class KeyframeTrackHeader<bool>;
//template class KeyframeTrackHeader<void>;
//template class KeyframeTrackHeader<char>;
//template class KeyframeTrackHeader<unsigned char>;
//template class KeyframeTrackHeader<signed char>;
//template class KeyframeTrackHeader<short>;
//template class KeyframeTrackHeader<unsigned short>;
//template class KeyframeTrackHeader<int>;
//template class KeyframeTrackHeader<unsigned int>;
//template class KeyframeTrackHeader<long>;
//template class KeyframeTrackHeader<unsigned long>;
//template class KeyframeTrackHeader<long long>;
//template class KeyframeTrackHeader<unsigned long long>;
//template class KeyframeTrackHeader<float>;
//template class KeyframeTrackHeader<double>;
//template class KeyframeTrackHeader<long double>;





template class KeyframeTrackHeader<int8_t>;
template class KeyframeTrackHeader<uint8_t>;
template class KeyframeTrackHeader<int16_t>;
template class KeyframeTrackHeader<uint16_t>;
template class KeyframeTrackHeader<int32_t>;
template class KeyframeTrackHeader<uint32_t>;
template class KeyframeTrackHeader<int64_t>;
template class KeyframeTrackHeader<uint64_t>;
template class KeyframeTrackHeader<float>;
template class KeyframeTrackHeader<double>;
template class KeyframeTrackHeader<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;








} } // ofx::LineaDeTiempo
