#include "SecondApp.h"


void SecondApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("SecondApp");
}


void SecondApp::update()
{
}


void SecondApp::draw()
{
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
}


void SecondApp::pointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::pointerUp") << evt.toString();
}


void SecondApp::pointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::pointerDown") << evt.toString();
}


void SecondApp::pointerMove(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::pointerMove") << evt.toString();
}


void SecondApp::pointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::pointerCancel") << evt.toString();
}
