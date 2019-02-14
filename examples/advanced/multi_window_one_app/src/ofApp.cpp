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
    for (auto& renderer: renderers)
        renderer.second.update();
}


void ofApp::draw()
{
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    renderers[ofGetCurrentWindow().get()].draw();
}


void ofApp::drawSecondWindow(ofEventArgs& args)
{
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    renderers[ofGetCurrentWindow().get()].draw();
}


void ofApp::onPointerEvent(ofx::PointerEventArgs& evt)
{
    renderers[reinterpret_cast<const ofAppBaseWindow*>(evt.eventSource())].add(evt);
}


