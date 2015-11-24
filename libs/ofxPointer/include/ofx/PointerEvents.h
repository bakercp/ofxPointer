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


#pragma once


#include <set>
#include <string>
#include "json/json.h"
#include "ofEvents.h"
#include "ofUtils.h"


namespace ofx {


/// \brief A PointShape describes the shape of a pointer.
///
/// For standard pointers, such as a mouse or a pen, the width and height of the
/// PointShape will be set to zero while some touch pointers may define the
/// size of the touch or even an ellipse describing the size and angle of a
/// finger tip.
///
/// When the ellipse is defined, the width and height should describe and axis-
/// aligned bounding box of the ellipse.
class PointShape
{
public:
    /// \brief Create a default PointShape.
    PointShape();

    /// \brief Create a PointShape with parameters.
	/// \param width Bounding box width.
	/// \param height Bounding box height.
	/// \param ellipseMajorAxis Ellipse major axis.
	/// \param ellipseMinorAxis Ellipse minor axis.
	/// \param ellipseAngle Ellipse angle in degrees.
    PointShape(float width,
               float height,
               float ellipseMajorAxis = 0,
               float ellipseMinorAxis = 0,
               float ellipseAngle = 0);

    /// \brief Destroy the PointShape.
    virtual ~PointShape();

    /// \brief Get the width of the PointShape.
    ///
    /// When an ellipse is defined, this represents the width of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the Point width.
    float getWidth() const;

    /// \brief Get the height of the PointShape.
    ///
    /// When an ellipse is defined, this represents the height of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the Point height.
    float getHeight() const;

    /// \brief Get the angle of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse angle in degrees.
    float getEllipseAngle() const;

    /// \brief Get the major axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse major axis.
    float getEllipseMajorAxis() const;

    /// \brief Get the minor axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse minor axis.
    float getEllipseMinorAxis() const;

    /// \brief Deserialize a PointShape from JSON.
    /// \param json The json to deserialize.
    /// \returns the deserized PointShape.
    static PointShape fromJSON(const Json::Value& json);

    /// \brief Serialize a PointShape as JSON.
    /// \param point the PointShape to serialize.
    /// \returns the PointShape as serialized JSON.
    static Json::Value toJSON(const PointShape& pointShape);

protected:
    /// \brief Bounding box width.
    float _width = 0;

    /// \brief Bounding box height.
    float _height = 0;

    /// \brief Ellipse major axis.
    float _ellipseMajorAxis = 0;

    /// \brief Ellipse minor axis.
    float _ellipseMinorAxis = 0;

    /// \brief Ellipse angle in degrees.
    float _ellipseAngle = 0;

};


class Point: public ofVec3f
{
public:
	/// \brief Construct a Point
	Point();

	/// \brief Construct a Point
	/// \param position The position in screen coordinates.
    Point(const ofVec3f& position);

	/// \brief Construct a Point
	/// \param position The position in screen coordinates.
	/// \param shape The point shape.
    Point(const ofVec3f& position, const PointShape& shape);

	/// \brief Construct a Point
	/// \param position The position in screen coordinates.
	/// \param pressure The normalized pressure.
	/// \param tiltX The tilt X angle.
	/// \param tiltY The tilt Y angle.
    Point(const ofVec3f& position, float pressure, float tiltX, float tiltY);

	/// \brief Construct a Point
	/// \param position The position in screen coordinates.
	/// \param absolutePosition The absolute position in device coordinates.
	/// \param shape The point shape.
	/// \param pressure The normalized pressure.
	/// \param tangentialPressure The tangential pressure (aka barrel pressure).
	/// \param rotation The rotation.
	/// \param tiltX The tilt X angle.
	/// \param tiltY The tilt Y angle.
    Point(const ofVec3f& position,
          const ofVec3f& absolutePosition,
          const PointShape& shape,
          float pressure,
          float tangentialPressure,
          float rotation,
          float tiltX,
          float tiltY);

    /// \brief Destroy the Point.
    virtual ~Point();

    /// \brief Get the position in absolute device coordinates.
    ///
    /// Point extends ofVec3f, providing position relative to the origin of the
    /// screen coordinate system.  Absolute position is returned in absolute
    /// device coordinates, which may be defined at a resolution that differs
    /// from the screen position.
    ///
    /// For devices that do not differentiate between screen and absolute
    /// positions, the value is equal to the screen position.
    ///
    /// \returns the absolute position in device coordinates.
    const ofVec3f& getAbsolutePosition() const;

    /// \brief Get the normalized point pressure.
    ///
    /// The normalized pressure is in the range [0, 1].  For devices that do not
    /// support pressure, the value is 0.5 when a button is active or 0
    /// otherwise.
    ///
    /// \returns the normalized point pressure [0, 1].
    float getPressure() const;

    /// \brief Get the Point's normalized tangential pressure.
    ///
    /// The normalized tangential pressure (aka the barrel pressure) is in the
    /// range [0, 1].  For devices that do not support tangential pressure, the
    /// value is 0.
    ///
    /// \returns the normalized tangential pressure [0, 1].
    float getTangentialPressure() const;

    /// \brief Get the Point's rotation in degrees.
    ///
    /// For tablets, the point's rotation is the angle between the "front" of
    /// the transducer (e.g. pen stylus) and the top of the tablet.  For devices
    /// that do not support rotation reporting, the value is 0.
    ///
    /// \note This rotation value similar to but independent of the ellipse
    /// angle value recorded by the PointShape.
    ///
    /// \returns the rotation in degrees.
    float getRotation() const;

    /// \brief Get the Tilt X angle.
    ///
    /// Tilt X is given in degrees [-90, 90] between the Y-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the Y axis.  A
    /// positive tilt X is to the right.  The value is 0 if the tilt X is
    /// undefined.
    ///
    /// \returns the Tilt X angle in degrees.
    float getTiltX() const;

    /// \brief Get the Tilt Y angle.
    ///
    /// Tilt Y is given in degrees [-90, 90] between the X-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the X axis.  A
    /// positive tilt Y is toward the user.  The value is 0 if the tilt Y is
    /// undefined.
    ///
    /// \returns the Tilt Y angle in degrees.
    float getTiltY() const;

    /// \brief Get the shape of the Point.
    /// \returns The PointShape.
    const PointShape& getShape() const;

    /// \brief Deserialize a Point from JSON.
    /// \param json The json to deserialize.
    /// \returns the deserized Point.
    static Point fromJSON(const Json::Value& json);

    /// \brief Serialize a Point as JSON.
    /// \param point the Point to serialize.
    /// \returns the Point as serialized JSON.
    static Json::Value toJSON(const Point& point);

private:
    /// \brief The Point's absolute position in device coordinates.
    ofVec3f _absolutePosition;

    /// \brief The Point shape.
    PointShape _shape;

    /// \brief The Point's normalized pressure.
    float _pressure = 0;

    /// \brief The Point's tangential pressure (aka barrel pressure).
    float _tangentialPressure = 0;

    /// \brief The Point's rotation.
    float _rotation = 0;

    /// \brief The Point tilt X angle.
    float _tiltX = 0;

    /// \brief The Point tilt Y angle.
    float _tiltY = 0;

};


class PointerEventArgs: public ofEventArgs
{
public:
    PointerEventArgs();

    PointerEventArgs(const std::string& type,
                     const Point& point,
                     long deviceId,
                     long pointerIndex,
                     const std::string& deviceType,
                     bool isPrimary,
                     unsigned long button,
                     unsigned long buttons,
                     unsigned long modifiers,
                     uint64_t tapCount,
                     uint64_t timestamp);

    virtual ~PointerEventArgs();

    std::string eventType() const;

    Point point() const;

    /// \brief Get the unique input device id.
    /// \returns the unique input device id.
    long deviceId() const;

    /// \brief Get the unique pointer index for the given device id.
    ///
    /// This ID should correspend to different touches for a multi-touch device.
    ///
    /// \returns the unique pointer index for the given device id.
    long index() const;

    /// \brief Get a single unique id for a device id and Pointer index.
    /// \returns a single unique id for a device id and Pointer index.
    std::size_t id() const;

    /// \brief Get the device type string.
    ///
    /// This string may be TYPE_MOUSE, TYPE_TOUCH, TYPE_PEN, or a custom string.
    ///
    /// \returns a device description string.
    std::string deviceType() const;

    /// \brief Determine if this pointer is the primary.
    /// \returns true if this pointer is the primary pointer.
    /// \sa https://w3c.github.io/pointerevents/#the-primary-pointer
    bool isPrimary() const;

    /// \brief Get the button id for this event.
    /// \returns the button id for this event.
    unsigned long button() const;

    /// \brief Get all pressed buttons for this pointer.
    /// \return all pressed buttons for this pointer.
    /// \sa https://w3c.github.io/pointerevents/#button-states
    unsigned long buttons() const;

    /// \brief Get all modifiers for this pointer.
    /// \returns all modifiers for this pointer.
    unsigned long modifiers() const;

    /// \returns the timestamp of this event.
    uint64_t timestamp() const;

    /// \returns the number of presses, clicks or taps associated with this pointer.
    uint64_t tapCount() const;

    static PointerEventArgs toPointerEventArgs(const ofTouchEventArgs& evt);
    static PointerEventArgs toPointerEventArgs(const ofMouseEventArgs& evt);

    std::string toString() const
    {
        std::stringstream ss;

        ss << "------------" << std::endl;
        ss << "      Event: " << eventType() << std::endl;
        ss << "         Id: " << id() << std::endl;
        ss << "  Device Id: " << deviceId() << std::endl;
        ss << "Device Type: " << deviceType() << std::endl;
        ss << "     Button: " << button() << std::endl;
        ss << "    Buttons: " << ofToBinary(buttons()) << std::endl;
        ss << "  Modifiers: " << ofToBinary(modifiers()) << std::endl;
        ss << "  Tap Count: " << tapCount() << std::endl;
        ss << "Touch Index: " << index() << std::endl;

        return ss.str();
    }

    static const std::string TYPE_MOUSE;
    static const std::string TYPE_PEN;
    static const std::string TYPE_TOUCH;
    static const std::string TYPE_UNKNOWN;

    static const std::string POINTER_OVER;
    static const std::string POINTER_ENTER;
    static const std::string POINTER_DOWN;
    static const std::string POINTER_MOVE;
    static const std::string POINTER_UP;
    static const std::string POINTER_CANCEL;
    static const std::string POINTER_OUT;
    static const std::string POINTER_LEAVE;

    /// \todo This is not part of the PointerEvents spec.
    /// Should be an extension of a mouse event.
    static const std::string POINTER_SCROLL;

    static const std::string GOT_POINTER_CAPTURE;
    static const std::string LOST_POINTER_CAPTURE;

    /// \brief Deserialize a PointerEventArgs from JSON.
    /// \param json The json to deserialize.
    /// \returns the deserized PointerEventArgs.
    static PointerEventArgs fromJSON(const Json::Value& json);

    /// \brief Serialize a PointerEventArgs as JSON.
    /// \param point the PointerEventArgs to serialize.
    /// \returns the PointerEventArgs as serialized JSON.
    static Json::Value toJSON(const PointerEventArgs& pointerEventArgs);

private:
    /// \brief The name of this event type.
    std::string _eventType;

    /// \brief The unique id of this pointer.
    std::size_t _id;

    /// \brief The id of the device producing the pointer events.
    long _deviceId;

    /// \brief A unique pointer ID.
    ///
    /// This value must be unique from all other active pointers at any given
    /// time.  Pointer IDs can be reused and are implementation specific.
    long _pointerIndex;

    /// \brief The type of device that generated this Point.
    std::string _deviceType;

    /// \brief The location and orientation of the pointer.
    Point _point;

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

	/// \brief The current button associated with this event.
    unsigned long _button;

	/// \brief The current buttons being pressed.
    unsigned long _buttons;

	/// \brief The current modifiers being pressed.
    unsigned long _modifiers;

	/// \brief The current number of taps associated with this event.
    uint64_t _tapCount;

	/// \brief The timestamp of this event.
    uint64_t _timestamp;

    friend class PointerEvents;

};


class PointerEvents
{
public:
    PointerEvents();
    virtual ~PointerEvents();

    bool mouseMoved(ofMouseEventArgs& e);
    bool mouseDragged(ofMouseEventArgs& e);
    bool mousePressed(ofMouseEventArgs& e);
    bool mouseReleased(ofMouseEventArgs& e);

    bool touchDown(ofTouchEventArgs& e);
    bool touchMoved(ofTouchEventArgs& e);
    bool touchUp(ofTouchEventArgs& e);
    bool touchDoubleTap(ofTouchEventArgs& e);
    bool touchCancelled(ofTouchEventArgs& e);

    void setConsumeMouseEvents(bool consumeMouseEvents);
    void setConsumeTouchEvents(bool consumeTouchEvents);

    template<class ListenerClass>
    void registerPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP);

    template<class ListenerClass>
    void unregisterPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Event that is triggered when a point is introduced.
    ofEvent<PointerEventArgs> onPointerDown;

    /// \brief Event that is triggered when a point is removed.
    ofEvent<PointerEventArgs> onPointerUp;

    /// \brief Event that is triggered when a point moves.
    ofEvent<PointerEventArgs> onPointerMove;

    ///  \brief Event when the system cancels a pointer event.
    ///
    /// This event occurs when the pointer (touch or pen contact) is removed
    /// from the system. Here are common reasons why this might happen:
    ///     - A touch contact is canceled by a pen coming into range of the
    ///     surface.
    ///     - The device doesn't report an active contact for more than 100ms.
    ///     - A mapping for a device's monitor changes while contacts are
    ///     active. For example, the user changes the position of a screen in a
    ///     two screen configuration.
    ///     - The desktop is locked or the user logged off.
    ///     - The number of simultaneous contacts exceeds the number that the
    ///     device can support. For example, if a device supports only two
    ///     contact points, if the user has two fingers on a surface, and then
    ///     touches it with a third finger, this event is raised.
    ofEvent<PointerEventArgs> onPointerCancel;

    /// \todo Remaining element-related methods don't apply to the same event
    /// structure because they depend on the target.

    static PointerEvents& instance()
    {
        static PointerEvents instance;
        return instance;
    }

protected:
    typedef std::pair<long, unsigned long> PointerPressEventKey;
    typedef std::map<PointerPressEventKey, PointerEventArgs> PointerPressEvents;

    /// \brief True iff the PointerEvents should consume mouse events.
    bool _consumeMouseEvents;

    /// \brief True iff the PointerEvents should consume touch events.
    bool _consumeTouchEvents;

    /// \brief A callback for multiple tap events.
    void handleMultiTap(PointerEventArgs& evt);

    /// \brief The Pointer down events.
    PointerPressEvents _pointerDownEvents;

};


template<class ListenerClass>
void PointerEvents::registerPointerEvents(ListenerClass* listener, int prio)
{
    ofAddListener(onPointerDown, listener, &ListenerClass::onPointerDown, prio);
    ofAddListener(onPointerUp, listener, &ListenerClass::onPointerUp, prio);
    ofAddListener(onPointerMove, listener, &ListenerClass::onPointerMove, prio);
    ofAddListener(onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
}


template<class ListenerClass>
void PointerEvents::unregisterPointerEvents(ListenerClass* listener, int prio)
{
    ofRemoveListener(onPointerDown, listener, &ListenerClass::onPointerDown, prio);
    ofRemoveListener(onPointerUp, listener, &ListenerClass::onPointerUp, prio);
    ofRemoveListener(onPointerMove, listener, &ListenerClass::onPointerMove, prio);
    ofRemoveListener(onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
}


template<class ListenerClass>
void RegisterPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    PointerEvents::instance().registerPointerEvents(listener, prio);
}


template<class ListenerClass>
void UnregisterPointerEvents(ListenerClass* listener)
{
    PointerEvents::instance().unregisterPointerEvents(listener);
}


} // namespace ofx


template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
