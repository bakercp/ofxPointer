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


        ss << evtType << " pos: " << getPosition() << endl;

//#define OF_KEY_CONTROL		(0x200 | OF_KEY_MODIFIER)
//#define OF_KEY_ALT			(0x400 | OF_KEY_MODIFIER)
//#define OF_KEY_SHIFT		(0x800 | OF_KEY_MODIFIER)
//#define OF_KEY_SUPER		(0x1000 | OF_KEY_MODIFIER)

        if(isModifierPressed(OF_KEY_CONTROL)) ss << "\tOF_KEY_CONTROL" << endl;
        if(isModifierPressed(OF_KEY_ALT)) ss << "\tOF_KEY_ALT" << endl;
        if(isModifierPressed(OF_KEY_SHIFT)) ss << "\tOF_KEY_SHIFT" << endl;
        if(isModifierPressed(OF_KEY_SUPER)) ss << "\tOF_KEY_SUPER" << endl;

        if(isButtonPressed(OF_MOUSE_BUTTON_LEFT)) ss << "\tOF_MOUSE_BUTTON_LEFT" << endl;
        if(isButtonPressed(OF_MOUSE_BUTTON_MIDDLE)) ss << "\tOF_MOUSE_BUTTON_MIDDLE" << endl;
        if(isButtonPressed(OF_MOUSE_BUTTON_RIGHT)) ss << "\tOF_MOUSE_BUTTON_RIGHT" << endl;

        cout << "IN HERE" << endl;

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
