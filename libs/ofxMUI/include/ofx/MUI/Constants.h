//
//  Constants.h
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#pragma once

namespace ofx {
namespace MUI {


class ConstVars{

public:

static void enableHiDpi()
{
	_displayScaleFactor = 2;
}


static void disableHiDpi()
{
	_displayScaleFactor = 1;
}


static bool isHiDpiEnabled()
{
	return (_displayScaleFactor ==  2);
}


static int getScrollBarSize(){ 
		return 20 * _displayScaleFactor;
}


static int getContainerMargin(){ 
	return 3 * _displayScaleFactor;
}
	
///\ this is the minimum size factor that defines the minimum distance between the in and out zoom handles.
///  it is a factor of SCROLLBARSIZE, thus the real minimum distance is found by SCROLLBARSIZE*SCROLLERMINSIZEFACTOR
static float getScrollerMinSizeFactor(){ 
	return 1.5 ;
}

static float getHandleMinSize(){ 
	return (getScrollBarSize()*(getScrollerMinSizeFactor()+2));
}


static int getEdgeHandleSize(){ 
	return 5  * _displayScaleFactor;
}


static int getDisplayScaleFactor(){
    return _displayScaleFactor;
}
    

private:
	static int _displayScaleFactor;

};

// #define SCROLL_BAR_SIZE 20
// #define CONTAINER_MARGIN 3
	
// ///\ this is the minimum size factor that defines the minimum distance between the in and out zoom handles.
// ///  it is a factor of SCROLL_BAR_SIZE, thus the real minimum distance is found by SCROLL_BAR_SIZE*SCROLLER_MIN_SIZE_FACTOR
// #define SCROLLER_MIN_SIZE_FACTOR 1.5

// #define HANDLE_MIN_SIZE (SCROLL_BAR_SIZE*(SCROLLER_MIN_SIZE_FACTOR+2))


// #define EDGE_HANDLE_SIZE 5

} } // ofx::MUI
