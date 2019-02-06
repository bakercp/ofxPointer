#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // The simplest way to get basic PointerEvents. This method will capture
    // the default touch events and convert them into pointer events.
    //
    // Due to a limitation in openFrameworks, these pointer events will not
    // have a high temporal resolution or other useful touch data available
    // on iOS. To receive advanced touch data in the pointer events, see the
    // `example_ios_advanced` example.
    //
    // If the pointer events are consumed, then the the normal touch events
    // will not be called, otherwise, they will continued to be received via:
    //
    //  void touchDown(ofTouchEventArgs& touch) override;
    //  void touchMoved(ofTouchEventArgs& touch) override;
    //  void touchUp(ofTouchEventArgs& touch) override;
    //  void touchDoubleTap(ofTouchEventArgs& touch) override;
    //  void touchCancelled(ofTouchEventArgs& touch) override;
    //
    // These standard callbacks are not included in this example for simplicity.
    //
    // When calling ofx::RegisterPointerEvents(this), it is expected that the
    // following methods are present in the listener class.
    //
    //  void onPointerUp(ofx::PointerEventArgs& evt);
    //  void onPointerDown(ofx::PointerEventArgs& evt);
    //  void onPointerMove(ofx::PointerEventArgs& evt);
    //  void onPointerCancel(ofx::PointerEventArgs& evt);
    //
    // or if pointer events can be consumed:
    //
    //  bool onPointerUp(ofx::PointerEventArgs& evt);
    //  bool onPointerDown(ofx::PointerEventArgs& evt);
    //  bool onPointerMove(ofx::PointerEventArgs& evt);
    //  bool onPointerCancel(ofx::PointerEventArgs& evt);

    ofx::RegisterPointerEvents(this);
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerUp") << evt.toString();
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerDown") << evt.toString();
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerMove") << evt.toString();
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerCancel") << evt.toString();
}
