//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofConstants.h"


#if defined(TARGET_OSX)


#import <AppKit/NSEvent.h>


#include "ofx/PointerEventsMacOS.h"
#include "ofx/PointerEvents.h"
#include "ofMath.h"


using namespace ofx;
//
//
//@implementation NativePointerInput
//{
//    int device;
//    id eventMonitor;
//    // callback instance.
//    // start time.
//}
//
//
//- (id)initWithDevice:(int)_device
//{
//    if ((self = [super init]))
//    {
//        device = _device;
//
//        uint64_t tabletMask = 0;
//
//        tabletMask |= NSLeftMouseDownMask;
//        tabletMask |= NSLeftMouseUpMask;
//        tabletMask |= NSRightMouseDownMask;
//        tabletMask |= NSRightMouseUpMask;
//        tabletMask |= NSMouseMovedMask;
//        tabletMask |= NSLeftMouseDraggedMask;
//        tabletMask |= NSRightMouseDraggedMask;
//
//        id handler = [NSEvent addLocalMonitorForEventsMatchingMask: tabletMask
//                                                           handler: ^(NSEvent *event)
//                      {
//                          switch ([event subtype])
//                          {
//                              case NX_SUBTYPE_TABLET_POINT:
//                              case NX_SUBTYPE_TABLET_PROXIMITY:
//                              {
////                                  ofx::TabletData data;
////
////                                  if ([event type] == NSLeftMouseDown || [event type] == NSRightMouseDown)
////                                  {
////                                      data.eventType = ofx::TabletData::DOWN;
////                                  }
////                                  else if ([event type] == NSLeftMouseUp || [event type] == NSRightMouseUp)
////                                  {
////                                      data.eventType = ofx::TabletData::UP;
////                                  }
////                                  else
////                                  {
////                                      data.eventType = ofx::TabletData::MOVE;
////                                  }
////
////                                  data.evt = [event type];
////
////                                  data.absX = [NSEvent mouseLocation].x;
////                                  data.absY = [NSEvent mouseLocation].y;
////                                  data.absZ = 0;
////
////                                  data.x = [NSEvent mouseLocation].x;
////                                  data.y = [NSEvent mouseLocation].y;
////
////                                  data.tiltX = [event tilt].x;
////                                  data.tiltY = [event tilt].y;
////                                  data.pressure = [event pressure];
////                                  data.rotation = [event rotation];
////                                  data.tangentialPressure = [event tangentialPressure];
////
////                                  data.isProximityEvent = [event isEnteringProximity];
////
////                                  data.button = [event buttonNumber];
////                                  data.pointerID = [event pointingDeviceID];
////                                  data.deviceID = [event deviceID];
////
////                                  data.clickCount = [event clickCount];
////
////                                  data.vendorID = [event vendorID];
////
////                                  data.vendorPointerType = [event vendorPointingDeviceType];
////
////                                  NSTimeInterval timestampSeconds = [event timestamp];
////                                  NSTimeInterval elapsedTimestampSeconds = timestampSeconds - _startTimeSeconds;
////                                  data.timestampMicros = elapsedTimestampSeconds * 1000000.0;
////
////                                  ofx::Tablet::callback(data);
//                              }
//                                  break;
//                              case NX_SUBTYPE_DEFAULT:
//                                  // If the pen tablet sends events of this subtype,
//                                  // it probably means the driver is not installed
//                                  // and the OS is treating it as a mouse.
//                                  break;
//                              default:
//                                  break;
//                          }
//
//                          return event;
//
//                      }];
//
////        eventMonitor = [NSEvent addLocalMonitorForEventsMatchingMask:(NSEventMaskLeftMouseDown | NSEventMaskLeftMouseUp)
////                                                                   handler:^(NSEvent *theEvent) {
////                                                                       [self postMouseState:theEvent];
////                                                                       return theEvent;
////                                                                   }];
////
////        dragEventMonitor = [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseDragged
////                                                                 handler:^(NSEvent *theEvent) {
////                                                                     [self postMouseLocation:theEvent];
////                                                                     return theEvent;
////                                                                 }];
//    }
//
//    return self;
//}
//
//
//
//
//
//
//
//////
//////UITouchProperties toUITouchProperties(const std::set<std::string>& properties)
//////{
//////    UITouchProperties result = 0;
//////
//////    for (const auto& property: properties)
//////    {
//////        if (property == PointerEventArgs::PROPERTY_PRESSURE)
//////            result &= UITouchPropertyForce;
//////        else if (property == PointerEventArgs::PROPERTY_TILT_X || property == PointerEventArgs::PROPERTY_TILT_Y)
//////            result &= (UITouchPropertyAzimuth & UITouchPropertyAltitude);
//////        else if (property == PointerEventArgs::PROPERTY_POSITION)
//////            result &= UITouchPropertyLocation;
//////        else
//////            ofLogWarning("toUITouchProperties") << "Unknown UITouchProperty: " << property;
//////    }
//////
//////    return result;
//////}
//////
//////
//////std::set<std::string> toPopertySet(UITouchProperties properties)
//////{
//////    std::set<std::string> result;
//////
//////    if (properties & UITouchPropertyForce)
//////        result.insert(PointerEventArgs::PROPERTY_PRESSURE);
//////
//////    if (properties & UITouchPropertyAzimuth || properties & UITouchPropertyAltitude)
//////        result.insert({ PointerEventArgs::PROPERTY_TILT_X, PointerEventArgs::PROPERTY_TILT_Y });
//////
//////    if (properties & UITouchPropertyLocation)
//////        result.insert(PointerEventArgs::PROPERTY_POSITION);
//////
//////    return result;
//////}
////
////
////bool dispatchPointerEvent(ofAppBaseWindow* window, PointerEventArgs& e)
////{
////    bool consumed = false;
////
////    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().eventsForWindow(window);
////
////    if (events)
////    {
////        // All pointer events get dispatched via pointerEvent.
////        consumed = ofNotifyEvent(events->pointerEvent, e, window);
////
////        // If the pointer was not consumed, then send it along to the standard five.
////        if (!consumed)
////        {
////            if (e.eventType() == PointerEventArgs::POINTER_DOWN)
////            {
////                consumed = ofNotifyEvent(events->pointerDown, e, window);
////            }
////            else if (e.eventType() == PointerEventArgs::POINTER_UP)
////            {
////                consumed = ofNotifyEvent(events->pointerUp, e, window);
////            }
////            else if (e.eventType() == PointerEventArgs::POINTER_MOVE)
////            {
////                consumed = ofNotifyEvent(events->pointerMove, e, window);
////            }
////            else if (e.eventType() == PointerEventArgs::POINTER_CANCEL)
////            {
////                consumed = ofNotifyEvent(events->pointerCancel, e, window);
////            }
////            else if (e.eventType() == PointerEventArgs::POINTER_UPDATE)
////            {
////                consumed = ofNotifyEvent(events->pointerUpdate, e, window);
////            }
////        }
////    }
////    else
////    {
////        ofLogError("PointerViewIOS::touchesEnded") << "Invalid event, passing.";
////    }
////
////    // TODO address consumeLegacy events.
////    return /*events->consumeLegacyEvents ||*/ consumed;
////}
////
////
////
////
////@implementation PointerView
////
////- (id)initWithFrame:(CGRect)frame
////{
////    self = [super initWithFrame:frame];
////    self.multipleTouchEnabled = true;
////
////    _window = ofxiOSGetOFWindow();
////
////    if(_window->getWindowControllerType() == METAL_KIT
////    || _window->getWindowControllerType() == GL_KIT)
////    {
////        if ([ofxiOSGLKView getInstance])
////            _viewGLK = [ofxiOSGLKView getInstance];
////    }
////    else
////    {
////        if ([ofxiOSEAGLView getInstance])
////            _viewEAGL = [ofxiOSEAGLView getInstance];
////    }
////
////    _startTimeSeconds = [[NSProcessInfo processInfo] systemUptime];
////
////    [self resetTouches];
////
////    return self;
////}
////
////- (void)dealloc
////{
////    [super dealloc];
////}
////
////
////-(void) resetTouches
////{
////    _activePointerIndices[UITouchTypeDirect] = {};
////    _activePointerIndices[UITouchTypeIndirect] = {};
////#if defined(__IPHONE_9_1)
////    _activePointerIndices[UITouchTypeStylus] = {};
////#endif
////    _primaryPointerIndices[UITouchTypeDirect] = -1;
////    _primaryPointerIndices[UITouchTypeIndirect] = -1;
////#if defined(__IPHONE_9_1)
////    _primaryPointerIndices[UITouchTypeStylus] = -1;
////#endif
////}
////
////
////- (void)willMoveToSuperview:(UIView *)newSuperview;
////{
////    [self resetTouches];
////}
////
////
////- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
////{
////    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();
////
////    if (events)
////    {
////        for (UITouch* touch in touches)
////        {
////            auto evt = [self toPointerEventArgs:(_viewGLK ? _viewGLK : _viewEAGL)
////                                      withTouch:touch
////                                      withEvent:event
////                               withPointerIndex:[touch hash]
////                                  withCoalesced:false
////                                  withPredicted:false
////                                     withUpdate:false];
////            dispatchPointerEvent(_window, evt);
////        }
////    }
////    else
////    {
////        ofLogError("PointerViewIOS::touchesBegan") << "Invalid event, passing.";
////        [super touchesBegan:touches withEvent:event];
////    }
////}
////
////- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
////{
////    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();
////
////    if (events)
////    {
////        for (UITouch* touch in touches)
////        {
////            auto evt = [self toPointerEventArgs:(_viewGLK ? _viewGLK : _viewEAGL)
////                                      withTouch:touch
////                                      withEvent:event
////                               withPointerIndex:[touch hash]
////                                  withCoalesced:false
////                                  withPredicted:false
////                                     withUpdate:false];
////            dispatchPointerEvent(_window, evt);
////        }
////    }
////    else
////    {
////        ofLogError("PointerViewIOS::touchesMoved") << "Invalid event, passing.";
////        [super touchesMoved:touches withEvent:event];
////    }
////}
////
////- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
////{
////    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();
////
////    if (events)
////    {
////        for (UITouch* touch in touches)
////        {
////            auto evt = [self toPointerEventArgs:(_viewGLK ? _viewGLK : _viewEAGL)
////                                      withTouch:touch
////                                      withEvent:event
////                               withPointerIndex:[touch hash]
////                                  withCoalesced:false
////                                  withPredicted:false
////                                     withUpdate:false];
////            dispatchPointerEvent(_window, evt);
////        }
////    }
////    else
////    {
////        ofLogError("PointerViewIOS::touchesEnded") << "Invalid event, passing.";
////        [super touchesEnded:touches withEvent:event];
////    }
////}
////
////
////- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
////{
////    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();
////
////    if (events)
////    {
////        for (UITouch* touch in touches)
////        {
////            auto evt = [self toPointerEventArgs:(_viewGLK ? _viewGLK : _viewEAGL)
////                                      withTouch:touch
////                                      withEvent:event
////                               withPointerIndex:[touch hash]
////                                  withCoalesced:false
////                                  withPredicted:false
////                                     withUpdate:false];
////            dispatchPointerEvent(_window, evt);
////        }
////    }
////    else
////    {
////        ofLogError("PointerViewIOS::touchesCancelled") << "Invalid event, passing.";
////        [super touchesCancelled:touches withEvent:event];
////    }
////}
////
////
////#ifdef __IPHONE_9_1
////- (void)touchesEstimatedPropertiesUpdated:(NSSet<UITouch *> *)touches NS_AVAILABLE_IOS(9_1);
////{
////    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();
////
////    if (events)
////    {
////        for (UITouch* touch in touches)
////        {
////            auto evt = [self toPointerEventArgs:(_viewGLK ? _viewGLK : _viewEAGL)
////                                      withTouch:touch
////                                      withEvent:nil
////                               withPointerIndex:[touch hash]
////                                  withCoalesced:false
////                                  withPredicted:false
////                                     withUpdate:true
////                                ];
////            dispatchPointerEvent(_window, evt);
////        }
////    }
////    else
////    {
////        ofLogError("PointerViewIOS::touchesEstimatedPropertiesUpdated") << "Invalid event, passing.";
////        [super touchesEstimatedPropertiesUpdated:touches];
////    }
////}
////#endif
////
////
////- (ofx::PointerEventArgs)toPointerEventArgs:(UIView*)view
////                                  withTouch:(UITouch*)touch
////                                  withEvent:(UIEvent*)event
////                                  withPointerIndex:(int64_t)_pointerIndex
////                                  withCoalesced:(bool)_isCoalesced
////                                  withPredicted:(bool)_isPredicted
////                                     withUpdate:(bool)_isUpdate
////{
////    CGFloat majorRadius = 0.5;
////    CGFloat majorRadiusTolerance = 0;
////
////#if defined(__IPHONE_8_0)
////    majorRadius = [touch majorRadius];
////    majorRadiusTolerance = [touch majorRadiusTolerance];
////#endif
////
////    PointShape shape(PointShape::ShapeType::ELLIPSE,
////                     majorRadius * 2,
////                     majorRadiusTolerance * 2);
////
////    CGPoint position;
////    CGPoint precisePosition;
////
////    position = [touch locationInView:view];
////    position.x *= view.contentScaleFactor;
////    position.y *= view.contentScaleFactor;
////    position = [self orientateTouchPoint:position];
////
////#if defined(__IPHONE_9_1)
////    precisePosition = [touch preciseLocationInView:view];
////    precisePosition.x *= view.contentScaleFactor;
////    precisePosition.y *= view.contentScaleFactor;
////    precisePosition = [self orientateTouchPoint:precisePosition];
////#else
////    precisePosition = position;
////#endif
////
////    uint64_t buttons = 0;
////
////    std::string eventType = PointerEventArgs::EVENT_TYPE_UNKNOWN;
////    uint64_t detail = 0;
////
////    uint64_t sequenceIndex = [[touch estimationUpdateIndex] unsignedLongLongValue];
////
////    std::set<std::string> estimatedProperties = toPopertySet([touch estimatedProperties]);
////
////    std::set<std::string> estimatedPropertiesExpectingUpdates = toPopertySet([touch estimatedPropertiesExpectingUpdates]);
////
////    int64_t pointerIndex = _pointerIndex;
////
////    switch ([touch phase])
////    {
////        case UITouchPhaseBegan:
////        {
////            eventType = PointerEventArgs::POINTER_DOWN;
////            buttons |= (1 << OF_MOUSE_BUTTON_1);
////            if (_activePointerIndices[[touch type]].empty())
////                _primaryPointerIndices[[touch type]] = pointerIndex;
////            _activePointerIndices[[touch type]].insert(pointerIndex);
////            break;
////        }
////        case UITouchPhaseMoved:
////        case UITouchPhaseStationary:
////        {
////            eventType = PointerEventArgs::POINTER_MOVE;
////            buttons |= (1 << OF_MOUSE_BUTTON_1);
////            break;
////        }
////        case UITouchPhaseEnded:
////        {
////            eventType = PointerEventArgs::POINTER_UP;
////            _activePointerIndices[[touch type]].erase(pointerIndex);
////            break;
////        }
////        case UITouchPhaseCancelled:
////        {
////            eventType = PointerEventArgs::POINTER_CANCEL;
////            _activePointerIndices[[touch type]].erase(pointerIndex);
////            break;
////        }
////    }
////
////    // If this is an update, we change its event type.
////    if (_isUpdate)
////    {
////        eventType = PointerEventArgs::POINTER_UPDATE;
////        // TODO ... this shouldn't happen.
////        if ([touch estimatedPropertiesExpectingUpdates] > 0)
////            assert(false);
////    }
////
////    // By default our pressure depends on if a "button" is pressed.
////    CGFloat pressure = buttons > 0 ? 0.5 : 0;
////
////#if defined(__IPHONE_9_0)
////    // If force is supported, then we try to update it.
////    CGFloat maximumPossibleForce = [touch maximumPossibleForce];
////
////    if (maximumPossibleForce > 0)
////        pressure = [touch force] / maximumPossibleForce;
////#endif
////
////    float twistDeg = 0;
////    float tangentialPressure = 0;
////    float tiltXDeg = 0;
////    float tiltYDeg = 0;
////
////    bool isPredicted = _isPredicted;
////    bool isCoalesced = _isCoalesced;
////    bool isPrimary = (pointerIndex == _primaryPointerIndices[[touch type]]);
////
////    std::string deviceType = PointerEventArgs::TYPE_UNKNOWN;
////
////    switch ([touch type])
////    {
////        case UITouchTypeDirect:
////        {
////            deviceType = PointerEventArgs::TYPE_TOUCH;
////            break;
////        }
////        case UITouchTypeIndirect:
////        {
////            deviceType = PointerEventArgs::TYPE_MOUSE;
////            break;
////        }
////#if defined(__IPHONE_9_1)
////        case UITouchTypeStylus:
////        {
////            deviceType = PointerEventArgs::TYPE_PEN;
////            // Azimuth angle. Valid only for stylus touch types. Zero radians points along the positive X axis.
////            // Passing a nil for the view parameter will return the azimuth relative to the touch's window.
////            CGFloat azimuthRad = [touch azimuthAngleInView:view];
////
////            // Put into range 0 - 2PI
////            if (azimuthRad < 0)
////                azimuthRad += glm::two_pi<CGFloat>();
////
////            // Zero radians indicates that the stylus is parallel to the screen surface,
////            // while M_PI/2 radians indicates that it is normal to the screen surface.
////            CGFloat altitudeRad = [touch altitudeAngle];
////
////            // Alternative way to calculate tiltX, tiltY.
////            // Get the unit tilt vector then scale to degrees +/- 90 degrees.
////            // - Reference: https://books.google.com/books?id=iYALAAAAQBAJ&pg=PA471&lpg=PA471&dq=azimuth+unit+vector+to+tiltX+tiltY&source=bl&ots=Z_M3-2caR8&sig=ACfU3U1vPG4qwkXBMqd9eT3k65wGLhbA3A&hl=en&sa=X&ved=2ahUKEwjGh-bbvargAhWmj4MKHR1sCRwQ6AEwDnoECAgQAQ#v=onepage&q=azimuth%20unit%20vector%20to%20tiltX%20tiltY&f=false
////            // double lengthXY = std::cos(altitudeAngleRad);
////            // tiltXDeg = std::cos(az) * lengthXY * 90;
////            // tiltYDeg = std::sin(az) * lengthXY * 90;
////            // tiltZDeg = std::cos(altitudeAngleRad) * 90;
////
////            // Instead we use a conversion that is easily reversible. See:
////            // Point::_cacheAzimuthAltitude().
////            double tanAltitude = std::tan(altitudeRad);
////            tiltXDeg = glm::degrees(std::atan(std::cos(azimuthRad) / tanAltitude));
////            tiltYDeg = glm::degrees(std::atan(std::sin(azimuthRad) / tanAltitude));
////
////            break;
////        }
////#endif
////    }
////
////    ofx::Point point({ position.x, position.y },
////                     { precisePosition.x, precisePosition.y },
////                     shape,
////                     pressure,
////                     tangentialPressure,
////                     twistDeg,
////                     tiltXDeg,
////                     tiltYDeg);
////
////    uint64_t modifiers = 0;
////
////    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
////    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
////    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
////    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;
////
////    // Convert seconds to milliseconds.
////    NSTimeInterval timestampSeconds = [touch timestamp];
////    NSTimeInterval elapsedTimestampSeconds = timestampSeconds - _startTimeSeconds;
////    uint64_t timestampMicros = elapsedTimestampSeconds * 1000000.0;
////
////    std::size_t deviceId = 0;
////    uint64_t button = 0;
////
////    std::vector<PointerEventArgs> coalescedPointerEvents;
////
////    if (event)
////    {
////        NSArray<UITouch*>* coalescedTouchesForTouch = [event coalescedTouchesForTouch:touch];
////        UITouch* thisTouch = [coalescedTouchesForTouch lastObject];
////        for (UITouch* _touch in coalescedTouchesForTouch)
////        {
////            coalescedPointerEvents.push_back([self toPointerEventArgs:view
////                                                            withTouch:_touch
////                                                            withEvent:event
////                                                     withPointerIndex:pointerIndex
////                                                        withCoalesced:(_touch != thisTouch)
////                                                        withPredicted:false
////                                                           withUpdate:false]);
////        }
////    }
////
////    std::vector<PointerEventArgs> predictedPointerEvents;
////
////    if (event)
////    {
////        for (UITouch* _touch in [event predictedTouchesForTouch:touch])
////            predictedPointerEvents.push_back([self toPointerEventArgs:view
////                                                            withTouch:_touch
////                                                            withEvent:event
////                                                     withPointerIndex:pointerIndex
////                                                        withCoalesced:false
////                                                        withPredicted:true
////                                                           withUpdate:false]);
////    }
////
////    const void* eventSource = self->_window;
////
////    std::size_t pointerId = 0;
////    hash_combine(pointerId, deviceId);
////    hash_combine(pointerId, pointerIndex);
////    hash_combine(pointerId, deviceType);
////
////    return PointerEventArgs(eventSource,
////                            eventType,
////                            timestampMicros,
////                            detail,
////                            point,
////                            pointerId,
////                            deviceId,
////                            pointerIndex,
////                            sequenceIndex,
////                            deviceType,
////                            isCoalesced,
////                            isPredicted,
////                            isPrimary,
////                            button,
////                            buttons,
////                            modifiers,
////                            coalescedPointerEvents,
////                            predictedPointerEvents,
////                            estimatedProperties,
////                            estimatedPropertiesExpectingUpdates);
////}
////
////- (CGPoint)orientateTouchPoint:(CGPoint)touchPoint
////{
////    if (!_window)
////    {
////        ofLogError("PointerView::orientateTouchPoint") << "Window is nil.";
////        return touchPoint;
////    }
////
////    if (_window->doesHWOrientation())
////        return touchPoint;
////
////    ofOrientation orientation = _window->getOrientation();
////    CGPoint touchPointOriented = CGPointZero;
////
////    switch(orientation)
////    {
////        case OF_ORIENTATION_180:
////            touchPointOriented.x = _window->getWidth() - touchPoint.x;
////            touchPointOriented.y = _window->getHeight() - touchPoint.y;
////            break;
////        case OF_ORIENTATION_90_LEFT:
////            touchPointOriented.x = touchPoint.y;
////            touchPointOriented.y = _window->getHeight() - touchPoint.x;
////            break;
////        case OF_ORIENTATION_90_RIGHT:
////            touchPointOriented.x = _window->getWidth() - touchPoint.y;
////            touchPointOriented.y = touchPoint.x;
////            break;
////        case OF_ORIENTATION_DEFAULT:
////        default:
////            touchPointOriented = touchPoint;
////            break;
////    }
////
////    return touchPointOriented;
////}
////
////
//@end


namespace ofx {


///// \brief The global PointerView associated with the single iOS window.
///// \note Currently we only support one window. In the future we might support more if iOS allows it.
//static PointerView* pointerView = nullptr;


void EnableAdvancedPointerEventsMacOS()
{
    uint64_t tabletMask = 0;

    tabletMask |= NSLeftMouseDownMask;
    tabletMask |= NSLeftMouseUpMask;
    tabletMask |= NSRightMouseDownMask;
    tabletMask |= NSRightMouseUpMask;
    tabletMask |= NSMouseMovedMask;
    tabletMask |= NSLeftMouseDraggedMask;
    tabletMask |= NSRightMouseDraggedMask;

    id handler = [NSEvent addLocalMonitorForEventsMatchingMask: tabletMask
                                                       handler: ^(NSEvent *event)
                  {
                      switch ([event subtype])
                      {
                          case NX_SUBTYPE_TABLET_POINT:
                          case NX_SUBTYPE_TABLET_PROXIMITY:
                          {
//                                  ofx::TabletData data;
//
//                                  if ([event type] == NSLeftMouseDown || [event type] == NSRightMouseDown)
//                                  {
//                                      data.eventType = ofx::TabletData::DOWN;
//                                  }
//                                  else if ([event type] == NSLeftMouseUp || [event type] == NSRightMouseUp)
//                                  {
//                                      data.eventType = ofx::TabletData::UP;
//                                  }
//                                  else
//                                  {
//                                      data.eventType = ofx::TabletData::MOVE;
//                                  }
//
//                                  data.evt = [event type];
//
//                                  data.absX = [NSEvent mouseLocation].x;
//                                  data.absY = [NSEvent mouseLocation].y;
//                                  data.absZ = 0;
//
//                                  data.x = [NSEvent mouseLocation].x;
//                                  data.y = [NSEvent mouseLocation].y;
//
//                                  data.tiltX = [event tilt].x;
//                                  data.tiltY = [event tilt].y;
//                                  data.pressure = [event pressure];
//                                  data.rotation = [event rotation];
//                                  data.tangentialPressure = [event tangentialPressure];
//
//                                  data.isProximityEvent = [event isEnteringProximity];
//
//                                  data.button = [event buttonNumber];
//                                  data.pointerID = [event pointingDeviceID];
//                                  data.deviceID = [event deviceID];
//
//                                  data.clickCount = [event clickCount];
//
//                                  data.vendorID = [event vendorID];
//
//                                  data.vendorPointerType = [event vendorPointingDeviceType];
//
//                                  NSTimeInterval timestampSeconds = [event timestamp];
//                                  NSTimeInterval elapsedTimestampSeconds = timestampSeconds - _startTimeSeconds;
//                                  data.timestampMicros = elapsedTimestampSeconds * 1000000.0;
//
//                                  ofx::Tablet::callback(data);
                          }
                              break;
                          case NX_SUBTYPE_DEFAULT:
                              // If the pen tablet sends events of this subtype,
                              // it probably means the driver is not installed
                              // and the OS is treating it as a mouse.
                              break;
                          default:
                              break;
                      }

                      return event;

                  }];















//    if (!pointerView)
//    {
////        // Since iOS can only have one window, we initialize our PointerView on
////        // that window.
////        pointerView = [[PointerView alloc] initWithFrame:CGRectMake(0,
////                                                                    0,
////                                                                    ofxiOSGetOFWindow()->getWidth(),
////                                                                    ofxiOSGetOFWindow()->getHeight())];
////
////        [[ofxiOSGetAppDelegate() uiViewController].view addSubview:pointerView];
//
//    }
}


void DisableAdvancedPointerEventsMacOS()
{

// The monitor Block is called for all future events that match mask. You must call removeMonitor: to stop the monitor. Under garbage collection, the monitor (and everything the Block references) will not be collected until removeMonitor: is invoked.


//    if (pointerView)
//    {
//        [pointerView removeFromSuperview];
//        [pointerView release];
//        pointerView = nullptr;
//    }
}


} // namespace ofx


#endif
