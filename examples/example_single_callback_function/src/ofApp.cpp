//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofx::RegisterPointerEvent(this);
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::pointerEvent(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerEvent") << evt.toString();
}

