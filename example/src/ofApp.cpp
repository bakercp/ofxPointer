// =============================================================================
//
// Copyright (c) 2009-2014 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    pointerManager.registerAllPointerEvents(this);
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


bool ofApp::onPointerUp(Input::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerUp") << evt.toString();
    return true;
}


bool ofApp::onPointerDown(Input::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerDown") << evt.toString();
    return true;
}


bool ofApp::onPointerMove(Input::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerMove") << evt.toString();
    return true;
}


bool ofApp::onPointerDoubleTap(Input::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerDoubleTap") << evt.toString();
    return true;
}


bool ofApp::onPointerCancel(Input::PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerCancel") << evt.toString();
    return true;
}
