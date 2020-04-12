/*
 *
 *  Created by James George on 1/15/11.
 *  Templated by Christopher Baker on 6/27/12
 *
 */

//----------------------------------------------------------
// ofRange_<T>
//----------------------------------------------------------
#pragma once
#include <algorithm>
#include <iostream> 
#include "ofMath.h"
template<typename T>
class ofRange_ {
  public:
	virtual ~ofRange_(){}
	
	ofRange_( const ofRange_<T>& rg){
        set(rg.min,rg.max);
	}
	
    ofRange_(T _value = 0.0f){
        set(_value);
	}

	ofRange_( T _min, T _max){
        set(_min, _max);
	}
    
    void set(const ofRange_<T>& rg) {
        set(rg.min,rg.max);
    }
    
    void set(T _value){
        min = _value;
        max = _value;
	}

	void set(T _min, T _max){
        // enforce min <= max
        if(_min <= _max) {
            min = _min;
            max = _max;
        } else {
            min = _max;
            max = _min;
        }
	}
	
	void setMin(T _min){
		min = std::min(_min, max);
	}
	
	void setMax(T _max){
		max = std::max(min, _max);
	}
    
    void growToInclude(T _value) {
		min = MIN(_value, min);
		max = MAX(_value, max);
    }
    
    // map
    //
	
//    typename std::enable_if<std::is_floating_point<T>::value, bool>::type
	bool operator==( const ofRange_<T>& rg )
	{
		if(std::is_floating_point<T>::value){
			return ofIsFloatEqual(min,rg.min) && ofIsFloatEqual(max, rg.max);
		}else{
			return (min == rg.min) && (max == rg.max);
		}
    }
	
//	typename std::enable_if<std::is_floating_point<T>::value, bool>::type
	bool operator!=( const ofRange_<T>& rg )
	{
//		if(std::is_floating_point<T>::value){
//			return ! ofIsFloatEqual(min,rg.min) || !ofIsFloatEqual(max, rg.max);
//		}else{
			 return (min != rg.min) || (max != rg.max);
//		}
    }
	
//	typename std::enable_if<std::is_integral<T>::value, bool>::type
//	operator!=( const ofRange_<T>& rg )
//	{
//		return (min != rg.min) || (max != rg.max);
//	}
//
//	typename std::enable_if<std::is_integral<T>::value, bool>::type
//	operator ==( const ofRange_<T>& rg )
//	{
//		return (min == rg.min) && (max == rg.max);
//	}
	
	bool contains(T p) const{
		return p >= min && p <= max;
	}
	
	bool contains(const ofRange_<T>& rg) const{
		return rg.min >= min && rg.max <= max;
	}
	
	bool intersects(const ofRange_<T>& rg) const{
        bool intersects = this->contains(rg) || (min >= rg.min && max < rg.max) || contains(rg.min) || contains(rg.max);
		return intersects;
	}

    //this is broken
	ofRange_<T> getClamped(const ofRange_<T>& rg){
		return contains(rg.min) || contains(rg.max);
	}
	
	T span() const{
		return max - min;
	}
	
	T center() const{
		return span()/2 + min;
	}
	
	T getNormalized(const T v) const {
		return (v - min) / (max - min);
	}

	ofRange_<T> getClamped(const ofRange_<T>& rg) const {
		ofRange_<T> crg;
		crg.min = std::max(rg.min,min);
		crg.max = std::min(rg.max,max);		
		return crg;
	}
	
    ofRange_<T>& clamp(const ofRange_<T>& rg){
		min = std::max(rg.min,min);
		max = std::min(rg.max,max);
		return *this;
	}

	//union
	ofRange_<T>  operator +( const ofRange_<T>& rg ) const {
        return ofRange_<T>(std::min(min, rg.min), std::max(max, rg.max));
    }
	ofRange_<T>& operator+=( const ofRange_<T>& rg ) {
        min = std::min(min, rg.min);
        max = std::max(max, rg.max);
        return *this;
    }
	//intersection
	inline ofRange_<T>  operator -(const ofRange_<T>& rg) const {
        //	if(!ofRange_<T>::intersects(rg)) return ofRange_<T>(0,0);
        return ofRange_<T>(std::max(min, rg.min), std::min(max, rg.max));
    }

	inline ofRange_<T>& operator-=(const ofRange_<T>& rg) {
        //	if(!ofRange_<T>::intersects(rg)) return ofRange_<T>(0,0);
        min = std::max(min, rg.min);
        max = std::min(max, rg.max);
        return *this;
    }

    ofRange_<T>& operator = (const ofRange_<T>& rg) {
        set(rg);
        return *this;
    }
    
	ofRange_<T>  operator +( const T f ) const {
        return ofRange_<T>(min+f, max+f);
    }
	
    inline ofRange_<T>& operator+=( const T f ) {
        min += f;
        max += f;
        return *this;
    }

	inline ofRange_<T>  operator -( const T f ) const {
        return ofRange_<T>(min-f, max-f);
    }
	
    inline ofRange_<T>& operator-=( const T f ) {
        min -= f;
        max -= f;
        return *this;
    }
	
    
	
    inline friend std::ostream& operator<<(std::ostream& os, const ofRange_<T>& rg) {
        os << "[" << rg.min << " - " << rg.max << "]";
        return os;
    }
    
    inline friend std::istream& operator>>(std::istream& is, ofRange_<T>& rg) {
        is.ignore(1);
        is >> rg.min;
        is.ignore(3);
        is >> rg.max;
        is.ignore(1);
        return is;
    }

    union  {
        struct {
            T min;
            T max;
        };
        T r[2];
    };	
    
    
};

//non member ops
template<typename T>
ofRange_<T> operator+( T f, const ofRange_<T>& vec );
template<typename T>
ofRange_<T> operator-( T f, const ofRange_<T>& vec );


template<typename T>
inline ofRange_<T> operator+( T f, const ofRange_<T>& rg ){
	return ofRange_<T>(f + rg.min, f + rg.max);
}

template<typename T>
inline ofRange_<T> operator-( T f, const ofRange_<T>& rg ){
	return ofRange_<T>(f - rg.min, f - rg.max);
};





typedef ofRange_<char>   ofCharRange;
typedef ofRange_<float>  ofFloatRange;
typedef ofFloatRange     ofRange;
typedef ofRange_<double> ofDoubleRange;
typedef ofRange_<int>    ofIntRange;
typedef ofRange_<long>   ofLongRange;

typedef ofRange_<int8_t> ofRange8;
typedef ofRange_<int16_t> ofRange16;
typedef ofRange_<int32_t> ofRange32;
typedef ofRange_<int64_t> ofRange64;

typedef ofRange_<uint8_t> ofRange8u;
typedef ofRange_<uint16_t> ofRange16u;
typedef ofRange_<uint32_t> ofRange32u;
typedef ofRange_<uint64_t> ofRange64u;
