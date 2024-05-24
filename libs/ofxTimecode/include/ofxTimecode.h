/**
 * ofxTimecode
 * James George 2012
 *
 * Created as part of the Duration + ofxTimeline project
 * Supported by YCAM InterLab Guest Research Project ( http://interlab.ycam.jp/en/ )
 *
 */

#pragma once

#include <cstdint>//"ofMain.h"
#include <string>

class ofxTimecode {
  public:
//    ofxTimecode();
    
    void                setFPS(float fps); //default is 30;
    float               getFPS();
    
    //these functions expect format HH:MM:SS:MLS
    //and negative value if improperly formatted
	static uint64_t     millisForTimecode(std::string timecode);
    static float        secondsForTimecode(std::string timecode);

    uint64_t            frameForTimecode(std::string timecode);
    uint64_t            frameForSeconds(float timeInSeconds);
    uint64_t            frameForMillis(uint64_t timeInMillis);    
    float               secondsForFrame(uint64_t frame);
    uint64_t            millisForFrame(uint64_t frame);

    static uint64_t     frameForTimecode(std::string timecode, float fps);
    static uint64_t     frameForSeconds(float timeInSeconds, float fps);
    static uint64_t     frameForMillis(uint64_t timeInMillis, float fps);
    static float        secondsForFrame(uint64_t frame, float fps);
    static uint64_t     millisForFrame(uint64_t frame, float fps);
    
    //returns format HH:MM:SS:FR
    static std::string  timecodeForMillis(uint64_t millis, std::string millisDelimiter = ":");
    static std::string  timecodeForSeconds(float seconds, std::string millisDelimiter = ":");
    static std::string  timecodeForFrame(uint64_t frame, float fps, std::string millisDelimiter = ":");
    std::string         timecodeForFrame(uint64_t frame, std::string millisDelimiter = ":");
    
  protected:
    float fps = 30.0f;
    static bool decodeString(std::string time, int* times);
};
