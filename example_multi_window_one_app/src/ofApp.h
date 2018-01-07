#pragma once


#include "ofMain.h"
#include "ofxPointer.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void drawSecondWindow(ofEventArgs& args);

    // Pointer Events
    void pointerUp(ofx::PointerEventArgs& evt);
    void pointerDown(ofx::PointerEventArgs& evt);
    void pointerMove(ofx::PointerEventArgs& evt);
    void pointerCancel(ofx::PointerEventArgs& evt);

};
