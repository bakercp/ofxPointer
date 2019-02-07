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
                                  ofGetElapsedTimeMillis(),
                                  0)
{
}


EventArgs::EventArgs(const void* eventSource,
                     const std::string& eventType,
                     uint64_t timestampMillis,
                     uint64_t detail):
    _eventSource(eventSource),
    _eventType(eventType),
    _timestampMillis(timestampMillis),
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
    return _timestampMillis;
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
    if (_axisAlignedSizeCached)
        return _axisAlignedWidth;

    _calculateAxisAlignedSize();
    
    return _axisAlignedWidth;
}


float PointShape::axisAlignedHeight() const
{
    if (_axisAlignedSizeCached)
        return _axisAlignedHeight;
    
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


//PointerEventArgs::PointerEventArgs(const std::string& eventType,
//                                   const PointerEventArgs& e):
//    PointerEventArgs(e.eventSource(),
//                     eventType,
//                     e.timestampMillis(),
//                     e.point(),
//                     e.pointerId(),
//                     e.deviceId(),
//                     e.pointerIndex(),
//                     e.sequenceIndex(),
//                     e.deviceType(),
//                     e.isPrimary(),
//                     e.button(),
//                     e.buttons(),
//                     e.modifiers(),
//                     e.coalescedPointerEvents(),
//                     e.predictedPointerEvents(),
//                     e.estimatedProperties(),
//                     e.estimatedPropertiesExpectingUpdates())
//{
//}

PointerEventArgs::PointerEventArgs(const void* eventSource,
                                   const std::string& eventType,
                                   uint64_t timestampMillis,
                                   uint64_t detail,
                                   const Point& point,
                                   std::size_t pointerId,
                                   int64_t deviceId,
                                   int64_t pointerIndex,
                                   uint64_t sequenceIndex,
                                   const std::string& deviceType,
                                   bool isPredicted,
                                   bool isPrimary,
                                   int16_t button,
                                   uint16_t buttons,
                                   uint16_t modifiers,
                                   const std::vector<PointerEventArgs>& coalescedPointerEvents,
                                   const std::vector<PointerEventArgs>& predictedPointerEvents,
                                   const std::set<std::string>& estimatedProperties,
                                   const std::set<std::string>& estimatedPropertiesExpectingUpdates):
    EventArgs(eventSource, eventType, timestampMillis, detail),
    _point(point),
    _pointerId(pointerId),
    _deviceId(deviceId),
    _pointerIndex(pointerIndex),
    _sequenceIndex(sequenceIndex),
    _deviceType(deviceType),
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

    
bool PointerEventArgs::isPredicted() const
{
    return _isPredicted;
}
    

bool PointerEventArgs::isEstimated() const
{
    return !_estimatedProperties.empty();
}
    

bool PointerEventArgs::isPrimary() const
{
    return _isPrimary;
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
    if (e.sequenceIndex() != sequenceIndex())
    {
        ofLogVerbose("PointerEventArgs::updateEstimatedPropertiesWithEvent") << "Sequence numbers do not match.";
        return false;
    }
    
//    auto otherExpected = e.estimatedPropertiesExpectingUpdates();

//    std::cout << "Other Expected: " << std::endl;
//    for (auto& e: otherExpected)
//        std::cout << "\t" << e << std::endl;
    
    auto newEstimatedProperties = e.estimatedProperties();
//
    std::cout << "New Estimated: " << std::endl;
    for (auto& e: newEstimatedProperties)
        std::cout << "\t" << e << std::endl;

//    auto expected = estimatedPropertiesExpectingUpdates();
//    std::cout << "Expecting: " << std::endl;
//    for (auto& e: expected)
//        std::cout << "\t" << e << std::endl;
//
//    auto estimated = estimatedProperties();
//    std::cout << "Estimated: " << std::endl;
//    for (auto& e: estimated)
//        std::cout << "\t" << e << std::endl;

    // Go through the updates we are expecting.
//    auto iter = _estimatedPropertiesExpectingUpdates.begin();
//    while (iter != _estimatedPropertiesExpectingUpdates.end())
//    {
//        auto property = *iter;
//
//        if (otherEstimated.find(*iter) == otherEstimated.end())
//        {
//
//        }
//        ++iter;
//    }
    
    std::vector<std::string> propertiesToUpdate;
    
    std::set_difference(_estimatedPropertiesExpectingUpdates.begin(),
                        _estimatedPropertiesExpectingUpdates.end(),
                        newEstimatedProperties.begin(),
                        newEstimatedProperties.end(),
                        std::inserter(propertiesToUpdate, propertiesToUpdate.begin()));

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
            ofNotifyEvent(pointerPropertyUpdate, property, this);
        }
        else if (property == PointerEventArgs::PROPERTY_TILT_Y)
        {
            _point._tiltYDeg = e.point().tiltYDeg();
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
            ofLogWarning("PointerEventArgs::updateEstimatedPropertiesWithEvent") << "Uknown property to update: " << property;
        }

        _estimatedPropertiesExpectingUpdates.erase(property);
    }
    
    
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

    uint64_t timestampMillis = ofGetElapsedTimeMillis();

    std::string eventType = EVENT_TYPE_UNKNOWN;

    uint64_t detail = 0;
    
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

    // If pressure is not reported and a button is pressed, the pressure is
    // 0.5. If no pressure is reported and no button is pressed, then the
    // pressure is 0.
    float pressure = e.pressure > 0 ? e.pressure : (buttons > 0 ? 0.5 : 0);
    
    Point point(glm::vec2(e.x, e.y), shape, pressure);
    
    // Since we can't know for sure, we assume TOUCH because it came from a
    // ofTouchEventArgs.
    std::string deviceType = PointerEventArgs::TYPE_TOUCH;

    bool isPredicted = false;

    // If the id is 0, it is primary -- theoretically. But in the current legacy
    // implementation, 0 can be reused even if the there are active touches.
    // So, openFrameworks treats this as primary (synthesizes mouse events from
    // touches), but it doesn't work according to the PointerEvents spec.
    //
    // https://www.w3.org/TR/pointerevents/#dfn-primary-pointer
    bool isPrimary = (e.id == 0);
    
    std::size_t pointerId = 0;
    hash_combine(pointerId, deviceId);
    hash_combine(pointerId, e.id);
    hash_combine(pointerId, deviceType);

    int64_t sequenceIndex = 0;
    
    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMillis,
                            detail,
                            point,
                            pointerId,
                            deviceId,
                            e.id,
                            sequenceIndex,
                            deviceType,
                            isPredicted,
                            isPrimary,
                            button,
                            buttons,
                            modifiers,
                            {},
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

    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMillis,
                            detail,
                            point,
                            pointerId,
                            deviceId,
                            pointerIndex,
                            sequenceIndex,
                            deviceType,
                            isPredicted,
                            isPrimary,
                            button,
                            buttons,
                            modifiers,
                            {},
                            {},
                            {},
                            {});
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
    std::cout << "here" << std::endl;
    return _dispatchPointerEvent(source, e);
}

    
    
bool PointerEvents::onMouseEvent(const void* source, ofMouseEventArgs& e)
{
    auto p = PointerEventArgs::toPointerEventArgs(source, e);
    return _dispatchPointerEvent(source, p);
}


bool PointerEvents::onTouchEvent(const void* source, ofTouchEventArgs& e)
{
    std::cout << "2 here" << std::endl;

    auto p = PointerEventArgs::toPointerEventArgs(source, e);
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
    for (auto& events: _activeStrokes)
    {
        ofMesh mesh;

        if (events.second.size() > 2)
        {
            for (std::size_t index = 0; index < events.second.size(); ++index)
            {
                // float width = 0;

                if (index > 1 && events.second.size() > 2)
                {
                    std::size_t i1 = index - 1;
                    std::size_t i2 = index;
                    std::size_t i3 = index + 1;
                    const auto& p1 = events.second[i1].point().position();
                    const auto& p2 = events.second[i2].point().position();
                    const auto& p3 = events.second[i3].point().position();
                    auto v1(p1 - p2); // vector to previous point
                    auto v2(p3 - p2); // vector to next point
                    v1 = glm::normalize(v1);
                    v2 = glm::normalize(v2);
                    glm::vec2 tangent = glm::length2(v2 - v1) > 0 ? glm::normalize(v2 - v1) : -v1;
                    glm::vec3 normal = glm::cross(glm::vec3(tangent, 0), { 0, 0, 1});
                    ofSetColor(ofColor::red);
                    ofDrawLine(p2, p2 + glm::vec2(normal) * 50);
                }

                ofSetColor(ofColor::white, 80);
                ofDrawCircle(events.second[index].point().position(), 10);
            }
        }
    }
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


void PointerDebugRenderer::onPointerEvent(PointerEventArgs& evt)
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


PointerEventCollection::PointerEventCollection()
{
}


//PointerEventCollection::PointerEventCollection(const std::set<std::string>& pointerEventTypes):
//    _pointerEventTypes(pointerEventTypes)
//{
//}


PointerEventCollection::~PointerEventCollection()
{
}

//void PointerEventCollection::setPointerEventTypes(const std::set<std::string>& pointerEventTypes)
//{
//    clear();
//    _pointerEventTypes = pointerEventTypes;
//}
//
//
//std::set<std::string> PointerEventCollection::getPointerEventTypes() const
//{
//    return _pointerEventTypes;
//}

    
//void PointerEventCollection::setMaxNumEventKeys(std::size_t maxNumEventKeys)
//{
//    clear();
//    _maxNumEventKeys = maxNumEventKeys;
//}
//    
//
//std::size_t PointerEventCollection::getMaxNumEventKeys() const
//{
//    return _maxNumEventKeys;
//}


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

    
} // namespace ofx
