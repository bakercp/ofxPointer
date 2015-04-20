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


#include "ofx/PointerEvent.h"


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
    json["position"]["x"] = point.x;
    json["position"]["y"] = point.y;
    json["position"]["z"] = point.z;
    json["absolutePosition"]["x"] = point._absolutePosition.x;
    json["absolutePosition"]["y"] = point._absolutePosition.y;
    json["absolutePosition"]["z"] = point._absolutePosition.z;
    json["pointShape"] = PointShape::toJSON(point._shape);
    json["pressure"] = point._pressure;
    json["tangentialPressure"] = point._tangentialPressure;
    json["rotation"] = point._rotation;
    json["tiltX"] = point._tiltX;
    json["tiltY"] = point._tiltY;
    
    return json;
}


const PointerEvent::DeviceType PointerEvent::TYPE_MOUSE = "mouse";
const PointerEvent::DeviceType PointerEvent::TYPE_PEN = "pen";
const PointerEvent::DeviceType PointerEvent::TYPE_TOUCH = "touch";
const PointerEvent::DeviceType PointerEvent::TYPE_UNKNOWN = "unknown";

const PointerEvent::EventType PointerEvent::POINTER_DOWN = "down";
const PointerEvent::EventType PointerEvent::POINTER_UP = "up";
const PointerEvent::EventType PointerEvent::POINTER_MOVE = "move";
const PointerEvent::EventType PointerEvent::POINTER_CANCEL = "cancel";
const PointerEvent::EventType PointerEvent::POINTER_SCROLL = "scroll";


PointerEvent::PointerEvent():
    _eventType(POINTER_MOVE),
    _point(Point()),
    _deviceID(-1),
    _pointerID(-1),
    _deviceType(TYPE_UNKNOWN),
    _isPrimary(false),
    _button(0),
    _buttons(0),
    _modifiers(0),
    _timestamp(0)
{
}


PointerEvent::PointerEvent(const EventType& eventType,
                                   const Point& point,
                                   long deviceID,
                                   long pointerID,
                                   const DeviceType& deviceType,
                                   bool isPrimary,
                                   unsigned long button,
                                   unsigned long buttons,
                                   unsigned long modifiers,
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
    _timestamp(timestamp)
{
}


PointerEvent::~PointerEvent()
{
}


const PointerEvent::EventType& PointerEvent::getEventType() const
{
    return _eventType;
}


const Point& PointerEvent::getPoint() const
{
    return _point;
}


long PointerEvent::getDeviceID() const
{
    return _deviceID;
}


long PointerEvent::getPointerID() const
{
    return _pointerID;
}


PointerEvent::PointerID PointerEvent::getID() const
{
    return std::pair<long, long>(_deviceID, _pointerID);
}


const PointerEvent::DeviceType& PointerEvent::getDeviceType() const
{
    return _deviceType;
}


bool PointerEvent::isPrimary() const
{
    return _isPrimary;
}


unsigned long PointerEvent::getButton() const
{
    return _button;
}


unsigned long PointerEvent::getButtons() const
{
    return _buttons;
}


unsigned long PointerEvent::getModifiers() const
{
    return _modifiers;
}


unsigned long long PointerEvent::getTimestamp() const
{
    return _timestamp;
}


PointerEvent PointerEvent::toPointerEvent(const ofTouchEventArgs& evt)
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

    switch (evt.type)
    {
        case ofTouchEventArgs::down:
        case ofTouchEventArgs::doubleTap:
            type = POINTER_DOWN;
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

    return PointerEvent(type,
                        point,
                        0,
                        evt.id,
                        PointerEvent::TYPE_TOUCH,
                        false,
                        0,
                        0,
                        modifiers,
                        timestamp);
}


PointerEvent PointerEvent::toPointerEvent(const ofMouseEventArgs& evt)
{
    PointShape shape;

    float pressure = 0;

    unsigned long tapCount = 0;

    EventType type = POINTER_MOVE;

    switch (evt.type)
    {
        case ofMouseEventArgs::Pressed:
            type = POINTER_DOWN;
            pressure = 0.5;
            tapCount = 1;
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

    return PointerEvent::PointerEvent(type,
                                              point,
                                              0,
                                              0,
                                              PointerEvent::TYPE_MOUSE,
                                              true,
                                              evt.button,
                                              buttons,
                                              modifiers,
                                              timestamp);

}


PointerEvent PointerEvent::fromJSON(const Json::Value& json)
{
    return PointerEvent(json.get("eventType", POINTER_MOVE).asString(),
                            Point::fromJSON(json.get("point", Json::Value())),
                            json.get("deviceID", 0).asLargestInt(),
                            json.get("pointerID", 0).asLargestInt(),
                            json.get("deviceType", TYPE_UNKNOWN).asString(),
                            json.get("isPrimary", false).asBool(),
                            json.get("button", 0).asLargestInt(),
                            json.get("buttons", 0).asLargestInt(),
                            json.get("modifiers", 0).asLargestInt(),
                            json.get("timestamp", 0).asLargestUInt());
}


Json::Value PointerEvent::toJSON(const PointerEvent& pointerEventArgs)
{
    Json::Value json;

    json["eventType"] = pointerEventArgs._eventType;
    json["point"] = Point::toJSON(pointerEventArgs._point);
    json["deviceID"] = (Json::Int64)pointerEventArgs._deviceID;
    json["pointerID"] = (Json::Int64)pointerEventArgs._pointerID;
    json["deviceType"] = pointerEventArgs._deviceType;
    json["isPrimary"] = pointerEventArgs._isPrimary;
    json["button"] = (Json::Int64)pointerEventArgs._button;
    json["buttons"] = (Json::Int64)pointerEventArgs._buttons;
    json["modifiers"] = (Json::Int64)pointerEventArgs._modifiers;
    json["timestamp"] = (Json::Int64)pointerEventArgs._timestamp;

    return json;
}


} // namespace ofx
