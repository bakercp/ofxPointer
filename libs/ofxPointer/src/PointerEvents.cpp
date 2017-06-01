//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/PointerEvents.h"
#include "ofx/PointerUtilities.h"


namespace ofx {


PointShape::PointShape(): PointShape(0, 0, 0, 0, 0)
{
}


PointShape::PointShape(float width,
                       float height,
                       float ellipseMajorAxis,
                       float ellipseMinorAxis,
                       float ellipseAngle):
    _width(width),
    _height(height),
    _ellipseMajorAxis(ellipseMajorAxis),
    _ellipseMinorAxis(ellipseMinorAxis),
    _ellipseAngle(ellipseAngle)
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


float PointShape::ellipseAngle() const
{
    return _ellipseAngle;
}


Point::Point(): Point(glm::vec3(0, 0, 0))
{
}


Point::Point(const glm::vec3& position): Point(position, PointShape())
{
}


Point::Point(const glm::vec3& position, const PointShape& shape):
    Point(position, PointShape(), 0)
{
}


Point::Point(const glm::vec3& position, float pressure, float tiltX, float tiltY):
    Point(position, position, PointShape(), pressure, 0, 0, tiltX, tiltY)
{
}


Point::Point(const glm::vec3& position,
             const PointShape& shape,
             float pressure):
    Point(position, position, shape, pressure, 0, 0, 0, 0)
{
}


Point::Point(const glm::vec3& position,
             const glm::vec3& absolutePosition,
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


Point::operator glm::vec3() const
{
    return _position;
}


const glm::vec3& Point::position() const
{
    return _position;
}


const glm::vec3& Point::absolutePosition() const
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
    PointerEventArgs(POINTER_MOVE,
                     Point(),
                     0,
                     -1,
                     TYPE_UNKNOWN,
                     false,
                     false,
                     0,
                     0,
                     0,
                     0,
                     0,
                     nullptr)
{
}


PointerEventArgs::PointerEventArgs(const std::string& type,
                                   const PointerEventArgs& e):
    PointerEventArgs(type,
                     e.point(),
                     e.deviceId(),
                     e.index(),
                     e.deviceType(),
                     e.canHover(),
                     e.isPrimary(),
                     e.button(),
                     e.buttons(),
                     e.modifiers(),
                     e._tapCount,
                     e.timestamp(),
                     nullptr)

{
}



PointerEventArgs::PointerEventArgs(const std::string& eventType,
                                   const Point& point,
                                   std::size_t deviceId,
                                   int64_t pointerIndex,
                                   const std::string& deviceType,
                                   bool canHover,
                                   bool isPrimary,
                                   uint64_t button,
                                   uint64_t buttons,
                                   uint64_t modifiers,
                                   uint64_t tapCount, // deprecated
                                   uint64_t timestamp,
                                   ofAppBaseWindow* source):
    _eventType(eventType),
    _point(point),
    _id(0),
    _deviceId(deviceId),
    _pointerIndex(pointerIndex),
    _deviceType(deviceType),
    _canHover(canHover),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers),
    _tapCount(tapCount), // deprecated
    _timestamp(timestamp),
    _source(source)
{
    hash_combine(_id, _deviceId);
    hash_combine(_id, _pointerIndex);
    hash_combine(_id, _deviceType);
}


PointerEventArgs::~PointerEventArgs()
{
}


std::string PointerEventArgs::eventType() const
{
    return _eventType;
}


Point PointerEventArgs::point() const
{
    return _point;
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


uint64_t PointerEventArgs::tapCount() const // deprecated
{
    return _tapCount;
}


uint64_t PointerEventArgs::timestampMillis() const
{
    return _timestamp;
}


uint64_t PointerEventArgs::timestamp() const // deprecated
{
    return timestampMillis();
}


const ofAppBaseWindow* PointerEventArgs::source() const
{
    return _source;
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofTouchEventArgs& e,
                                                      ofAppBaseWindow* source)
{
    PointShape shape(e.width,
                     e.height,
                     e.majoraxis,
                     e.minoraxis,
                     e.angle);

    Point point(glm::vec3(e.x, e.y, 0), shape, e.pressure);

    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    uint64_t timestamp = PointerUtilities::timestampMillis();

    std::string type = POINTER_MOVE;

    uint64_t buttons = 0;
    uint64_t tapCount = 0; // deprecated

    switch (e.type)
    {
        case ofTouchEventArgs::doubleTap:
            // Pointers don't use this event. We synthesize them.
            break;
        case ofTouchEventArgs::down:
            type = POINTER_DOWN;
            buttons |= (1 << OF_MOUSE_BUTTON_1);
            tapCount = 1;
            break;
        case ofTouchEventArgs::up:
            type = POINTER_UP;
            break;
        case ofTouchEventArgs::move:
            buttons |= (1 << OF_MOUSE_BUTTON_1);
            type = POINTER_MOVE;
            break;
        case ofTouchEventArgs::cancel:
            type = POINTER_CANCEL;
            break;
    }

    return PointerEventArgs(type,
                            point,
                            0,
                            e.id,
                            PointerEventArgs::TYPE_TOUCH,
                            false,
                            false,
                            0,
                            buttons,
                            modifiers,
                            tapCount,
                            timestamp,
                            source);
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofMouseEventArgs& e,
                                                      ofAppBaseWindow* source)
{
    PointShape shape;

    float pressure = 0;

    std::string type = POINTER_MOVE;

    uint64_t tapCount = 0;

    switch (e.type)
    {
        case ofMouseEventArgs::Pressed:
            type = POINTER_DOWN;
            tapCount = 1;
            pressure = 0.5;
            break;
        case ofMouseEventArgs::Dragged:
            type = POINTER_MOVE;
            pressure = 0.5;
            break;
        case ofMouseEventArgs::Moved:
            type = POINTER_MOVE;
            pressure = 0.0;
            break;
        case ofMouseEventArgs::Released:
            type = POINTER_UP;
            pressure = 0.0;
            break;
        case ofMouseEventArgs::Scrolled:
            type = POINTER_SCROLL;
            pressure = 0.0;
            break;
        case ofMouseEventArgs::Entered:
        case ofMouseEventArgs::Exited:
            break;
    }

    Point point(glm::vec3(e.x, e.y, 0), shape, pressure);

    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    uint64_t buttons = 0;

    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_1) ? (1 << OF_MOUSE_BUTTON_1) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_2) ? (1 << OF_MOUSE_BUTTON_2) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_3) ? (1 << OF_MOUSE_BUTTON_3) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_4) ? (1 << OF_MOUSE_BUTTON_4) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_5) ? (1 << OF_MOUSE_BUTTON_5) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_6) ? (1 << OF_MOUSE_BUTTON_6) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_7) ? (1 << OF_MOUSE_BUTTON_7) : 0;

    uint64_t timestamp = PointerUtilities::timestampMillis();

    return PointerEventArgs(type,
                            point,
                            0,
                            0,
                            PointerEventArgs::TYPE_MOUSE,
                            true,
                            true,
                            e.button,
                            buttons,
                            modifiers,
                            tapCount,
                            timestamp,
                            source);

}


PointerEvents::PointerEvents(): PointerEvents::PointerEvents(nullptr)
{
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
    _mouseMovedListener = eventSource->mouseMoved.newListener(this, &PointerEvents::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    _mouseDraggedListener = eventSource->mouseDragged.newListener(this, &PointerEvents::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    _mousePressedListener = eventSource->mousePressed.newListener(this, &PointerEvents::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    _mouseReleasedListener = eventSource->mouseReleased.newListener(this, &PointerEvents::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
#endif

    _touchUpListener = eventSource->touchUp.newListener(this, &PointerEvents::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    _touchDownListener = eventSource->touchDown.newListener(this, &PointerEvents::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    _touchMovedListener = eventSource->touchMoved.newListener(this, &PointerEvents::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    _touchDoubleTapListener = eventSource->touchDoubleTap.newListener(this, &PointerEvents::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    _touchCancelledListener = eventSource->touchCancelled.newListener(this, &PointerEvents::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


PointerEvents::~PointerEvents()
{
}


bool PointerEvents::mouseMoved(const void* source, ofMouseEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    ofNotifyEvent(onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::mouseDragged(const void* source, ofMouseEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    ofNotifyEvent(onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::mousePressed(const void* source, ofMouseEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    updateTapCount(p);
    ofNotifyEvent(onPointerDown, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::mouseReleased(const void* source, ofMouseEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    updateTapCount(p);
    ofNotifyEvent(onPointerUp, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::touchDown(const void* source, ofTouchEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    updateTapCount(p);
    ofNotifyEvent(onPointerDown, p, this);
    return _consumeTouchEvents;
}


bool PointerEvents::touchMoved(const void* source, ofTouchEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    ofNotifyEvent(onPointerMove, p, this);
    return _consumeTouchEvents;
}


bool PointerEvents::touchUp(const void* source, ofTouchEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    updateTapCount(p);
    ofNotifyEvent(onPointerUp, p, this);
    return _consumeTouchEvents;
}


bool PointerEvents::touchDoubleTap(const void* source, ofTouchEventArgs& e)
{
    // We can consume these events, but skip them.
    // Users should check the tap count.
    return _consumeTouchEvents;
}


bool PointerEvents::touchCancelled(const void* source, ofTouchEventArgs& e)
{
    // TODO: Recognize source when sent by oF core.
    auto p = PointerEventArgs::toPointerEventArgs(e, _source);
    updateTapCount(p);
    ofNotifyEvent(onPointerCancel, p, this);
    return _consumeTouchEvents;
}


void PointerEvents::setConsumeMouseEvents(bool consumeMouseEvents)
{
    _consumeMouseEvents = consumeMouseEvents;
}


void PointerEvents::setConsumeTouchEvents(bool consumeTouchEvents)
{
    _consumeTouchEvents = consumeTouchEvents;
}


PointerEvents& PointerEvents::instance()
{
    static PointerEvents instance;
    return instance;
}


void PointerEvents::updateTapCount(PointerEventArgs& e)
{
    PointerEventArgs::PointerEventKey key(e.id(), e.button());

    uint64_t _doubleTapThreshold = PointerUtilities::tapTimeoutMillis();

    auto iter = _pointerDownEventTimeMap.find(key);

    if (e.eventType() == PointerEventArgs::POINTER_DOWN)
    {
        if (iter != _pointerDownEventTimeMap.end())
        {
            if (e.timestampMillis() <= (iter->second.timestampMillis() + _doubleTapThreshold))
            {
                e._tapCount += iter->second._tapCount;
            }
        }
        
        _pointerDownEventTimeMap[key] = e;
    }
    else if (iter != _pointerDownEventTimeMap.end() && e.eventType() == PointerEventArgs::POINTER_UP)
    {
        // Transfer the tap count.
        e._tapCount += iter->second._tapCount;
    }
    else if (iter != _pointerDownEventTimeMap.end() && e.timestampMillis() > (iter->second.timestampMillis() + _doubleTapThreshold))
    {
        _pointerDownEventTimeMap.erase(iter);
    }
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


} // namespace ofx
