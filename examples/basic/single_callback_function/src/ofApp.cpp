//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    // Calling ofx::RegisterPointerEvent, will register a single callback with
    // the following method signature:
    //
    // void onPointerEvent(ofx::PointerEventArgs& evt)
    //
    ofx::RegisterPointerEvent(this);
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::onPointerEvent(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerEvent") << evt.toString();
}
