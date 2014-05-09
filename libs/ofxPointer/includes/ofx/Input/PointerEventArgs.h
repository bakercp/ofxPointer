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


#pragma once


#include "ofEvents.h"
#include "ofVec3f.h"
#include "ofUtils.h"


namespace ofx {
namespace Input {


class PointerEventArgs: public ofEventArgs
{
public:
    enum EventType
    {
        EVENT_UNKNOWN,
        EVENT_DOWN,
        EVENT_UP,
        EVENT_MOVE,
        EVENT_DOUBLE_TAP,
        EVENT_CANCEL
	};

    enum DeviceType
    {
        DEVICE_UNKNOWN = -1,
        DEVICE_MOUSE = 0,
        DEVICE_TOUCH = 1,
        DEVICE_PEN   = 2
    };

    enum Buttons
    {
        POINTER_BUTTON_1        = 0x00000001,
        POINTER_BUTTON_2        = 0x00000010,
        POINTER_BUTTON_3        = 0x00000100,
        POINTER_BUTTON_4        = 0x00001000,
        POINTER_BUTTON_5        = 0x00010000,
        POINTER_BUTTON_6        = 0x00100000,
        POINTER_BUTTON_7        = 0x01000000,
        POINTER_BUTTON_8        = 0x10000000,
        POINTER_BUTTON_LAST     = POINTER_BUTTON_8,
        POINTER_BUTTON_LEFT     = POINTER_BUTTON_1,
        POINTER_BUTTON_MIDDLE   = POINTER_BUTTON_2,
        POINTER_BUTTON_RIGHT    = POINTER_BUTTON_3
    };


    PointerEventArgs();
    PointerEventArgs(const ofTouchEventArgs& evt);
    PointerEventArgs(const ofMouseEventArgs& evt);
    virtual ~PointerEventArgs();

    EventType getEventType() const;
    DeviceType getDeviceType() const;

    unsigned int getFrameId() const;
    unsigned int getId() const;
    unsigned int getDeviceId() const;
    unsigned int getWindowId() const;

    unsigned int getModifiers() const;
    
    bool isInContact() const;

    ofVec3f getPosition() const;
    ofVec3f getLastPosition() const;
    ofVec3f getVelocity() const;
    ofVec3f getAcceleration() const;

    bool isModifierPressed(unsigned int modifier) const;
    bool isButtonPressed(unsigned int button) const;

    unsigned long long getTimeStamp() const;

    bool operator == (const PointerEventArgs& other) const;
    bool operator != (const PointerEventArgs& other) const;

    std::string toString() const
    {
        std::stringstream ss;

        std::string evtType = "UNKNOWN";

        switch(getEventType())
        {
            case EVENT_UNKNOWN:
                evtType = "UNKNOWN";
                break;
            case EVENT_DOWN:
                evtType = "DOWN";
                break;
            case EVENT_UP:
                evtType = "UP";
                break;
            case EVENT_MOVE:
                evtType = "MOVE";
                break;
            case EVENT_DOUBLE_TAP:
                evtType = "DOUBLE_TAP";
                break;
            case EVENT_CANCEL:
                evtType = "CANCEL";
                break;
        }

        ss << evtType << " pos: " << getPosition();

        if(isModifierPressed(OF_KEY_CONTROL)) ss << endl << "\tOF_KEY_CONTROL";
        if(isModifierPressed(OF_KEY_ALT)) ss << endl << "\tOF_KEY_ALT";
        if(isModifierPressed(OF_KEY_SHIFT)) ss << endl << "\tOF_KEY_SHIFT";
        if(isModifierPressed(OF_KEY_SUPER)) ss << endl << "\tOF_KEY_SUPER";

        if(isButtonPressed(POINTER_BUTTON_LEFT)) ss << endl << "\tPOINTER_BUTTON_LEFT";
        if(isButtonPressed(POINTER_BUTTON_MIDDLE)) ss << endl << "\tPOINTER_BUTTON_MIDDLE";
        if(isButtonPressed(POINTER_BUTTON_RIGHT)) ss << endl << "\tPOINTER_BUTTON_RIGHT";

        return ss.str();
    }

private:
    EventType _eventType;
    DeviceType _deviceType;

    unsigned int _frameId;
    unsigned int _id;
    unsigned int _deviceId;
    unsigned int _windowId;

    // multipointers
	unsigned int _pointerId;   // number of active pointers
	unsigned int _pointerCount;   // number of active pointers

    // pointer shape
    float _width;
    float _height;

    // touch ellipse
	float _angle;        // radians
	float _minorAxis;
    float _majorAxis;

    // pressure
	float _pressure;     // pressure

    unsigned int _tapCount;

    unsigned int _modifiers;
    unsigned int _buttons;

    bool _isInContact;

    ofVec3f _position;
    ofVec3f _lastPosition;
    ofVec3f _velocity;
    ofVec3f _acceleration;
    
    unsigned long long _timeStamp;
    
};


} } // namespace ofx::Input
