//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxPointer.h"
#include "SecondApp.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    // Pointer Events
    void onPointerEvent(ofx::PointerEventArgs& evt);

    std::shared_ptr<SecondApp> secondApp;

    ofx::PointerDebugRenderer renderer;
};
