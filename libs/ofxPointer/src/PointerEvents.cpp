// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


float PointShape::getWidth() const
{
    return _width;
}


float PointShape::getHeight() const
{
    return _height;
}


float PointShape::getEllipseMajorAxis() const
{
    return _ellipseMajorAxis;
}


float PointShape::getEllipseMinorAxis() const
{
    return _ellipseMinorAxis;
}


float PointShape::getEllipseAngle() const
{
    return _ellipseAngle;
}


PointShape PointShape::fromJSON(const Json::Value& json)
{
    return PointShape(json.get("width", 0).asFloat(),
                      json.get("height", 0).asFloat(),
                      json.get("ellipseMajorAxis", 0).asFloat(),
                      json.get("ellipseMinorAxis", 0).asFloat(),
                      json.get("ellipseAngle", 0).asFloat());
}


Json::Value PointShape::toJSON(const PointShape& pointShape)
{
    Json::Value json;
    
    json["width"] = pointShape._width;
    json["height"] = pointShape._height;
    json["ellipseMajorAxis"] = pointShape._ellipseMajorAxis;
    json["ellipseMinorAxis"] = pointShape._ellipseMinorAxis;
    json["ellipseAngle"] = pointShape._ellipseAngle;
    
    return json;
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


const ofVec3f& Point::getAbsolutePosition() const
{
    return _absolutePosition;
}


float Point::getPressure() const
{
    return _pressure;
}


float Point::getTangentialPressure() const
{
    return _tangentialPressure;
}


float Point::getRotation() const
{
    return _rotation;
}


float Point::getTiltX() const
{
    return _tiltX;
}


float Point::getTiltY() const
{
    return _tiltY;
}


const PointShape& Point::getShape() const
{
    return _shape;
}


Point Point::fromJSON(const Json::Value& json)
{
    ofVec3f position;

    if (json.isMember("position"))
    {
        const Json::Value& positionJSON = json["position"];
        position.x = positionJSON.get("x", 0).asFloat();
        position.y = positionJSON.get("y", 0).asFloat();
        position.z = positionJSON.get("z", 0).asFloat();
    }

    ofVec3f absolutePosition;

    if (json.isMember("absolutePosition"))
    {
        const Json::Value& positionJSON = json["absolutePosition"];
        position.x = positionJSON.get("x", 0).asFloat();
        position.y = positionJSON.get("y", 0).asFloat();
        position.z = positionJSON.get("z", 0).asFloat();
    }

    return Point(position,
                 absolutePosition,
                 PointShape::fromJSON(json.get("pointShape", Json::Value())),
                 json.get("pressure", 0).asFloat(),
                 json.get("tangentialPressure", 0).asFloat(),
                 json.get("rotation", 0).asFloat(),
                 json.get("tiltX", 0).asFloat(),
                 json.get("tiltY", 0).asFloat());

}


Json::Value Point::toJSON(const Point& point)
{
    Json::Value json;
    json["position"]["x"] =         point.x;
    json["position"]["y"] =         point.y;
    json["position"]["z"] =         point.z;
    json["absolutePosition"]["x"] = point._absolutePosition.x;
    json["absolutePosition"]["y"] = point._absolutePosition.y;
    json["absolutePosition"]["z"] = point._absolutePosition.z;
    json["pointShape"] =            PointShape::toJSON(point._shape);
    json["pressure"] =              point._pressure;
    json["tangentialPressure"] =    point._tangentialPressure;
    json["rotation"] =              point._rotation;
    json["tiltX"] =                 point._tiltX;
    json["tiltY"] =                 point._tiltY;
    
    return json;
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
                     -1,
                     -1,
                     TYPE_UNKNOWN,
                     false,
                     0,
                     0,
                     0,
                     0,
                     0)
{
}


PointerEventArgs::PointerEventArgs(const std::string& eventType,
                                   const Point& point,
                                   long deviceId,
                                   long pointerIndex,
                                   const std::string& deviceType,
                                   bool isPrimary,
                                   unsigned long button,
                                   unsigned long buttons,
                                   unsigned long modifiers,
                                   unsigned int pressCount,
                                   uint64_t timestamp):
    _eventType(eventType),
    _id(0),
    _deviceId(deviceId),
    _pointerIndex(pointerIndex),
    _deviceType(deviceType),
    _point(point),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers),
    _pressCount(pressCount),
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


long PointerEventArgs::deviceId() const
{
    return _deviceId;
}


long PointerEventArgs::index() const
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


bool PointerEventArgs::isPrimary() const
{
    return _isPrimary;
}


unsigned long PointerEventArgs::button() const
{
    return _button;
}


unsigned long PointerEventArgs::buttons() const
{
    return _buttons;
}


unsigned long PointerEventArgs::modifiers() const
{
    return _modifiers;
}


unsigned int PointerEventArgs::pressCount() const
{
    return _pressCount;
}


uint64_t PointerEventArgs::timestamp() const
{
    return _timestamp;
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofTouchEventArgs& evt)
{
    PointShape shape(evt.width,
                     evt.height,
                     evt.majoraxis,
                     evt.minoraxis,
                     evt.angle);

    Point point(evt, evt, shape, evt.pressure, 0, 0, 0, 0);

    unsigned long modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    uint64_t timestamp = ofGetElapsedTimeMillis();

    std::string type = POINTER_MOVE;

    unsigned long buttons = 0;
    unsigned int pressCount = 0;

    switch (evt.type)
    {
		case ofTouchEventArgs::doubleTap:
			// We don't use this event.
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
                            evt.id,
                            PointerEventArgs::TYPE_TOUCH,
                            false,
                            0,
                            buttons,
                            modifiers,
                            pressCount,
                            timestamp);
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofMouseEventArgs& evt)
{
    PointShape shape;

    float pressure = 0;

    std::string type = POINTER_MOVE;

    unsigned int pressCount = 0;

    switch (evt.type)
    {
        case ofMouseEventArgs::Pressed:
            type = POINTER_DOWN;
            pressCount = 1;
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

    Point point(evt, evt, shape, pressure, 0, 0, 0 , 0);

    unsigned long modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    unsigned long buttons = 0;

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
                            evt.button,
                            buttons,
                            modifiers,
                            pressCount,
                            timestamp);

}


PointerEventArgs PointerEventArgs::fromJSON(const Json::Value& json)
{
    return PointerEventArgs(json.get("eventType", POINTER_MOVE).asString(),
                            Point::fromJSON(json.get("point", Json::Value())),
                            json.get("deviceId", 0).asLargestInt(),
                            json.get("pointerId", 0).asLargestInt(),
                            json.get("deviceType", TYPE_UNKNOWN).asString(),
                            json.get("isPrimary", false).asBool(),
                            json.get("button", 0).asUInt64(),
                            json.get("buttons", 0).asUInt64(),
                            json.get("modifiers", 0).asUInt64(),
                            json.get("pressCount", 0).asUInt(),
                            json.get("timestamp", 0).asUInt64());
}


Json::Value PointerEventArgs::toJSON(const PointerEventArgs& evt)
{
    Json::Value json;

    json["eventType"]  = evt._eventType;
    json["point"]      = Point::toJSON(evt._point);
    json["deviceId"]   = (Json::Int64)evt._deviceId;
    json["pointerIndex"]  = (Json::Int64)evt._pointerIndex;
    json["deviceType"] = evt._deviceType;
    json["isPrimary"]  = evt._isPrimary;
    json["button"]     = (Json::Int64)evt._button;
    json["buttons"]    = (Json::Int64)evt._buttons;
    json["modifiers"]  = (Json::Int64)evt._modifiers;
    json["pressCount"] = (Json::Int64)evt._pressCount;
    json["timestamp"]  = (Json::Int64)evt._timestamp;

    return json;
}


PointerEvents::PointerEvents():
    _consumeMouseEvents(false),
    _consumeTouchEvents(false)
{
#if !defined(TARGET_OF_IOS) && !defined(TARGET_ANDROID)
    ofAddListener(ofEvents().mouseMoved, this, &PointerEvents::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseDragged, this, &PointerEvents::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &PointerEvents::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &PointerEvents::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
#endif

    ofAddListener(ofEvents().touchUp, this, &PointerEvents::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDown, this, &PointerEvents::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchMoved, this, &PointerEvents::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDoubleTap, this, &PointerEvents::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchCancelled, this, &PointerEvents::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


PointerEvents::~PointerEvents()
{
#if !defined(TARGET_OF_IOS) && !defined(TARGET_ANDROID)
    ofRemoveListener(ofEvents().mouseMoved, this, &PointerEvents::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseDragged, this, &PointerEvents::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &PointerEvents::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseReleased, this, &PointerEvents::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
#endif

    ofRemoveListener(ofEvents().touchUp, this, &PointerEvents::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchDown, this, &PointerEvents::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchMoved, this, &PointerEvents::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchDoubleTap, this, &PointerEvents::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().touchCancelled, this, &PointerEvents::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
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
    handleMultiPress(p);
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
    handleMultiPress(p);
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


void PointerEvents::handleMultiPress(PointerEventArgs& evt)
{
    PointerPressEventKey key(evt.id(), evt.button());

    uint64_t _doublePressThreshold = PointerUtilities::getSystemDoublePressInterval();
    
    PointerPressEvents::iterator iter = _pointerDownEvents.find(key);
    
    if (iter != _pointerDownEvents.end())
    {
        PointerEventArgs& lastEvent = (*iter).second;
        
        if (evt.timestamp() <= (lastEvent.timestamp() + _doublePressThreshold))
        {
            evt._pressCount += lastEvent.pressCount();
        }
    }
    
    _pointerDownEvents[key] = evt;
}


} // namespace ofx
