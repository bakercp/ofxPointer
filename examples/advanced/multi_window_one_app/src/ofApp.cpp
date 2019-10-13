//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
}


void ofApp::update()
{
    for (auto& renderer: renderers)
    {
        renderer.second.update();
    }
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
    // Send the pointer event to the renderer associated with the window source.

    // Determine which window the event came from.
    const ofAppBaseWindow* theWindow = reinterpret_cast<const ofAppBaseWindow*>(evt.eventSource());

    // Add the event to the correct renderer.
    renderers[theWindow].add(evt);
}


