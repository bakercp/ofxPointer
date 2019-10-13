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

    // All pointer events are sent to this single callback.
    void onPointerEvent(ofx::PointerEventArgs& e);

    // A debug renderer for visualizing the output of pointer events.
    ofx::PointerDebugRenderer renderer;
};
