#pragma once


#include "ofxiOS.h"
#include "ofxPointer.h"


class ofApp: public ofxiOSApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void pointerUp(ofx::PointerEventArgs& evt);
    void pointerDown(ofx::PointerEventArgs& evt);
    void pointerMove(ofx::PointerEventArgs& evt);
    void pointerCancel(ofx::PointerEventArgs& evt);

};


