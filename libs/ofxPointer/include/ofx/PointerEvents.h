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
#include "ofRectangle.h"


namespace ofx {


/// \brief A base class describing the basic components of event arguments.
class EventArgs: public ofEventArgs
{
public:
    /// \brief Create a default EventArgs.
    EventArgs();

    /// \brief Create a BaseEventArgs with the given paramaters.
    /// \param eventSource The source of the event.
    /// \param eventType A string describing the type of the event.
    /// \param timestampMillis The timestamp of the event.
    EventArgs(const void* eventSource,
              const std::string& eventType,
              uint64_t timestampMillis);

    /// \brief Destroy the EventArgs.
    virtual ~EventArgs();

    /// \returns the event type.
    std::string eventType() const;

    /// \returns the timestamp of this event in milliseconds.
    uint64_t timestampMillis() const;

    /// \returns the source of the event if available.
    const void* eventSource() const;

    /// \brief An unknown event type.
    static const std::string EVENT_TYPE_UNKNOWN;

private:
    /// \brief A pointer to the event source.
    const void* _eventSource = nullptr;

    /// \brief The name of this event type.
    std::string _eventType;

    /// \brief The timestamp of this event in milliseconds.
    uint64_t _timestampMillis = 0;

};


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
    /// \param ellipseAngleDeg Ellipse angle in degrees.
    PointShape(float width,
               float height,
               float ellipseMajorAxis = 0,
               float ellipseMinorAxis = 0,
               float ellipseAngleDeg = 0);

    /// \brief Destroy the PointShape.
    virtual ~PointShape();

    /// \brief Get the width of the PointShape.
    ///
    /// When an ellipse is defined, this represents the width of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the PointShape width.
    float width() const;

    /// \brief Get the height of the PointShape.
    ///
    /// When an ellipse is defined, this represents the height of the ellipse's
    /// axis-aligned bounding box.
    ///
    /// \returns the PointShape height.
    float height() const;

    /// \brief Get the angle of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the PointShape's ellipse angle in degrees.
    float ellipseAngleDeg() const;

    /// \brief Get the angle of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the PointShape's ellipse angle in radians.
    float ellipseAngleRad() const;

    OF_DEPRECATED_MSG("Use elipseAngleDeg() or ellipseAngleRad().", float ellipseAngle() const);

    /// \brief Get the major axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the PointShape's ellipse major axis.
    float ellipseMajorAxis() const;

    /// \brief Get the minor axis of the PointShape ellipse.
    ///
    /// Some touch pointers may define the elliptical shape and angle of a
    /// contact point.
    ///
    /// \returns the PointShape's ellipse minor axis.
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
    float _ellipseAngleDeg = 0;

};


/// \brief A class representing a pointer's point.
///
/// Captures all position, shape, tilt rotation and pressure information.
class Point
{
public:
    /// \brief Construct a Point
    Point();

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    Point(const glm::vec2& position);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param shape The point shape.
    Point(const glm::vec2& position, const PointShape& shape);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param pressure The normalized pressure.
    /// \param tiltX The tilt X angle.
    /// \param tiltY The tilt Y angle.
    Point(const glm::vec2& position, float pressure, float tiltX, float tiltY);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param shape The point shape.
    /// \param pressure The normalized pressure.
    Point(const glm::vec2& position, const PointShape& shape, float pressure);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param absolutePosition The absolute position in device coordinates.
    /// \param shape The point shape.
    /// \param pressure The normalized pressure.
    /// \param tangentialPressure The tangential pressure (aka barrel pressure).
    /// \param rotation The rotation.
    /// \param tiltX The tilt X angle.
    /// \param tiltY The tilt Y angle.
    Point(const glm::vec2& position,
          const glm::vec2& absolutePosition,
          const PointShape& shape,
          float pressure,
          float tangentialPressure,
          float rotation,
          float tiltX,
          float tiltY);

    /// \brief Destroy the Point.
    virtual ~Point();

    /// \returns the position in screen coordinates.
    glm::vec2 position() const;

    /// \brief Get the position in absolute device coordinates.
    ///
    /// Absolute position is returned in absolute device coordinates, which may
    /// be defined at a resolution that differs from the screen position.
    ///
    /// For devices that do not differentiate between screen and absolute
    /// positions, the value is equal to the screen position.
    ///
    /// \returns the absolute position in device coordinates.
    glm::vec2 absolutePosition() const;

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
    /// \brief The position in screen coordinates.
    glm::vec2 _position;

    /// \brief The Point's absolute position in device coordinates.
    glm::vec2 _absolutePosition;

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
///
/// PointerEventArgs are usually passed as arguments in the openFrameworks event
/// system, for example, POINTER_UP events might be dispatched to an event like:
///
///     ofEvent<PointerEventArgs> onPointerUp;
class PointerEventArgs: public EventArgs
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
    /// \param eventType The event type.
    /// \param e The event to copy.
    PointerEventArgs(const std::string& eventType,
                     const PointerEventArgs& e);

    /// \brief Create a PointerEventArgs with parameters.
    /// \param eventSource The event source if available.
    /// \param eventType The pointer event type.
    /// \param timestampMillis The timestamp of this event in milliseconds
    /// \param point The point.
    /// \param deviceId The unique input device id.
    /// \param pointerIndex The unique pointer index for the given device id.
    /// \param deviceType The device type string.
    /// \param canHover True if the device type can hover.
    /// \param isPrimary True if this pointer is the primary pointer.
    /// \param button The button id for this event.
    /// \param buttons All pressed buttons for this pointer.
    /// \param modifiers All modifiers for this pointer.
    PointerEventArgs(const void* eventSource,
                     const std::string& eventType,
                     uint64_t timestampMillis,
                     const Point& point,
                     std::size_t deviceId,
                     int64_t pointerIndex,
                     const std::string& deviceType,
                     bool canHover,
                     bool isPrimary,
                     uint64_t button,
                     uint64_t buttons,
                     uint64_t modifiers);

    /// \brief Destroy the pointer event args.
    virtual ~PointerEventArgs();

    /// \returns the Point data associated with this event.
    Point point() const;

    /// \brief Get the position of the event in screen coordinates.
    ///
    /// A convenience method equivalent to point().position();
    ///
    /// \returns the position in screen coordinates.
    glm::vec2 position() const;

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

    /// \return a unique event key.
    PointerEventKey eventKey() const;

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

    /// \brief Utility to convert ofTouchEventArgs events to PointerEventArgs.
    /// \param source The event source.
    /// \param e The touch event to convert.
    /// \returns a PointerEventArgs.
    static PointerEventArgs toPointerEventArgs(const void* source,
                                               const ofTouchEventArgs& e);

    /// \brief Utility to convert ofTouchEventArgs events to PointerEventArgs.
    /// \param e The touch event to convert.
    /// \param source The event source.
    /// \returns a PointerEventArgs.
    static PointerEventArgs toPointerEventArgs(const void* source,
                                               const ofMouseEventArgs& e);

    /// \brief A debug utility for viewing the contents of PointerEventArgs.
    /// \returns A string representation of the PointerEventArgs.
    std::string toString() const
    {
        std::stringstream ss;

        ss << "------------" << std::endl;
        ss << "     Source: " << eventSource() << std::endl;
        ss << "      Event: " << eventType() << std::endl;
        ss << "  Timestamp: " << timestampMillis() << std::endl;
        ss << "         Id: " << id() << std::endl;
        ss << "  Device Id: " << deviceId() << std::endl;
        ss << "Device Type: " << deviceType() << std::endl;
        ss << "     Button: " << button() << std::endl;
        ss << "    Buttons: " << ofToBinary(buttons()) << std::endl;
        ss << "  Modifiers: " << ofToBinary(modifiers()) << std::endl;
        ss << "Touch Index: " << index() << std::endl;

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

    friend std::ostream& operator << (std::ostream& os, const PointerEventArgs& e);

private:
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

    friend class PointerEvents;

};


/// \brief Write a PointerEventArgs to a std::ostream.
/// \param os The std::ostream to write to.
/// \param e The event to write.
/// \returns a reference to the provided std::ostream.
inline std::ostream& operator << (std::ostream& os, const PointerEventArgs& e)
{
    os << e.toString();
    return os;
}


/// \brief A set of pointers of a certain event type with unique event keys.
class PointerEventSet
{
public:
    PointerEventSet();

    /// \brief Create a PointerEventSet
    PointerEventSet(const std::string& pointerEventType);

    /// \brief Destroy the PointerEventSet.
    virtual ~PointerEventSet();

    /// \returns the pointer event type.
    std::string pointerEventType() const;

    /// \returns the first timestamp in the set in milliseconds.
    uint64_t firstTimestampMillis() const;

    /// \returns the last timestamp in the set in milliseconds.
    uint64_t lastTimestampMillis() const;

    /// \returns lastTimestampMillis() - firstTimestampMillis().
    uint64_t deltaTimeMillis() const;

    /// \returns the centroid of the set.
    glm::vec2 centroid() const;

    /// \returns the bounding box of the set.
    ofRectangle boundingBox() const;

    /// \returns the size of the set.
    std::size_t size() const;

    /// \returns true if the size == 0.
    std::size_t empty() const;

    /// \brief Clear all items in the set.
    void clear();

    /// \brief Determine fi the PointerEventSet has the given pointer key.
    /// \param pointerEvent The pointer key to test.
    /// \returns true if the set already has the pointerEvent.eventKey().
    bool hasEventKey(const PointerEventArgs& pointerEvent);

    /// \brief Add a pointer event to the set.
    ///
    /// Will add a pointer event to the set if its eventType matches the
    /// this set's event type and the set does not already contain the
    /// eventKey().
    ///
    /// \param pointerEvent The pointer event to add.
    /// \returns true if the pointer was added successfully, false otherwise.
    bool add(const PointerEventArgs& pointerEvent);

    /// \returns the pointer events comprising this group.
    std::vector<PointerEventArgs> pointerEvents() const;

private:
    /// \brief Update cached values.
    void _updateCache() const;

    /// \brief The pointer event type required for this set.
    std::string _pointerEventType;

    /// \brief The set of pointer events ordered by
    std::vector<PointerEventArgs> _pointerEvents;

    /// \brief True if the cache variables need updating.
    mutable bool _cacheNeedsUpdate = true;

    /// \brief The cached first timestamp in milliseconds.
    mutable uint64_t _cachedFirstTimestampMillis = 0;

    /// \brief The cached last timestamp in milliseconds.
    mutable uint64_t _cachedLastTimestampMillis = 0;

    /// \brief The cached centroid value.
    mutable glm::vec2 _cachedCentroid;

    /// \brief The cached bounding box value.
    mutable ofRectangle _cachedBoundingBox;

};


/// \brief A class for converting touch and mouse events into pointer events.
///
/// This class is a source of pointer events.  It captures mouse and touch
/// events from openFrameworks and repackages and distributes them as pointer
/// events.
///
/// This should not be accessed directly.
class PointerEvents
{
public:
    /// \brief Create a PointerEvents object with the given source.
    /// \param source The window that will provide the events.
    PointerEvents(ofAppBaseWindow* window);

    /// \brief Destroy the PointerEvents.
    ~PointerEvents();

    /// \brief Mouse event callback.
    /// \param source The event source.
    /// \param e the event arguments.
    /// \returns true of the event was consumed.
    bool mouseEvent(const void* source, ofMouseEventArgs& e);  

    /// \brief Touch event callback.
    /// \param source The event source.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool touchEvent(const void* source, ofTouchEventArgs& e);

    /// \brief Disable legacy mouse / touch events.
    ///
    /// If legacy mouse / touch events are disabled, they will be automatically
    /// consumed if not already consumed by another callback.
    ///
    /// For legacy addons and other legacy user interface code, this should not
    /// users should think carefully about disabling legacy events.
    ///
    /// Alternatively users that wish to use PointerEvents should simply not
    /// register listeners for mouse or touch events.
    void disableLegacyEvents();

    /// \brief Enable legacy mouse / touch events.
    ///
    /// If legacy mouse / touch events are enabled, event propagation will not
    /// artificially halted. If a consumer handles the event manually it will
    /// not be propagated.
    void enableLegacyEvents();

    /// \brief Register a pointer event listener.
    ///
    /// Event listeners registered via this function must have the following
    /// ofEvent callbacks defined:
    ///
    ///     `void pointerDown(PointerEventArgs& evt)`
    ///     `void pointerUp(PointerEventArgs& evt)`
    ///     `void pointerMove(PointerEventArgs& evt)`
    ///     `void pointerCancel(PointerEventArgs& evt)`
    ///
    /// Other method signatures event signatures are also supported.
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
    ///     `void pointerDown(PointerEventArgs& evt)`
    ///     `void pointerUp(PointerEventArgs& evt)`
    ///     `void pointerMove(PointerEventArgs& evt)`
    ///     `void pointerCancel(PointerEventArgs& evt)`
    ///
    /// Other method signatures event signatures are also supported.
    ///
    /// \tparam ListenerClass The class of the listener.
    /// \param listener A pointer to the listener class.
    /// \param prio The event priority.
    template <class ListenerClass>
    void unregisterPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Event that is triggered for any pointer event.
    ///
    /// All specific events below are triggered for matching events types if the
    /// event was not handled by an pointerEvent listener.
    ofEvent<PointerEventArgs> pointerEvent;

    /// \brief Event that is triggered when a point is introduced.
    ///
    /// Triggered after pointerEvent, if pointerEvent is not consumed.
    ofEvent<PointerEventArgs> pointerDown;

    /// \brief Event that is triggered when a point is removed.
    ///
    /// Triggered after pointerEvent, if pointerEvent is not consumed.
    ofEvent<PointerEventArgs> pointerUp;

    /// \brief Event that is triggered when a point moves.
    ///
    /// Triggered after pointerEvent, if pointerEvent is not consumed.
    ofEvent<PointerEventArgs> pointerMove;

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
    ofEvent<PointerEventArgs> pointerCancel;

protected:
    /// \brief Dispatch the pointer events.
    /// \param source The event source.
    /// \param e the event arguments.
    /// \returns true of the event was handled.
    bool _dispatchPointerEvent(const void* source, PointerEventArgs& e);

    /// \brief True if the PointerEvents should consume mouse / touch events.
    bool _consumeLegacyEvents = false;

#if !defined(TARGET_OF_IOS) && !defined(TARGET_ANDROID)
    /// \brief Mouse moved event listener.
    ofEventListener _mouseMovedListener;

    /// \brief Mouse dragged event listener.
    ofEventListener _mouseDraggedListener;

    /// \brief Mouse pressed event listener.
    ofEventListener _mousePressedListener;

    /// \brief Mouse released event listener.
    ofEventListener _mouseReleasedListener;

    /// \brief Mouse scrolled event listener.
    ofEventListener _mouseScrolledListener;

    /// \brief Mouse entered the source window event listener.
    ofEventListener _mouseEnteredListener;

    /// \brief Mouse exited the source window event listener.
    ofEventListener _mouseExitedListener;
#endif

    /// \brief Touch downevent listener.
    ofEventListener _touchDownListener;

    /// \brief Touch up event listener.
    ofEventListener _touchUpListener;

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
    ofAddListener(pointerDown, listener, &ListenerClass::pointerDown, prio);
    ofAddListener(pointerUp, listener, &ListenerClass::pointerUp, prio);
    ofAddListener(pointerMove, listener, &ListenerClass::pointerMove, prio);
    ofAddListener(pointerCancel, listener, &ListenerClass::pointerCancel, prio);
}


template <class ListenerClass>
void PointerEvents::unregisterPointerEvents(ListenerClass* listener, int prio)
{
    ofRemoveListener(pointerDown, listener, &ListenerClass::pointerDown, prio);
    ofRemoveListener(pointerUp, listener, &ListenerClass::pointerUp, prio);
    ofRemoveListener(pointerMove, listener, &ListenerClass::pointerMove, prio);
    ofRemoveListener(pointerCancel, listener, &ListenerClass::pointerCancel, prio);
}


/// \brief Manages PointerEvents objects based on their ofAppBaseWindow source.
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
    RegisterPointerEventsForWindow<ListenerClass>(nullptr, listener, prio);
}


template <class ListenerClass>
void UnregisterPointerEvents(ListenerClass* listener)
{
    UnregisterPointerEventsForWindow<ListenerClass>(nullptr, listener);
}


template <class ListenerClass>
void RegisterPointerEventForWindow(ofAppBaseWindow* window, ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    PointerEvents* events = PointerEventsManager::instance().eventsForWindow(window);

    if (events)
    {
        ofAddListener(events->pointerEvent, listener, &ListenerClass::pointerEvent, prio);
    }
    else
    {
        ofLogError("RegisterPointerEventForWindow") << "No PointerEvents available for given window.";
    }
}


template <class ListenerClass>
void UnregisterPointerEventForWindow(ofAppBaseWindow* window, ListenerClass* listener)
{
    PointerEvents* events = PointerEventsManager::instance().eventsForWindow(window);

    if (events)
    {
        ofRemoveListener(events->pointerEvent, listener, &ListenerClass::pointerEvent);
    }
    else
    {
        ofLogError("UnregisterPointerEventForWindow") << "No PointerEvents available for given window.";
    }
}



template <class ListenerClass>
void RegisterPointerEvent(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    RegisterPointerEventForWindow<ListenerClass>(nullptr, listener, prio);
}


template <class ListenerClass>
void UnregisterPointerEvent(ListenerClass* listener)
{
    UnregisterPointerEventForWindow<ListenerClass>(nullptr, listener);
}



class PointerDebugUtilities
{
public:
    static void draw(const PointerEventArgs& evt, float alpha = 1.0f);

//    static std::string toString(PointerEventArgs& evt);

};





} // namespace ofx


/// \brief A hash function for combining std::hash<> values.
/// \param seed The hash to append to.
/// \param v The value to append.
/// \tparam T The class to hash. Must be compatible with std::hash<>.
template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}


//namespace ns
//{
//    PointShape
//    Point
//    PointerEventArgs
//
//    void to_json(json& j, const person& p) {
//        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
//    }
//
//    void from_json(const json& j, person& p) {
//        p.name = j.at("name").get<std::string>();
//        p.address = j.at("address").get<std::string>();
//        p.age = j.at("age").get<int>();
//    }
//} // namespace ns
