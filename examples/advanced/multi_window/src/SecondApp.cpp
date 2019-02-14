//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "SecondApp.h"


void SecondApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("SecondApp");


    ofx::PointerDebugRenderer::Settings settings;
    settings.pointColor = ofColor::red;
    renderer.setup(settings);
}


void SecondApp::update()
{
    renderer.update();
}


void SecondApp::draw()
{
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    renderer.draw();
}


void SecondApp::onPointerEvent(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}

