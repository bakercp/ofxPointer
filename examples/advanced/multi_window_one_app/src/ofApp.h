//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxPointer.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void drawSecondWindow(ofEventArgs& args);

    // All pointer events for both windows arrive here.
    void onPointerEvent(ofx::PointerEventArgs& evt);

    // Create a renderer for each window.
    std::map<const ofAppBaseWindow*, ofx::PointerDebugRenderer> renderers;

};
