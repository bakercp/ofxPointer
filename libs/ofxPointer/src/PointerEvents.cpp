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


PointShape::PointShape():
    _width(0),
    _height(0),
    _ellipseMajorAxis(0),
    _ellipseMinorAxis(0),
    _ellipseAngle(0)
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

Point::Point():
    ofVec3f(0, 0, 0),
    _absolutePosition(0, 0, 0),
    _shape(PointShape()),
    _pressure(0),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(0),
    _tiltY(0)
{
}


Point::Point(const ofVec3f& position):
    ofVec3f(position),
    _absolutePosition(position),
    _shape(PointShape()),
    _pressure(0),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(0),
    _tiltY(0)
{
}


Point::Point(const ofVec3f& position, const PointShape& shape):
    ofVec3f(position),
    _absolutePosition(position),
    _shape(shape),
    _pressure(0),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(0),
    _tiltY(0)
{
}


Point::Point(const ofVec3f& position, float pressure, float tiltX, float tiltY):
    ofVec3f(position),
    _absolutePosition(position),
    _shape(PointShape()),
    _pressure(pressure),
    _tangentialPressure(0),
    _rotation(0),
    _tiltX(tiltX),
    _tiltY(tiltY)
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


const PointerEventArgs::DeviceType PointerEventArgs::TYPE_MOUSE    = "mouse";
const PointerEventArgs::DeviceType PointerEventArgs::TYPE_PEN      = "pen";
const PointerEventArgs::DeviceType PointerEventArgs::TYPE_TOUCH    = "touch";
const PointerEventArgs::DeviceType PointerEventArgs::TYPE_UNKNOWN  = "unknown";

const PointerEventArgs::EventType PointerEventArgs::POINTER_DOWN   = "down";
const PointerEventArgs::EventType PointerEventArgs::POINTER_UP     = "up";
const PointerEventArgs::EventType PointerEventArgs::POINTER_MOVE   = "move";
const PointerEventArgs::EventType PointerEventArgs::POINTER_CANCEL = "cancel";
const PointerEventArgs::EventType PointerEventArgs::POINTER_SCROLL = "scroll";


PointerEventArgs::PointerEventArgs():
    _point(Point()),
    _eventType(POINTER_MOVE),
    _deviceID(-1),
    _pointerID(-1),
    _deviceType(TYPE_UNKNOWN),
    _isPrimary(false),
    _button(0),
    _buttons(0),
    _modifiers(0),
    _pressCount(0),
    _timestamp(0)
{
}


PointerEventArgs::PointerEventArgs(const EventType& eventType,
                                   const Point& point,
                                   long deviceID,
                                   long pointerID,
                                   const DeviceType& deviceType,
                                   bool isPrimary,
                                   unsigned long button,
                                   unsigned long buttons,
                                   unsigned long modifiers,
                                   unsigned int pressCount,
                                   unsigned long long timestamp):
    _point(point),
    _eventType(eventType),
    _deviceID(deviceID),
    _pointerID(pointerID),
    _deviceType(deviceType),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers),
    _pressCount(pressCount),
    _timestamp(timestamp)
{
}


PointerEventArgs::~PointerEventArgs()
{
}


const PointerEventArgs::EventType& PointerEventArgs::getEventType() const
{
    return _eventType;
}


const Point& PointerEventArgs::getPoint() const
{
    return _point;
}


long PointerEventArgs::getDeviceID() const
{
    return _deviceID;
}


long PointerEventArgs::getPointerID() const
{
    return _pointerID;
}


PointerEventArgs::PointerID PointerEventArgs::getID() const
{
    return std::pair<long, long>(_deviceID, _pointerID);
}


const PointerEventArgs::DeviceType& PointerEventArgs::getDeviceType() const
{
    return _deviceType;
}


bool PointerEventArgs::isPrimary() const
{
    return _isPrimary;
}


unsigned long PointerEventArgs::getButton() const
{
    return _button;
}


unsigned long PointerEventArgs::getButtons() const
{
    return _buttons;
}


unsigned long PointerEventArgs::getModifiers() const
{
    return _modifiers;
}


unsigned int PointerEventArgs::getPressCount() const
{
    return _pressCount;
}


unsigned long long PointerEventArgs::getTimestamp() const
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

    unsigned long long timestamp = ofGetElapsedTimeMillis();

    EventType type = POINTER_MOVE;

    unsigned int pressCount = 0;

    switch (evt.type)
    {
        case ofTouchEventArgs::down:
        case ofTouchEventArgs::doubleTap:
            type = POINTER_DOWN;
            pressCount = 1;
            break;
        case ofTouchEventArgs::up:
            type = POINTER_UP;
            break;
        case ofTouchEventArgs::move:
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
                            0,
                            modifiers,
                            pressCount,
                            timestamp);
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofMouseEventArgs& evt)
{
    PointShape shape;

    float pressure = 0;

    EventType type = POINTER_MOVE;

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

    unsigned long long timestamp = ofGetElapsedTimeMillis();

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
                            json.get("deviceID", 0).asLargestInt(),
                            json.get("pointerID", 0).asLargestInt(),
                            json.get("deviceType", TYPE_UNKNOWN).asString(),
                            json.get("isPrimary", false).asBool(),
                            json.get("button", 0).asLargestInt(),
                            json.get("buttons", 0).asLargestInt(),
                            json.get("modifiers", 0).asLargestInt(),
                            json.get("pressCount", 0).asLargestInt(),
                            json.get("timestamp", 0).asLargestUInt());
}


Json::Value PointerEventArgs::toJSON(const PointerEventArgs& evt)
{
    Json::Value json;

    json["eventType"]  = evt._eventType;
    json["point"]      = Point::toJSON(evt._point);
    json["deviceID"]   = (Json::Int64)evt._deviceID;
    json["pointerID"]  = (Json::Int64)evt._pointerID;
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
    ofAddListener(ofEvents().mouseMoved, this, &PointerEvents::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseDragged, this, &PointerEvents::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &PointerEvents::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &PointerEvents::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);

    ofAddListener(ofEvents().touchUp, this, &PointerEvents::touchUp, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDown, this, &PointerEvents::touchDown, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchMoved, this, &PointerEvents::touchMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchDoubleTap, this, &PointerEvents::touchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().touchCancelled, this, &PointerEvents::touchCancelled, OF_EVENT_ORDER_BEFORE_APP);
}


PointerEvents::~PointerEvents()
{
    ofRemoveListener(ofEvents().mouseMoved, this, &PointerEvents::mouseMoved, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseDragged, this, &PointerEvents::mouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &PointerEvents::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mouseReleased, this, &PointerEvents::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);

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
    PointerPressEventKey key(evt.getID(), evt.getButton());

    Poco::Timespan _doublePressThreshold = PointerUtilities::getSystemDoublePressInterval();
    
    PointerPressEvents::iterator iter = _pointerDownEvents.find(key);
    
    if (iter != _pointerDownEvents.end())
    {
        PointerEventArgs& lastEvent = (*iter).second;
        
        if (evt.getTimestamp() <= (lastEvent.getTimestamp() + _doublePressThreshold.totalMilliseconds()))
        {
            evt._pressCount += lastEvent.getPressCount();
        }
    }
    
    _pointerDownEvents[key] = evt;
}


} // namespace ofx
