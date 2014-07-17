// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


#include "PointerEventArgs.h"


namespace ofx {


PointerEventArgs::PointerEventArgs():
    _eventType(EVENT_UNKNOWN),
    _deviceType(DEVICE_UNKNOWN),
    _frameId(0),
    _id(0),
    _deviceId(0),
    _windowId(0),
    _pointerId(0),
    _pointerCount(0),
    _width(0),
    _height(0),
    _angle(0),
    _majorAxis(0),
    _minorAxis(0),
    _pressure(0),
    _tapCount(0),
    _modifiers(0),
    _buttons(0),
    _isInContact(false),
    _position(ofVec3f(0,0,0)),
    _lastPosition(ofVec3f(0,0,0)),
    _velocity(ofVec3f(0,0,0)),
    _acceleration(ofVec3f(0,0,0)),
    _timeStamp(0)
{
}


PointerEventArgs::PointerEventArgs(const ofTouchEventArgs& evt):
    _eventType(EVENT_UNKNOWN),
    _deviceType(DEVICE_UNKNOWN),
    _frameId(0),
    _id(evt.id),
    _deviceId(0),
    _windowId(0),
    _pointerId(0),
    _pointerCount(evt.numTouches),
    _width(evt.width),
    _height(evt.height),
    _angle(evt.angle),
    _majorAxis(evt.majoraxis),
    _minorAxis(evt.minoraxis),
    _pressure(evt.pressure),
    _tapCount(0),
    _modifiers(0),
    _buttons(0),
    _isInContact(true),
    _position(evt),
    _lastPosition(ofVec3f(0,0,0)),
    _velocity(ofVec2f(evt.xspeed,evt.yspeed)),
    _acceleration(ofVec2f(evt.xaccel,evt.yaccel)),
    _timeStamp(evt.time)
{
    switch (evt.type)
    {
        case ofTouchEventArgs::down:
            _eventType = EVENT_DOWN;
            break;
        case ofTouchEventArgs::up:
            _eventType = EVENT_UP;
            break;
        case ofTouchEventArgs::move:
            _eventType = EVENT_MOVE;
            break;
        case ofTouchEventArgs::doubleTap:
            _eventType = EVENT_DOUBLE_TAP;
            break;
        case ofTouchEventArgs::cancel:
            _eventType = EVENT_CANCEL;
            break;
    }
}


PointerEventArgs::PointerEventArgs(const ofMouseEventArgs& evt):
    _eventType(EVENT_UNKNOWN),
    _deviceType(DEVICE_UNKNOWN),
    _frameId(0),
    _id(0),
    _deviceId(0),
    _windowId(0),
    _pointerId(0),
    _pointerCount(0),
    _width(0),
    _height(0),
    _angle(0),
    _majorAxis(0),
    _minorAxis(0),
    _pressure(0),
    _tapCount(0),
    //_modifiers(evt.modifiers),
    _buttons(evt.button),
    _isInContact(false),
    _position(evt),
    _lastPosition(ofVec3f(0,0,0)),
    _velocity(ofVec3f(0,0,0)),
    _acceleration(ofVec3f(0,0,0)),
    _timeStamp(ofGetSystemTime())
{
    _buttons = 0;

    switch (evt.type)
    {
        case ofMouseEventArgs::Pressed:
            _eventType = EVENT_DOWN;
            _pressure = 1;
            _isInContact = true;
            break;
        case ofMouseEventArgs::Moved:
            _eventType = EVENT_MOVE;
            _pressure = 0;
            _isInContact = false;
            break;
        case ofMouseEventArgs::Released:
            _eventType = EVENT_UP;
            _pressure = 0;
            _isInContact = true;
            break;
        case ofMouseEventArgs::Dragged:
            _eventType = EVENT_MOVE;
            _pressure = 1;
            _isInContact = true;
            break;
    }

    if(ofGetMousePressed(OF_MOUSE_BUTTON_1)) _buttons |= POINTER_BUTTON_1;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_2)) _buttons |= POINTER_BUTTON_2;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_3)) _buttons |= POINTER_BUTTON_3;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_4)) _buttons |= POINTER_BUTTON_4;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_5)) _buttons |= POINTER_BUTTON_5;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_6)) _buttons |= POINTER_BUTTON_6;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_7)) _buttons |= POINTER_BUTTON_7;
    if(ofGetMousePressed(OF_MOUSE_BUTTON_8)) _buttons |= POINTER_BUTTON_8;

}

PointerEventArgs::~PointerEventArgs()
{
}


PointerEventArgs::EventType PointerEventArgs::getEventType() const
{
    return _eventType;
}


PointerEventArgs::DeviceType PointerEventArgs::getDeviceType() const
{
    return _deviceType;
}


ofVec3f PointerEventArgs::getPosition() const
{
    return _position;
}


ofVec3f PointerEventArgs::getLastPosition() const
{
    return _lastPosition;
}


ofVec3f PointerEventArgs::getVelocity() const
{
    return _velocity;
}


bool PointerEventArgs::isModifierPressed(unsigned int modifier) const
{
    return _modifiers & modifier;
}


bool PointerEventArgs::isButtonPressed(unsigned int button) const
{
    return _buttons & button;
}


unsigned long long PointerEventArgs::getTimeStamp() const
{
    return _timeStamp;
}


unsigned int PointerEventArgs::getId() const
{
    return _id;
}


unsigned int PointerEventArgs::getModifiers() const
{
    return _modifiers;
}


bool PointerEventArgs::operator == (const PointerEventArgs& other) const
{
    // TODO::
    return false;
}


bool PointerEventArgs::operator != (const PointerEventArgs& other) const
{
    return !(*this == other);
}


} // namespace ofx
