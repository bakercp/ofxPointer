//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
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
    void update() override;
    void draw() override;

    void onPointerUp(ofx::PointerEventArgs& evt);
    void onPointerDown(ofx::PointerEventArgs& evt);
    void onPointerMove(ofx::PointerEventArgs& evt);
    void onPointerCancel(ofx::PointerEventArgs& evt);
    void onPointerUpdate(ofx::PointerEventArgs& evt);

    void pointerPropertyUpdate(const void* source, std::string& evt);

    void addEvent(ofx::PointerEventArgs& evt);
    
    std::map<uint64_t, ofx::PointerEventArgs> t;

    
  //  PointerDebugRenderer renderer;

};
