ofxPointer
==========

Currently the openFrameworks pointer model separates touch and mouse events, making cross platform development a little tricky.

This frameworks adapts the [W3C Pointer Event](http://www.w3.org/TR/pointerevents/) specification to work with openFrameworks.

Simply put, ofxPointer merges pointer, touch and pen input into a single extensible interface.

This addon also keeps track of additional information like number of clicks, etc.

The addon requires (ofxJSON)[https://github.com/jefftimesten/ofxJSON] but will replaced with core JSON support in 0.10.0+.

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
        // Register the pointer events.
        ofx::RegisterPointerEvents(this);
    }


    void update()
    {
        // Update
    }


    void draw()
    {
        // Draw
    }


    void onPointerUp(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerUp") << evt.toString();
    }


    void onPointerDown(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerDown") << evt.toString();
    }


    void onPointerMove(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerMove") << evt.toString();
    }


    void onPointerCancel(ofx::PointerEventArgs& evt)
    {
        ofLogNotice("ofApp::onPointerCancel") << evt.toString();
    }

};

```
