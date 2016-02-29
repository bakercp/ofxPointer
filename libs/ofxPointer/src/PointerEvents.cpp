// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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


Point::Point(): Point(ofVec3f(0,0,0))
{
}


Point::Point(const ofVec3f& position): Point(position, PointShape())
{
}


Point::Point(const ofVec3f& position, const PointShape& shape):
    Point(position, position, PointShape(), 0, 0, 0, 0, 0)
{
}


Point::Point(const ofVec3f& position, float pressure, float tiltX, float tiltY):
    Point(position, position, PointShape(), pressure, 0, 0, tiltX, tiltY)
{
}


Point::Point(const ofVec3f& position,
             const ofVec3f& absolutePosition,
             const PointShape& shape,
             float pressure,
             float tangentialPressure,
             float rotation,
             float tiltX,
             float tiltY):
    ofVec3f(position),
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


const ofVec3f& Point::absolutePosition() const
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
                     0)
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
                     e.tapCount(),
                     e.timestamp())

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
                                   uint64_t tapCount,
                                   uint64_t timestamp):
    _eventType(eventType),
    _id(0),
    _deviceId(deviceId),
    _pointerIndex(pointerIndex),
    _deviceType(deviceType),
    _canHover(canHover),
    _point(point),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers),
    _tapCount(tapCount),
    _timestamp(timestamp)
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


uint64_t PointerEventArgs::tapCount() const
{
    return _tapCount;
}


uint64_t PointerEventArgs::timestamp() const
{
    return _timestamp;
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofTouchEventArgs& e)
{
    PointShape shape(e.width,
                     e.height,
                     e.majoraxis,
                     e.minoraxis,
                     e.angle);

    Point point(e, e, shape, e.pressure, 0, 0, 0, 0);

    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    uint64_t timestamp = ofGetElapsedTimeMillis();

    std::string type = POINTER_MOVE;

    uint64_t buttons = 0;
    uint64_t pressCount = 0;

    switch (e.type)
    {
        case ofTouchEventArgs::doubleTap:
            // Pointers don't use this event. We synthesize them.
            break;
        case ofTouchEventArgs::down:
            type = POINTER_DOWN;
            buttons |= (1 << OF_MOUSE_BUTTON_1);
            pressCount = 1;
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
                            pressCount,
                            timestamp);
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofMouseEventArgs& e)
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

    Point point(e, e, shape, pressure, 0, 0, 0 , 0);

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

    uint64_t timestamp = ofGetElapsedTimeMillis();

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
                            timestamp);

}


PointerEvents::PointerEvents()
{
#if !defined(TARGET_OF_IOS) && !defined(TARGET_ANDROID)
    _mouseMovedListener = ofEvents().mouseMoved.newListener(this, &PointerEvents::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    _mouseDraggedListener = ofEvents().mouseDragged.newListener(this, &PointerEvents::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    _mousePressedListener = ofEvents().mousePressed.newListener(this, &PointerEvents::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    _mouseReleasedListener = ofEvents().mouseReleased.newListener(this, &PointerEvents::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
#endif

    _touchUpListener = ofEvents().touchUp.newListener(this, &PointerEvents::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    _touchDownListener = ofEvents().touchDown.newListener(this, &PointerEvents::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    _touchMovedListener = ofEvents().touchMoved.newListener(this, &PointerEvents::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    _touchDoubleTapListener = ofEvents().touchDoubleTap.newListener(this, &PointerEvents::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    _touchCancelledListener = ofEvents().touchCancelled.newListener(this, &PointerEvents::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


PointerEvents::~PointerEvents()
{
}


bool PointerEvents::mouseMoved(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::mouseDragged(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(onPointerMove, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::mousePressed(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    handleMultiTap(p);
    ofNotifyEvent(onPointerDown, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::mouseReleased(ofMouseEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(onPointerUp, p, this);
    return _consumeMouseEvents;
}


bool PointerEvents::touchDown(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    handleMultiTap(p);
    ofNotifyEvent(onPointerDown, p, this);
    return _consumeTouchEvents;
}


bool PointerEvents::touchMoved(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(onPointerMove, p, this);
    return _consumeTouchEvents;
}


bool PointerEvents::touchUp(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
    ofNotifyEvent(onPointerUp, p, this);
    return _consumeTouchEvents;
}


bool PointerEvents::touchDoubleTap(ofTouchEventArgs& e)
{
    // We consume these events.
    // Users should check the press count.
    return _consumeTouchEvents;
}


bool PointerEvents::touchCancelled(ofTouchEventArgs& e)
{
    PointerEventArgs p = PointerEventArgs::toPointerEventArgs(e);
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


void PointerEvents::handleMultiTap(PointerEventArgs& e)
{
    PointerDownEventKey key(e.id(), e.button());

    uint64_t _doubleTapThreshold = PointerUtilities::getSystemDoubleTapInterval();

    PointerDownEvents::iterator iter = _pointerDownEvents.find(key);

    if (iter != _pointerDownEvents.end())
    {
        PointerEventArgs& lastEvent = (*iter).second;

        if (e.timestamp() <= (lastEvent.timestamp() + _doubleTapThreshold))
        {
            e._tapCount += lastEvent.tapCount();
        }
    }

    _pointerDownEvents[key] = e;
}


} // namespace ofx
