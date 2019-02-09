//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofConstants.h"


#if defined(TARGET_OF_IOS)


#include "ofx/PointerEventsiOS.h"
#include "ofx/PointerEvents.h"


using namespace ofx;


const int64_t POINTER_INDEX_UPDATE = std::numeric_limits<int64_t>::max();
const int64_t POINTER_INDEX_UNKNOWN = std::numeric_limits<int64_t>::lowest();


UITouchProperties toUITouchProperties(const std::set<std::string>& properties)
{
    UITouchProperties result = 0;

    for (const auto& property: properties)
    {
        if (property == PointerEventArgs::PROPERTY_PRESSURE)
            result &= UITouchPropertyForce;
        else if (property == PointerEventArgs::PROPERTY_TILT_X || property == PointerEventArgs::PROPERTY_TILT_Y)
            result &= (UITouchPropertyAzimuth & UITouchPropertyAltitude);
        else if (property == PointerEventArgs::PROPERTY_POSITION)
            result &= UITouchPropertyLocation;
        else
            ofLogWarning("toUITouchProperties") << "Unknown UITouchProperty: " << property;
    }

    return result;
}


std::set<std::string> toPopertySet(UITouchProperties properties)
{
    std::set<std::string> result;

    if (properties & UITouchPropertyForce)
        result.insert(PointerEventArgs::PROPERTY_PRESSURE);

    if (properties & UITouchPropertyAzimuth || properties & UITouchPropertyAltitude)
        result.insert({ PointerEventArgs::PROPERTY_TILT_X, PointerEventArgs::PROPERTY_TILT_Y });

    if (properties & UITouchPropertyLocation)
        result.insert(PointerEventArgs::PROPERTY_POSITION);

    return result;
}


bool dispatchPointerEvent(ofAppBaseWindow* window, PointerEventArgs& e)
{
//    std::cout << "dispatchPointerEvent: "  << source  << " window: " << window<< std::endl;

    bool consumed = false;

    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().eventsForWindow(window);

    if (events)
    {
        // All pointer events get dispatched via pointerEvent.
        consumed = ofNotifyEvent(events->pointerEvent, e, window);

        // If the pointer was not consumed, then send it along to the standard five.
        if (!consumed)
        {
            if (e.eventType() == PointerEventArgs::POINTER_DOWN)
            {
                consumed = ofNotifyEvent(events->pointerDown, e, window);
            }
            else if (e.eventType() == PointerEventArgs::POINTER_UP)
            {
                consumed = ofNotifyEvent(events->pointerUp, e, window);
            }
            else if (e.eventType() == PointerEventArgs::POINTER_MOVE)
            {
                consumed = ofNotifyEvent(events->pointerMove, e, window);
            }
            else if (e.eventType() == PointerEventArgs::POINTER_CANCEL)
            {
                consumed = ofNotifyEvent(events->pointerCancel, e, window);
            }
            else if (e.eventType() == PointerEventArgs::POINTER_UPDATE)
            {
                consumed = ofNotifyEvent(events->pointerUpdate, e, window);
            }
        }
    }
    else
    {
        ofLogError("PointerViewIOS::touchesEnded") << "Invalid event, passing.";
    }


    return /*events->consumeLegacyEvents ||*/ consumed;
}




@implementation PointerView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    self.multipleTouchEnabled = true;

    _activeTouches = [[NSMutableDictionary alloc] init];
    _window = ofxiOSGetOFWindow();

    return self;
}

- (void)dealloc
{
    [_activeTouches release];
    [super dealloc];
}


-(void) resetTouches
{
    [_activeTouches removeAllObjects];
}


- (void)willMoveToSuperview:(UIView *)newSuperview;
{
    [self resetTouches];
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();

    if (events)
    {
        for (UITouch* touch in touches)
        {
            auto evt = [self toPointerEventArgs:self
                                      withTouch:touch
                                      withEvent:event
                               withPointerIndex:POINTER_INDEX_UNKNOWN
                                  withPredicted:false];
            dispatchPointerEvent(_window, evt);
        }
    }
    else
    {
        ofLogError("PointerViewIOS::touchesBegan") << "Invalid event, passing.";
        [super touchesBegan:touches withEvent:event];
    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();

    if (events)
    {
        for (UITouch* touch in touches)
        {
            auto evt = [self toPointerEventArgs:self
                                      withTouch:touch
                                      withEvent:event
                               withPointerIndex:POINTER_INDEX_UNKNOWN
                                  withPredicted:false];
            dispatchPointerEvent(_window, evt);
        }
    }
    else
    {
        ofLogError("PointerViewIOS::touchesMoved") << "Invalid event, passing.";
        [super touchesMoved:touches withEvent:event];
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();

    if (events)
    {
        for (UITouch* touch in touches)
        {
            auto evt = [self toPointerEventArgs:self
                                      withTouch:touch
                                      withEvent:event
                               withPointerIndex:POINTER_INDEX_UNKNOWN
                                  withPredicted:false];
            dispatchPointerEvent(_window, evt);
        }
    }
    else
    {
        ofLogError("PointerViewIOS::touchesEnded") << "Invalid event, passing.";
        [super touchesEnded:touches withEvent:event];
    }
}


- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();

    if (events)
    {
        for (UITouch* touch in touches)
        {
            auto evt = [self toPointerEventArgs:self
                                      withTouch:touch
                                      withEvent:event
                               withPointerIndex:POINTER_INDEX_UNKNOWN
                                  withPredicted:false];
            dispatchPointerEvent(_window, evt);
        }
    }
    else
    {
        ofLogError("PointerViewIOS::touchesCancelled") << "Invalid event, passing.";
        [super touchesCancelled:touches withEvent:event];
    }
}


#ifdef __IPHONE_9_1
- (void)touchesEstimatedPropertiesUpdated:(NSSet<UITouch *> *)touches NS_AVAILABLE_IOS(9_1);
{
    ofx::PointerEvents* events = ofx::PointerEventsManager::instance().events();

    if (events)
    {
        for (UITouch* touch in touches)
        {
            auto evt = [self toPointerEventArgs:self
                                      withTouch:touch
                                      withEvent:nil
                               withPointerIndex:std::numeric_limits<int64_t>::max()
                               withPredicted:false];
            dispatchPointerEvent(_window, evt);
        }
    }
    else
    {
        ofLogError("PointerViewIOS::touchesEstimatedPropertiesUpdated") << "Invalid event, passing.";
        [super touchesEstimatedPropertiesUpdated:touches];
    }
}
#endif


- (ofx::PointerEventArgs)toPointerEventArgs:(UIView*)view
                                  withTouch:(UITouch*)touch
                                  withEvent:(UIEvent*)event
                                  withPointerIndex:(int64_t)_pointerIndex
                                  withPredicted:(bool)_isPredicted
{
#if defined(__IPHONE_8_0)
    CGFloat majorRadius = [touch majorRadius];
    CGFloat majorRadiusTolerance = [touch majorRadiusTolerance];
#else
    CGFloat majorRadius = 0.5;
    CGFloat majorRadiusTolerance = 0;
#endif

    PointShape shape(PointShape::ShapeType::ELLIPSE,
                     majorRadius * 2,
                     majorRadiusTolerance * 2);

    // NSUInteger tapCount = [touch tapCount];

    CGPoint position = [touch locationInView:view];

#if defined(__IPHONE_9_1)
    CGPoint precisePosition = [touch preciseLocationInView:view];
#else
    CGFloat precisePosition = position;
#endif

    uint64_t buttons = 0;

    std::string eventType = PointerEventArgs::EVENT_TYPE_UNKNOWN;
    uint64_t detail = 0;

    uint64_t sequenceIndex = [[touch estimationUpdateIndex] unsignedLongLongValue];

    std::set<std::string> estimatedProperties = toPopertySet([touch estimatedProperties]);

    std::set<std::string> estimatedPropertiesExpectingUpdates = toPopertySet([touch estimatedPropertiesExpectingUpdates]);

    // UITouch objects are kept for the duration of the touch and are often
    // reused. The pointer to the touch object can thus be used as a unique id.
    // int64_t pointerIndex = *reinterpret_cast<int64_t*>(&touch);
    // We could use the above method but the activeTouches method makes it
    // easier to keep track of primary pointers and matches expected
    // ofTouchEvent indices (even though they shouldn't be relied upon according
    // to the PointerEvent spec.

    // Pointer indices == POINTER_INDEX_UNKNOWN (i.e. that have not been set)
    // will be set below. Otherwise, the pointer index passed into the function
    // will be set with the new function.
    int64_t pointerIndex = _pointerIndex;

    switch ([touch phase])
    {
        case UITouchPhaseBegan:
        {
            eventType = PointerEventArgs::POINTER_DOWN;
            buttons |= (1 << OF_MOUSE_BUTTON_1);

            // This strategy, as opposed to the existing while() strategy
            // will ensure that the 0 pointer is reserved for the primary
            // pointer.

            if (pointerIndex == POINTER_INDEX_UNKNOWN)
            {
                if ([_activeTouches count] > 0)
                    pointerIndex = [[[_activeTouches allValues] valueForKeyPath:@"@max.intValue"] intValue] + 1;
                else
                    pointerIndex = 0;

                [_activeTouches setObject:[NSNumber numberWithInt:pointerIndex] forKey:[NSValue valueWithPointer:touch]];
            }

            break;
        }
        case UITouchPhaseMoved:
        case UITouchPhaseStationary:
        {
            eventType = PointerEventArgs::POINTER_MOVE;
            buttons |= (1 << OF_MOUSE_BUTTON_1);

            if (pointerIndex == POINTER_INDEX_UNKNOWN)
            {
                pointerIndex = [[_activeTouches objectForKey:[NSValue valueWithPointer:touch]] intValue];
            }
            break;
        }
        case UITouchPhaseEnded:
        {
            eventType = PointerEventArgs::POINTER_UP;
            if (pointerIndex == POINTER_INDEX_UNKNOWN)
            {
                pointerIndex = [[_activeTouches objectForKey:[NSValue valueWithPointer:touch]] intValue];
                [_activeTouches removeObjectForKey:[NSValue valueWithPointer:touch]];
            }
            break;
        }
        case UITouchPhaseCancelled:
        {
            eventType = PointerEventArgs::POINTER_CANCEL;
            if (pointerIndex == POINTER_INDEX_UNKNOWN)
            {
                pointerIndex = [[_activeTouches objectForKey:[NSValue valueWithPointer:touch]] intValue];
                [_activeTouches removeObjectForKey:[NSValue valueWithPointer:touch]];
            }
            break;
        }
    }

    // Update the event type for certain situations.
    if (pointerIndex == POINTER_INDEX_UPDATE)
    {
        eventType = PointerEventArgs::POINTER_UPDATE;

        // TODO ... this shouldn't happen.
        if ([touch estimatedPropertiesExpectingUpdates] > 0)
            assert(false);

    }

    // By default our pressure depends on if a "button" is pressed.
    CGFloat pressure = buttons > 0 ? 0.5 : 0;

#if defined(__IPHONE_9_0)
    // If force is supported, then we try to update it.
    CGFloat maximumPossibleForce = [touch maximumPossibleForce];

    if (maximumPossibleForce > 0)
        pressure = [touch force] / maximumPossibleForce;
#endif

    float twistDeg = 0;
    float tangentialPressure = 0;
    float tiltXDeg = 0;
    float tiltYDeg = 0;

    bool isPredicted = _isPredicted;
    bool isPrimary = (pointerIndex == 0); // We reserved 0 for primary pointers.

    std::string deviceType = PointerEventArgs::TYPE_UNKNOWN;

    switch ([touch type])
    {
        case UITouchTypeDirect:
        {
            deviceType = PointerEventArgs::TYPE_TOUCH;
            break;
        }
        case UITouchTypeIndirect:
        {
            deviceType = PointerEventArgs::TYPE_MOUSE;
            isPrimary = true; // Mice are always primary.
            break;
        }
#if defined(__IPHONE_9_1)
        case UITouchTypePencil:
        {
            deviceType = PointerEventArgs::TYPE_PEN;
            isPrimary = true; // Pens are always primary.

            // Azimuth angle. Valid only for stylus touch types. Zero radians points along the positive X axis.
            // Passing a nil for the view parameter will return the azimuth relative to the touch's window.
            CGFloat azimuthAngleInViewRad = [touch azimuthAngleInView:view];

            // Zero radians indicates that the stylus is parallel to the screen surface,
            // while M_PI/2 radians indicates that it is normal to the screen surface.
            CGFloat altitudeAngleRad = [touch altitudeAngle];

            // Get the unit tilt vector then scale to degrees +/- 90 degrees.
            float lengthXY = std::cos(altitudeAngleRad);
            tiltXDeg = std::sin(azimuthAngleInViewRad) * lengthXY * 90;
            tiltYDeg = std::cos(azimuthAngleInViewRad) * lengthXY * 90;
            break;
        }
#endif
    }

    ofx::Point point({ position.x, position.y },
                     { precisePosition.x, precisePosition.y },
                     shape,
                     pressure,
                     tangentialPressure,
                     twistDeg,
                     tiltXDeg,
                     tiltYDeg);

    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    // Convert seconds to milliseconds.
    uint64_t timestampMillis = [touch timestamp] * 1000;
    std::size_t deviceId = 0;
    uint64_t button = 0;

    std::vector<PointerEventArgs> coalescedPointerEvents;
    if (event)
    {
        for (UITouch* _touch in [event coalescedTouchesForTouch:touch])
            coalescedPointerEvents.push_back([self toPointerEventArgs:self
                                                            withTouch:_touch
                                                            withEvent:event
                                                     withPointerIndex:pointerIndex
                                                        withPredicted:false]);
    }

    std::vector<PointerEventArgs> predictedPointerEvents;

    if (event)
    {
        for (UITouch* _touch in [event predictedTouchesForTouch:touch])
            predictedPointerEvents.push_back([self toPointerEventArgs:self
                                                            withTouch:_touch
                                                            withEvent:event
                                                     withPointerIndex:pointerIndex
                                                        withPredicted:true]);
    }

    const void* eventSource = self->_window;

    std::size_t pointerId = 0;
    hash_combine(pointerId, deviceId);
    hash_combine(pointerId, pointerIndex);
    hash_combine(pointerId, deviceType);

    return PointerEventArgs(eventSource,
                            eventType,
                            timestampMillis,
                            detail,
                            point,
                            pointerId,
                            deviceId,
                            pointerIndex,
                            sequenceIndex,
                            deviceType,
                            isPredicted,
                            isPrimary,
                            button,
                            buttons,
                            modifiers,
                            coalescedPointerEvents,
                            predictedPointerEvents,
                            estimatedProperties,
                            estimatedPropertiesExpectingUpdates);
}

@end


namespace ofx {


///// \brief The global PointerView associated with the single iOS window.
///// \note Currently we only support one window. In the future we might support more if iOS allows it.
static PointerView* pointerView = nullptr;


void EnableAdvancedPointerEventsiOS()
{
    if (!pointerView)
    {
        // Since iOS can only have one window, we initialize our PointerView on
        // that window.
        pointerView = [[PointerView alloc] initWithFrame:CGRectMake(0,
                                                                    0,
                                                                    ofxiOSGetOFWindow()->getWidth(),
                                                                    ofxiOSGetOFWindow()->getHeight())];

        [[ofxiOSGetAppDelegate() uiViewController].view addSubview:pointerView];

    }
}


void DisableAdvancedPointerEventsiOS()
{
    if (pointerView)
    {
        [pointerView removeFromSuperview];
        [pointerView release];
        pointerView = nullptr;
    }
}


} // namespace ofx


#endif
