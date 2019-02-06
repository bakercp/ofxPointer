//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//



#pragma once


#include "ofConstants.h"


#if defined(TARGET_OF_IOS)


#include "ofxiOS.h"
#include "ofEvents.h"
#include "ofAppBaseWindow.h"
#include "ofAppRunner.h"
#include "ofx/PointerEvents.h"



/// \brief PointerView is a UIView subclass that intercepts and transforms touches as PointerEvents.
/// \todo Update the UIView size in response to size changes.
@interface PointerView: UIView {

@protected
    /// \brief A list of the current active touches.
    NSMutableDictionary* _activeTouches;
    
    /// \brief A pointer to the current iOS window.
    ///
    /// This may not be necessary as there can only be one window currently
    /// accessible by calling ofxiOSGetOFWindow().
    ofAppiOSWindow* _window;

    UITapGestureRecognizer *singleFingerTap;
    UITapGestureRecognizer *doubleFingerTap;
//    UITapGestureRecognizer *tripleFingerTap;
//    UITapGestureRecognizer *quadFingerTap;
//    UITapGestureRecognizer *pentaFingerTap;
//    UIPanGestureRecognizer *pan;
}

- (void)resetTouches;

/// \brief Convert UITouch data to PointerEventArgs values.
- (ofx::PointerEventArgs)toPointerEventArgs:(UIView*) view
                                  withTouch:(UITouch*) touch
                                  withEvent:(UIEvent*) event
                                  withPointerIndex:(int64_t)pointerIndex;

- (void)handleTap:(UITapGestureRecognizer *)recognizer;
//- (void)handlePan:(UIPanGestureRecognizer *)recognizer;

@end


namespace ofx {


/// \brief This must be called to add the PointerView to the primary iOS window.
void EnableAdvancedPointerEventsiOS();

/// \brief This must be called to remove the PointerView from the primary iOS window.
void DisableAdvancedPointerEventsiOS();


template <class ListenerClass>
void RegisterAdvancedPointerEventsiOS(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    EnableAdvancedPointerEventsiOS();
    RegisterPointerEventsForWindow<ListenerClass>(ofGetWindowPtr(), listener, prio);
    ofAddListener(ofx::PointerEventsManager::instance().eventsForWindow(ofGetWindowPtr())->pointerUpdate,
                  listener,
                  &ListenerClass::onPointerUpdate, prio);
}


template <class ListenerClass>
void UnregisterAdvancedPointerEventsiOS(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    UnregisterPointerEventsForWindow<ListenerClass>(ofGetWindowPtr(), listener, prio);
    ofRemoveListener(ofx::PointerEventsManager::instance().eventsForWindow(ofGetWindowPtr())->pointerUpdate,
                     listener,
                     &ListenerClass::onPointerUpdate, prio);
    DisableAdvancedPointerEventsiOS();
}

    
    

    
    
} // namespace ofx


#endif
