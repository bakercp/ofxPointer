//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxPointer.h"


class SecondApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void onPointerEvent(ofx::PointerEventArgs& evt);

    ofx::PointerDebugRenderer renderer;
    
};
