//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/PointerEvents.h"
#include <cassert>
#include "ofGraphics.h"
#include "ofMesh.h"


namespace ofx {


const std::string EventArgs::EVENT_TYPE_UNKNOWN = "EVENT_TYPE_UNKNOWN";


EventArgs::EventArgs(): EventArgs(nullptr,
                                  EVENT_TYPE_UNKNOWN,
                                  ofGetElapsedTimeMillis())
{
}


EventArgs::EventArgs(const void* eventSource,
                     const std::string& eventType,
                     uint64_t timestampMillis):
    _eventSource(eventSource),
    _eventType(eventType),
    _timestampMillis(timestampMillis)
{
}


EventArgs::~EventArgs()
{
}


std::string EventArgs::eventType() const
{
    return _eventType;
}


uint64_t EventArgs::timestampMillis() const
{
    return _timestampMillis;
}


const void* EventArgs::eventSource() const
{
    return _eventSource;
}


PointShape::PointShape(): PointShape(0, 0, 0, 0, 0)
{
}


PointShape::PointShape(float width,
                       float height,
                       float ellipseMajorAxis,
                       float ellipseMinorAxis,
                       float ellipseAngleDeg):
    _width(width),
    _height(height),
    _ellipseMajorAxis(ellipseMajorAxis),
    _ellipseMinorAxis(ellipseMinorAxis),
    _ellipseAngleDeg(ellipseAngleDeg)
{
}


PointShape::~PointShape()
{
}


float PointShape::width() const
{
    return _width;
}


float PointShape::height() const
{
    return _height;
}


float PointShape::ellipseMajorAxis() const
{
    return _ellipseMajorAxis;
}


float PointShape::ellipseMinorAxis() const
{
    return _ellipseMinorAxis;
}


float PointShape::ellipseAngleDeg() const
{
    return _ellipseAngleDeg;
}


float PointShape::ellipseAngleRad() const
{
    return ofDegToRad(_ellipseAngleDeg);
}


float PointShape::ellipseAngle() const
{
    return ellipseAngleDeg();
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


Point::Point(const glm::vec2& position, float pressure, float tiltX, float tiltY):
    Point(position, position, PointShape(), pressure, 0, 0, tiltX, tiltY)
{
}


Point::Point(const glm::vec2& position,
             const PointShape& shape,
             float pressure):
    Point(position, position, shape, pressure, 0, 0, 0, 0)
{
}


Point::Point(const glm::vec2& position,
             const glm::vec2& absolutePosition,
             const PointShape& shape,
             float pressure,
             float tangentialPressure,
             float rotation,
             float tiltX,
             float tiltY):
    _position(position),
    _absolutePosition(absolutePosition),
    _shape(shape),
    _pressure(pressure),
    _tangentialPressure(tangentialPressure),
    _rotation(rotation),
    _tiltX(tiltX),
    _tiltY(tiltY)
{
}


Point::~Point()
{
}


glm::vec2 Point::position() const
{
    return _position;
}


glm::vec2 Point::absolutePosition() const
{
    return _absolutePosition;
}


float Point::pressure() const
{
    return _pressure;
}


float Point::tangentialPressure() const
{
    return _tangentialPressure;
}


float Point::rotation() const
{
    return _rotation;
}


float Point::tiltX() const
{
    return _tiltX;
}


float Point::tiltY() const
{
    return _tiltY;
}


const PointShape& Point::shape() const
{
    return _shape;
}


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
const std::string PointerEventArgs::POINTER_OUT    = "pointerout";
const std::string PointerEventArgs::POINTER_LEAVE  = "pointerleave";
const std::string PointerEventArgs::POINTER_SCROLL = "pointerscroll";

const std::string PointerEventArgs::GOT_POINTER_CAPTURE  = "gotpointercapture";
const std::string PointerEventArgs::LOST_POINTER_CAPTURE = "lostpointercapture";


PointerEventArgs::PointerEventArgs():
    PointerEventArgs(nullptr,       // eventSource
                     EVENT_TYPE_UNKNOWN, // eventType
                     ofGetElapsedTimeMillis(), // timestampMillis
                     Point(),       // point
                     0,             // deviceId
                     -1,            // pointerIndex
                     TYPE_UNKNOWN,  // deviceType
                     false,         // canHover
                     false,         // isPrimary
                     0,             // button
                     0,             // buttons
                     0              // modifiers
                     )
{
}


PointerEventArgs::PointerEventArgs(const std::string& eventType,
                                   const PointerEventArgs& e):
    PointerEventArgs(e.eventSource(),
                     eventType,
                     e.timestampMillis(),
                     e.point(),
                     e.deviceId(),
                     e.index(),
                     e.deviceType(),
                     e.canHover(),
                     e.isPrimary(),
                     e.button(),
                     e.buttons(),
                     e.modifiers())
{
}


PointerEventArgs::PointerEventArgs(const void* eventSource,
                                   const std::string& eventType,
                                   uint64_t timestampMillis,
                                   const Point& point,
                                   std::size_t deviceId,
                                   int64_t pointerIndex,
                                   const std::string& deviceType,
                                   bool canHover,
                                   bool isPrimary,
                                   uint64_t button,
                                   uint64_t buttons,
                                   uint64_t modifiers):
    EventArgs(eventSource, eventType, timestampMillis),
    _point(point),
    _id(0),
    _deviceId(deviceId),
    _pointerIndex(pointerIndex),
    _deviceType(deviceType),
    _canHover(canHover),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers)
{
    hash_combine(_id, _deviceId);
    hash_combine(_id, _pointerIndex);
    hash_combine(_id, _deviceType);
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


int64_t PointerEventArgs::index() const
{
    return _pointerIndex;
}


std::size_t PointerEventArgs::id() const
{
    return _id;
}


PointerEventArgs::PointerEventKey PointerEventArgs::eventKey() const
{
    return PointerEventArgs::PointerEventKey(id(), button());
}


std::string PointerEventArgs::deviceType() const
{
    return _deviceType;
}


bool PointerEventArgs::canHover() const
{
    return _canHover;
}


bool PointerEventArgs::isPrimary() const
{
    return _isPrimary;
}


uint64_t PointerEventArgs::button() const
{
    return _button;
}


uint64_t PointerEventArgs::buttons() const
{
    return _buttons;
}


uint64_t PointerEventArgs::modifiers() const
{
    return _modifiers;
}

PointerEventArgs PointerEventArgs::toPointerEventArgs(const void* eventSource,
                                                      const ofTouchEventArgs& e)
{
    PointShape shape(e.width,
                     e.height,
                     e.majoraxis,
                     e.minoraxis,
                     e.angle);

    Point point(glm::vec2(e.x, e.y), shape, e.pressure);

    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    uint64_t timestampMillis = ofGetElapsedTimeMillis();

    std::string eventType = EVENT_TYPE_UNKNOWN;

    uint64_t button = 0;

    uint64_t buttons = 0;

    std::size_t deviceId = 0;

    switch (e.type)
    {
        case ofTouchEventArgs::doubleTap:
            // Pointers don't use this event. We use gestures for this.
            break;
        case ofTouchEventArgs::down:
            eventType = POINTER_DOWN;
            buttons |= (1 << OF_MOUSE_BUTTON_1);
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

    std::string deviceType = PointerEventArgs::TYPE_UNKNOWN;

//    switch (e.pointerType)
//    {
//        case ofTouchEventArgs::mouse:
//            deviceType = PointerEventArgs::TYPE_MOUSE;
//            break;
//        case ofTouchEventArgs::pen:
//            deviceType = PointerEventArgs::TYPE_PEN;
//            break;
//        case ofTouchEventArgs::touch:
//            deviceType = PointerEventArgs::TYPE_TOUCH;
//            break;
//        case ofTouchEventArgs::unknown:
//            deviceType = PointerEventArgs::TYPE_UNKNOWN;
//            break;
//    }

    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMillis,
                            point,
                            deviceId,
                            e.id,
                            deviceType,
                            false,
                            false,
                            button,
                            buttons,
                            modifiers);
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const void* eventSource,
                                                      const ofMouseEventArgs& e)
{
    // We begin with an unknown event type.
    std::string eventType = EVENT_TYPE_UNKNOWN;

    // Convert the ofMouseEventArgs type to a string event type.
    switch (e.type)
    {
        case ofMouseEventArgs::Pressed:
            eventType = POINTER_DOWN;
            break;
        case ofMouseEventArgs::Dragged:
            eventType = POINTER_MOVE;
            break;
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
    uint64_t timestampMillis = ofGetElapsedTimeMillis();

    // Create the point, if a button is pressed, the pressure is 0.5.
    Point point(glm::vec2(e.x, e.y), PointShape(), (e.button > 0 ? 0.5 : 0));

    // Note the mouse button associated with this event.
    uint64_t button = e.button;

    // Calculate buttons.
    uint64_t buttons = 0;

    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_1) ? (1 << OF_MOUSE_BUTTON_1) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_2) ? (1 << OF_MOUSE_BUTTON_2) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_3) ? (1 << OF_MOUSE_BUTTON_3) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_4) ? (1 << OF_MOUSE_BUTTON_4) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_5) ? (1 << OF_MOUSE_BUTTON_5) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_6) ? (1 << OF_MOUSE_BUTTON_6) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_7) ? (1 << OF_MOUSE_BUTTON_7) : 0;

    bool canHover = true;  // A mouse can hover.
    bool isPrimary = true; // A mouse is primary.

    // Calculate modifiers.
    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    std::size_t deviceId = 0;
    int64_t pointerIndex = 0;

    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMillis,
                            point,
                            deviceId,
                            pointerIndex,
                            PointerEventArgs::TYPE_MOUSE,
                            canHover,
                            isPrimary,
                            button,
                            buttons,
                            modifiers);
}


PointerEventSet::PointerEventSet():
    PointerEventSet(EventArgs::EVENT_TYPE_UNKNOWN)
{
}


PointerEventSet::PointerEventSet(const std::string& pointerEventType):
    _pointerEventType(pointerEventType)
{
}


PointerEventSet::~PointerEventSet()
{
}


std::string PointerEventSet::pointerEventType() const
{
    return _pointerEventType;
}


uint64_t PointerEventSet::firstTimestampMillis() const
{
    _updateCache();
    return _cachedFirstTimestampMillis;
}

uint64_t PointerEventSet::lastTimestampMillis() const
{
    _updateCache();
    return _cachedLastTimestampMillis;
}


uint64_t PointerEventSet::deltaTimeMillis() const
{
    return lastTimestampMillis() - lastTimestampMillis();
}

glm::vec2 PointerEventSet::centroid() const
{
    _updateCache();
    return _cachedCentroid;
}


ofRectangle PointerEventSet::boundingBox() const
{
    _updateCache();
    return _cachedBoundingBox;
}


std::size_t PointerEventSet::size() const
{
    return _pointerEvents.size();
}


std::size_t PointerEventSet::empty() const
{
    return _pointerEvents.empty();
}


void PointerEventSet::clear()
{
    _pointerEvents.clear();
    _cacheNeedsUpdate = true;
}


bool PointerEventSet::hasEventKey(const PointerEventArgs& pointerEvent)
{
    auto thisEventKey = pointerEvent.eventKey();

    for (const auto& thatEvent: _pointerEvents)
    {
        if (thisEventKey == thatEvent.eventKey())
        {
            return true;
        }
    }

    return false;
}


bool PointerEventSet::add(const PointerEventArgs& pointerEvent)
{
    if (pointerEvent.eventType() == _pointerEventType && !hasEventKey(pointerEvent))
    {
        _pointerEvents.push_back(pointerEvent);
        _cacheNeedsUpdate = true;
        return true;
    }

    return false;
}


std::vector<PointerEventArgs> PointerEventSet::pointerEvents() const
{
    return _pointerEvents;
}


void PointerEventSet::_updateCache() const
{
    if (_cacheNeedsUpdate)
    {
        if (_pointerEvents.empty())
        {
            _cachedFirstTimestampMillis = 0;
            _cachedLastTimestampMillis  = 0;
            _cachedCentroid = glm::vec2(0, 0);
            _cachedBoundingBox = ofRectangle();
        }
        else if (_pointerEvents.size() == 1)
        {
            _cachedFirstTimestampMillis = _pointerEvents.begin()->timestampMillis();
            _cachedLastTimestampMillis  = _pointerEvents.begin()->timestampMillis();
            _cachedCentroid = _pointerEvents.begin()->position();
            _cachedBoundingBox = ofRectangle(_cachedCentroid.x, _cachedCentroid.y, 0, 0);
        }
        else
        {
            _cachedFirstTimestampMillis = std::numeric_limits<uint64_t>::max();
            _cachedLastTimestampMillis  = std::numeric_limits<uint64_t>::lowest();
            _cachedCentroid = glm::vec2(0, 0);
            _cachedBoundingBox = ofRectangle(_pointerEvents.begin()->position(), 0, 0);

            for (const auto& event: _pointerEvents)
            {
                _cachedFirstTimestampMillis = std::min(_cachedFirstTimestampMillis, event.timestampMillis());
                _cachedLastTimestampMillis = std::min(_cachedLastTimestampMillis, event.timestampMillis());
                _cachedCentroid += event.position();
                _cachedBoundingBox.growToInclude(event.position());
            }

            _cachedCentroid /= _pointerEvents.size();
        }

        _cacheNeedsUpdate = false;
    }
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
    _mouseMovedListener = eventSource->mouseMoved.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseDraggedListener = eventSource->mouseDragged.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mousePressedListener = eventSource->mousePressed.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseReleasedListener = eventSource->mouseReleased.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseScrolledListener = eventSource->mouseScrolled.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseEnteredListener = eventSource->mouseEntered.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
    _mouseExitedListener = eventSource->mouseExited.newListener(this, &PointerEvents::mouseEvent, OF_EVENT_ORDER_BEFORE_APP);
#endif
    _touchDownListener = eventSource->touchDown.newListener(this, &PointerEvents::touchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchUpListener = eventSource->touchUp.newListener(this, &PointerEvents::touchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchMovedListener = eventSource->touchMoved.newListener(this, &PointerEvents::touchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchDoubleTapListener = eventSource->touchDoubleTap.newListener(this, &PointerEvents::touchEvent, OF_EVENT_ORDER_BEFORE_APP);
    _touchCancelledListener = eventSource->touchCancelled.newListener(this, &PointerEvents::touchEvent, OF_EVENT_ORDER_BEFORE_APP);

}


PointerEvents::~PointerEvents()
{
}


bool PointerEvents::mouseEvent(const void* source, ofMouseEventArgs& e)
{
    // TODO: Update this when openFrameworks core supports source on events.
    if (source && source != _source)
    {
        // "Event source sent, but does not match window. PointerEvents should be updated to respect source."
        assert(false);
    }

    auto p = PointerEventArgs::toPointerEventArgs(_source, e);
    return _dispatchPointerEvent(_source, p);
}


bool PointerEvents::touchEvent(const void* source, ofTouchEventArgs& e)
{
    // TODO: Update this when openFrameworks core supports source on events.
    if (source && source != _source)
    {
        // "Event source sent, but does not match window. PointerEvents should be updated to respect source."
        assert(false);
    }

    auto p = PointerEventArgs::toPointerEventArgs(_source, e);
    return _dispatchPointerEvent(_source, p);
}


void PointerEvents::disableLegacyEvents()
{
    _consumeLegacyEvents = true;
}


void PointerEvents::enableLegacyEvents()
{
    _consumeLegacyEvents = false;
}


bool PointerEvents::_dispatchPointerEvent(const void* source, PointerEventArgs& e)
{
    // All pointer events get dispatched via pointerEvent.
    bool consumed = ofNotifyEvent(pointerEvent, e, _source);

    // If the pointer was not consumed, then send it along to the standard four.
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
    }

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
    else
    {
        _windowEventMap[window] = std::make_unique<PointerEvents>(window);
        return _windowEventMap[window].get();
    }
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


PointerDebugRenderer::PointerDebugRenderer()
{
    setEnabled(true);
}


PointerDebugRenderer::~PointerDebugRenderer()
{
    setEnabled(false);
}


void PointerDebugRenderer::update(ofEventArgs& args)
{
    auto now = ofGetElapsedTimeMillis();

    auto iter = _savedStrokes.begin();

    while (iter != _savedStrokes.end())
    {
        if ((iter->back().timestampMillis() + _timeoutMillis) < now)
        {
            iter = _savedStrokes.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}


void PointerDebugRenderer::draw(ofEventArgs& args)
{
//    for (auto& events: _eventMap)
//    {
//        ofMesh mesh;
//
//        if (events.second.size() > 2)
//        {
//            for (std::size_t index = 0; index < events.second.size(); ++index)
//            {
//                float width = 0;
//
//                if (index > 1 && events.second.size() > 2)
//                {
//                    std::size_t i1 = index - 1;
//                    std::size_t i2 = index;
//                    std::size_t i3 = index + 1;
//                    const auto& p1 = events.second[i1].point().position();
//                    const auto& p2 = events.second[i2].point().position();
//                    const auto& p3 = events.second[i3].point().position();
//                    auto v1(p1 - p2); // vector to previous point
//                    auto v2(p3 - p2); // vector to next point
//                    v1 = glm::normalize(v1);
//                    v2 = glm::normalize(v2);
//                    glm::vec2 tangent = glm::length2(v2 - v1) > 0 ? glm::normalize(v2 - v1) : -v1;
//                    glm::vec3 normal = glm::cross(glm::vec3(tangent, 0), { 0, 0, 1});
//                    ofSetColor(ofColor::red);
//                    ofDrawLine(p2, p2 + normal.xy * 50);
//                }
//
//                ofSetColor(ofColor::white, 80);
//                ofDrawCircle(events.second[index].point().position(), 10);
//            }
//        }
//    }
}


void PointerDebugRenderer::setTimeoutMillis(uint64_t timeoutMillis)
{
    _timeoutMillis = timeoutMillis;
}


uint64_t PointerDebugRenderer::getTimeoutMillis() const
{
    return _timeoutMillis;
}


void PointerDebugRenderer::setEnabled(bool enabled)
{
    if (enabled != _enabled)
    {
        _enabled = enabled;

        if (_enabled)
        {
            ofAddListener(ofEvents().update, this, &PointerDebugRenderer::update, OF_EVENT_ORDER_AFTER_APP);
            ofAddListener(ofEvents().draw, this, &PointerDebugRenderer::draw, OF_EVENT_ORDER_AFTER_APP);
            RegisterPointerEvent(this);
        }
        else
        {
            ofRemoveListener(ofEvents().update, this, &PointerDebugRenderer::update, OF_EVENT_ORDER_AFTER_APP);
            ofRemoveListener(ofEvents().draw, this, &PointerDebugRenderer::draw, OF_EVENT_ORDER_AFTER_APP);
            UnregisterPointerEvent(this);
        }
    }
}


bool PointerDebugRenderer::isEnabled() const
{
    return _enabled;
}


void PointerDebugRenderer::pointerEvent(PointerEventArgs& evt)
{
    if (evt.eventType() == PointerEventArgs::POINTER_UP
    ||  evt.eventType() == PointerEventArgs::POINTER_CANCEL)
    {
        // finish the associated stroke, move it to saved stroke, if any.
    }
    else if (evt.eventType() == PointerEventArgs::POINTER_UP)
    {
        
    }
    else if (evt.eventType() != PointerEventArgs::POINTER_MOVE
         || (evt.eventType() == PointerEventArgs::POINTER_MOVE && evt.buttons() > 0))
    {
        // Add the stroke to the active stroke if one.
        // if none
    }



//
//
//    // We only want pointer "move" events if a pointer is "down".
//    if (evt.eventType() != PointerEventArgs::POINTER_MOVE
//    || (evt.eventType() == PointerEventArgs::POINTER_MOVE && evt.buttons() > 0))
//    {
//        auto iter = _eventMap.find(evt.id());
//
//        if (iter != _eventMap.end())
//        {
//            iter->second.push_back(evt);
//        }
//        else
//        {
//            _eventMap[evt.id()] = { evt };
//        }
//    }
}

//void PointerDebugUtilities::draw(const PointerEventArgs& evt, float alpha)
//{
//    const auto& point = evt.point();
//
//    auto position = point.position();
//
//    ofPushMatrix();
//    ofTranslate(point.position());
//
//    float w = point.shape().ellipseMajorAxis();
//    float h = point.shape().ellipseMinorAxis();
//
//    float defaultAxis = 60.f;
//    ofColor typeColor;
//
//    if (evt.eventType() == PointerEventArgs::POINTER_DOWN)
//    {
//        typeColor = ofColor::green;
//        defaultAxis *= 2;
//    }
//    else if (evt.eventType() == PointerEventArgs::POINTER_MOVE)
//    {
//        typeColor = ofColor::yellow;
//        defaultAxis /= 2;
//    }
//    else if (evt.eventType() == PointerEventArgs::POINTER_UP)
//    {
//        typeColor = ofColor::blue;
//        defaultAxis *= 2;
//    }
//    else if (evt.eventType() == PointerEventArgs::POINTER_CANCEL)
//    {
//        typeColor = ofColor::red;
//        defaultAxis *= 4;
//    }
//    else
//    {
//        std::cout << "EVENT: " << evt.eventType() << std::endl;
//        typeColor = ofColor::purple;
//    }
//
//    float defaultPressureScaler = defaultAxis / 2;
//
//    // In case the width / height info is not available.
//    if (w <= 0) w = defaultAxis;
//    if (h <= 0) h = defaultAxis;
//
//    float halfW = w / 2.0f;
//    float halfH = h / 2.0f;
//
//    float pressure = point.pressure() * defaultPressureScaler;
//
//    // In case the pressure is not available.
//    if (pressure <= 0) pressure = defaultPressureScaler;
//
//    ofNoFill();
//    ofSetColor(typeColor, 60 * alpha);
//    ofRotateZDeg(point.shape().ellipseAngleDeg());
//
//    if (evt.deviceType() == PointerEventArgs::TYPE_PEN)
//    {
//        ofDrawRectangle(-halfW, -halfH, w, h);
//        ofFill();
//        ofSetColor(typeColor, 100 * alpha);
//        ofDrawRectangle(-pressure/2, -pressure/2, pressure, pressure);
//    }
//    else
//    {
//        ofDrawEllipse(0, 0, w, h);
//        ofFill();
//        ofSetColor(typeColor, 100 * alpha);
//        ofDrawEllipse(0, 0, pressure, pressure);
//    }
//
////    ofSetColor(255, 100);
////    ofDrawLine(-halfW, 0.f, halfW, 0.f);
////    ofDrawLine(0.f, -halfH, 0.f, halfH);
//
//    ofPopMatrix();
//
////    ofFill();
////    ofSetColor(255);
////    ofDrawBitmapString(ofToString(evt.eventType()), position.x - 6, position.y + 3);
////    ofSetColor(255, 255, 255, 100);
//}

//std::string PointerDebugUtilities::toString(PointerEventArgs& evt)
//{
//
//}


} // namespace ofx
