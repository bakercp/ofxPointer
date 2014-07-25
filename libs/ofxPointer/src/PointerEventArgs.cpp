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


PointerEventArgs::PointerEventArgs(const Point& point,
                                   long deviceID,
                                   long pointerID,
                                   const std::string& type,
                                   bool isPrimary,
                                   unsigned long button,
                                   unsigned long buttons,
                                   unsigned long modifiers,
                                   unsigned long tapCount,
                                   const Poco::Timestamp& timestamp):
    _point(point),
    _deviceID(deviceID),
    _pointerID(pointerID),
    _type(type),
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


const std::string& PointerEventArgs::getType() const
{
    return _type;
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
                     evt.angle,
                     evt.majoraxis,
                     evt.minoraxis);

    Point point(evt, shape, evt.pressure, 0, 0);

    unsigned long modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    Poco::Timestamp timestamp; // evt.time (?);

    return PointerEventArgs(point,
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

    switch (evt.type)
    {
        case ofMouseEventArgs::Pressed:
            pressure = 0.5;
            tapCount = 1;
            break;
        case ofMouseEventArgs::Dragged:
            pressure = 0.5;
            break;
        case ofMouseEventArgs::Moved:
        case ofMouseEventArgs::Released:
            pressure = 0.0;
            break;
    }

    Point point(evt, shape, pressure, 0, 0);

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

    return PointerEventArgs::PointerEventArgs(evt,
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
