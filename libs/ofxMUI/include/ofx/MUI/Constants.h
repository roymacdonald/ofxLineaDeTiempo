//
//  Constants.h
//  ofxMUI_scrollbars
//
//  Created by Roy Macdonald on 2/6/20.
//

#pragma once
 
#define SCROLL_BAR_SIZE 20
#define CONTAINER_MARGIN 3
	
///\ this is the minimum size factor that defines the minimum distance between the in and out zoom handles.
///  it is a factor of SCROLL_BAR_SIZE, thus the real minimum distance is found by SCROLL_BAR_SIZE*SCROLLER_MIN_SIZE_FACTOR
#define SCROLLER_MIN_SIZE_FACTOR 1.5

#define HANDLE_MIN_SIZE (SCROLL_BAR_SIZE*(SCROLLER_MIN_SIZE_FACTOR+2))


#define EDGE_HANDLE_SIZE 5
