//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <set>
#include <string>
#include "ofEvents.h"
#include "ofUtils.h"
#include "ofAppBaseWindow.h"


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
    float width() const;

    /// \brief Get the height of the PointShape.
    ///
    /// When an ellipse is defined, this represents the height of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the Point height.
    float height() const;

    /// \brief Get the angle of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse angle in degrees.
    float ellipseAngle() const;

    /// \brief Get the major axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse major axis.
    float ellipseMajorAxis() const;

    /// \brief Get the minor axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the Point's ellipse minor axis.
    float ellipseMinorAxis() const;

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


/// \brief A class representing a pointer's point.
///
/// Captures all relevant position, tilt rotation and presssure information.
class Point: public glm::vec3
{
public:
    /// \brief Construct a Point
    Point();

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    Point(const glm::vec3& position);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param shape The point shape.
    Point(const glm::vec3& position, const PointShape& shape);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param pressure The normalized pressure.
    /// \param tiltX The tilt X angle.
    /// \param tiltY The tilt Y angle.
    Point(const glm::vec3& position, float pressure, float tiltX, float tiltY);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param shape The point shape.
    /// \param pressure The normalized pressure.
    Point(const glm::vec3& position, const PointShape& shape, float pressure);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param absolutePosition The absolute position in device coordinates.
    /// \param shape The point shape.
    /// \param pressure The normalized pressure.
    /// \param tangentialPressure The tangential pressure (aka barrel pressure).
    /// \param rotation The rotation.
    /// \param tiltX The tilt X angle.
    /// \param tiltY The tilt Y angle.
    Point(const glm::vec3& position,
          const glm::vec3& absolutePosition,
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
    /// Point extends glm::vec3, providing position relative to the origin of the
    /// screen coordinate system.  Absolute position is returned in absolute
    /// device coordinates, which may be defined at a resolution that differs
    /// from the screen position.
    ///
    /// For devices that do not differentiate between screen and absolute
    /// positions, the value is equal to the screen position.
    ///
    /// \returns the absolute position in device coordinates.
    const glm::vec3& absolutePosition() const;

    /// \brief Get the normalized point pressure.
    ///
    /// The normalized pressure is in the range [0, 1].  For devices that do not
    /// support pressure, the value is 0.5 when a button is active or 0
    /// otherwise.
    ///
    /// \returns the normalized point pressure [0, 1].
    float pressure() const;

    /// \brief Get the Point's normalized tangential pressure.
    ///
    /// The normalized tangential pressure (aka the barrel pressure) is in the
    /// range [0, 1].  For devices that do not support tangential pressure, the
    /// value is 0.
    ///
    /// \returns the normalized tangential pressure [0, 1].
    float tangentialPressure() const;

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
    float rotation() const;

    /// \brief Get the Tilt X angle.
    ///
    /// Tilt X is given in degrees [-90, 90] between the Y-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the Y axis.  A
    /// positive tilt X is to the right.  The value is 0 if the tilt X is
    /// undefined.
    ///
    /// \returns the Tilt X angle in degrees.
    float tiltX() const;

    /// \brief Get the Tilt Y angle.
    ///
    /// Tilt Y is given in degrees [-90, 90] between the X-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the X axis.  A
    /// positive tilt Y is toward the user.  The value is 0 if the tilt Y is
    /// undefined.
    ///
    /// \returns the Tilt Y angle in degrees.
    float tiltY() const;

    /// \brief Get the shape of the Point.
    /// \returns The PointShape.
    const PointShape& shape() const;

private:
    /// \brief The Point's absolute position in device coordinates.
    glm::vec3 _absolutePosition;

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


/// \brief A class representing all of the arguments in a pointer event.
class PointerEventArgs
{
public:
    /// \brief A typedef defining a key for a pointer.
    ///
    /// Where first is the event id, and second is the event button. Create a
    /// new key like this:
    ///
    ///     PointerEventKey key(e.id(), e.button());
    ///
    typedef std::pair<int32_t, uint64_t> PointerEventKey;

    /// \brief Create a default PointerEventArgs.
    PointerEventArgs();

    /// \brief Create a PointerEventArgs with a new event type.
    PointerEventArgs(const std::string& type,
                     const PointerEventArgs& e);

    /// \brief Create a PointerEventArgs with arguments.
    PointerEventArgs(const std::string& type,
                     const Point& point,
                     std::size_t deviceId,
                     int64_t pointerIndex,
                     const std::string& deviceType,
                     bool canHover,
                     bool isPrimary,
                     uint64_t button,
                     uint64_t buttons,
                     uint64_t modifiers,
                     uint64_t tapCount, // deprecated
                     uint64_t timestamp,
                     ofAppBaseWindow* source);

    /// \brief Destroy the pointer event args.
    virtual ~PointerEventArgs();

    /// \returns the pointer event type.
    std::string eventType() const;

    /// \returns the Point data associated with this event.
    Point point() const;

    /// \brief Get the unique input device id.
    /// \returns the unique input device id.
    int64_t deviceId() const;

    /// \brief Get the unique pointer index for the given device id.
    ///
    /// This ID should correspend to different touches for a multi-touch device.
    ///
    /// \returns the unique pointer index for the given device id.
    int64_t index() const;

    /// \brief Get a single unique id for a device id and Pointer index.
    /// \returns a single unique id for a device id and Pointer index.
    std::size_t id() const;

    /// \brief Get the device type string.
    ///
    /// This string may be TYPE_MOUSE, TYPE_TOUCH, TYPE_PEN, or a custom string.
    ///
    /// \returns a device description string.
    std::string deviceType() const;

    /// \returns true if the device type can hover.
    bool canHover() const;

    /// \brief Determine if this pointer is the primary pointer.
    /// \returns true if this pointer is the primary pointer.
    /// \sa https://w3c.github.io/pointerevents/#the-primary-pointer
    bool isPrimary() const;

    /// \brief Get the button id for this event.
    /// \returns the button id for this event.
    uint64_t button() const;

    /// \brief Get all pressed buttons for this pointer.
    /// \return all pressed buttons for this pointer.
    /// \sa https://w3c.github.io/pointerevents/#button-states
    uint64_t buttons() const;

    /// \brief Get all modifiers for this pointer.
    /// \returns all modifiers for this pointer.
    uint64_t modifiers() const;

    /// \brief Get the number of presses, clicks or taps associated with this event.
    ///
    /// This is not part of the official Pointer Events specification, but is
    /// useful enough to be included here.
    ///
    /// \returns the tap count when the event is of type POINTER_DOWN or POINTER_UP.
    OF_DEPRECATED_MSG("Use ofx::TapGesture.", uint64_t tapCount() const);

    /// \returns the timestamp of this event.
    uint64_t timestamp() const;

    /// \returns the event source if available.
    const ofAppBaseWindow* source() const;

    /// \brief Utility to convert ofTouchEventArgs events to PointerEventArgs.
    /// \param e The touch event to convert.
    /// \param source The event source.
    /// \returns a PointerEventArgs.
    static PointerEventArgs toPointerEventArgs(const ofTouchEventArgs& e,
                                               ofAppBaseWindow* source);

    /// \brief Utility to convert ofTouchEventArgs events to PointerEventArgs.
    /// \param e The touch event to convert.
    /// \param source The event source.
    /// \returns a PointerEventArgs.
    static PointerEventArgs toPointerEventArgs(const ofMouseEventArgs& e,
                                               ofAppBaseWindow* source);

    /// \brief A debug utility for viewing the contents of PointerEventArgs.
    /// \returns A string representation of the PointerEventArgs.
    std::string toString() const
    {
        std::stringstream ss;

        ss << "------------" << std::endl;
        ss << "      Event: " << eventType() << std::endl;
        ss << "  Timestamp: " << timestamp() << std::endl;
        ss << "         Id: " << id() << std::endl;
        ss << "  Device Id: " << deviceId() << std::endl;
        ss << "Device Type: " << deviceType() << std::endl;
        ss << "     Button: " << button() << std::endl;
        ss << "    Buttons: " << ofToBinary(buttons()) << std::endl;
        ss << "  Modifiers: " << ofToBinary(modifiers()) << std::endl;
        ss << "Touch Index: " << index() << std::endl;
        ss << "     Source: " << source() << std::endl;

        return ss.str();
    }

    /// \brief The mouse pointer type.
    static const std::string TYPE_MOUSE;

    /// \brief The pen pointer type.
    static const std::string TYPE_PEN;

    /// \brief The touch pointer type.
    static const std::string TYPE_TOUCH;

    /// \brief The unknown pointer type.
    static const std::string TYPE_UNKNOWN;

    /// \brief The pointer over event type.
    static const std::string POINTER_OVER;

    /// \brief The pointer enter event type.
    static const std::string POINTER_ENTER;

    /// \brief The pointer down event type.
    static const std::string POINTER_DOWN;

    /// \brief The pointer move event type.
    static const std::string POINTER_MOVE;

    /// \brief The pointer up event type.
    static const std::string POINTER_UP;

    /// \brief The pointer cancel event type.
    static const std::string POINTER_CANCEL;

    /// \brief The pointer out event type.
    static const std::string POINTER_OUT;

    /// \brief The pointer leave event type.
    static const std::string POINTER_LEAVE;

    /// \brief The pointer scroll type.
    /// \todo This is not part of the PointerEvents spec.
    ///       It should be an extension of a mouse event.
    static const std::string POINTER_SCROLL;

    /// \brief The got pointer capture event type.
    static const std::string GOT_POINTER_CAPTURE;

    /// \brief The lost pointer capture event type.
    static const std::string LOST_POINTER_CAPTURE;

private:
    /// \brief The name of this event type.
    std::string _eventType = POINTER_MOVE;

    /// \brief The location and orientation of the pointer.
    Point _point;

    /// \brief The unique id of this pointer.
    std::size_t _id = 0;

    /// \brief The id of the device producing the pointer events.
    int64_t _deviceId = -1;

    /// \brief A unique pointer ID.
    ///
    /// This value must be unique from all other active pointers at any given
    /// time. Pointer IDs can be reused and are implementation specific.
    int64_t _pointerIndex = -1;

    /// \brief The type of device that generated this Point.
    std::string _deviceType = TYPE_UNKNOWN;

    /// \brief True if the device type can hover.
    ///
    /// False for touch screens, true for mouse and most pen devices.
    bool _canHover = false;

    /// \brief Indicates if the pointer is a primary pointer.
    ///
    /// In a multi-pointer (e.g. multi-touch) scenario, the isPrimary property
    /// is used to identify a master pointer amongst the set of active pointers
    /// for each pointer type. Only a primary pointer will produce compatibility
    /// mouse events. Authors who desire single-pointer interaction can achieve
    /// this by ignoring non-primary pointers.
    ///
    /// \sa http://www.w3.org/TR/pointerevents/#the-primary-pointer
    bool _isPrimary = false;

    /// \brief The current button associated with this event.
    uint64_t _button = 0;

    /// \brief The current buttons being pressed.
    uint64_t _buttons = 0;

    /// \brief The current modifiers being pressed.
    uint64_t _modifiers = 0;

    /// \brief The current number of taps associated with this event.
    /// \deprecated
    uint64_t _tapCount = 0;

    /// \brief The timestamp of this event.
    uint64_t _timestamp = 0;

    /// \brief The event source.
    ofAppBaseWindow* _source = nullptr;

    friend class PointerEvents;

};


/// \brief A class for converting touch and mouse events into pointer events.
///
/// This class is a source of pointer events.  It captures mouse and touch
/// events and repackages and distributes them as pointer events.
class PointerEvents
{
public:
    /// \brief Create a default PointerEvents object.
    PointerEvents();

    /// \brief Create a PointerEvents object with the given source.
    PointerEvents(ofAppBaseWindow* source);

    /// \brief Destroy the PointerEvents.
    ~PointerEvents();

    /// \brief Mouse moved callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool mouseMoved(const void* source, ofMouseEventArgs& e);

    /// \brief Mouse dragged callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool mouseDragged(const void* source, ofMouseEventArgs& e);

    /// \brief Mouse pressed callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool mousePressed(const void* source, ofMouseEventArgs& e);

    /// \brief Mouse released callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool mouseReleased(const void* source, ofMouseEventArgs& e);

    /// \brief Touch down callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool touchDown(const void* source, ofTouchEventArgs& e);

    /// \brief Touch moved callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool touchMoved(const void* source, ofTouchEventArgs& e);

    /// \brief Touch up callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool touchUp(const void* source, ofTouchEventArgs& e);

    /// \brief Touch double tap callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool touchDoubleTap(const void* source, ofTouchEventArgs& e);

    /// \brief Touch cancelled callback.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool touchCancelled(const void* source, ofTouchEventArgs& e);

    /// \brief Set the PointerEvents instance to consume mouse events.
    ///
    /// If mouse events are consumed, they will not be futher propagated.
    ///
    /// \param consumeMouseEvents true if events should be consumed.
    void setConsumeMouseEvents(bool consumeMouseEvents);

    /// \brief Set the PointerEvents instance to consume touch events.
    ///
    /// If touch events are consumed, they will not be futher propagated.
    ///
    /// \param consumeTouchEvents true if events should be consumed.
    void setConsumeTouchEvents(bool consumeTouchEvents);

    /// \brief Register a pointer event listener.
    ///
    /// Event listeners registered via this function must have the following
    /// ofEvent callbacks defined:
    ///
    ///     `onPointerDown(...)`
    ///     `onPointerUp(...)`
    ///     `onPointerMove(...)`
    ///     `onPointerCancel(...)`
    ///
    /// \tparam ListenerClass The class of the listener.
    /// \param listener A pointer to the listener class.
    /// \param prio The event priority.
    template <class ListenerClass>
    void registerPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Unregister a pointer event listener.
    ///
    /// Event listeners unregistered via this function must have the following
    /// ofEvent callbacks defined:
    ///
    ///     `onPointerDown(...)`
    ///     `onPointerUp(...)`
    ///     `onPointerMove(...)`
    ///     `onPointerCancel(...)`
    ///
    /// \tparam ListenerClass The class of the listener.
    /// \param listener A pointer to the listener class.
    /// \param prio The event priority.
    template <class ListenerClass>
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

    /// \brief Get the singleton instance of the PointerEvents.
    /// \returns an instance of PointerEvents attached global event context.
    static PointerEvents& instance();

protected:
    /// \brief A typedef defining a pointer down event map.
    typedef std::map<PointerEventArgs::PointerEventKey, PointerEventArgs> PointerDownTimeMap;

    /// \brief Update POINTER_DOWN or POINTER_UP event tap counts.
    /// \param e The event data.
    /// \deprecated
    void updateTapCount(PointerEventArgs& e);

    /// \brief True iff the PointerEvents should consume mouse events.
    bool _consumeMouseEvents = false;

    /// \brief True iff the PointerEvents should consume touch events.
    bool _consumeTouchEvents = false;

    /// \brief The Pointer down event times.
    ///
    /// These are used to keep track of multiple taps since the oF event system
    /// does not currently keep track of tap count.
    PointerDownTimeMap _pointerDownEventTimeMap;

#if !defined(TARGET_OF_IOS) && !defined(TARGET_ANDROID)
    /// \brief Mouse moved event listener.
    ofEventListener _mouseMovedListener;

    /// \brief Mouse dragged event listener.
    ofEventListener _mouseDraggedListener;

    /// \brief Mouse pressed event listener.
    ofEventListener _mousePressedListener;

    /// \brief Mouse released event listener.
    ofEventListener _mouseReleasedListener;
#endif

    /// \brief Touch up event listener.
    ofEventListener _touchUpListener;

    /// \brief Touch downevent listener.
    ofEventListener _touchDownListener;

    /// \brief Touch moved event listener.
    ofEventListener _touchMovedListener;

    /// \brief Touch double tap event listener.
    ofEventListener _touchDoubleTapListener;

    /// \brief Touch cancelled event listener.
    ofEventListener _touchCancelledListener;

    /// \brief The default source if the callback is missing.
    ofAppBaseWindow* _source = nullptr;

};


template <class ListenerClass>
void PointerEvents::registerPointerEvents(ListenerClass* listener, int prio)
{
    ofAddListener(onPointerDown, listener, &ListenerClass::onPointerDown, prio);
    ofAddListener(onPointerUp, listener, &ListenerClass::onPointerUp, prio);
    ofAddListener(onPointerMove, listener, &ListenerClass::onPointerMove, prio);
    ofAddListener(onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
}


template <class ListenerClass>
void PointerEvents::unregisterPointerEvents(ListenerClass* listener, int prio)
{
    ofRemoveListener(onPointerDown, listener, &ListenerClass::onPointerDown, prio);
    ofRemoveListener(onPointerUp, listener, &ListenerClass::onPointerUp, prio);
    ofRemoveListener(onPointerMove, listener, &ListenerClass::onPointerMove, prio);
    ofRemoveListener(onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
}


class PointerEventsManager
{
public:
    /// \returns a PointerEvents instance registered to listen to the global events or nullptr.
    PointerEvents* events();

    /// \returns a PointerEvents instance registered to listen to the given window or nullptr.
    PointerEvents* eventsForWindow(ofAppBaseWindow* window);

    /// \brief Get the singleton instance of the PointerEventsManager.
    /// \returns an instance of PointerEventsManager.
    static PointerEventsManager& instance();

private:
    /// \brief Create a default PointerEventsManager object.
    PointerEventsManager();

    /// \brief Destroy the PointerEventsManager.
    ~PointerEventsManager();

    /// \brief A map of windows to their pointer events.
    std::map<ofAppBaseWindow*, std::unique_ptr<PointerEvents>> _windowEventMap;

};


template <class ListenerClass>
void RegisterPointerEventsForWindow(ofAppBaseWindow* window, ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    PointerEvents* events = PointerEventsManager::instance().eventsForWindow(window);

    if (events)
    {
        events->registerPointerEvents(listener, prio);
    }
    else
    {
        ofLogError("RegisterPointerEventsForWindow") << "No PointerEvents available for given window.";
    }
}


template <class ListenerClass>
void UnregisterPointerEventsForWindow(ofAppBaseWindow* window, ListenerClass* listener)
{
    PointerEvents* events = PointerEventsManager::instance().eventsForWindow(window);

    if (events)
    {
        events->unregisterPointerEvents(listener);
    }
    else
    {
        ofLogError("UnregisterPointerEventsForWindow") << "No PointerEvents available for given window.";
    }
}


template <class ListenerClass>
void RegisterPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    RegisterPointerEventsForWindow(nullptr, listener, prio);
}


template <class ListenerClass>
void UnregisterPointerEvents(ListenerClass* listener)
{
    UnregisterPointerEventsForWindow(nullptr, listener);
}


} // namespace ofx


template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
