//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofx::RegisterPointerEvents(this);
    ofBackground(0);
}


void ofApp::update()
{
    auto now = ofGetElapsedTimeMillis();
    
    auto iter = events.begin();
    while (iter != events.end())
    {
        if (now > 5000 && iter->timestampMillis() < (now - 5000))
        {
            iter = events.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}


void ofApp::draw()
{
    auto now = ofGetElapsedTimeMillis();

    for (const auto& event: events)
    {
        float alpha = ofMap(now - event.timestampMillis(), 0, 5000, 1, 0, true);

        ofx::PointerDebugUtilities::draw(event, alpha);

    }
}


void ofApp::pointerUp(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}


void ofApp::pointerDown(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}


void ofApp::pointerMove(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}


void ofApp::pointerCancel(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}
