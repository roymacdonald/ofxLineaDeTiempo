//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/PointerStrokes.h"
#include "ofGraphics.h"
#include "ofMesh.h"


namespace ofx {


const std::string PointerStroke::ATTRIBUTE_COLOR = "ATTRIBUTE_COLOR";


PointerStroke::PointerStroke()
{
}


PointerStroke::~PointerStroke()
{
}


bool PointerStroke::add(const PointerEventArgs& e)
{
    // 1. Ingore any non-stroke events.
    if (e.eventType() != PointerEventArgs::POINTER_DOWN
        && e.eventType() != PointerEventArgs::POINTER_MOVE
        && e.eventType() != PointerEventArgs::POINTER_UP
        && e.eventType() != PointerEventArgs::POINTER_CANCEL
        && e.eventType() != PointerEventArgs::POINTER_UPDATE)
    {
        return false;
    }

    // 2. Is this the first event to be added and it's a pointer down
    if (_events.empty())
    {
        // Make sure we are starting with a pointer down event.
        if (e.eventType() == PointerEventArgs::POINTER_DOWN)
        {
            _pointerId = e.pointerId();
        }
        else
        {
            return false;
        }
    }
    else if (_pointerId != e.pointerId())
    {
        // If it doesn't match, this isn't the right stroke.
        return false;
    }

    // 3. Check to see if this is an update event.
    if (e.eventType() == PointerEventArgs::POINTER_UPDATE)
    {
        // If it is, find the event that is waiting for an update ...
        auto riter = _events.rbegin();

        while (riter != _events.rend())
        {
            // Does it match?
            if (riter->sequenceIndex() == e.sequenceIndex())
            {
                // If it does match, try to update it!
                if (!riter->updateEstimatedPropertiesWithEvent(e))
                    ofLogWarning("PointerStroke::add") << "Error updating matching property.";

                // We don't add update events, just update existing events.
                return true;
            }

            ++riter;
        }

        ofLogWarning("PointerStroke::add") << "No matching sequence index was found for update.";
        return false;
    }

    // 4.5 Don't allow any other events to be added to a finished stroke.
    if (isFinished())
    {
        ofLogWarning("PointerStroke::add") << "Tried to add a " << e.eventType() << " to a finished stroke.";
        return false;
    }

    // 4. Remove predicted events that were placed at the end of our event list
    // on the last call to add().
    _events.erase(std::remove_if(_events.begin(),
                                 _events.end(),
                                [](const PointerEventArgs& x) { return x.isPredicted(); }),
                 _events.end());

    // 5. Add the coalesced events to the end fo the event list. The coalesced
    // events should always include a copy of the current event, so the current
    // event gets added.
    const auto& coalesced = e.coalescedPointerEvents();

    // If the coalesced events are empty, we just add a copy of this event.
    if (coalesced.empty())
    {
        _events.push_back(e);
    }
    else
    {
        // Otherwise add the events to the end.
        _events.insert(_events.end(), coalesced.begin(), coalesced.end());
    }

    // 6. Now add the predicted events to the end of the event list. They will
    // be removed when the stroke is ended or on the next call to add.
    auto predicted = e.predictedPointerEvents();

    if (!predicted.empty())
        _events.insert(_events.end(), predicted.begin(), predicted.end());

    _minSequenceIndex = std::min(e.sequenceIndex(), _minSequenceIndex);
    _maxSequenceIndex = std::max(e.sequenceIndex(), _maxSequenceIndex);

    _boundingBoxNeedsUpdate = true;

    return true;
}


std::size_t PointerStroke::pointerId() const
{
    return _pointerId;
}


uint64_t PointerStroke::minSequenceIndex() const
{
    return _minSequenceIndex;
}


uint64_t PointerStroke::maxSequenceIndex() const
{
    return _maxSequenceIndex;
}


uint64_t PointerStroke::minTimestampMicros() const
{
    if (_events.empty())
        return 0;

    return _events.front().timestampMicros();
}


uint64_t PointerStroke::maxTimestampMicros() const
{
    if (_events.empty())
        return 0;

    return _events.back().timestampMicros();
}


bool PointerStroke::isFinished() const
{
    if (_events.empty())
        return false;

    return _events.back().eventType() == PointerEventArgs::POINTER_CANCEL
        || _events.back().eventType() == PointerEventArgs::POINTER_UP;

}


bool PointerStroke::isCancelled() const
{
    if (_events.empty())
        return false;

    return _events.back().eventType() == PointerEventArgs::POINTER_CANCEL;
}


bool PointerStroke::isExpectingUpdates() const
{
    // Start at the end, because newer events are likely the ones with estimated
    // properties.
    int i = 0;
    auto riter = _events.rbegin();
    while (riter != _events.rend())
    {
        if (!riter->estimatedPropertiesExpectingUpdates().empty())
        {
            std::vector<std::string> expected;

            for (auto s: riter->estimatedPropertiesExpectingUpdates())
                expected.push_back(s);

            return true;
        }

        i++;
        ++riter;
    }

    return false;
}


std::size_t PointerStroke::size() const
{
    return _events.size();
}


bool PointerStroke::empty() const
{
    return _events.empty();
}


std::vector<PointerEventArgs>::const_iterator PointerStroke::begin() const
{
    return _events.begin();
}


std::vector<PointerEventArgs>::const_iterator PointerStroke::end() const
{
    return _events.end();
}


const std::vector<PointerEventArgs>& PointerStroke::events() const
{
    return _events;
}


ofRectangle PointerStroke::boundingBox() const
{
    if (_boundingBoxNeedsUpdate)
    {
        for (std::size_t i = 0; i < _events.size(); ++i)
        {
            if (i == 0)
                _boundingBox.set(_events[i].position(), 0, 0);
            else
                _boundingBox.growToInclude(_events[i].position());
        }
    }

    return _boundingBox;
}


bool PointerStroke::intersectsWith(const PointerStroke& stroke) const
{
    for (std::size_t i = 0; i < stroke.size(); ++i)
    {
        for (std::size_t j = 0; j < size(); ++j)
        {
            const auto& thisPoint = _events[i].position();
            const auto& thatPoint = stroke._events[i].position();

            // Check point equality.
            if (glm::all(glm::equal(thisPoint, thatPoint)))
                return false;

            if (j == 0 || i == 0)
            {
                continue;
            }

            const auto& thisPointLast = _events[i - 1].position();
            const auto& thatPointLast = stroke._events[i - 1].position();

            // Check point equality.
            if (glm::all(glm::equal(thisPointLast, thatPointLast)))
                return false;

            glm::vec2 intersection(0);

            bool didIntersect = ofLineSegmentIntersection(thisPoint,
                                                          thisPointLast,
                                                          thatPoint,
                                                          thatPointLast,
                                                          intersection);

            if (didIntersect)
                return true;
        }
    }

    return false;
}


    ///////////////////

//void PointerStrokeSet::clear()
//{
//    _strokes.clear();
//}
//
//
//std::size_t PointerStrokeSet::size() const
//{
//    return _strokes.size();
//}
//
//
//bool PointerStrokeSet::empty()
//{
//    return _strokes.empty();
//}
//
//
//void PointerStrokeSet::add(const PointerStroke& stroke)
//{
//    _strokes.push_back(stroke);
//}
//
//
//std::vector<PointerStroke> PointerStrokeSet::strokes()
//{
//    return _strokes;
//}


//const std::vector<PointerStroke>& PointerStrokeSet::strokes() const
//{
//    return _strokes;
//}



////////////////////////////////////////////////////////////////////////////////


const std::string PointerStrokeSet::ATTRIBUTE_TRANSCRIPTION = "ATTRIBUTE_TRANSCRIPTION";


const std::string PointerStrokeEventArgs::STROKE_BEGIN = "STROKE_BEGIN";
const std::string PointerStrokeEventArgs::STROKE_UPDATE = "STROKE_UPDATE";
const std::string PointerStrokeEventArgs::STROKE_END = "STROKE_END";
const std::string PointerStrokeEventArgs::STROKE_CANCEL = "STROKE_CANCEL";


PointerStrokeEventArgs::PointerStrokeEventArgs(const std::string& eventType,
                                               const PointerStroke& stroke_):
    EventArgs(stroke_.events().back().eventSource(),
              eventType,
              stroke_.events().back().timestampMicros(),
              0),
    stroke(stroke_)
{
}


PointerStrokeEventArgs::~PointerStrokeEventArgs()
{
}

////////////////////////////////////////////////////////////////////////////////



PointerStrokeRecorder::PointerStrokeRecorder():
    PointerStrokeRecorder(Settings())
{
}


PointerStrokeRecorder::PointerStrokeRecorder(const Settings& settings):
    _settings(settings),
    _updateListener(ofEvents().update.newListener(this, &PointerStrokeRecorder::update))
{
}


PointerStrokeRecorder::~PointerStrokeRecorder()
{
}


bool PointerStrokeRecorder::setup(const Settings& settings)
{
    _settings = settings;
    return true;
}


void PointerStrokeRecorder::update(ofEventArgs&)
{
    auto strokeMapIter = _strokeMap.begin();

    while (strokeMapIter != _strokeMap.end())
    {
        if (strokeMapIter->second.strokes.empty())
        {
            strokeMapIter = _strokeMap.erase(strokeMapIter);
        }
        else
        {
            // Iterate through each stroke for the given id.
            auto strokeIter = strokeMapIter->second.strokes.begin();

            while (strokeIter != strokeMapIter->second.strokes.end())
            {
                // If the stroke is cancelled, then
                if (strokeIter->isCancelled())
                {
                    PointerStrokeEventArgs eventArgs(PointerStrokeEventArgs::STROKE_CANCEL,
                                                     *strokeIter);
                    ofNotifyEvent(strokeEvent, eventArgs, this);
                    strokeIter = strokeMapIter->second.strokes.erase(strokeIter);
                }
                else if (strokeIter->isFinished())
                {
                    if (strokeIter->isExpectingUpdates())
                    {
                        // If this happens a lot, then we probably need a timeout mechanism.
                        // Keep a map? Check the timestamp 
                        ofLogNotice("PointerStrokeRecorder::update") << "Expecting an update.";
                        ++strokeIter;
                    }
                    else
                    {
                        PointerStrokeEventArgs eventArgs(PointerStrokeEventArgs::STROKE_END,
                                                         *strokeIter);
                        ofNotifyEvent(strokeEvent, eventArgs, this);
                        strokeIter = strokeMapIter->second.strokes.erase(strokeIter);
                    }
                }
                else
                {
                    ++strokeIter;
                }
            }

            ++strokeMapIter;
        }
    }
}


PointerStrokeRecorder::Settings PointerStrokeRecorder::settings() const
{
    return _settings;
}


void PointerStrokeRecorder::clear()
{
    // Cancel any in progress strokes.
    for (auto& strokes: _strokeMap)
        for (auto& stroke: strokes.second.strokes)
        {
            PointerStrokeEventArgs eventArgs(PointerStrokeEventArgs::STROKE_CANCEL,
                                             stroke);
            ofNotifyEvent(strokeEvent, eventArgs, this);
        }

    _strokeMap.clear();
}


bool PointerStrokeRecorder::add(const PointerEventArgs& e)
{
    // 1. Ingore any non-stroke events.
    if (e.eventType() != PointerEventArgs::POINTER_DOWN
        && e.eventType() != PointerEventArgs::POINTER_MOVE
        && e.eventType() != PointerEventArgs::POINTER_UP
        && e.eventType() != PointerEventArgs::POINTER_CANCEL
        && e.eventType() != PointerEventArgs::POINTER_UPDATE)
    {
        return false;
    }

    // Ignore mouse just rolling around.
    if (e.deviceType() == PointerEventArgs::TYPE_MOUSE
     && e.eventType() == PointerEventArgs::POINTER_MOVE
     && e.buttons() == 0)
        return false;

    auto strokeMapIter = _strokeMap.find(e.pointerId());

    // First deterime if there are any strokes that can be updated.
    if (e.eventType() == PointerEventArgs::POINTER_UPDATE)
    {
        bool foundIt = false;

        if (strokeMapIter != _strokeMap.end())
        {
            // Try to add this update to all existing strokes.
            for (auto& stroke: strokeMapIter->second.strokes)
            {
                foundIt = stroke.add(e);

                if (foundIt)
                    break;
            }
        }

        if (!foundIt)
        {
            ofLogWarning("PointerStrokeRecorder::add") << "The sequence to be updated was nowhere to be found. This probably should not happen.";
        }

        return foundIt;
    }

    // If there are not events in the map for the given id, create a new one.
    if (strokeMapIter == _strokeMap.end())
    {
        bool result;
        std::tie(strokeMapIter, result) = _strokeMap.insert(std::make_pair(e.pointerId(), PointerStrokeSet()));
    }

    // If there are no strokes for this id, or the last one is finished,
    // create a new one.
    if (strokeMapIter->second.strokes.empty() || strokeMapIter->second.strokes.back().isFinished())
    {
        strokeMapIter->second.strokes.push_back(PointerStroke());
    }

    // Get a reference to the current stroke.
    auto& stroke = strokeMapIter->second.strokes.back();

    if (!stroke.add(e))
    {
        ofLogError("PointerStrokeRecorder::add") << "Could not add event: " << e.eventType();
        return false;
    }
    else if (stroke.size() == 1)
    {
        PointerStrokeEventArgs eventArgs(PointerStrokeEventArgs::STROKE_BEGIN, stroke);
        ofNotifyEvent(strokeEvent, eventArgs, this);
    }
    else if (!stroke.isFinished())
    {
        PointerStrokeEventArgs eventArgs(PointerStrokeEventArgs::STROKE_UPDATE, stroke);
        ofNotifyEvent(strokeEvent, eventArgs, this);
    }
    else
    {
        // We will take care of the finished stroke in the update.
    }

    return true;
}


const std::map<std::size_t, PointerStrokeSet>& PointerStrokeRecorder::strokes() const
{
    return _strokeMap;
}


////////////////////////////////////////////////////////////////////////////////



PointerStrokeRenderer::Settings::Settings():
    pointColor(ofColor::blue),
    coalescedPointColor(ofColor::red),
    predictedPointColor(ofColor::darkGray)
{
}


PointerStrokeRenderer::PointerStrokeRenderer()
{
}


PointerStrokeRenderer::PointerStrokeRenderer(const Settings& settings)
{
    setup(settings);
}


PointerStrokeRenderer::~PointerStrokeRenderer()
{
}


bool PointerStrokeRenderer::setup(const Settings& settings)
{
    _settings = settings;
    return true;
}


ofMesh PointerStrokeRenderer::generateMesh(const PointerStroke& stroke) const
{
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    bool useZ = false;
    float R = _settings.maximumStrokeWidth;

    const auto& events = stroke.events();

    for (std::size_t i = 0; i < events.size(); ++i)
    {
        const auto& e = events[i];

        // Pen tip.
        glm::vec3 p0 = { e.position().x, e.position().y, 0 };
        glm::vec3 p1 = p0;

        float az = e.point().azimuthRad();
        float al = e.point().altitudeRad();

        if (!ofIsFloatEqual(az, 0.0f) || !ofIsFloatEqual(al, 0.0f))
        {
            float cosAl = std::cos(al);
            p1.x += R * std::cos(az) * cosAl;
            p1.y += R * std::sin(az) * cosAl;

            if (useZ)
                p1.z += R * std::sin(al);
        }
        else
        {
            // If no altitude / azimuth are available, use tangents to simulate.
            if (i > 0 && i < events.size() - 1)
            {
                std::size_t i1 = i - 1;
                std::size_t i2 = i;
                std::size_t i3 = i + 1;
                const auto& p_1 = events[i1].position();
                const auto& p_2 = events[i2].position();
                const auto& p_3 = events[i3].position();
                auto v1(p_1 - p_2); // vector to previous point
                auto v2(p_3 - p_2); // vector to next point
                v1 = glm::normalize(v1);
                v2 = glm::normalize(v2);
                glm::vec2 tangent = glm::length2(v2 - v1) > 0 ? glm::normalize(v2 - v1) : -v1;
                glm::vec3 normal = glm::cross(glm::vec3(tangent, 0), { 0, 0, 1 });
                auto pp0 = p_2 + normal * R / 2;
                auto pp1 = p_2 - normal * R / 2;
                p0 = { pp0.x, pp0.y, 0 };
                p1 = { pp1.x, pp1.y, 0 };
            }
        }

        // Here we combine the age of the line and the pressure to fade out
        // the line via an opacity change.
        float pressure = e.point().pressure();

        ofColor c0, c1;

        // Here we color the points based on the point type.
        if (e.isCoalesced())
            c0 = c1 = ofColor(_settings.coalescedPointColor, pressure * 255);
        else if (e.isPredicted())
            c0 = c1 = ofColor(_settings.predictedPointColor);
        else
            c0 = c1 = ofColor(_settings.pointColor, pressure * 255);

        mesh.addVertex(p0);
        mesh.addColor(c0);
        mesh.addVertex(p1);
        mesh.addColor(c1);
    }

    return mesh;
}


void PointerStrokeRenderer::draw(const PointerStroke& stroke) const
{
    generateMesh(stroke).draw();
}


PointerStrokeRenderer::Settings PointerStrokeRenderer::settings() const
{
    return _settings;
}



PointerEventCollection::PointerEventCollection()
{
}


PointerEventCollection::~PointerEventCollection()
{
}


std::size_t PointerEventCollection::size() const
{
    return _events.size();
}


bool PointerEventCollection::empty() const
{
    return _events.empty();
}


void PointerEventCollection::clear()
{
    _events.clear();
    _eventsForPointerId.clear();
}


std::size_t PointerEventCollection::numPointers() const
{
    return _eventsForPointerId.size();
}


bool PointerEventCollection::hasPointerId(std::size_t pointerId)
{
    return _eventsForPointerId.find(pointerId) != _eventsForPointerId.end();
}


void PointerEventCollection::add(const PointerEventArgs& pointerEvent)
{
    _events.push_back(pointerEvent);

    auto iter = _eventsForPointerId.find(pointerEvent.pointerId());

    if (iter != _eventsForPointerId.end())
        iter->second.push_back(&_events.back());
    else
        _eventsForPointerId[pointerEvent.pointerId()] = { &_events.back() };

}


void PointerEventCollection::removeEventsForPointerId(std::size_t pointerId)
{
    _eventsForPointerId.erase(pointerId);

    auto iter = _events.begin();

    while (iter != _events.end())
    {
        if (iter->pointerId() == pointerId)
            iter = _events.erase(iter);
        else
            ++iter;
    }
}


std::vector<PointerEventArgs> PointerEventCollection::events() const
{
    return _events;
}


std::vector<PointerEventArgs> PointerEventCollection::eventsForPointerId(std::size_t pointerId) const
{
    std::vector<PointerEventArgs> results;

    auto iter = _eventsForPointerId.find(pointerId);

    if (iter != _eventsForPointerId.end())
    {
        for (auto* event: iter->second)
            results.push_back(*event);
    }

    return results;
}


const PointerEventArgs* PointerEventCollection::firstEventForPointerId(std::size_t pointerId) const
{
    auto iter = _eventsForPointerId.find(pointerId);

    if (iter != _eventsForPointerId.end())
    {
        return iter->second.front();
    }

    return nullptr;
}


const PointerEventArgs* PointerEventCollection::lastEventForPointerId(std::size_t pointerId) const
{
    auto iter = _eventsForPointerId.find(pointerId);

    if (iter != _eventsForPointerId.end())
    {
        return iter->second.back();
    }

    return nullptr;
}


PointerDebugRenderer::PointerDebugRenderer(): PointerDebugRenderer(Settings())
{
}


PointerDebugRenderer::PointerDebugRenderer(const Settings& settings):
    _strokeEventListener(_recorder.strokeEvent.newListener(this, &PointerDebugRenderer::onStrokeEvent))
{
    setup(settings);
}


PointerDebugRenderer::~PointerDebugRenderer()
{
}


void PointerDebugRenderer::setup(const Settings& settings)
{
    _recorder.setup(settings.recorderSettings);
    _renderer.setup(settings.rendererSettings);
}


void PointerDebugRenderer::update()
{
    // noop
}


void PointerDebugRenderer::draw() const
{
    for (const auto& strokes: _recorder.strokes())
    {
        for (const auto& stroke: strokes.second.strokes)
        {
            _renderer.draw(stroke);
        }
    }

    for (const auto& stroke: _strokes)
    {
        _renderer.draw(stroke);
    }
}


void PointerDebugRenderer::add(const PointerEventArgs& pointerEvent)
{
    _recorder.add(pointerEvent);
}


void PointerDebugRenderer::onStrokeEvent(PointerStrokeEventArgs& e)
{
    if (e.eventType() == PointerStrokeEventArgs::STROKE_END)
    {
        _strokes.push_back(e.stroke);
    }
}


} // namespace ofx
