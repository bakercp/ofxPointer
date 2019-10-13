//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetWindowTitle("ofApp");
}


void ofApp::update()
{
    renderer.update();
}


void ofApp::draw()
{
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    renderer.draw();
}


void ofApp::onPointerEvent(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}
