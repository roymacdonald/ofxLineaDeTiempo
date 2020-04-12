/**
 * ofxTimecode
 * James George 2012
 *
 * Created as part of the Duration + ofxTimeline project
 * Supported by YCAM InterLab Guest Research Project ( http://interlab.ycam.jp/en/ )
 *
 */

#include "ofxTimecode.h"
#include "ofUtils.h"
#include "ofLog.h"

//ofxTimecode::ofxTimecode(){
//    fps = 30;
//}
    
void ofxTimecode::setFPS(float _fps){
    if(fps < 1){
        ofLogError("ofxTimecode::setFPS invalid FPS set");
        return;
    }
	fps = _fps;
}

float ofxTimecode::getFPS(){
    return fps;
}
    
//expects format HH:MM:SS:MLS
uint64_t ofxTimecode::millisForTimecode(std::string timecode){
    int times[4];
    if(decodeString(timecode, times)){
               //hours						
    	return times[0] * 60 * 60 * 1000 + 
               //minutes
               times[1] * 60 * 1000 +
               //seconds
               times[2] * 1000 +
               //millis
               times[3];
        
    }
	return -1;
}

std::string ofxTimecode::timecodeForMillis(uint64_t millis, std::string millisDelimiter){
    char buf[512];
	sprintf(buf, "%02d:%02d:%02d%s%03d", int(millis / (60 * 60 * 1000)),  //hours
            						    int((millis / (60 * 1000)) % 60), //minutes
            						    int((millis / 1000) % 60), 		//seconds
            							millisDelimiter.c_str(),
                                        int(millis % 1000));
//    sprintf(buf, "%ld", millis);

    return std::string(buf);
}

//expects format HH:MM:SS:FR
float ofxTimecode::secondsForTimecode(std::string timecode){
    return millisForTimecode(timecode) / 1000.;
}

//---------------------------------------------------------------------------------------------------------------------
uint64_t ofxTimecode::frameForSeconds(float timeInSeconds, float fps){
    return timeInSeconds * fps;
}
uint64_t ofxTimecode::frameForSeconds(float timeInSeconds){
    return frameForSeconds(timeInSeconds, fps);
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t ofxTimecode::frameForMillis(uint64_t timeInMillis, float fps){
    return timeInMillis * fps / 1000;
}
uint64_t ofxTimecode::frameForMillis(uint64_t timeInMillis){
    return frameForMillis(timeInMillis, fps);
}
//---------------------------------------------------------------------------------------------------------------------
float ofxTimecode::secondsForFrame(uint64_t frame, float fps){
    return frame / fps;
}
float ofxTimecode::secondsForFrame(uint64_t frame){
    return secondsForFrame(frame, fps);
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t ofxTimecode::millisForFrame(uint64_t frame, float fps){
	return frame * 1000 / fps;    
}
uint64_t ofxTimecode::millisForFrame(uint64_t frame){
    return millisForFrame(frame, fps);
}
//---------------------------------------------------------------------------------------------------------------------
uint64_t ofxTimecode::frameForTimecode(std::string timecode, float fps){
    return frameForMillis(millisForTimecode(timecode), fps);

}
uint64_t ofxTimecode::frameForTimecode(std::string timecode){
    return frameForTimecode(timecode, fps);
}
//---------------------------------------------------------------------------------------------------------------------
std::string ofxTimecode::timecodeForSeconds(float seconds, std::string millisDelimiter){
    return timecodeForMillis(seconds*1000, millisDelimiter);
}
    
std::string ofxTimecode::timecodeForFrame(uint64_t frame, std::string millisDelimiter){
    return timecodeForMillis(millisForFrame(frame), millisDelimiter);
}

bool ofxTimecode::decodeString(std::string time, int* times){
	ofStringReplace(time, ",", ":");
    ofStringReplace(time, ";", ":");
    std::vector<std::string> split = ofSplitString(time, ":");
    if(split.size() != 4){
        ofLogError("ofxTimecode::decodeString -- incorrect timecode");
        return false;
    }
    for(uint64_t i = 0; i < split.size(); i++){
    	times[i] = ofToInt(split[i]);
    }
    return true;
}
