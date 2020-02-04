# ofxLineaDeTiempo

A new timeline addon for openFrameworks.

## Introduction

Several years ago [ofxTimeline](https://github.com/YCAMInterlab/ofxTimeline) was created by [James George](https://github.com/obviousjim/). It was a really complete but it was never properly mantained and though the years it has become increasingly dificult to make it work. As such there has been an increasing need for a timeline addon within the openFrameworks community, where some have modified ofxTimeline to fit their needs but it has been alwasy something cumbersome and time consuming. ofxLineaDeTiempo comes into play in order to fulfill this need, making it easy to anyone to get a functional timeline with both basic and advanced features with minimal coding.

As I could not use ofxTimeline as the name of this addon, ofxTimeline2 sounded boring. As I am a native Spanish speakeer it made sense to use a Spanish word instead.
**Linea De Tiempo** is the literal translation of **Timeline** into Spanish.


## Goals

* Make an usable timeline from both the coding and user points of view.
* Rely heavily on openFrameworks interanal classes and functionalities.
* An `ofParameter` is held by each timeline track.
* As a consequence, `ofxGui` will be an integral part of the addon.
* Behave in a similar usage to `ofxPanel` so the code for it can be directly swapped with an instance of this addon.
* The renderer is a different class which will allow to customize its visual appearance as well as having specialized timeline tracks (ie. video and audio)
* Have an optimized rendering, redrawing only when needed. 

## License

This addon's license is stated in the `license.md` file.

Installation
------------
Copy or clone this addon into your `openFrameworks/addons/` folder.
Make sure you have all the dependencies installed as well.

Dependencies
------------
What other addons are needed to properly work with this one?




