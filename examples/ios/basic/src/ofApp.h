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

};
