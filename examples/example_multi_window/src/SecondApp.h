#pragma once


#include "ofMain.h"
#include "ofxPointer.h"


class SecondApp: public ofBaseApp
{
public:
	void setup() override;
	void update() override;
	void draw() override;

    // Pointer Events
    void pointerUp(ofx::PointerEventArgs& evt);
    void pointerDown(ofx::PointerEventArgs& evt);
    void pointerMove(ofx::PointerEventArgs& evt);
    void pointerCancel(ofx::PointerEventArgs& evt);

};

