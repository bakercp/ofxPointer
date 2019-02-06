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
    void update() override;
    void draw() override;

    void pointerUp(ofx::PointerEventArgs& e);
    void pointerDown(ofx::PointerEventArgs& e);
    void pointerMove(ofx::PointerEventArgs& e);
    void pointerCancel(ofx::PointerEventArgs& e);

    ofx::PointerDebugRenderer debugRenderer;

};
