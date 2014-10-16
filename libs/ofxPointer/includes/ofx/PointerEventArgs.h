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


#include <string>
#include "Poco/Timestamp.h"
#include "ofEvents.h"
#include "ofUtils.h"
#include "ofx/Point.h"


namespace ofx {


class PointerEventArgs: public ofEventArgs
{
public:
    typedef std::pair<long, long> PointerID;

    enum EventType
    {
        DOWN,
        UP,
        MOVE,
        CANCEL
    };

    PointerEventArgs();

    PointerEventArgs(EventType eventType,
                     const Point& point,
                     long deviceID,
                     long pointerID,
                     const std::string& type,
                     bool isPrimary,
                     unsigned long button,
                     unsigned long buttons,
                     unsigned long modifiers,
                     unsigned long tapCount,
                     const Poco::Timestamp& timestamp);

    virtual ~PointerEventArgs();

    EventType getEventType() const;

    const Point& getPoint() const;

    /// \brief Get the unique input device ID.
    /// \returns the unique input device ID.
    long getDeviceID() const;

    /// \brief Get the unique pointer ID for the given device ID.
    ///
    /// This ID should correspend to different touches for a multi-touch device.
    ///
    /// \returns the unique pointer ID for the given device ID.
    long getPointerID() const;

    /// \brief Get a single unique ID for a device ID and Pointer ID.
    /// \returns a single unique ID for a device ID and Pointer ID.
    PointerID getID() const;

    /// \brief Get the device type string.
    ///
    /// This string may be TYPE_MOUSE, TYPE_TOUCH, TYPE_PEN, or a custom string.
    ///
    /// \returns a device description string.
    const std::string& getDeviceType() const;

    bool isPrimary() const;

    unsigned long getButton() const;

    unsigned long getButtons() const;

    unsigned long getModifiers() const;

    unsigned long getTapCount() const;

    const Poco::Timestamp& getTimestamp() const;

    static PointerEventArgs toPointerEventArgs(const ofTouchEventArgs& evt);
    static PointerEventArgs toPointerEventArgs(const ofMouseEventArgs& evt);

    std::string toString() const
    {
        std::stringstream ss;

        ss << "------------" << std::endl;
        ss << "Device Type: " << getDeviceType() << std::endl;
        ss << "     Button: " << getButton() << std::endl;
        ss << "    Buttons: " << ofToBinary(getButtons()) << std::endl;
        ss << "  Modifiers: " << ofToBinary(getModifiers()) << std::endl;
        ss << "  Tap Count: " << getTapCount() << std::endl;

        return ss.str();
    }

    static const std::string TYPE_MOUSE;
    static const std::string TYPE_PEN;
    static const std::string TYPE_TOUCH;
    static const std::string TYPE_UNKNOWN;

private:
    EventType _eventType;

    Point _point;

    long _deviceID;

    /// \brief A unique pointer ID.
    ///
    /// This value must be unique from all other active pointers at any given
    /// time.  Pointer IDs can be reused and are implementation specific.
    long _pointerID;


    /// \brief The type of device that generated this Point.
    std::string _deviceType;


    /// \brief Indicates if the pointer is a primary pointer.
    ///
    /// In a multi-pointer (e.g. multi-touch) scenario, the isPrimary property
    /// is used to identify a master pointer amongst the set of active pointers
    /// for each pointer type. Only a primary pointer will produce compatibility
    /// mouse events. Authors who desire single-pointer interaction can achieve
    /// this by ignoring non-primary pointers.
    ///
    /// \sa http://www.w3.org/TR/pointerevents/#the-primary-pointer
    bool _isPrimary;

    unsigned long _button;

    unsigned long _buttons;

    unsigned long _modifiers;

    unsigned long _tapCount;

    Poco::Timestamp _timestamp;

};



//class PointerDoubleTapEventArgs: public PointerEventArgs
//{
//public:
//    PointerDoubleTapEventArgs(const PointerEventArgs& evt,
//                              unsigned int tapCount);
//
//    virtual ~PointerGestureEventArgs();
//
//    unsigned int getTapCount() const;
//
//private:
//    unsigned int _tapCount;
//    
//};


} // namespace ofx
