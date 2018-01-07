#pragma once


#include "ofMain.h"
#include "ofxPointer.h"
#include "SecondApp.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    // Pointer Events
    void pointerUp(ofx::PointerEventArgs& evt);
    void pointerDown(ofx::PointerEventArgs& evt);
    void pointerMove(ofx::PointerEventArgs& evt);
    void pointerCancel(ofx::PointerEventArgs& evt);

    std::shared_ptr<SecondApp> secondApp;

};
