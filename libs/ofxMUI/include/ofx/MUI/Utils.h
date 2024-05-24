//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <cmath>
#include <limits>
#include <algorithm>
//#include "ofxMUI.h"
#include "ofx/DOM/Element.h"
#include "ofRange.h"
// #include "ofMath.h"


namespace ofx {
namespace MUI {


class Math
{
public:
	
    static double lerp(double inputValue,
                       double inputMin,
                       double inputMax,
                       double outputMin,
                       double outputMax,
                       bool clampOutput = false)
    {
        if (std::fabs(inputMin - inputMax) < std::numeric_limits<double>::epsilon())
        {
            return outputMin;
        }
        else
        {
            double outputValue = ((inputValue - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

            if (clampOutput)
            {
                return clamp(outputValue, outputMin, outputMax);
            }
            else
            {
                return outputValue;
            }
        }
    }

	
	static double lerpl(long double inputValue,
                        long double inputMin,
                        long double inputMax,
                        long double outputMin,
                        long double outputMax,
						bool clampOutput = false)
    {
		
		
#if defined TARGET_OSX || (defined TARGET_WIN32 && defined _MSC_VER)
        if (std::fabsl(inputMin - inputMax) < std::numeric_limits<long double>::epsilon())
#else
		if (std::fabs(inputMin - inputMax) < std::numeric_limits<long double>::epsilon())
#endif
        {
            return outputMin;
        }
        else
        {
            long double outputValue = ((inputValue - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

            if (clampOutput)
            {
                return clamp(outputValue, outputMin, outputMax);
            }
            else
            {
                return outputValue;
            }
        }
    }
	
	

    template <typename Type>
    static Type clamp(const Type& inputValue, const Type& inputMin, const Type& inputMax)
    {
        return std::max(inputMin, std::min(inputValue, inputMax));
    }



	
};


static bool setPosIfNonEqual(DOM::Element* e, const glm::vec2& pos){
    if(e->getPosition() == pos)return false;
    e->setPosition(pos);
    return true;
}
static bool setShapeIfNonEqual(DOM::Element* e, const ofRectangle& shape){
    if(e->getShape() == shape)return false;
    e->setShape(shape);
    return true;
}
static bool setSizeIfNonEqual(DOM::Element* e, const glm::vec2& size){
    if(e->getSize() == size)return false;
    e->setSize(size.x, size.y);
    return true;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
setFloatIfNonEqual(T& subject, const T&target){
    if(ofIsFloatEqual(subject, target))return false;
    subject = target;
    return true;
}

static bool setRangeIfNonEqual(ofRange& subject, const ofRange& target){
    if(subject == target ) return false;
    subject = target;
    return true;
    
}
template<typename T>
static
typename std::enable_if<std::is_floating_point<T>::value, void>::type  avoidZero(ofRange_<T>& range){
    if(ofIsFloatEqual(range.min, range.max)){
        if(ofIsFloatEqual(range.min, 0.0f)){
            range.max += std::numeric_limits<T>::epsilon();
        }else{
            range.min += std::numeric_limits<T>::epsilon();
        }
    }
}

/// this makes the span to never be less than the minimum,
/// if it is, it will "grow" the span so it is the minimum
/// while still keeping the bounds
template<typename T>
static
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
keepRangeMinSpan(ofRange_<T>& r, const T& minSpan,  const ofRange_<T>& bounds)
{
    if(std::is_floating_point<T>::value){
        if(ofIsFloatEqual(minSpan, T(0))){
            std::cout << "keepRangeMinSpan: minimum can not be zero";
            return;
        }
    }else if(minSpan == 0){
        std::cout << "keepRangeMinSpan: minimum can not be zero";
        return;
    }
    if(r.span() < minSpan){
    
        r.max += minSpan;
        if(r.max > bounds.max){
            r.min -= (r.max - bounds.max);
        }
        r.min = MIN( MAX(bounds.min, r.min) ,bounds.max);
        r.max = MIN( MAX(bounds.min, r.max) ,bounds.max);
    }
}


static std::string elementStructureToString(std::stringstream& ss, ofx::DOM::Element* e, std::string prefix){
    if(e){
        ss << prefix << e->getId() << " - " << e->getShape() << "\n";
        
        prefix += "    ";
        for(auto c: e->children()){
            elementStructureToString(ss, c, prefix);
        }
    }
    return ss.str();
}

static void printStructure(ofx::DOM::Element* e){
    std::stringstream ss;
    std::cout << elementStructureToString(ss, e, "    ") << "\n";
}



} } // ofx::MUI
