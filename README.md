ofxPointer
==========

A framework to unify openFrameworks pointer events into a single WC3-pointerevents/MSPointer-like interface.

The goal is to have something that unites pointer events in openFrameworks to work like these:

http://www.w3.org/TR/pointerevents/
http://msdn.microsoft.com/en-us/library/ie/hh673557(v=vs.85).aspx

This will ease gui development, interaction, etc.

Basically, PointerEvents merge touch, pen and mouse events into one simple event system.

A typical program will now look like this:

```c++

#pragma once


#include "ofMain.h"
#include "ofxPointer.h"


class ofApp: public ofBaseApp
{
public:
    void setup()
    {
      ofx::RegisterPointerEvents(this);
      ofx::RegisterPointerGestureEvents(this);
    }

    void update()
    {
    }

    void draw()
    {  
    }

    // Pointer Events
    void onPointerUp(ofx::PointerEventArgs& evt)
    {
    }

    void onPointerDown(ofx::PointerEventArgs& evt)
    {
    }

    void onPointerMove(ofx::PointerEventArgs& evt)
    {
    }

    void onPointerCancel(ofx::PointerEventArgs& evt)
    {
    }

    // Gesture Events
    void onPointerDoublePress(ofx::PointerEventArgs& evt)
    {
    }

    void onPointerPressAndHold(ofx::PointerEventArgs& evt)
    {
    }

};

```
