//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/PointerEvents.h"
#include "ofAppBaseWindow.h"
#include "ofMath.h"


namespace ofx {


const std::string EventArgs::EVENT_TYPE_UNKNOWN = "EVENT_TYPE_UNKNOWN";


EventArgs::EventArgs(): EventArgs(nullptr,
                                  EVENT_TYPE_UNKNOWN,
                                  ofGetElapsedTimeMicros(),
                                  0)
{
}


EventArgs::EventArgs(const void* eventSource,
                     const std::string& eventType,
                     uint64_t timestampMicros,
                     uint64_t detail):
    _eventSource(eventSource),
    _eventType(eventType),
    _timestampMicros(timestampMicros),
    _detail(detail)
{
}


EventArgs::~EventArgs()
{
}


const void* EventArgs::eventSource() const
{
    return _eventSource;
}


std::string EventArgs::eventType() const
{
    return _eventType;
}


uint64_t EventArgs::timestampMillis() const
{
    return timestampMicros() / 1000;
}


uint64_t EventArgs::timestampMicros() const
{
    return _timestampMicros;
}


double EventArgs::timestampSeconds() const
{
    return timestampMicros() / 1000000.0;
}


uint64_t EventArgs::detail() const
{
    return _detail;
}


PointShape::PointShape()
{
}


PointShape::PointShape(ShapeType shapeType,
                       float size,
                       float sizeTolerance):
    PointShape(shapeType,
               size,
               size,
               sizeTolerance,
               sizeTolerance,
               0)
{
}

PointShape::PointShape(ShapeType shapeType,
                       float width,
                       float height,
                       float widthTolerance,
                       float heightTolerance,
                       float angleDeg):
    _width(width),
    _height(height),
    _widthTolerance(widthTolerance),
    _heightTolerance(heightTolerance),
    _angleDeg(angleDeg)
{
}


PointShape::~PointShape()
{
}


PointShape::ShapeType PointShape::shapeType() const
{
    return _shapeType;
}


float PointShape::width() const
{
    return _width;
}


float PointShape::height() const
{
    return _height;
}


float PointShape::widthTolerance() const
{
    return _widthTolerance;
}


float PointShape::heightTolerance() const
{
    return _heightTolerance;
}


float PointShape::angleDeg() const
{
    return _angleDeg;
}


float PointShape::angleRad() const
{
    return glm::radians(_angleDeg);
}


float PointShape::axisAlignedWidth() const
{
    if (!_axisAlignedSizeCached)
        _calculateAxisAlignedSize();

    return _axisAlignedWidth;
}


float PointShape::axisAlignedHeight() const
{
    if (!_axisAlignedSizeCached)
        _calculateAxisAlignedSize();

    return _axisAlignedHeight;
}


void PointShape::_calculateAxisAlignedSize() const
{
    float _angleRad = angleRad();

    switch (_shapeType)
    {
        case ShapeType::ELLIPSE:
        {
            // via http://www.iquilezles.org/www/articles/ellipses/ellipses.htm
            auto u = glm::rotate(glm::vec2(1, 0) * _width  / 2.0f, _angleRad);
            auto v = glm::rotate(glm::vec2(0, 1) * _height / 2.0f, _angleRad);
            glm::vec2 size = glm::sqrt(u * u + v * v) * 2;
            _axisAlignedWidth = size.x;
            _axisAlignedHeight = size.y;
            break;
        }
        case ShapeType::RECTANGLE:
        {
            // via https://stackoverflow.com/a/6657768/1518329
            float _cos = std::cos(_angleRad);
            float _sin = std::sin(_angleRad);
            _axisAlignedWidth  = _height * _sin + _width * _cos;
            _axisAlignedHeight = _height * _cos + _width * _sin;
            break;
        }
    }

    _axisAlignedSizeCached = true;
}


Point::Point(): Point(glm::vec2(0, 0))
{
}


Point::Point(const glm::vec2& position): Point(position, PointShape())
{
}


Point::Point(const glm::vec2& position, const PointShape& shape):
    Point(position, PointShape(), 0)
{
}


Point::Point(const glm::vec2& position, float pressure, float tiltXDeg, float tiltYDeg):
    Point(position, position, PointShape(), pressure, 0, 0, tiltXDeg, tiltYDeg)
{
}


Point::Point(const glm::vec2& position,
             const PointShape& shape,
             float pressure):
    Point(position, position, shape, pressure, 0, 0, 0, 0)
{
}


Point::Point(const glm::vec2& position,
             const glm::vec2& precisePosition,
             const PointShape& shape,
             float pressure,
             float tangentialPressure,
             float twistDeg,
             float tiltXDeg,
             float tiltYDeg):
    _position(position),
    _precisePosition(precisePosition),
    _shape(shape),
    _pressure(pressure),
    _tangentialPressure(tangentialPressure),
    _twistDeg(twistDeg),
    _tiltXDeg(tiltXDeg),
    _tiltYDeg(tiltYDeg)
{
}


Point::~Point()
{
}


glm::vec2 Point::position() const
{
    return _position;
}


glm::vec2 Point::precisePosition() const
{
    return _precisePosition;
}


float Point::pressure() const
{
    return _pressure;
}


float Point::tangentialPressure() const
{
    return _tangentialPressure;
}


float Point::twistDeg() const
{
    return _twistDeg;
}


float Point::twistRad() const
{
    return glm::radians(_twistDeg);
}


float Point::tiltXDeg() const
{
    return _tiltXDeg;
}


float Point::tiltXRad() const
{
    return glm::radians(_tiltXDeg);
}


float Point::tiltYDeg() const
{
    return _tiltYDeg;
}


float Point::tiltYRad() const
{
    return glm::radians(_tiltYDeg);
}


float Point::azimuthDeg() const
{
    if (!_azimuthAltitudeCached)
        _cacheAzimuthAltitude();
    return _azimuthDeg;
}


float Point::azimuthRad() const
{
    return glm::radians(azimuthDeg());
}


float Point::altitudeDeg() const
{
    if (!_azimuthAltitudeCached)
        _cacheAzimuthAltitude();
    return _altitudeDeg;
}


float Point::altitudeRad() const
{
    return glm::radians(altitudeDeg());
}


void Point::_cacheAzimuthAltitude() const
{
    double _azimuthRad = 0;
    double _altitudeRad = 0;

    bool tiltXIsZero = ofIsFloatEqual(_tiltXDeg, 0.0f);
    bool tiltYIsZero = ofIsFloatEqual(_tiltYDeg, 0.0f);

    // Take care of edge cases where std::tan(...) is undefined.
    if (!tiltXIsZero && !tiltYIsZero)
    {
        double _tanTy = std::tan(tiltYRad());
        _azimuthRad = std::atan2(_tanTy, std::tan(tiltXRad()));
        _altitudeRad = std::atan(std::sin(_azimuthRad) / _tanTy);
    }
    else if (tiltXIsZero && tiltYIsZero)
    {
        _azimuthRad = 0;
        _altitudeRad = 0;
    }
    else if (tiltXIsZero)
    {
        _azimuthRad = tiltYRad() > 0 ? glm::half_pi<double>() : glm::three_over_two_pi<double>();
        _altitudeRad = tiltYRad();
    }
    else if (tiltYIsZero)
    {
        _azimuthRad = tiltXRad() > 0 ? 0 : glm::pi<double>();
        _altitudeRad = tiltXRad();
    }

    // Put into range 0 - 2PI.
    if (_azimuthRad < 0)
        _azimuthRad += glm::two_pi<double>();

    _azimuthDeg = glm::degrees(_azimuthRad);
    _altitudeDeg = glm::degrees(_altitudeRad);

    _azimuthAltitudeCached = true;
}

const PointShape& Point::shape() const
{
    return _shape;
}


Point Point::lerp(const Point& p0, const Point& p1, float amount)
{
    return Point(glm::mix(p0.position(), p1.position(), amount),
                 glm::mix(p0.precisePosition(), p1.precisePosition(), amount),
                 p0.shape(),
                 glm::mix(p0.pressure(), p1.pressure(), amount),
                 glm::mix(p0.tangentialPressure(),
                          p1.tangentialPressure(),
                          amount),
                 glm::mix(p0.twistDeg(), p1.twistDeg(), amount),
                 glm::mix(p0.tiltXDeg(), p1.tiltXDeg(), amount),
                 glm::mix(p0.tiltYDeg(), p1.tiltYDeg(), amount));
}


Point Point::transform(const Point& point, const glm::mat4& matrix)
{
    auto xform = [](const glm::vec2& vec, const glm::mat4& matrix)
    {
        glm::vec4 v = { vec.x, vec.y, 0.0f, 1.0f };
        v = matrix * v;
        return glm::vec2(v) / v.w;
    };

    return ofx::Point(xform(point.position(), matrix),
                      xform(point.precisePosition(), matrix),
                      point.shape(),
                      point.pressure(),
                      point.tangentialPressure(),
                      point.twistDeg(),
                      point.tiltXDeg(),
                      point.tiltYDeg());
};


const std::string PointerEventArgs::TYPE_MOUSE    = "mouse";
const std::string PointerEventArgs::TYPE_PEN      = "pen";
const std::string PointerEventArgs::TYPE_TOUCH    = "touch";
const std::string PointerEventArgs::TYPE_UNKNOWN  = "unknown";

const std::string PointerEventArgs::POINTER_OVER   = "pointerover";
const std::string PointerEventArgs::POINTER_ENTER  = "pointerenter";
const std::string PointerEventArgs::POINTER_DOWN   = "pointerdown";
const std::string PointerEventArgs::POINTER_MOVE   = "pointermove";
const std::string PointerEventArgs::POINTER_UP     = "pointerup";
const std::string PointerEventArgs::POINTER_CANCEL = "pointercancel";
const std::string PointerEventArgs::POINTER_UPDATE = "pointerupdate";
const std::string PointerEventArgs::POINTER_OUT    = "pointerout";
const std::string PointerEventArgs::POINTER_LEAVE  = "pointerleave";
const std::string PointerEventArgs::POINTER_SCROLL = "pointerscroll";

const std::string PointerEventArgs::GOT_POINTER_CAPTURE  = "gotpointercapture";
const std::string PointerEventArgs::LOST_POINTER_CAPTURE = "lostpointercapture";

const std::string PointerEventArgs::PROPERTY_POSITION = "PROPERTY_POSITION";
const std::string PointerEventArgs::PROPERTY_PRESSURE = "PROPERTY_PRESSURE";
const std::string PointerEventArgs::PROPERTY_TILT_X = "PROPERTY_TILT_X";
const std::string PointerEventArgs::PROPERTY_TILT_Y = "PROPERTY_TILT_Y";


PointerEventArgs::PointerEventArgs()
{
}


PointerEventArgs::PointerEventArgs(const std::string& eventType,
                                   const PointerEventArgs& event):
    PointerEventArgs(event.eventSource(),
                     eventType,
                     event.timestampMicros(),
                     event.detail(),
                     event.point(),
                     event.pointerId(),
                     event.deviceId(),
                     event.pointerIndex(),
                     event.sequenceIndex(),
                     event.deviceType(),
                     event.isCoalesced(),
                     event.isPredicted(),
                     event.isPrimary(),
                     event.button(),
                     event.buttons(),
                     event.modifiers(),
                     event.coalescedPointerEvents(),
                     event.predictedPointerEvents(),
                     event.estimatedProperties(),
                     event.estimatedPropertiesExpectingUpdates())
{
}


PointerEventArgs::PointerEventArgs(const Point& point,
                                   const PointerEventArgs& event):
    PointerEventArgs(event.eventSource(),
                     event.eventType(),
                     event.timestampMicros(),
                     event.detail(),
                     point,
                     event.pointerId(),
                     event.deviceId(),
                     event.pointerIndex(),
                     event.sequenceIndex(),
                     event.deviceType(),
                     event.isCoalesced(),
                     event.isPredicted(),
                     event.isPrimary(),
                     event.button(),
                     event.buttons(),
                     event.modifiers(),
                     event.coalescedPointerEvents(),
                     event.predictedPointerEvents(),
                     event.estimatedProperties(),
                     event.estimatedPropertiesExpectingUpdates())
{
}


PointerEventArgs::PointerEventArgs(const void* eventSource,
                                   const std::string& eventType,
                                   uint64_t timestampMicros,
                                   uint64_t detail,
                                   const Point& point,
                                   std::size_t pointerId,
                                   int64_t deviceId,
                                   int64_t pointerIndex,
                                   uint64_t sequenceIndex,
                                   const std::string& deviceType,
                                   bool isCoalesced,
                                   bool isPredicted,
                                   bool isPrimary,
                                   int16_t button,
                                   uint16_t buttons,
                                   uint16_t modifiers,
                                   const std::vector<PointerEventArgs>& coalescedPointerEvents,
                                   const std::vector<PointerEventArgs>& predictedPointerEvents,
                                   const std::set<std::string>& estimatedProperties,
                                   const std::set<std::string>& estimatedPropertiesExpectingUpdates):
    EventArgs(eventSource, eventType, timestampMicros, detail),
    _point(point),
    _pointerId(pointerId),
    _deviceId(deviceId),
    _pointerIndex(pointerIndex),
    _sequenceIndex(sequenceIndex),
    _deviceType(deviceType),
    _isCoalesced(isCoalesced),
    _isPredicted(isPredicted),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers),
    _coalescedPointerEvents(coalescedPointerEvents),
    _predictedPointerEvents(predictedPointerEvents),
    _estimatedProperties(estimatedProperties),
    _estimatedPropertiesExpectingUpdates(estimatedPropertiesExpectingUpdates)
{
}


PointerEventArgs::~PointerEventArgs()
{
}


Point PointerEventArgs::point() const
{
    return _point;
}


glm::vec2 PointerEventArgs::position() const
{
    return point().position();
}


int64_t PointerEventArgs::deviceId() const
{
    return _deviceId;
}


int64_t PointerEventArgs::pointerIndex() const
{
    return _pointerIndex;
}


uint64_t PointerEventArgs::sequenceIndex() const
{
    return _sequenceIndex;
}


std::size_t PointerEventArgs::pointerId() const
{
    return _pointerId;
}


//PointerEventArgs::PointerKey PointerEventArgs::pointerKey() const
//{
//    return PointerEventArgs::PointerKey(pointerId(), deviceId(), pointerIndex(), button());
//}


std::string PointerEventArgs::deviceType() const
{
    return _deviceType;
}


bool PointerEventArgs::isCoalesced() const
{
    return _isCoalesced;
}


bool PointerEventArgs::isPredicted() const
{
    return _isPredicted;
}


bool PointerEventArgs::isPrimary() const
{
    return _isPrimary;
}


bool PointerEventArgs::isEstimated() const
{
    return !_estimatedProperties.empty();
}


int16_t PointerEventArgs::button() const
{
    return _button;
}


uint16_t PointerEventArgs::buttons() const
{
    return _buttons;
}


uint16_t PointerEventArgs::modifiers() const
{
    return _modifiers;
}


std::vector<PointerEventArgs> PointerEventArgs::coalescedPointerEvents() const
{
    return _coalescedPointerEvents;
}


std::vector<PointerEventArgs> PointerEventArgs::predictedPointerEvents() const
{
    return _predictedPointerEvents;
}


std::set<std::string> PointerEventArgs::estimatedProperties() const
{
    return _estimatedProperties;
}


std::set<std::string> PointerEventArgs::estimatedPropertiesExpectingUpdates() const
{
    return _estimatedPropertiesExpectingUpdates;
}


bool PointerEventArgs::updateEstimatedPropertiesWithEvent(const PointerEventArgs& e)
{
    if (e.sequenceIndex() == 0 || sequenceIndex() == 0)
    {
        ofLogVerbose("PointerEventArgs::updateEstimatedPropertiesWithEvent") << "One or more of the sequence indices are zero.";
        return false;
    }

    if (e.sequenceIndex() != sequenceIndex())
    {
        ofLogVerbose("PointerEventArgs::updateEstimatedPropertiesWithEvent") << "Sequence indices do not match.";
        return false;
    }

    auto newEstimatedProperties = e.estimatedProperties();
    std::vector<std::string> propertiesToUpdate;

    std::set_difference(_estimatedPropertiesExpectingUpdates.begin(),
                        _estimatedPropertiesExpectingUpdates.end(),
                        newEstimatedProperties.begin(),
                        newEstimatedProperties.end(),
                        std::inserter(propertiesToUpdate, propertiesToUpdate.begin()));

    std::vector<std::string> ptu;
    ptu.assign(propertiesToUpdate.begin(), propertiesToUpdate.end());

    for (auto& property: propertiesToUpdate)
    {
        if (property == PointerEventArgs::PROPERTY_PRESSURE)
        {
            _point._pressure = e.point().pressure();
            ofNotifyEvent(pointerPropertyUpdate, property, this);
        }
        else if (property == PointerEventArgs::PROPERTY_TILT_X)
        {
            _point._tiltXDeg = e.point().tiltXDeg();
            _point._azimuthAltitudeCached = false;
            ofNotifyEvent(pointerPropertyUpdate, property, this);
        }
        else if (property == PointerEventArgs::PROPERTY_TILT_Y)
        {
            _point._tiltYDeg = e.point().tiltYDeg();
            _point._azimuthAltitudeCached = false;
            ofNotifyEvent(pointerPropertyUpdate, property, this);
        }
        else if (property == PointerEventArgs::PROPERTY_POSITION)
        {
            _point._position = e.point().position();
            _point._precisePosition = e.point().precisePosition();
            ofNotifyEvent(pointerPropertyUpdate, property, this);
        }
        else
        {
            ofLogWarning("PointerEventArgs::updateEstimatedPropertiesWithEvent") << "Unknown property to update: " << property;
        }

        _estimatedPropertiesExpectingUpdates.erase(property);
    }

    std::vector<std::string> epeu;
    epeu.assign(_estimatedPropertiesExpectingUpdates.begin(), _estimatedPropertiesExpectingUpdates.end());
    return true;
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const void* eventSource,
                                                      const ofTouchEventArgs& e)
{
    // If major or minor axis is defined, then use them, otherwise, use width
    // and height. If neither are defined, use 1 and 1.
    float majorAxis = e.majoraxis > 0 ? e.majoraxis : e.width;
    float minorAxis = e.minoraxis > 0 ? e.minoraxis : e.height;

    majorAxis = std::max(majorAxis, 1.f);
    minorAxis = std::max(minorAxis, 1.f);

    PointShape shape(PointShape::ShapeType::ELLIPSE,
                     majorAxis,
                     minorAxis,
                     0,
                     0,
                     e.angle);

    uint16_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    uint64_t timestampMicros = ofGetElapsedTimeMicros();

    std::string eventType = EVENT_TYPE_UNKNOWN;

    uint64_t detail = 0;

    // TODO https://www.w3.org/TR/pointerevents/#the-button-property
    // This is not correctly implemented.
    int16_t button = -1;

    uint16_t buttons = 0;

    std::size_t deviceId = 0;

    switch (e.type)
    {
        case ofTouchEventArgs::doubleTap:
            // Pointers don't use this event. We use gestures for this.
            break;
        case ofTouchEventArgs::down:
            buttons |= (1 << OF_MOUSE_BUTTON_1);
            eventType = POINTER_DOWN;
            break;
        case ofTouchEventArgs::up:
            eventType = POINTER_UP;
            break;
        case ofTouchEventArgs::move:
            buttons |= (1 << OF_MOUSE_BUTTON_1);
            eventType = POINTER_MOVE;
            break;
        case ofTouchEventArgs::cancel:
            eventType = POINTER_CANCEL;
            break;
    }

    // If pressure is not reported and a button is pressed, the pressure is
    // 0.5. If no pressure is reported and no button is pressed, then the
    // pressure is 0.
    float pressure = e.pressure > 0 ? e.pressure : (buttons > 0 ? 0.5 : 0);

    Point point(glm::vec2(e.x, e.y), shape, pressure);

    // Since we can't know for sure, we assume TOUCH because it came from a
    // ofTouchEventArgs.
    std::string deviceType = PointerEventArgs::TYPE_TOUCH;

    bool isCoalesced = false;
    bool isPredicted = false;
    bool isPrimary = (e.id == 0);

    std::size_t pointerId = 0;
    hash_combine(pointerId, deviceId);
    hash_combine(pointerId, e.id);
    hash_combine(pointerId, deviceType);

    int64_t sequenceIndex = 0;

    PointerEventArgs event(eventSource,
                           eventType,
                           timestampMicros,
                           detail,
                           point,
                           pointerId,
                           deviceId,
                           e.id,
                           sequenceIndex,
                           deviceType,
                           isCoalesced,
                           isPredicted,
                           isPrimary,
                           button,
                           buttons,
                           modifiers,
                           {},
                           {},
                           {},
                           {});

    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMicros,
                            detail,
                            point,
                            pointerId,
                            deviceId,
                            e.id,
                            sequenceIndex,
                            deviceType,
                            isCoalesced,
                            isPredicted,
                            isPrimary,
                            button,
                            buttons,
                            modifiers,
                            { event },
                            {},
                            {},
                            {});
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const void* eventSource,
                                                      const ofMouseEventArgs& e)
{
    // We begin with an unknown event type.
    std::string eventType = EVENT_TYPE_UNKNOWN;
    uint64_t detail = 0;

    // Convert the ofMouseEventArgs type to a string event type.
    switch (e.type)
    {
        case ofMouseEventArgs::Pressed:
            eventType = POINTER_DOWN;
            break;
        case ofMouseEventArgs::Dragged:
        case ofMouseEventArgs::Moved:
            eventType = POINTER_MOVE;
            break;
        case ofMouseEventArgs::Released:
            eventType = POINTER_UP;
            break;
        case ofMouseEventArgs::Scrolled:
            eventType = POINTER_SCROLL;
            break;
        case ofMouseEventArgs::Entered:
            // This is with respect to the source window.
            eventType = POINTER_ENTER;
            break;
        case ofMouseEventArgs::Exited:
            // This is with respect to the source window.
            eventType = POINTER_LEAVE;
            break;
    }

    // Record a timestamp.
    uint64_t timestampMicros = ofGetElapsedTimeMicros();

    // TODO https://www.w3.org/TR/pointerevents/#the-button-property
    // This is not correctly implemented.
    // Note the mouse button associated with this event.
    int16_t button = -1;

    // Calculate buttons.
    uint16_t buttons = 0;

    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_1) ? (1 << OF_MOUSE_BUTTON_1) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_2) ? (1 << OF_MOUSE_BUTTON_2) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_3) ? (1 << OF_MOUSE_BUTTON_3) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_4) ? (1 << OF_MOUSE_BUTTON_4) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_5) ? (1 << OF_MOUSE_BUTTON_5) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_6) ? (1 << OF_MOUSE_BUTTON_6) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_7) ? (1 << OF_MOUSE_BUTTON_7) : 0;

    // Create the point, if a button is pressed, the pressure is 0.5.
    Point point(glm::vec2(e.x, e.y), PointShape(), (buttons > 0 ? 0.5 : 0));

    bool isCoalesced = false;
    bool isPredicted = false;
    bool isPrimary = true; // A mouse is primary.

    // Calculate modifiers.
    uint16_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    std::size_t deviceId = 0;
    int64_t pointerIndex = 0;
    uint64_t sequenceIndex = 0;

    std::string deviceType = PointerEventArgs::TYPE_MOUSE;

    std::size_t pointerId = 0;
    hash_combine(pointerId, deviceId);
    hash_combine(pointerId, pointerIndex);
    hash_combine(pointerId, deviceType);

    PointerEventArgs event(eventSource,
                           eventType,
                           timestampMicros,
                           detail,
                           point,
                           pointerId,
                           deviceId,
                           pointerIndex,
                           sequenceIndex,
                           deviceType,
                           isCoalesced,
                           isPredicted,
                           isPrimary,
                           button,
                           buttons,
                           modifiers,
                           {},
                           {},
                           {},
                           {});

    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMicros,
                            detail,
                            point,
                            pointerId,
                            deviceId,
                            pointerIndex,
                            sequenceIndex,
                            deviceType,
                            isCoalesced,
                            isPredicted,
                            isPrimary,
                            button,
                            buttons,
                            modifiers,
                            { event },
                            {},
                            {},
                            {});
}


PointerEventArgs PointerEventArgs::transform(const ofx::PointerEventArgs& event,
                                             const glm::mat4& matrix)
{
    auto coalesced = event.coalescedPointerEvents();
    auto predicted = event.predictedPointerEvents();

    for (ofx::PointerEventArgs& evt: coalesced)
        evt = transform(evt, matrix);
    
    for (ofx::PointerEventArgs& evt: predicted)
        evt = transform(evt, matrix);

    return PointerEventArgs(event.eventSource(),
                            event.eventType(),
                            event.timestampMicros(),
                            event.detail(),
                            Point::transform(event.point(), matrix),
                            event.pointerId(),
                            event.deviceId(),
                            event.pointerIndex(),
                            event.sequenceIndex(),
                            event.deviceType(),
                            event.isCoalesced(),
                            event.isPredicted(),
                            event.isPrimary(),
                            event.button(),
                            event.buttons(),
                            event.modifiers(),
                            coalesced,
                            predicted,
                            event.estimatedProperties(),
                            event.estimatedPropertiesExpectingUpdates());
}


PointerEvents::PointerEvents(ofAppBaseWindow* source): _source(source)
{
    ofCoreEvents* eventSource = nullptr;

    if (_source)
    {
        eventSource = &_source->events();
    }
    else
    {
        eventSource = &ofEvents();
    }

#if !defined(TARGET_OF_IOS) && !defined(TARGET_ANDROID)
    _mouseMovedListener = eventSource->mouseMoved.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseDraggedListener = eventSource->mouseDragged.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mousePressedListener = eventSource->mousePressed.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseReleasedListener = eventSource->mouseReleased.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseScrolledListener = eventSource->mouseScrolled.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseEnteredListener = eventSource->mouseEntered.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseExitedListener = eventSource->mouseExited.newListener(this, &PointerEvents::onMouseEvent, OF_EVENT_ORDER_BEFORE_APP);
#endif
    _touchDownListener = eventSource->touchDown.newListener(this, &PointerEvents::onTouchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchUpListener = eventSource->touchUp.newListener(this, &PointerEvents::onTouchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchMovedListener = eventSource->touchMoved.newListener(this, &PointerEvents::onTouchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchDoubleTapListener = eventSource->touchDoubleTap.newListener(this, &PointerEvents::onTouchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchCancelledListener = eventSource->touchCancelled.newListener(this, &PointerEvents::onTouchEvent, OF_EVENT_ORDER_BEFORE_APP);

}


PointerEvents::~PointerEvents()
{
}


bool PointerEvents::onPointerEvent(const void* source, PointerEventArgs& e)
{
    return _dispatchPointerEvent(source, e);
}


bool PointerEvents::onMouseEvent(const void* source, ofMouseEventArgs& e)
{
    // We use _source here because ofMouseEventArgs events aren't currently
    // delivered with a source.
    auto p = PointerEventArgs::toPointerEventArgs(_source, e);
    return _dispatchPointerEvent(source, p);
}


bool PointerEvents::onTouchEvent(const void* source, ofTouchEventArgs& e)
{
    // We use _source here because ofTouchEventArgs events aren't currently
    // delivered with a source.
    auto p = PointerEventArgs::toPointerEventArgs(_source, e);
    return _dispatchPointerEvent(source, p);
}


//void PointerEvents::disableLegacyEvents()
//{
//    _consumeLegacyEvents = true;
//}
//
//
//void PointerEvents::enableLegacyEvents()
//{
//    _consumeLegacyEvents = false;
//}


bool PointerEvents::_dispatchPointerEvent(const void* source, PointerEventArgs& e)
{
    // TODO: Update this when openFrameworks core supports source on events.
    if (source && source != _source)
    {
        // "Event source sent, but does not match window. PointerEvents should be updated to respect source."
        assert(false);
        ofLogError("PointerEvents::_dispatchPointerEvent") << "Mismatched source.";
        return false;
    }

    if (e.eventType() == PointerEventArgs::EVENT_TYPE_UNKNOWN)
    {
        // We don't deliver unknown event types.
        // These are usually double-tap events from OF core.
        return true;
    }

    



    // All pointer events get dispatched via pointerEvent.
    bool consumed = ofNotifyEvent(pointerEvent, e, _source);

    // If the pointer was not consumed, then send it along to the standard five.
    if (!consumed)
    {
        if (e.eventType() == PointerEventArgs::POINTER_DOWN)
        {
            consumed = ofNotifyEvent(pointerDown, e, _source);
        }
        else if (e.eventType() == PointerEventArgs::POINTER_UP)
        {
            consumed = ofNotifyEvent(pointerUp, e, _source);
        }
        else if (e.eventType() == PointerEventArgs::POINTER_MOVE)
        {
            consumed = ofNotifyEvent(pointerMove, e, _source);
        }
        else if (e.eventType() == PointerEventArgs::POINTER_CANCEL)
        {
            consumed = ofNotifyEvent(pointerCancel, e, _source);
        }
        else if (e.eventType() == PointerEventArgs::POINTER_UPDATE)
        {
            consumed = ofNotifyEvent(pointerUpdate, e, _source);
        }
    }

//    ofGetTargetFrameRate()
//
//    uint64_t samplinePeriod
    uint64_t timetampMicros = e.timestampMicros();


    _lastEventTimestampMicros = e.timestampMicros();

    return _consumeLegacyEvents || consumed;
}


PointerEvents* PointerEventsManager::events()
{
    return eventsForWindow(nullptr);
}


PointerEvents* PointerEventsManager::eventsForWindow(ofAppBaseWindow* window)
{
    auto iter = _windowEventMap.find(window);

    if (iter != _windowEventMap.end())
    {
        return iter->second.get();
    }

    _windowEventMap[window] = std::make_unique<PointerEvents>(window);
    return _windowEventMap[window].get();
}


PointerEventsManager& PointerEventsManager::instance()
{
    static PointerEventsManager instance;
    return instance;
}


PointerEventsManager::PointerEventsManager()
{
}


PointerEventsManager::~PointerEventsManager()
{
}


} // namespace ofx
