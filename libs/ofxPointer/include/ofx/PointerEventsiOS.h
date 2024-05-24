//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofConstants.h"


#if defined(TARGET_OF_IOS)


#include "ofxiOS.h"
#include "ofEvents.h"
#include "ofAppBaseWindow.h"
#include "ofAppRunner.h"
#include "ofx/PointerEvents.h"


/// \brief PointerView is a UIView subclass that intercepts and transforms touches as PointerEvents.
/// \todo Update the UIView size in response to size changes.
@interface PointerView: UIView {

@protected
    /// \brief A pointer to the current iOS window.
    ///
    /// This may not be necessary as there can only be one window currently
    /// accessible by calling ofxiOSGetOFWindow().
    ofAppiOSWindow* _window;

    ofxiOSGLKView* _viewGLK;
    ofxiOSEAGLView* _viewEAGL;

    /// \brief The start time of the program to calculate set timestamps based on elapsed time.
    NSTimeInterval _startTimeSeconds;

    /// \brief Keep track of active pointers based on UITouchType.
    std::map<UITouchType, std::set<int64_t>> _activePointerIndices;

    /// \brief Keep track of the primary pointer for each UITouchType.
    std::map<UITouchType, int64_t> _primaryPointerIndices;

}

- (void)resetTouches;

/// \brief Convert UITouch data to PointerEventArgs values.
- (ofx::PointerEventArgs)toPointerEventArgs:(UIView*) view
                                  withTouch:(UITouch*) touch
                                  withEvent:(UIEvent*) event
                                  withPointerIndex:(int64_t) pointerIndex
                                  withCoalesced:(bool)_isCoalesced
                                  withPredicted:(bool)_isPredicted
                                  withUpdate:(bool)_isUpdate;

/// \brief Orient the touch point depending on the current orientation.
- (CGPoint)orientateTouchPoint:(CGPoint)touchPoint;

@end


namespace ofx {


/// \brief This must be called to add the PointerView to the primary iOS window.
/// \warning This will disable events that are automatically sent to ofBaseApp.
void EnableAdvancedPointerEventsiOS();

/// \brief This must be called to remove the PointerView from the primary iOS window.
void DisableAdvancedPointerEventsiOS();


template <class ListenerClass>
void RegisterAdvancedPointerEventsiOS(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    EnableAdvancedPointerEventsiOS();
    RegisterPointerEventsForWindow<ListenerClass>(ofGetWindowPtr(), listener, prio);
    ofAddListener(ofx::PointerEventsManager::instance().eventsForWindow(ofGetWindowPtr())->pointerUpdate,
                  listener,
                  &ListenerClass::onPointerUpdate, prio);
}


template <class ListenerClass>
void UnregisterAdvancedPointerEventsiOS(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    UnregisterPointerEventsForWindow<ListenerClass>(ofGetWindowPtr(), listener, prio);
    ofRemoveListener(ofx::PointerEventsManager::instance().eventsForWindow(ofGetWindowPtr())->pointerUpdate,
                     listener,
                     &ListenerClass::onPointerUpdate, prio);
    DisableAdvancedPointerEventsiOS();
}


template <class ListenerClass>
void RegisterAdvancedPointerEventiOS(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    EnableAdvancedPointerEventsiOS();
    RegisterPointerEventForWindow<ListenerClass>(ofGetWindowPtr(), listener, prio);
    ofAddListener(ofx::PointerEventsManager::instance().eventsForWindow(ofGetWindowPtr())->pointerUpdate,
                  listener,
                  &ListenerClass::onPointerEvent, prio);
}


template <class ListenerClass>
void UnregisterAdvancedPointerEventiOS(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    UnregisterPointerEventForWindow<ListenerClass>(ofGetWindowPtr(), listener, prio);
    ofRemoveListener(ofx::PointerEventsManager::instance().eventsForWindow(ofGetWindowPtr())->pointerUpdate,
                     listener,
                     &ListenerClass::onPointerEvent, prio);
    DisableAdvancedPointerEventsiOS();
}


} // namespace ofx


#endif
