//
//  TimedData_impl.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/17/20.
//

#include "src/Data/TimedData.cpp"
#include "src/Data/KeyframedData.cpp"

namespace ofx {
namespace LineaDeTiempo {




//#define ENABLE_GLM_QUAT_MAT_TIMED_DATA
//#define ENABLE_OF_RECTANGLE_TIMED_DATA
//#define ENABLE_OF_COLOR_DOUBLE_TIMED_DATA
//#define ENABLE_LONG_DOUBLE_TIMED_DATA


//
//#ifdef ENABLE_OF_RECTANGLE_TIMED_DATA
//template class TimedData_<ofRectangle>;
//#endif
//
//template class TimedData_<ofColor_<char>>;
//template class TimedData_<ofColor_<unsigned char>>;
//template class TimedData_<ofColor_<short>>;
//template class TimedData_<ofColor_<unsigned short>>;
//template class TimedData_<ofColor_<int>>;
//template class TimedData_<ofColor_<unsigned int>>;
//template class TimedData_<ofColor_<long>>;
//template class TimedData_<ofColor_<unsigned long>>;
//template class TimedData_<ofColor_<float>>;
//#ifdef ENABLE_OF_COLOR_DOUBLE_TIMED_DATA
//template class TimedData_<ofColor_<double>>;
//#endif
//
//template class TimedData_<glm::vec2>;
//template class TimedData_<glm::vec3>;
//template class TimedData_<glm::vec4>;
//#ifdef ENABLE_GLM_QUAT_MAT_TIMED_DATA
//template class TimedData_<glm::quat>;
//template class TimedData_<glm::mat4>;
//#endif
//
template class TimedData_<char>;
template class TimedData_<unsigned char>;
template class TimedData_<short>;
template class TimedData_<unsigned short>;
template class TimedData_<int>;
template class TimedData_<unsigned int>;
template class TimedData_<long>;
template class TimedData_<unsigned long>;
template class TimedData_<float>;
//template class TimedData_<double>;
//#ifdef ENABLE_LONG_DOUBLE_TIMED_DATA
//template class TimedData_<long double>;
//#endif

//
////-----------------------------------------------------------------------------
//#ifdef ENABLE_OF_RECTANGLE_TIMED_DATA
//template class KeyframedData_<ofRectangle>;
//#endif
//template class KeyframedData_<ofColor_<char>>;
//template class KeyframedData_<ofColor_<unsigned char>>;
//template class KeyframedData_<ofColor_<short>>;
//template class KeyframedData_<ofColor_<unsigned short>>;
//template class KeyframedData_<ofColor_<int>>;
//template class KeyframedData_<ofColor_<unsigned int>>;
//template class KeyframedData_<ofColor_<long>>;
//template class KeyframedData_<ofColor_<unsigned long>>;
//template class KeyframedData_<ofColor_<float>>;
//#ifdef ENABLE_OF_COLOR_DOUBLE_TIMED_DATA
//template class KeyframedData_<ofColor_<double>>;
//#endif
//
//template class KeyframedData_<glm::vec2>;
//template class KeyframedData_<glm::vec3>;
//template class KeyframedData_<glm::vec4>;
//
//#ifdef ENABLE_GLM_QUAT_MAT_TIMED_DATA
//template class KeyframedData_<glm::quat>;
//template class KeyframedData_<glm::mat4>;
//#endif
//
//
//
template class KeyframedData_<char>;
template class KeyframedData_<unsigned char>;
template class KeyframedData_<short>;
template class KeyframedData_<unsigned short>;
template class KeyframedData_<int>;
template class KeyframedData_<unsigned int>;
template class KeyframedData_<long>;
template class KeyframedData_<unsigned long>;
template class KeyframedData_<float>;
//template class KeyframedData_<double>;
//#ifdef ENABLE_LONG_DOUBLE_TIMED_DATA
//template class KeyframedData_<long double>;
//#endif




} } // ofx::LineaDeTiempo
