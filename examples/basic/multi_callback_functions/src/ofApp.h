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

    void onPointerUp(ofx::PointerEventArgs& e);
    void onPointerDown(ofx::PointerEventArgs& e);
    void onPointerMove(ofx::PointerEventArgs& e);
    void onPointerCancel(ofx::PointerEventArgs& e);

    ofx::PointerDebugRenderer debugRenderer;

};
