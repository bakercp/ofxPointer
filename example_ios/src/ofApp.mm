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
    //  void pointerUp(ofx::PointerEventArgs& evt);
    //  void pointerDown(ofx::PointerEventArgs& evt);
    //  void pointerMove(ofx::PointerEventArgs& evt);
    //  void pointerCancel(ofx::PointerEventArgs& evt);
    //
    // or if pointer events can be consumed:
    //
    //  bool pointerUp(ofx::PointerEventArgs& evt);
    //  bool pointerDown(ofx::PointerEventArgs& evt);
    //  bool pointerMove(ofx::PointerEventArgs& evt);
    //  bool pointerCancel(ofx::PointerEventArgs& evt);

    ofx::RegisterPointerEvents(this);
}


void ofApp::update()
{
}


void ofApp::draw()
{
}

void ofApp::pointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerUp") << evt.toString();
}


void ofApp::pointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerDown") << evt.toString();
}


void ofApp::pointerMove(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerMove") << evt.toString();
}


void ofApp::pointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::pointerCancel") << evt.toString();
}
