//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("ofApp");
}


void ofApp::update()
{
}


void ofApp::draw()
{
	ofDrawBitmapString(ofGetFrameRate(), 20, 20);
}


void ofApp::pointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerUp") << evt.toString();
}


void ofApp::pointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerDown") << evt.toString();
}


void ofApp::pointerMove(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerMove") << evt.toString();
}


void ofApp::pointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerCancel") << evt.toString();
}
