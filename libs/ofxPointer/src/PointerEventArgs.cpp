// =============================================================================
//
// Copyright (c) 2010-2014 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/PointerEventArgs.h"


namespace ofx {


const std::string PointerEventArgs::TYPE_MOUSE = "mouse";
const std::string PointerEventArgs::TYPE_PEN = "pen";
const std::string PointerEventArgs::TYPE_TOUCH = "touch";
const std::string PointerEventArgs::TYPE_UNKNOWN = "unknown";


PointerEventArgs::PointerEventArgs():
    _eventType(MOVE),
    _point(Point()),
    _deviceID(-1),
    _pointerID(-1),
    _deviceType(TYPE_UNKNOWN),
    _isPrimary(false),
    _button(0),
    _buttons(0),
    _modifiers(0),
    _tapCount(0),
    _timestamp(Poco::Timestamp())
{
}


PointerEventArgs::PointerEventArgs(EventType eventType,
                                   const Point& point,
                                   long deviceID,
                                   long pointerID,
                                   const std::string& deviceType,
                                   bool isPrimary,
                                   unsigned long button,
                                   unsigned long buttons,
                                   unsigned long modifiers,
                                   unsigned long tapCount,
                                   const Poco::Timestamp& timestamp):
    _point(point),
    _eventType(eventType),
    _deviceID(deviceID),
    _pointerID(pointerID),
    _deviceType(deviceType),
    _isPrimary(isPrimary),
    _button(button),
    _buttons(buttons),
    _modifiers(modifiers),
    _tapCount(tapCount),
    _timestamp(timestamp)
{
}


PointerEventArgs::~PointerEventArgs()
{
}


PointerEventArgs::EventType PointerEventArgs::getEventType() const
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



const std::string& PointerEventArgs::getDeviceType() const
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


unsigned long PointerEventArgs::getTapCount() const
{
    return _tapCount;
}


const Poco::Timestamp& PointerEventArgs::getTimestamp() const
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

    Poco::Timestamp timestamp; // evt.time (?);

    EventType type = MOVE;

    switch (evt.type)
    {
        case ofTouchEventArgs::down:
        case ofTouchEventArgs::doubleTap:
            type = DOWN;
            break;
        case ofTouchEventArgs::up:
            type = UP;
            break;
        case ofTouchEventArgs::move:
            type = MOVE;
            break;
        case ofTouchEventArgs::cancel:
            type = CANCEL;
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
                            0,
                            timestamp);
}


PointerEventArgs PointerEventArgs::toPointerEventArgs(const ofMouseEventArgs& evt)
{
    PointShape shape;

    float pressure = 0;

    unsigned long tapCount = 0;

    EventType type = MOVE;

    switch (evt.type)
    {
        case ofMouseEventArgs::Pressed:
            type = DOWN;
            pressure = 0.5;
            tapCount = 1;
            break;
        case ofMouseEventArgs::Dragged:
            type = MOVE;
            pressure = 0.5;
            break;
        case ofMouseEventArgs::Moved:
            type = MOVE;
            pressure = 0.0;
            break;
        case ofMouseEventArgs::Released:
            type = UP;
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

    Poco::Timestamp timestamp;

    return PointerEventArgs(type,
                            point,
                            0,
                            0,
                            PointerEventArgs::TYPE_MOUSE,
                            true,
                            evt.button,
                            buttons,
                            modifiers,
                            tapCount,
                            timestamp);

}


} // namespace ofx
