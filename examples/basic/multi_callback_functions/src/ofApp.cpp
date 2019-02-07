//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
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


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    events.push_back(evt);
}
