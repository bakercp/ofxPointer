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


void SecondApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::onPointerUp") << evt.toString();
}


void SecondApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::onPointerDown") << evt.toString();
}


void SecondApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::onPointerMove") << evt.toString();
}


void SecondApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    ofLogVerbose("SecondApp::onPointerCancel") << evt.toString();
}
