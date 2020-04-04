#pragma once

#include "ofMain.h"
#include "ofxLineaDeTiempo.h"
//#include "ofxMUI.h"
#include "TracksPanelController.h"
#include "ofxGui.h"

using namespace ofx::LineaDeTiempo;

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;
	void update() override;
	
	void keyReleased(int key) override;
	

	// simply declare an ofxLineaDeTiempo instance.
	ofxLineaDeTiempo timeline = {"Timeline"};

	
	// just use a regular ofxPanel object. Does not matter how you initialize it or
	// how you add elements to it.
	
	ofxPanel gui;
	
	
	// I personally prefer instancing ofParameters instead of ofxGui's gui elements, as sliders or buttons.
	// But you can do it either way to.
	




	ofParameterGroup numbersGroup = {"numbersGroup"};
	ofParameterGroup glmGroup     = {"glmGroup"};
	ofParameterGroup colorGroup   = {"colorGroup"};
	
	
	// just making all the parameter types suported by ofxGui. You dont need this, just use as you need.
	// Tip: did you notice the nice way of declaring and initializing the ofParametrs using the curly brackets?
	// That's a newish C++ thing, not specific to ofParameter. These are called initializer lists.
	
	ofParameter <int32_t>      _param_int32_t      = {"int32_t"      ,      int32_t(0) ,  std::numeric_limits<int32_t>::min() ,  std::numeric_limits<int32_t>::max()};
	ofParameter <uint32_t>     _param_uint32_t     = {"uint32_t"     ,     uint32_t(0) , std::numeric_limits<uint32_t>::min() , std::numeric_limits<uint32_t>::max()};
	ofParameter <int64_t>      _param_int64_t      = {"int64_t"      ,      int64_t(0) ,  std::numeric_limits<int64_t>::min() ,  std::numeric_limits<int64_t>::max()};
	ofParameter <uint64_t>     _param_uint64_t     = {"uint64_t"     ,     uint64_t(0) , std::numeric_limits<uint64_t>::min() , std::numeric_limits<uint64_t>::max()};
	ofParameter <int8_t>       _param_int8_t       = {"int8_t"       ,       int8_t(0) ,   std::numeric_limits<int8_t>::min() ,   std::numeric_limits<int8_t>::max()};
	ofParameter <uint8_t>      _param_uint8_t      = {"uint8_t"      ,      uint8_t(0) ,  std::numeric_limits<uint8_t>::min() ,  std::numeric_limits<uint8_t>::max()};
	ofParameter <int16_t>      _param_int16_t      = {"int16_t"      ,      int16_t(0) ,  std::numeric_limits<int16_t>::min() ,  std::numeric_limits<int16_t>::max()};
	ofParameter <uint16_t>     _param_uint16_t     = {"uint16_t"     ,     uint16_t(0) , std::numeric_limits<uint16_t>::min() , std::numeric_limits<uint16_t>::max()};
	ofParameter <size_t>       _param_size_t       = {"size_t"       ,       size_t(0) ,   std::numeric_limits<size_t>::min() ,   std::numeric_limits<size_t>::max()};
	ofParameter <float>        _param_float        = {"float"        ,        float(0) ,    std::numeric_limits<float>::min() ,    std::numeric_limits<float>::max()};
	ofParameter <double>       _param_double       = {"double"       ,       double(0) ,   std::numeric_limits<double>::min() ,   std::numeric_limits<double>::max()};
	ofParameter <bool>         _param_bool         = {"bool"         ,         true};
	ofParameter <void>         _param_void         = {"void"};
	ofParameter <ofColor>      _param_ofColor      = {"ofColor"      , 		ofColor(0) ,      ofColor::black ,      ofColor::white};
	ofParameter <ofShortColor> _param_ofShortColor = {"ofShortColor" , ofShortColor(0) , ofShortColor::black , ofShortColor::white};
	ofParameter <ofFloatColor> _param_ofFloatColor = {"ofFloatColor" , ofFloatColor(0) , ofFloatColor::black , ofFloatColor::white};
	ofParameter<glm::vec2>     _param_Vec2         = {"glm::vec2"    ,     glm::vec2(0),        glm::vec2(-1),        glm::vec2(1)};
	ofParameter<glm::vec3>     _param_Vec3         = {"glm::vec3"    ,     glm::vec3(0),        glm::vec3(-1),        glm::vec3(1)};
	ofParameter<glm::vec4>     _param_Vec4         = {"glm::vec4"    ,     glm::vec4(0),        glm::vec4(-1),        glm::vec4(1)};


	
	
	
	
	bool bDrawGui = true;
	
};
