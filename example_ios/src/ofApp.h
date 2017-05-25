//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofxiOS.h"
#include "ofxPointer.h"


class ofApp: public ofxiOSApp
{
public:
    void setup() override;
    void draw() override;

    // Pointer Events
    void onPointerUp(ofx::PointerEventArgs& evt);
    void onPointerDown(ofx::PointerEventArgs& evt);
    void onPointerMove(ofx::PointerEventArgs& evt);
    void onPointerCancel(ofx::PointerEventArgs& evt);

    std::map<std::size_t, ofx::Point> pointers;

};


