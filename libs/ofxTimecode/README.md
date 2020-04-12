# ofxTimecode

ofxTimecode is a simple class for converting between frames, seconds, milliseconds, and SMPTE representation (HH:MM:SS:FRAME) for time.

Useful for displaying times as strings, or saving/pulling human readable times from xml

It stores a frame rate internally and is easily combined with ofGetElapsedTimef(), ofGetElapsedMillis(), and ofGetFrameNum() as well as ofxMSATimer.



History:

v. 00 July 22nd 2012

* first version, fairly untested but functional

* example-smpte shows very simple use case, and shows how ofGetElapsedTimef() always differs from ofGetFrameNum()



Developed by James George at YCAM InterLab as part of the ofxTimeline project.

http://interlab.ycam.jp/en/ // http://www.jamesgeorge.org
