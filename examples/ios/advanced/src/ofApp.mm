//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    ofBackground(255);

    // This example demonstrates the simplest way to get all advanced
    // PointerEvents. This method will creates a subview window that intercepts
    // all touch events before they are passed to the standard ofxiOSApp window.
    // Thus, in this advanced method, no events will be passed to the standard
    // ofxiOSApp::touch*(...) callbacks.
    //
    // Like the basic mode (e.g. ofx::RegisterPointerEvent(...) and
    // ofx::RegisterPointerEvents(...), one can call one can receve all pointer
    // events in seperate callbacks or in one unified callback.
    //
    // When calling ofx::RegisterAdvancedPointerEventsiOS(this), it is expected
    // that the following standard ofxPointer event methods are present in the
    // listener class:
    //
    //  void onPointerUp(ofx::PointerEventArgs& evt);
    //  void onPointerDown(ofx::PointerEventArgs& evt);
    //  void onPointerMove(ofx::PointerEventArgs& evt);
    //  void onPointerCancel(ofx::PointerEventArgs& evt);
    //
    // Additionally the following method must also be included:
    //
    //  void onPointerUpdate(ofx::PointerEventArgs& evt);
    //
    // The onPointerUpdate(...) is called when iOS updates previously estimated
    // point data. If the previous points are not preserved, then these events
    // should be ignored. Otherwise, they can be matched with previous events
    // by examining the pointerId() and sequenceIndex() of the the stored
    // events. The PointerDebugRenderer::add(...) method demonstrates one way
    // this can be done.
    //
    // Alternatively, by calling ofx::RegisterAdvancedPointerEventiOS(this),
    // a single method with the signature of:
    //
    // void onPointerEvent(ofx::PointerEventArgs& evt)
    //
    // will receive all events, including pointerUpdate events.

    // Register a single advanced iOS PointerEvents callback.
    ofx::RegisterAdvancedPointerEventiOS(this);

    // There are several settings that can be set in the debug renderer.
    ofx::PointerDebugRenderer::Settings settings;
    settings.timeoutMillis = 2000;
    settings.strokeWidth = 200;
    renderer.setup(settings);
}


void ofApp::update()
{
    renderer.update();
}


void ofApp::draw()
{
    renderer.draw();
}


void ofApp::onPointerEvent(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}
