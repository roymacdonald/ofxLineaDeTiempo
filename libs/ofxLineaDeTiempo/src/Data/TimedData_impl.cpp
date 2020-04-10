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


template class TimedData_<bool>;


template class TimedData_<char>;
template class TimedData_<unsigned char>;
template class TimedData_<signed char>;
template class TimedData_<short>;
template class TimedData_<unsigned short>;
template class TimedData_<int>;
template class TimedData_<unsigned int>;
template class TimedData_<long>;
template class TimedData_<unsigned long>;
template class TimedData_<long long>;
template class TimedData_<unsigned long long>;
template class TimedData_<float>;
template class TimedData_<double>;
template class TimedData_<long double>;

template class KeyframedData_<char>;
template class KeyframedData_<unsigned char>;
template class KeyframedData_<signed char>;
template class KeyframedData_<short>;
template class KeyframedData_<unsigned short>;
template class KeyframedData_<int>;
template class KeyframedData_<unsigned int>;
template class KeyframedData_<long>;
template class KeyframedData_<unsigned long>;
template class KeyframedData_<long long>;
template class KeyframedData_<unsigned long long>;
template class KeyframedData_<float>;
template class KeyframedData_<double>;
template class KeyframedData_<long double>;
	


} } // ofx::LineaDeTiempo
