//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/PointerEvents.h"
#include "ofColor.h"
#include "ofMesh.h"


namespace ofx {


/// \brief A PointerStroke is a collection of events with the same pointer id.
///
/// A pointer stroke begins with a pointerdown event and ends with a pointerup
/// or pointercancel event.
class PointerStroke
{
public:
    /// \brief Construct a default PointerStroke.
    PointerStroke();

    /// \brief Destroy the PointerStroke.
    ~PointerStroke();

    /// \brief Add the given pointer event to the stroke.
    /// \param evt The pointer event to add.
    /// \returns true if the event was successfully added.
    bool add(const PointerEventArgs& evt);

    /// \returns the PointerId of this PointerStroke.
    std::size_t pointerId() const;

    /// \returns the minimum sequence index.
    uint64_t minSequenceIndex() const;

    /// \returns the maximum sequence index.
    uint64_t maxSequenceIndex() const;

    /// \returns the minimum timestamp in microseconds.
    uint64_t minTimestampMicros() const;

    /// \returns the maximum timestamp in microseconds.
    uint64_t maxTimestampMicros() const;

    /// \returns true if the last event is a pointerup or pointercancel event.
    bool isFinished() const;

    /// \returns true if the last event is a pointercancel.
    bool isCancelled() const;

    /// \returns true if any events are still expecting updates.
    bool isExpectingUpdates() const;

    /// \returns the number of events.
    std::size_t size() const;

    /// \returns true if size() == 0.
    bool empty() const;

    std::vector<PointerEventArgs>::const_iterator begin() const;
    std::vector<PointerEventArgs>::const_iterator end() const;

    /// \returns the events.
    const std::vector<PointerEventArgs>& events() const;

    /// \returns the bounding box for this PointerStroke.
    ofRectangle boundingBox() const;

    /// \brief Determine if two strokes intersect.
    /// \param stroke The stroke to check.
    /// \returns true if this stroke intersects with the given stroke.
    bool intersectsWith(const PointerStroke& stroke) const;

//    const std::vector<float> distances() const
//    {
//        std::vector<float> results;
//
//        for (std::size_t i = 0; i < _events.size(); ++i)
//        {
//            float distance = 0;
//
//            if (i > 0)
//                distance = glm::distance(_events[i].position(), _events[i-1].position());
//
//            results.push_back(distance);
//        }
//
//        return results;
//    }
//
//    const std::vector<float> periods() const
//    {
//        std::vector<float> results;
//
//        for (std::size_t i = 1; i < _events.size(); ++i)
//        {
//            float period = 0;
//
//            if (i > 0)
//                period = _events[i].timestampMicros() - _events[i-1].timestampMicros();
//
//            results.push_back(period);
//        }
//
//        return results;
//    }
//
////    const std::vector<float> accelerations() const;
////    const std::vector<float> samplingPeriods() const;
////    const std::vector<float> samplingPeriods() const;
//
////    /// \brief Resample the timestamps
////    void setFixedSampleRate(float samplingRateHz = 60)
////    {
////        // Keep it sane.
////        samplingRateHz = std::max(1.0f, samplingRateHz);
////
////        uint64_t samplePeriodMicros = 1000000.0 / samplingRateHz;
////        uint64_t samplePeriodMicrosTol = samplePeriodMicros * 0.2;
////        uint64_t minSamplePeriodMicros = samplePeriodMicros - samplePeriodMicrosTol;
////        uint64_t maxSamplePeriodMicros = samplePeriodMicros + samplePeriodMicrosTol;
////
////
////        std::vector<std::size_t> pauseIndices;
////
////        for (std::size_t i = 1; i < _events.size(); ++i)
////        {
////            uint64_t measuredSamplePeriodMicros = _events[i].timestampMicros() - _events[i-1].timestampMicros();
////
////            std::cout << measuredSamplePeriodMicros << "->" << maxSamplePeriodMicros << std::endl;
////
////            if (measuredSamplePeriodMicros > maxSamplePeriodMicros)
////            {
////                pauseIndices.push_back(i);
////            }
////        }
////
////        std::cout << "Found " << pauseIndices.size() << " pauses " << std::endl;
////
//////        for (std::size_t i = 1; i < _events.size(); ++i)
//////        {
//////            float period = 0;
//////
//////            if (i > 0)
//////                period = _events[i].timestampMicros() - _events[i-1].timestampMicros();
//////
//////            results.push_back(period);
//////        }
////    }


    /// \brief A set of optional attributes associated with this pointer stroke.
    std::map<std::string, std::string> attributes;

    /// \brief The optional color attribute.
    static const std::string ATTRIBUTE_COLOR;

private:
    /// \brief The bounding box for this pointer stroke.
    mutable ofRectangle _boundingBox;

    /// \brief True if the bounding box needs and update.
    mutable bool _boundingBoxNeedsUpdate = false;

    /// \brief The pointer id of all events in this stroke.
    std::size_t _pointerId = -1;

    /// \brief The minimum update sequence index.
    uint64_t _minSequenceIndex = std::numeric_limits<uint64_t>::max();

    /// \brief The maximum update sequence index.
    uint64_t _maxSequenceIndex = std::numeric_limits<uint64_t>::lowest();

    /// \brief All events associated with this stroke.
    std::vector<PointerEventArgs> _events;

};


inline void to_json(nlohmann::json& j, const PointerStroke& v)
{
    // TODO attributes
    j = v.events();
}


inline void from_json(const nlohmann::json& j, PointerStroke& v)
{
    // TODO attributes
    v = PointerStroke();
    for (auto& event: j)
        v.add(event);
}

/// \brief A set of strokes that form a set.
struct PointerStrokeSet
{
    /// \returns strokes.
    std::vector<PointerStroke> strokes;

    /// \brief Optional attributes for the stroke set.
    std::map<std::string, std::string> attributes;

    /// \btief The attribute holding the text transcription.
    static const std::string ATTRIBUTE_TRANSCRIPTION;

    /// \returns the bounding box for this PointerStroke.
    ofRectangle boundingBox() const
    {
        ofRectangle boundingBox;

        for (std::size_t i = 0; i < strokes.size(); ++i)
        {
            if (i == 0)
                boundingBox.set(strokes[i].boundingBox());
            else
                boundingBox.growToInclude(strokes[i].boundingBox());
        }

        return boundingBox;
    }

};


inline void to_json(nlohmann::json& j, const PointerStrokeSet& v)
{
    j["strokes"] = v.strokes;
    j["attributes"] = v.attributes;
}


inline void from_json(const nlohmann::json& j, PointerStrokeSet& v)
{
    v.strokes = j.value("strokes", std::vector<PointerStroke>());
    v.attributes = j.value("attributes", std::map<std::string, std::string>());
}


class PointerStrokeEventArgs: public EventArgs
{
public:
    /// \brief Create a PointerStrokeEventArgs with the given paramaters.
    ///
    /// The event source, timestamp, detail, etc are set from the last pointer
    /// event in the stroke.
    ///
    /// \param eventType A string describing the type of the event.
    /// \param stroke The stroke associated with the event.
    /// \param detail Optional event detail.
    PointerStrokeEventArgs(const std::string& eventType,
                           const PointerStroke& stroke);

    /// \brief Destroy the PointerStrokeEventArgs;
    virtual ~PointerStrokeEventArgs();

    /// \brief Called when a stroke begins.
    static const std::string STROKE_BEGIN;

    /// \brief Called when a stroke is updated.
    static const std::string STROKE_UPDATE;

    /// \brief Called when a stroke has received all updates and is finished.
    static const std::string STROKE_END;

    /// \brief Called when a stroke is cancelled.
    static const std::string STROKE_CANCEL;

    /// \brief The stroke.
    PointerStroke stroke;

};


class PointerStrokeRecorder
{
public:
    struct Settings;

    /// \brief Create a default debug renderer.
    PointerStrokeRecorder();

    /// \brief Create a default debug renderer with the given settings.
    /// \param settings The settings values to set.
    PointerStrokeRecorder(const Settings& settings);

    /// \brief Destroy the recoder.
    ~PointerStrokeRecorder();

    /// \brief Configure the PointerStrokeRecorder with the given settings.
    /// \param settings The settings values to set.
    /// \returns true if the setup was successful.
    bool setup(const Settings& settings);

    /// \brief Update the strokes.
    ///
    /// This will remove strokes that have timed out.
    void update(ofEventArgs& evt);

    /// \brief A callback for all Pointer Events.
    /// \param e The Pointer Event arguments.
    bool add(const PointerEventArgs& e);

    // \returns the active stroke map.
    const std::map<std::size_t, PointerStrokeSet>& strokes() const;

    /// \brief Reset all data.
    void clear();

    /// \returns the Settings.
    Settings settings() const;

    /// \brief The stroke event.
    ofEvent<PointerStrokeEventArgs> strokeEvent;

    struct Settings
    {
        //Settings();

        /// \brief Set the amount of time in microseconds a stroke will wait for expected updates before timeout.
  //      uint64_t eventUpdateTimeoutMicros = 5 * 1000000;


//        /// \brief The maximum width of the stroke in pixels.
//        float strokeWidth = 100;
//
//        /// \brief The color of normal points.
//        ofColor pointColor;
//
//        /// \brief The color of coalesced points.
//        ofColor coalescedPointColor;
//
//        /// \brief The color of predicted points.
//        ofColor predictedPointColor;

    };

private:
    /// \brief The Settings.
    Settings _settings;

    /// \brief A map of strokes.
    ///
    /// The key is the pointer id. The value is a collection of strokes. Strokes
    /// Once a stroke is finished, new events that are not updates to the
    /// previous stroke are added to a new event. When a stroke finished, and
    /// no longer expecting updates (or times out) will be delivered via the
    /// strokeEvent.
    std::map<std::size_t, PointerStrokeSet> _strokeMap;

    /// \brief The update event listener.
    ofEventListener _updateListener;

};


/// \brief A utility class for visualizing Pointer events.
class PointerStrokeRenderer
{
public:
    struct Settings;

    /// \brief Create a default PointerStrokeRenderer.
    PointerStrokeRenderer();

    /// \brief Create a default PointerStrokeRenderer with the given settings.
    /// \param settings The settings values to set.
    PointerStrokeRenderer(const Settings& settings);

    /// \brief Destroy the PointerStrokeRenderer.
    ~PointerStrokeRenderer();

    /// \brief Configure the PointerStrokeRenderer with the given settings.
    /// \param settings The settings values to set.
    /// \returns true if the setup was successful.
    bool setup(const Settings& settings);

    /// \brief Get the rendered mesh for the given stroke.
    /// \param stroke The stroke to render.
    /// \returns the generated mesh.
    ofMesh generateMesh(const PointerStroke& stroke) const;

    /// \brief Draw a pointer stroke.
    /// \param stroke The stroke to render.
    void draw(const PointerStroke& stroke) const;

    /// \returns the Settings.
    Settings settings() const;

    struct Settings
    {
        Settings();

        /// \brief The minimum width of the stroke in pixels.
        float minimumStrokeWidth = 5;

        /// \brief The maximum width of the stroke in pixels.
        float maximumStrokeWidth = 10;

        /// \brief The color of normal points.
        ofColor pointColor;

        /// \brief The color of coalesced points.
        ofColor coalescedPointColor;

        /// \brief The color of predicted points.
        ofColor predictedPointColor;

    };

private:
    /// \brief The Settings.
    Settings _settings;

};


/// \brief A class for organizing and querying collections of pointers.
class PointerEventCollection
{
public:
    /// \brief Create an empty PointerEventCollection.
    PointerEventCollection();

    /// \brief Destroy the PointerEventCollection.
    virtual ~PointerEventCollection();

    /// \returns the number of events in the collection.
    std::size_t size() const;

    /// \returns true if the size == 0.
    bool empty() const;

    /// \brief Clear all events in the collection.
    void clear();

    /// \returns the number of pointers currently tracked.
    std::size_t numPointers() const;

    /// \brief Determine if the PointerEventCollection has the given pointer event key.
    /// \param pointerEventKey The pointer event key to query.
    /// \returns true if the set already has the pointer event key.
    bool hasPointerId(std::size_t pointerId);

    /// \brief Add a pointer event to the set.
    /// \param pointerEvent The pointer event to add.
    void add(const PointerEventArgs& pointerEvent);

    /// \brief Remove all events for the given pointerId.
    /// \param pointerId The pointer events to remove.
    void removeEventsForPointerId(std::size_t pointerId);

    /// \returns all pointer events in the collection.
    std::vector<PointerEventArgs> events() const;

    /// \brief Get the pointer events for a given key.
    /// \param pointerId The pointer id to query.
    /// \returns the pointer events for the given key or an empty set if none.
    std::vector<PointerEventArgs> eventsForPointerId(std::size_t pointerId) const;

    /// \brief Get a pointer to the first event for a given pointer id.
    /// \param pointerId The pointer id to query.
    /// \returns a const pointer to the first event or nullptr if none.
    const PointerEventArgs* firstEventForPointerId(std::size_t pointerId) const;

    /// \brief Get a pointer to the last event for a given pointer id.
    /// \param pointerId The pointer id to query.
    /// \returns a const pointer to the last event or nullptr if none.
    const PointerEventArgs* lastEventForPointerId(std::size_t pointerId) const;

private:
    /// \brief The set of pointer events in order of addition.
    std::vector<PointerEventArgs> _events;

    /// \brief A mapping between the pointer event keys and the pointer events.
    std::map<std::size_t, std::vector<PointerEventArgs*>> _eventsForPointerId;

};


class PointerDebugRenderer
{
public:
    struct Settings;

    PointerDebugRenderer();
    PointerDebugRenderer(const Settings& settings);
    
    virtual ~PointerDebugRenderer();

    void setup(const Settings& settings);

    void update();
    void draw() const;

    void add(const PointerEventArgs& pointerEvent);

    void onStrokeEvent(PointerStrokeEventArgs& e);

    struct Settings
    {
        PointerStrokeRecorder::Settings recorderSettings;
        PointerStrokeRenderer::Settings rendererSettings;
    };

private:

    std::vector<PointerStroke> _strokes;

    PointerStrokeRecorder _recorder;
    PointerStrokeRenderer _renderer;

    ofEventListener _strokeEventListener;
};


} // namespace ofx
