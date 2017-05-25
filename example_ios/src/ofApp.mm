//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    // ofSetLogLevel(OF_LOG_VERBOSE);
    ofx::RegisterPointerEvents(this);
}


void ofApp::draw()
{
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);

    for (const auto& entry: pointers)
    {
        const auto& point = entry.second;

        ofPushMatrix();
        ofTranslate(point);

        float w = point.shape().ellipseMajorAxis();
        float h = point.shape().ellipseMinorAxis();

        // In case the width / height info is not available.
        if (w <= 0) w = 60.0f;
        if (h <= 0) h = 60.0f;

        float halfW = w / 2.0f;
        float halfH = h / 2.0f;

        float pressure = point.pressure() * 30.f;

        // In case the pressure is not available.
        if (pressure <= 0) pressure = 30.f;

        ofRotateZRad(point.shape().ellipseAngle());
        ofSetColor(255, 100);
        ofDrawEllipse(0, 0, w, h);
        ofSetColor(255, 255,0, 100);
        ofDrawEllipse(0, 0, pressure, pressure);
        ofSetColor(255, 100);
        ofDrawLine(-halfW, 0.f, halfW, 0.f);
        ofDrawLine(0.f, -halfH, 0.f, halfH);
        ofPopMatrix();

        ofFill();
        ofSetColor(255);
        ofDrawBitmapString(ofToString(entry.first), point.x - 6, point.y + 3);
        ofSetColor(255, 255, 255, 100);
    }
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerUp") << evt.toString();
    pointers.erase(evt.id());
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerDown") << evt.toString();
    pointers[evt.id()] = evt.point();
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerMove") << evt.toString();
    pointers[evt.id()] = evt.point();
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerCancel") << evt.toString();
    pointers.erase(evt.id());
}
