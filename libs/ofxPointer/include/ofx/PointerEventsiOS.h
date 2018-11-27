//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//



#pragma once


#if defined(OF_TARGET_IOS)

#include "ofxiOS.h"

#include "ofx/PointerEvents.h"
#include "ofEvents.h"
#include "ofAppBaseWindow.h"
#include "ofAppRunner.h"


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


/// \brief The global PointerView associated with the single iOS window.
/// \note Currently we only support one window. In the future we might support more if iOS allows it.
static PointerView* pointerView = nullptr;

    
/// \brief This must be called to add the PointerView to the primary iOS window.
static void EnableAdvancedPointerEventsiOS()
{
    if (!pointerView)
    {
        // Since iOS can only have one window, we initialize our PointerView on
        // that window.
        pointerView = [[PointerView alloc] initWithFrame:CGRectMake(0, 0, ofxiOSGetOFWindow()->getWidth(), ofxiOSGetOFWindow()->getHeight())];
        
        // Add the view. PointerView will now intercept all pointer input.
        [[ofxiOSGetAppDelegate() uiViewController].view addSubview:pointerView];
    }
}
    
/// \brief This must be called to remove the PointerView from the primary iOS window.
static void DisableAdvancedPointerEventsiOS()
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
