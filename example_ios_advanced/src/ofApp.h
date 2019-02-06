#pragma once


#include "ofxiOS.h"
#include "ofxPointer.h"


class ofApp: public ofxiOSApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void touchDown(ofTouchEventArgs& touch) override;
    void touchMoved(ofTouchEventArgs& touch) override;
    void touchUp(ofTouchEventArgs& touch) override;
    void touchDoubleTap(ofTouchEventArgs& touch) override;
    void touchCancelled(ofTouchEventArgs& touch) override;

    void onPointerUp(ofx::PointerEventArgs& evt);
    void onPointerDown(ofx::PointerEventArgs& evt);
    void onPointerMove(ofx::PointerEventArgs& evt);
    void onPointerCancel(ofx::PointerEventArgs& evt);

    void onPointerUpdate(ofx::PointerEventArgs& evt);

    void pointerPropertyUpdate(std::string& evt);
    
    
    void addEvent(ofx::PointerEventArgs& evt);
    
    std::map<uint64_t, ofx::PointerEventArgs> t;

    
  //  PointerDebugRenderer renderer;

};


