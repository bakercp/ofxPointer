//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(255);
    ofx::RegisterPointerEvents(this);
}


void ofApp::update()
{
    renderer.update();
}


void ofApp::draw()
{
    renderer.draw();
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    renderer.add(evt);
}
