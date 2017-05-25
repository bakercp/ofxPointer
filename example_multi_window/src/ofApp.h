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
    void onPointerUp(ofx::PointerEventArgs& evt);
    void onPointerDown(ofx::PointerEventArgs& evt);
    void onPointerMove(ofx::PointerEventArgs& evt);
    void onPointerCancel(ofx::PointerEventArgs& evt);

    std::shared_ptr<SecondApp> secondApp;

};
