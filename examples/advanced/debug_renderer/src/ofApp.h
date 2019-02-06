//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
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
    void draw() override;

    void keyPressed(int key) override;

    ofx::PointerDebugRenderer debugRenderer;

};
